#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "FBGraph.h"

using namespace std;

/** Author: Dennis Vo
  * Date: 3/14/17
  * Assignment: PA4
  * Description: Implements a graph of facebook users and their friends.
  */

FBGraph::FBGraph(void) {}

FBGraph::~FBGraph() {
  for (auto it = users.begin(); it != users.begin(); it++) {
    delete it->second;
  }
}

bool FBGraph::loadFromFile(const char* in_filename) {
  // Initialize file stream
  ifstream infile(in_filename);
  bool have_header = false;

  // keep reading lines until EOF is reached
  while (infile) {
    string s;
    // get next line
    if (!getline( infile, s )) break;    
    if (!have_header){
      //skip the header
      have_header = true;
      continue;
    }
  
    istringstream ss(s);
    vector <string> record;
    while (ss){
      string next;      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline(ss, next, '\t')) break;
      record.push_back(next);
    }
    if (record.size() != 2) {
      continue;
    }

    string user1 = record[0];
    string user2 = record[1];
    insertGraph(user1, user2);
  } 

  if (!infile.eof()) {
    cout << "Failed to read "<< in_filename << "!\n";
    return false;
  }
  infile.close();
  return true;
}

void FBGraph::insertGraph(string id1, string id2) {
  if (users.find(id) == users.end()) {
    UserNode* newUser = new UserNode(id1);
    users[id1] = newUser; 
  }

  UserNode* firstUser = users[id1];
  UserNode* secondUser = users[id2]
  addEdge(firstUser,secondUser);
}

void FBGraph::addEdge(UserNode* start, UserNode* end) {
  if (start->friendships.find(start-> id + end->id) == start->friendships.end()) {
    Friendship* newFriends = new Friendship(start, end);
    start->friendships[start->id + end->id] = newFriends;
  }

  if (start->friends.find(id2) == start->friends.find(id2) {
    UserNode* newFriend = new UserNode(id2);
    start->friends[id2] = newFriend;
  }
} 
    
void FBGraph::printMutualFriends(string start, string end, ofstream& out) {
  unordered_map<string, UserNode*>  mutual_friends;
  UserNode* first = users[start]; // grab first user
  UserNode* second = users[end];  // grab second user

  for (auto it = first->friends.begin(); it != first->friends.end(); it++) {
    if (second->friends.find[it->first]) {
      mutual_friends.insert(it->first);
    }
  }

  out << "Mutual friends between " << start << "and " << end << "are.." << endl;
  for (auto iter = mutual_friends.begin(); iter != mutual_friends.end(); iter++) {
    out << iter->first << ", ";
}
