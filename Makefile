quiz: quiz.cc
	clang++ -Wall quiz.cc -ggdb -O0 -o prog.out -lSDL2 -lm

clean:
	rm -f prog.out
