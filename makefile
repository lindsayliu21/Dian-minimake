minimake: main.o args.o preprocess.o syntax_check.o parser.o
	gcc -Wall -g -o main.o args.o preprocess.o syntax_check.o parser.o

main.o: src/main.c
	gcc -Wall -g -Iinclude -c src/main.c -o main.o

args.o: src/args.c include/args.h
	gcc -Wall -g -Iinclude -c src/args.c -o args.o	

preprocess.o: src/preprocess.c include/preprocess.h
	gcc -Wall -g -Iinclude -c src/preprocess.c -o preprocess.o

syntax_check.o: src/syntax_check.c include/syntax_check.h
	gcc -Wall -g -Iinclude -c src/syntax_check.c -o syntax_check.o

parser.o: src/parser.c include/parser.h
	gcc -Wall -g -Iinclude -c src/parser.c -o parser.o

clean:
	rm -f minimake *.o