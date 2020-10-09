target:
	cd src && gcc main.c string_list.c -o main.out
test:
	cd src && valgrind --leak-check=yes --error-exitcode=1 ./main.out
run:
	cd src && ./main.out
