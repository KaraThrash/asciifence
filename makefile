all:
	g++ fencing.cpp -lncurses -o f.out

clean:
	rm -f *.out
