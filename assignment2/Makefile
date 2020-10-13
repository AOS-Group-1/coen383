SRC := round_robin.c

default: rr.out

rr.out: $(SRC)
	gcc -O -g -std=c11 -Wall -Wextra -o $@ $<

clean:
	rm -f rr.out
