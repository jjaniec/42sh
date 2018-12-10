# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 21:53:56 by jjaniec           #+#    #+#              #
#    Updated: 2018/12/10 22:06:39 by cgaspart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###### EXEC ######
NAME = 21sh
TESTS_EXEC = $(addprefix $(NAME),_tests)

###### FILES ######
SRC_NAME =  twenty_one_sh.c \
			init_shell_vars.c \
			is_separator.c \
			get_valid_input.c \
			exit_because_not_valid_tty.c \
			interpret_file.c \
			fatal_fork_fail.c \
			ft_free.c \
			lexer/lexer.c \
			lexer/fill_new_data_str.c \
			lexer/lexeme_type_rediropt.c \
			lexer/get_lexeme_type.c \
			lexer/create_lexeme.c \
			lexer/is_operator.c \
			lexer/lexeme_type_word.c \
			lexer/handle_quotes_expansions.c \
			lexer/has_matching_quote.c \
			lexer/env_assigns_status.c \
			lexer/handle_escape_offset.c \
			lexer/free_lexemes.c \
			lexer/handle_char_expansion.c \
			lexer/get_expansion_end.c \
			ast/ast.c \
			ast/ast_explore.c \
			ast/ast_constructor.c \
			ast/ast_constructor_subast.c \
			ast/put_node.c \
			ast/node_placer_classic.c \
			ast/node_placer_if.c \
			ast/node_placer_while.c \
			ast/check_parsing.c \
			ast/lvl_lex.c \
			ast/is_op.c \
			ast/ast_utils_node.c \
			ast/ast_debug.c \
			ast/print_ast_debug.c \
			ast/ast_free.c \
			ast/prepare_argv.c \
			ast/create_node.c \
			ast/access_ast_data.c \
			autocomplete/autocomplete.c \
			autocomplete/str_effect.c \
			autocomplete/autoc_dir.c \
			autocomplete/dir_get_items.c \
			autocomplete/autoc_menu.c \
			autocomplete/order_tab_ascii.c \
			autocomplete/autoc_mem_free.c \
			autocomplete/autoc_key_reader.c \
			autocomplete/autoc_fkey.c \
			autocomplete/autoc_menu_print_items.c \
			autocomplete/autoc_menu_print_spaces.c \
			autocomplete/dir_get_items_search.c \
			autocomplete/autoc_check_path.c \
			autocomplete/autoc_push_in_line.c \
			autocomplete/autoc_arrow.c \
			hash_table/ht_setup.c \
			hash_table/ht_create.c \
			hash_table/ht_mem_free.c \
			hash_table/ht_hash.c \
			hash_table/ht_tab_tools.c \
			hash_table/ht_update.c \
			prompt_details/print_prompt_details.c \
			prompt_details/get_git_info.c \
			line_edition/access_le_main_datas.c \
			line_edition/add_history.c \
			line_edition/get_key_number.c \
			line_edition/handle_window_resize.c \
			line_edition/get_le_debug_status.c \
			line_edition/le_free_datas_and_history.c \
			line_edition/line_edition.c \
			line_edition/process_key.c \
			line_edition/read_key.c \
			line_edition/actionk/action_key.c \
			line_edition/actionk/actionk_clear_screen.c \
			line_edition/actionk/actionk_copy_all.c \
			line_edition/actionk/actionk_copy_to_end.c \
			line_edition/actionk/actionk_copy_to_start.c \
			line_edition/actionk/actionk_cursor_move_left.c \
			line_edition/actionk/actionk_cursor_move_right.c \
			line_edition/actionk/actionk_cut_all.c \
			line_edition/actionk/actionk_cut_to_end.c \
			line_edition/actionk/actionk_cut_to_start.c \
			line_edition/actionk/actionk_delete_character.c \
			line_edition/actionk/actionk_delete_current_input.c \
			line_edition/actionk/actionk_eof.c \
			line_edition/actionk/actionk_history_down.c \
			line_edition/actionk/actionk_history_up.c \
			line_edition/actionk/actionk_move_cursor_by_word_left.c \
			line_edition/actionk/actionk_move_cursor_by_word_right.c \
			line_edition/actionk/actionk_move_cursor_end.c \
			line_edition/actionk/actionk_move_cursor_line_down.c \
			line_edition/actionk/actionk_move_cursor_line_up.c \
			line_edition/actionk/actionk_move_cursor_start.c \
			line_edition/actionk/actionk_past_clipboard.c \
			line_edition/tools/check_cmd_and_clipboard_storage.c \
			line_edition/colosyn/colosyn_add_char.c \
			line_edition/colosyn/colosyn_cut_to_start_or_end.c \
			line_edition/colosyn/colosyn_delete_char.c \
			line_edition/colosyn/colosyn_past_clipboard.c \
			line_edition/colosyn/colosyn_print_history_elem.c \
			line_edition/tools/cursor_crosses_screen.c \
			line_edition/boolean_check/cursor_is_at_end_of_cmd.c \
			line_edition/boolean_check/cursor_is_at_end_of_term_line.c \
			line_edition/actionk/delete_char_into_cmdline_backspace_mode.c \
			line_edition/actionk/delete_char_into_cmdline_delete_mode.c \
			line_edition/tools/get_terminal_sizes.c \
			line_edition/init_le/init_line_edition_attributes.c \
			line_edition/init_le/init_termcaps_strings.c \
			line_edition/print/insert_and_print_character_into_cmdline.c \
			line_edition/tools/insert_char_into_array.c \
			line_edition/boolean_check/is_separator.c \
			line_edition/boolean_check/possible_to_go_right.c \
			line_edition/print/print_history_cmd.c \
			line_edition/print/print_key_at_end.c \
			line_edition/print/print_key.c \
			line_edition/print/print_str_on_term.c \
			line_edition/colosyn/refresh_colosyn.c \
			line_edition/tools/reset_history_on_first_elem.c \
			line_edition/init_le/set_term_attr.c \
			line_edition/tools/weird_trick_to_erase_char.c \
			line_edition/tools/write_one_char.c \
			exec/exec_cmd.c \
			exec/close_and_redir_fd.c \
			exec/handle_node.c \
			exec/fork_and_exec.c \
			exec/child_process.c \
			exec/backup_apply_origin_fds.c \
			exec/io_manager.c \
			exec/manage_path.c \
			exec/handle_redirs.c \
			exec/check_redir_suffix_validity.c \
			exec/handle_redir_fd.c \
			exec/handle_env_assigns.c \
			exec/handle_pipes.c \
			exec/handle_open_error.c \
			exec/init_pipe_data.c \
			exec/get_last_pipe_node.c \
			exec/free_exec.c \
			exec/add_running_process.c \
			exec/create_job.c \
			exec/debug_jobs.c \
			exec/free_job.c \
			exec/refresh_job_running_processes.c \
			exec/remove_task_pid_from_job.c \
			exec/get_pipe_fds.c \
			exec/get_process_return_code.c \
			exec/resolve_cmd_path.c \
			exec/create_exec.c \
			exec/clean_data.c \
			builtin/echo/builtin_echo.c \
			builtin/echo/echo_print_opt.c \
			builtin/echo/echo_opt.c \
			builtin/echo/echo_opt_2.c \
			builtin/cd/builtin_cd.c \
			builtin/cd/cd_change_dir.c \
			builtin/cd/cd_check_link.c \
			builtin/cd/cd_opt.c \
			builtin/cd/cd_l_dot_manager.c \
			builtin/cd/cd_free_struct.c \
			builtin/alias/builtin_alias.c \
			builtin/alias/manage_aliases.c \
			builtin/builtin_history.c \
			builtin/builtin_history_2.c \
			builtin/builtin_read.c \
			builtin/builtin_read_get_activated_options.c \
			builtin/builtin_read_store_words.c \
			builtin/builtin_read_things.c \
			builtin/builtin_exit.c \
			builtin/builtin_setenv.c \
			builtin/builtin_toggle_syntax_highlighting.c \
			builtin/builtin_unalias.c \
			builtin/builtin_unsetenv.c \
			builtin/builtin_env.c \
			builtin/builtin_return.c \
			builtin/builtin_test.c \
			builtin/builtin_test_parse.c \
			builtin/is_builtin.c \
			script/script_lexer.c \
			script/good_start.c \
			script/find_end_lexeme.c \
			script/find_end_lexeme_solo.c \
			script/find_lexeme_compete.c \
			script/script_in_exec.c \
			script/script_colodyn.c \
			script/is_script_complete.c \
			syntax_highlighting/print_colorized_input.c \
			syntax_highlighting/print_lexeme_colorized.c \
			syntax_highlighting/print_to_line_edition.c \
			signals/init_signals.c \
			signals/handle_sigint.c \
			signals/handle_sigwinch.c \
			signals/handle_useless_signals.c \
			signals/handle_sigchild.c \
			sub_prompt.c \
			subp_lexeme.c \
			init_globals_config.c \
			parse_options.c \
			format_help.c \
			get_opt_elem.c \
			is_option_activated.c \
			syntax_highlighting/print_input_string_end.c \
			backup_files_checker.c \
			load_backup_files.c \
			env/add_env_var.c \
			env/init_environ.c \
			env/init_environ_struct_ptrs.c \
			env/del_env_var.c \
			env/get_env_var.c \
			env/upd_env_var.c \
			builtin/is_identifier_invalid.c \
			free_all_shell_datas.c \
			env/free_env_entries.c \
			get_next_line.c \
			get_parsed_backup_files_path.c \
			print_error.c \
			handle_exclamation_mark_in_lexer.c \
			parse_exclamation_mark_shortcuts.c \
			access_alias_datas.c \
			ft_strjoin_path.c \
			get_shell_vars.c \
			aliases_replace.c \
			log_close.c \
			ft_dup_2d_array.c \
			main.c

