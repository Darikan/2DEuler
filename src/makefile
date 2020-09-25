NAME=2Deuler
OBJFILES=main.o LFscheme.o M_vector.o boundary.o cell.o configuration.o math_lib.o meshReadWrite.o point.o bc.o postproc.o

CC=g++
CFLAGS= -time -Wall -pedantic

%.o : %.cpp
	$(CC) $(CFLAGS) -c -g $<

all: $(NAME) clean


dep:
	$(CC) -MM *.cpp >dep.list

-include dep.list

$(NAME): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $@

clean:
	rm -rf *.o
