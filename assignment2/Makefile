SRC1 := round_robin.c
SRC2 := hpq_pe.c

default: rr hpq_pe

rr: $(SRC1)
	gcc -O -g -std=c11 -Wall -Wextra -o $@ $<

hpq_pq: $(SRC2)
	gcc -O -g -std=c11 -Wall -Wextra -o $@ $<

clean:
	rm -f rr hpq_pe output.txt
