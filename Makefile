target:
	cd src && gcc main.c string_list.c email_filter.c -Wall -o main.out
test:
	cd src && python3 -m cpplint *.c *.h && cppcheck --error-exitcode=1 *.c *.h && gcc test.c -o test.out email_filter.c string_list.c -lcheck -lm -lpthread -lrt -lsubunit && ./test.out && valgrind --leak-check=yes --error-exitcode=1 ./main.out test_data.txt
run:
	cd src && ./main.out test_data.txt
