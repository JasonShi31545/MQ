CC=clang
CFLAGS=-Wall -Wpedantic -Wshadow -ggdb -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -O0 -Wno-unused-result -lm -lraylib
INCLUDES=-I/usr/local/include -L/usr/local/lib

# %: %.cc
# 	$(CC) $(CFLAGS) $< -o $@.out

MQ: main.c coords.c coords.h
	$(CC) $(CFLAGS) main.c coords.c -o ./MQ

# .PHONY: prod
# prod:
# 	$(CC) $(CFLAGS) main.c -o ./MQ
# 
# .PHONY: clean
# clean:
# 	rm -f *.out
