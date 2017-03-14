#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

#include "ActorGraph.h"

/** Author: Dennis Vo
  * Date: 2/25/17
  * Assignment: PA4
  * Description: Header file for UnionFind.
  */

class UnionFind{
private:
  unordered_map<string, ActorNode*> actorSet;
  int size;

public:
  UnionFind(unordered_map<string, ActorNode*>& as) : actorSet(as) {
     size = actorSet.size();
  };

  /* Find root of up-tree */
  ActorNode* find(ActorNode* actor);

  /* Merge 2 nodes into 1 cluster */
  void unite(ActorNode* actor1, ActorNode* actor2);

};

#endif
