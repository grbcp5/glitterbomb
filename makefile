default: buildAndRun

buildAndRun: build run

build: relBuild

relBuild:
	g++ -v *.cpp

run:
	./a.out

dbgBuild:
	g++ -g -v *.cpp

valgrind: dbgBuild
	valgrind --track-origins=yes --leak-check=full a.out

submit:
	run.sh
