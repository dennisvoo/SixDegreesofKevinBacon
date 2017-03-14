#ifndef USERNODE_H
#define USERNODE_H

#include <iostream>
#include <unordered_map>
#include "Friendship.h"

using namespace std;

/** Author: Dennis Vo
  * Date: 3/14/17
  * Assignment: PA4
  * Description: Header file for UserNode.cpp representing individual users
  */

class UserNode {
public:
  string id;
  unordered_map<string, Friendship*> friendships;
  unordered_map<string, UserNode*> friends;
  
  /* Ctor */
  UserNode();
  UserNode(string s);

  /* Deconstructor */
  ~UserNode();

};

#endif 
