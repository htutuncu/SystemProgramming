
all: compile run

compile:
	gcc -I ./libfdr/ -o ./libfdr/fields.o -c ./libfdr/fields.c
	gcc -I ./libfdr/ -o ./libfdr/jrb.o -c ./libfdr/jrb.c
	gcc -I ./libfdr/ -o ./libfdr/jval.o -c ./libfdr/jval.c
	gcc -I ./libfdr/ -o kripto ./libfdr/fields.o ./libfdr/jrb.o ./libfdr/jval.o main.c

run: clean 
	./kripto -e ornek_metin encripted
	./kripto -d encripted decripted

clean:
	rm ./libfdr/*.o

cleanall:
	rm ./libfdr/*.o *.txt giris encripted decripted ornek_metin kripto .kilit




