CC=clang++
CPPFLAGS=-std=c++17 -Wall -Wpedantic -Wshadow -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -O0 -Wno-unused-result -lm -lraylib  -I/usr/local/include -L/usr/local/lib
%: %.cc
	$(CC) $(CPPFLAGS) $< -o $@.out

clean:
	rm -f *.out