INCLUDES_NAME = ast.h \
				autocomplete.h \
				builtins.h \
				exec.h \
				twenty_one_sh.h \
				lexer.h \
				line_edition.h \
				script.h \
				signals.h \
				struct.h \
				syntax_highlighting.h \
				hash_table.h \
				prompt_details.h\

###### FOLDERS ######
SRC_DIR = ./srcs/
INCLUDES_DIR = ./includes/
OBJ_DIR = ./objs/
OBJ_SUBDIRS = lexer/ ast/ exec/ builtin/ builtin/echo builtin/cd builtin/alias \
			line_edition/ line_edition/actionk/ line_edition/colosyn/ \
			line_edition/init_le line_edition/boolean_check line_edition/print \
			line_edition/signals line_edition/tools syntax_highlighting/ \
			script/ autocomplete/ env/ signals/ hash_table/ prompt_details/
FT_PRINTF_DIR = ./ft_printf/

###### SRC / OBJ ######
SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

###### COMPILATION ######
CC = gcc
CFLAGS = -Wall -Wextra  -D_GNU_SOURCE -std=c11  -Werror -O3 
ADDITIONAL_FLAGS = # Used to know when running on travis-ci
CFLAGS += $(ADDITIONAL_FLAGS)

### FLAGS ###
VERBOSE_MODE = 0
VERBOSE_MODE_FLAGS = -DVERBOSE_MODE=$(VERBOSE_MODE) -DLOG_USE_COLOR
#DEV_FLAGS = -fsanitize=address -fno-omit-frame-pointer
CFLAGS += $(DEV_FLAGS)
IFLAGS = -I$(FT_PRINTF_DIR)/includes -I$(INCLUDES_DIR)

