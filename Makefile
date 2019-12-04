CFLAGS=-g
OBJS=Matrix.o

main: main.cpp Matrix.o
	g++ $(CFLAGS) $< $(OBJS) -o $@

Matrix.o: Matrix.cpp Matrix.hpp
	g++ $(CFLAGS) -c $< -o $@

clean:
	rm main $(OBJS)