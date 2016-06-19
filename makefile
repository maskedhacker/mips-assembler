all: main.o ri_type_to_rec.o js_type_to_rec.o get_input.o get_binary.o
	gcc -c dimage_gen.c
	gcc main.o ri_type_to_rec.o js_type_to_rec.o get_input.o get_binary.o dimage_gen.o -o proj
main.o: main.c
	gcc -c main.c
dimage_gen.o: dimage_gen.c
	gcc -c dimage_gen.c
r_func.o: ri_type_to_rec.c
	gcc -c r_func.cri_type_to_rec.c
i_func.o: js_type_to_rec.c
	gcc -c js_type_to_rec.c
js_func.o: get_input.c
	gcc -c get_input.c
get_images.o: get_binary.c
	gcc -c get_binary.c
clean: 
	rm *o proj *layout *depend middle_file.txt 

