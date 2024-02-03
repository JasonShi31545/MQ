quiz: quiz.cc
	clang++ -Wall quiz.cc -ggdb -O0 -o prog.out -lm libraylib.a

static:
	clang++ -Wall quiz.cc -ggdb -O0 -o prog.out -lm libraylib.a -static
clean:
	rm -f prog.out
