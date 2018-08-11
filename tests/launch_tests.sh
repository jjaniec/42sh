make CC=$CXX
make CC=$CXX tests

if [ "$(uname -s)" == "Darwin" ];
then
    valgrind --leak-check=full ./21sh_tests 2> ./tmp;
    r=$?;
    cat ./tmp | grep -A5 'LEAK SUMMARY';
    exit $r
else [ "$(uname -s)" == "Linux" ];
    ./21sh_tests
fi;
