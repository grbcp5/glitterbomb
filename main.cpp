#include <iostream>
#include "Puzzle.h"

using namespace std;

int main() {

  Puzzle *p1 = Puzzle::construct( "puzzles/puzzle1.txt" );
  cout << (*p1) << endl;

  return 0;
}