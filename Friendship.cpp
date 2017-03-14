#include "Friendship.h"

/** Author: Dennis Vo
  * Date: 3/14/17
  * Assignment: PA4
  * Description: Implements a edge class in the form of friendships
  */

Friendship::Friendship(UserNode* s, UserNode* e) {
  start = s;
  end = e;
}

Friendship::~Friendship(){}
