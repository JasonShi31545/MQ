quiz: quiz.cc
	clang++ -Wall quiz.cc -ggdb -O0 -o prog.out -lraylib -lm

clean:
	rm -f prog.out
