#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>
#include <vector>

#include "ActorEdge.h"

using namespace std;

/** Author: Dennis Vo
  * Date: 2/25/17
  * Assignment: PA4
  * Description: Header file for Movie class.
  */

class Movie {
public:
  string name;
  int year;
  int weight;
  vector<ActorNode*> cast;

  /* Constructor */ 
  Movie(string n, int y);

  /* Deconstructor */
  ~Movie();

  /* Overwrite less then op for pqueue */
  bool operator<(const Movie& other) {
    return year > other.year;
  }

};

/* Inner class for pqueue */
class MoviePtrLess {
public:
  bool operator()(Movie* const & left, Movie* const & right) const {
    return *left < *right;
  }
};

#endif
