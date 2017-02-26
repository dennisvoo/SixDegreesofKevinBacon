#include "Movie.h"

using namespace std;

/** Author: Dennis Vo
  * Date: 2/25/17
  * Assignment: PA4
  * Description: Movie class for holding movies.
  */

Movie::Movie(string n, int y) {
  name = n;
  year = y;
  weight = 1 + (2015 - year);
}

Movie::~Movie() {}
