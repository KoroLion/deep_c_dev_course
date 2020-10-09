target:
	cd src && gcc main.c string_list.c -o main.out
test:
	cd src && ./main.out
