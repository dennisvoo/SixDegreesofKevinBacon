#include <cstdlib>
#include "UnionFind.hpp"

using namespace std;

/** Author: Dennis Vo
  * Date: 3/10/17
  * Assignment: PA4
  * Description: UnionFind uses the Disjoint Set ADT to find connections between
  *              ActorNodes.
  */

ActorNode* UnionFind::find(ActorNode* actor) {
  if (!actor->prev) {
    return actor;
  }

  ActorNode* currActor = actor;
  
  while (currActor->prev) {
    currActor = currActor->prev;
  }
  
  // perform path compression
  actor->prev = currActor;
  return currActor;
}

void UnionFind::unite(ActorNode* actor1, ActorNode* actor2) {
  ActorNode* root1 = find(actor1);
  ActorNode* root2 = find(actor2);

  if (root1 == root2) {
    return;
  }

  root2->prev = root1;
  size--;
}


