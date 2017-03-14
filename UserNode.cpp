#include "UserNode.h"

/** Author: Dennis Vo
  * Date: 3/14/17
  * Assignment: PA4
  * Description: Implements a node class for each individual facebook user.
  */

UserNode::UserNode(){}

UserNode::UserNode(string s) {
  id = s;
}

UserNode::~UserNode() {
  for (auto it = friends.begin(); it!= friends.end(); it++) {
    delete it->second;
  }
}


