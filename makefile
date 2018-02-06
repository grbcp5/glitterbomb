default: buildAndRun

buildAndRun: build run

build: relBuild

relBuild:
	g++ -v *.cpp

run:
	./a.out

dbgBuild:
	g++ -g -v *.cpp

valgrind: clean dbgBuild
	valgrind --track-origins=yes --leak-check=full a.out

submit:
	run.sh

clean:
	rm -f a.out
