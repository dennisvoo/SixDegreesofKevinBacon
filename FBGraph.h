#ifndef FBGRAPH_H
#define FBGRAPH_H

#include <iostream>
#include <unordered_map>
#include "UserNode.h"
#include "Friendship.h"

using namespace std;

/** Author: Dennis Vo
  * Date: 3/14/17
  * Assignment: PA4
  * Description: Header file for FBGraph.cpp to create a FB friend graph
  */

class FBGraph {
protected:
  unordered_map<string,UserNode*> users;

public:
  /* Ctor */
  FBGraph(void);

  ~FBGraph();

  /** Loads graph form tab-delimited file of friend->friend relationship
   *
   * in_filename - file we're reading from
   *
   * returns true if we can read from the file
   */
  bool loadFromFile(const char* in_filename);

  /** Inserts a friend node into the graph
   * Add a single user node to the graph (one for each friendship
   *
   * id1 - first user id being added to graph
   * id2 - second user id being added to graph
   */
  void insertGraph(string id1, string id2);

  /** Adds edge between two user nodes
    *
    * start - first user
    * end - second user in friendship
    */
  void addEdge(UserNode* start, UserNode* end);

  /** Prints a list of mutual friends for two users
    * 
    * start - first user
    * end - second user
    * out - output stream we're printing to
    */
  void printMutualFriends(string start, string end, ofstream& out);
};

#endif
