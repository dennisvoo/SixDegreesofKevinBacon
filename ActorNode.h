#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <climits>
#include "Movie.h"

using namespace std;

/* Author: Dennis Vo
 * Date: 2/25/17
 * Assignment: PA4
 * Description: Header class for Node class
 */

class ActorNode {
public:

  string name;
  unordered_map<string, ActorEdge*> adj;
  int distance;
  ActorNode* prev;
  bool visited;

  /* Constructor */
  ActorNode();
  ActorNode(string s, int d);

  /* Deconstructor */
  ~ActorNode();

  /* Init node's args */
  void init();

  /* Overwriting less than op for pqueue */
  bool operator<(const ActorNode& other) {
    return distance > other.distance;
  }

};

/* Inner class used for pqueue */
class ActorNodePtrLess {
public:
  bool operator()(ActorNode* const & left, ActorNode* const & right) const {
   return *left < *right;
  }
};

#endif
