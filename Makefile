CFLAGS = -O3 -Wall -g

src = main.c
trg = $(src:.c=.out)

$(trg):main.c
	gcc $(CFLAGS) $< -o $@

test:$(trg)
	./$(trg)

run:$(trg)
	./$< | tee pythagorean_candidates.txt
