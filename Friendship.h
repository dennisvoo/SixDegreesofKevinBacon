#ifndef FRIENDSHIP_H
#define FRIENDSHIP_H

#include <iostream>

class UserNode;

class Friendship {
public:

  UserNode* start;
  UserNode* end;

  /* Ctor */
  Friendship(UserNode* s, UserNode* e);

  /* Deconstructor */
  ~Friendship();

};

#endif
