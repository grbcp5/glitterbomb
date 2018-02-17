# Glitterbomb

**Author:**  Grant Broadwater <grbcp5@mst.edu>

A Mechanical Match *(match-3 puzzle)* artificial intelligence. This program is
a assignment submission for Missouri University of Science and Technology course
CS5400.

#### Assignment

The assignment description can be found at: <http://web.mst.edu/~tauritzd/courses/cs5400/sp2018/puzzle.html>

## Building

A makefile is included as part of the repository to compile properly

##### Making the Executable

Using the default make rule will result in compiling the program with build
output (in the `./build/` directory) and the executable `./bin/glitterbomb`.

```
make
```

##### Cleaning

A `clean` rule is provided to remove all build output including all contents
including the `./build/` directory and the executable `./bin/glitterbomb`.

```
make clean
```

## Deployment

To deploy with no arguments, simply run the executable produced from the build
process

```
./bin/gitterbomb
```

You can provide an argument with with search algorithm to use. If multiple 
search algorithms are included, the first will be used. The following search
algorithms are supported:

* Breadth First Search *(BFS)*
* Iterative Deepening Depth First Search *(IDDFS)*
* Greedy Best First Graph Search *(GBFGS)*
* A* Graph Search *(A\*GS)*

```
./bin/glitterbomb --breadthFirstSearch
```

Along with the search algorithm, you can provide a puzzle file to search. The 
puzzle file format can be seen in the [assignment description](http://web.mst.edu/~tauritzd/courses/cs5400/sp2018/puzzle.html).
To provide a puzzle file simply include the path to the puzzle file. You can
provide as many puzzles as you want to search, the search will happen 
sequentially beginning with the first puzzle provided and ending with the last.

```
./bin/glitterbomb puzzle1.txt ./puzzles/special/puzzle.txt
```

These arguments can be used together to specify a search algorithm and puzzle
files.

```
./bin/glitterbomb --bfs puzzle1.txt puzzles/puzzle2.txt
```

###### Note:

Currently only one search algorithm is supported, and if multiple puzzle files 
are provided, that algorithm will be used for all puzzle files. To apply 
different search algorithms to different files, run the program multiple times.

##### Defaults

If no arguments are provided, the program will use a default search algorithm
and default puzzle files. To view these defaults, execute with the argument 
`--showDefaults`.

```
./bin/glitterbomb --showDefaults
```

## Testing

To execute tests, run with the argument `--test`.

```
./bin/glitterbomb --test
```

