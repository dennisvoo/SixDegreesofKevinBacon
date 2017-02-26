#include "ActorEdge.h"

/** Author: Dennis Vo
  * Date: 2/25/17
  * Assignment: PA4
  * Description: Class for instantiating edges in the graph.
  */

ActorEdge::ActorEdge(ActorNode* s, ActorNode* e, Movie* m) {
  start = s;
  end = e;
  movie = m;
}

ActorEdge::~ActorEdge(){}
