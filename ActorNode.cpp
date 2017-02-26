#include "ActorNode.h"

/** Author: Dennis Vo
  * Date: 2/25/17
  * Assignment: PA4
  * Description: Node class for actors.
  */

ActorNode::ActorNode(){}

ActorNode::ActorNode(string s, int d) {
  name = s;
  distance = d;
  visited = false;
  prev = 0;
}

ActorNode::~ActorNode() {
  for (auto it = adj.begin(); it != adj.end(); it++) {
    delete it->second;
  } 
}

void ActorNode::init() {
  prev = 0;
  distance = INT_MAX;
  visited = false;
}