### LIB ###
LFLAGS = -L$(FT_PRINTF_DIR) -lftprintf -lncurses
LIBFTPRINTF = $(addprefix $(FT_PRINTF_DIR),libftprintf.a)

### CROSS-COMPIL ###
UNAME_S := $(shell uname -s)
MAKEFILE_STATUS = $(addprefix $(addprefix $(FT_PRINTF_DIR),"libft/"),".makefile_status.sh")

define ui_line
	$(MAKEFILE_STATUS) $(1) $(2) || true
endef

###### RULES ######
.PHONY: fclean re all verbose
all : $(NAME)

$(NAME) : $(LIBFTPRINTF) $(OBJ)
ifeq ($(UNAME_S),Linux)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFTPRINTF) -o $(NAME) $(LFLAGS)
endif
ifeq ($(UNAME_S),Darwin)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)
endif

re: fclean all


###### OBJ RULES ######
$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(addprefix $(INCLUDES_DIR), $(INCLUDES_NAME))
	@mkdir -p $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ_SUBDIRS))
	@$(CC) $(CFLAGS) -c $(IFLAGS) $< -o $@ && $(call ui_line, $@, $(NAME))

###### LIB RULES ######
$(LIBFTPRINTF):
	@make -C $(FT_PRINTF_DIR)


###### CLEAN RULES ######
clean:
	-rm -rf $(OBJ_DIR)
	-make clean -C $(FT_PRINTF_DIR)

fclean: clean
	-rm -f $(NAME)
	-make fclean -C $(FT_PRINTF_DIR)
