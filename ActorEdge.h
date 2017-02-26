#ifndef ACTOREDGE_H
#define ACTOREDGE_H

#include <iostream>
#include <string>

class ActorNode;

class Movie;

class ActorEdge {
public:
  ActorNode* start;
  ActorNode* end;
  Movie* movie;

  /* Constructor */
  ActorEdge(ActorNode* s, ActorNode* e, Movie* m);

  /* Deconstructor */
  ~ActorEdge();

};

#endif
