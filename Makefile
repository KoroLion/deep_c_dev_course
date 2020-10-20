target:
	cd src && gcc main.c string_list.c email_filter.c -Wall -o main.out
test:
	cd src && \
    python3 -m cpplint *.c include/*.h && \
    cppcheck --error-exitcode=1 *.c include/*.h && \
    gcc test.c -o test.out email_filter.c string_list.c -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage && \
    ./test.out && \
    valgrind --leak-check=yes --error-exitcode=1 ./main.out test_data.txt && \
    gcov email_filter.c string_list.c
run:
	cd src && ./main.out test_data.txt
