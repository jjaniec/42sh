#!/bin/bash

#set -o errexit
set -o pipefail
set -o nounset
#set -o xtrace

cur_compiled_filename="${1:-}"
cur_compiled_project_name="${2:-}"

srcs_count=$(find srcs -type f -name '*.c' | wc -l);
objs_count=$(find objs -type f -name '*.o' | wc -l)

term_cols=$(tput cols)

COL_CYAN="\e[1;94m"
COL_YELLOW="\e[93m"
COL_GREEN="\e[92m"
COL_RESET="\e[0;39m"

# Elements sizes
spinner_size=$(( ${term_cols} / 16))
name_size=$(( ${term_cols} / 3 ))
bar_size=$(( ${term_cols} / 2 ))
percent_size=$(( ${term_cols} /  12))

# Format strings
SPINNER_FMT="\r%-*s"
COMPILED_FILENAME_FMT="%-*s"
PERCENTAGE_FMT="%*s%%"

# other
SPINNER_CHARS='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'
SPINNER_INDEX_TMP_FILE="/tmp/spinner_index_tmp_file" # As we're not sourcing this script, storing index in a tmp file is mandatory
bar_fill_char="="
bar_end_char=">"

function    header
{
    printf "Compiling %s\n" ${1}
}

function    spinner
{
    spinner_char=${SPINNER_CHARS:${1}:1}
    printf "${COL_CYAN}${SPINNER_FMT}${COL_RESET}" ${spinner_size} ${spinner_char}
}

function    print_compiled_filename
{
    cur_compiled_filename_size=${#cur_compiled_filename}

    if [ ${cur_compiled_filename_size} -gt ${name_size} ];
    then
        cur_compiled_filename="\\e[$(echo ${cur_compiled_filename:0:$[$name_size-3 - 5]})..."
    fi;
    printf ${COMPILED_FILENAME_FMT} ${name_size} ${cur_compiled_filename}
}

function    progress_bar
{
    if [ ${command_bc} -eq 0 ];
    then
      chars_per_percent=$(echo "( ${bar_size} - 2 ) / 100" | bc -l );

	    if [ ${srcs_count} -ne ${objs_count} ];
    	then
        chars_to_print=$(echo "( ${chars_per_percent} * ${1} ) - 0.5" | bc -l )
        chars_to_print=$(printf "%.0f" "${chars_to_print}")
        tmp_progress_bar=$(printf "%${chars_to_print}s")
        printf "[${COL_YELLOW}${tmp_progress_bar// /${bar_fill_char}}%*s%*s${COL_RESET}]" 1 ${bar_end_char} $( echo "((${bar_size} - 2) - ${chars_to_print})" | bc -l ) " "
    	else
        bar_size=$[${bar_size} - 2]
        tmp_progress_bar=$(printf "%${bar_size}s")

        printf "[${COL_GREEN}${tmp_progress_bar// /${bar_fill_char}}>${COL_RESET}]"
    	fi;
    fi;
}

function    comp_percentage
{
    if [ ${1} -gt 1 ];
    then
        printf ${PERCENTAGE_FMT} ${percent_size} ${1}
    fi;
}

command -v bc > /dev/null 2> /dev/null
command_bc=$?

if [ 1 -eq ${objs_count} ];
then
    header ${cur_compiled_project_name}
fi;
if ! [ -f ${SPINNER_INDEX_TMP_FILE} ];
then
    SPINNER_INDEX=0
else
    SPINNER_INDEX=$(cat ${SPINNER_INDEX_TMP_FILE})
fi;
spinner ${SPINNER_INDEX} #
SPINNER_INDEX=$[${SPINNER_INDEX}+1]
if [ ${SPINNER_INDEX} -eq ${#SPINNER_CHARS} ]
then
    SPINNER_INDEX=0
fi;

print_compiled_filename #

if [ ${command_bc} -eq 0 ];
then
    percentage=$(printf "%.0f" $( echo "${objs_count} / ${srcs_count} * 100" | bc -l))
else
    percentage=-1;
fi;
progress_bar ${percentage} #
comp_percentage ${percentage} #

if [ ${srcs_count} -eq ${objs_count} ];
then
    if [ -f ${SPINNER_INDEX_TMP_FILE} ];
    then
        rm ${SPINNER_INDEX_TMP_FILE}
    fi;
    echo -e '\n'
else
    echo ${SPINNER_INDEX} > ${SPINNER_INDEX_TMP_FILE}
fi;
