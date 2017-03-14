/*
 * ActorGraph.cpp
 * Author: Dennis Vo
 * Date:   2/25/17
 * Assignment: PA4
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack> 
#include <queue>
#include <deque>

#include "ActorGraph.h"

using namespace std;

ActorGraph::ActorGraph(void) {}	


ActorGraph::~ActorGraph() {
  for (auto it = actors.begin(); it != actors.end(); it++) {
    delete it->second;
  }

  for (auto it = ordered_movies.begin(); it != ordered_movies.end(); it++) {
    delete it->second;
  }
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;
  
  // keep reading lines until the end of file is reached
  while (infile) {
    string s;
    
    // get the next line
    if (!getline( infile, s )) break;

    if (!have_header) {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) {
      string next;
      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;

      record.push_back( next );
    }
    
    if (record.size() != 3) {
      // we should have exactly 3 columns
      continue;
    }

    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);
    
    insertGraph(actor_name, movie_title, movie_year);
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();

  return true;
}

bool ActorGraph::loadEmptyFromFile(const char* in_filename) {
  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;

  // keep reading lines until the end of file is reached
  while (infile) {
    string s;
  
    // get the next line
    if (!getline( infile, s )) break;

    if (!have_header) {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) {
      string next;
      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;

      record.push_back( next );
    }
    
    if (record.size() != 3) {
      // we should have exactly 3 columns
      continue;
    }

    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);
  
    if (actors.find(actor_name) == actors.end()) {
      ActorNode* newActor = new ActorNode(actor_name, -1);
      actors[actor_name] = newActor;
    }

    if (ordered_movies.find(to_string(movie_year) + movie_title) == 
          ordered_movies.end()) {
      Movie* newMovie = new Movie(movie_title, movie_year);
      ordered_movies[to_string(movie_year) + movie_title] = newMovie;
    }

    ordered_movies[to_string(movie_year) + 
                     movie_title]->cast.push_back(actors[actor_name]);
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();
  return true;
}

void ActorGraph::insertGraph(string actor_name, string movie_title,
                             int movie_year) {
  // if the actor isn't already in our map
  if (actors.find(actor_name) == actors.end()) {
    ActorNode* newActor = new ActorNode(actor_name, -1);
    // add actor to our actors map
    actors[actor_name] = newActor;
  }
  // set our current actor node to index where actor_name is
  ActorNode* currActor = actors[actor_name];
 
  // if the movie isn't already in map
  if (ordered_movies.find(movie_title) == ordered_movies.end()) {
    Movie* newMovie = new Movie(movie_title, movie_year);
    // add movie to our ordered movie map
    ordered_movies[movie_title] = newMovie;
  }
  // set our current movie node to index where movie_title is
  Movie* currMov = ordered_movies[movie_title];

  for (auto it = currMov->cast.begin(); it != currMov->cast.end(); it++) {
    updateEdge(currActor, *it, currMov);
    updateEdge(*it, currActor, currMov);
  }
  // add our current actor to the cast of our current movie
  currMov->cast.push_back(currActor);
}

void ActorGraph::updateEdge(ActorNode* start, ActorNode* end, Movie* mov) {
  if (start->adj.find(start->name + end->name) == start->adj.end()) {
    ActorEdge* newEdge = new ActorEdge(start, end, mov);
    start->adj[start->name + end->name] = newEdge;
  }

  ActorEdge* currEdge = start->adj[start->name + end->name];
  if (currEdge->movie->year < mov->year) {
    currEdge->movie = mov;
  }
}

void ActorGraph::init() {
  for (auto it = actors.begin(); it != actors.end(); it++) {
    // init all actor nodes with inf distance, NULL prev, and false visited
    it->second->init();
  }
}

void ActorGraph::BFS(string start, string end) {
  init();
  ActorNode* first = actors[start];
  first->distance = 0;
 
  queue<ActorNode*> q;
  q.push(first);
  
  while (!q.empty()) {
    ActorNode* tmp = q.front();
    q.pop();

    for (auto it = tmp->adj.begin(); it != tmp->adj.end(); it++) {
      if (it->second->end->distance == INT_MAX) {
        it->second->end->distance = tmp->distance + 1;
        it->second->end->prev = tmp;
        q.push(it->second->end);
      }
    }
  }
}

void ActorGraph::Dijkstra(string start, string end) {
  init();
  ActorNode* first = actors[start];
  first->distance = 0;

  priority_queue<ActorNode*, vector<ActorNode*>, ActorNodePtrLess> pq;
  pq.push(first);

  // we start with our optimal weight at 9999 so we can short circuit it
  // when we add in "end" 
  int optimal_weight = 9999;
 
   while (!pq.empty()) {
    ActorNode* tmp = pq.top();
    pq.pop();
 
    // can stop early if node we pop equals opt weight, can't find shorter path
    if (tmp->distance == optimal_weight) {
      break;
    }
  
    if (tmp->visited) {
      continue;
    }
 
    tmp->visited = true;

    // for each neighbor (going through each edge to find)..
    for (auto it = tmp->adj.begin(); it != tmp->adj.end(); it++) {
      // c is current node's distance plus weight of adjacent movie
      int c = tmp->distance + it->second->movie->weight;
      // cmp distance of each neighbor with c
      if (c < it->second->end->distance) {
        it->second->end->prev = tmp;
        it->second->end->distance = c;
        pq.push(it->second->end);
        // if we pushed our end node, we set our opt weight to its dist
        if (it->second->end == actors[end]) {
          optimal_weight = it->second->end->distance;
        }
      }
    }
  }
}

void ActorGraph::printPath(string start, string end, ofstream& out) {
  stack<ActorNode*> s;
  ActorNode* curr = actors[end];

  while (curr->name != start) {
    s.push(curr);
    curr = curr->prev;
  }

  while (!s.empty()) {
    ActorNode* next = s.top();
    s.pop();
    ActorEdge* e = curr->adj[curr->name + next->name];
    Movie* m = e->movie;
    out << "(" + curr->name + ")" + "--[" + m->name + "#@" + 
      to_string(m->year) + "]-->";
    curr = next;
  }
  out << "(" + curr->name + ")" << endl;
}

int ActorGraph::connectBFS(string start, string end) {
  for (auto it = ordered_movies.begin(); it != ordered_movies.end(); it++) {
    Movie* mov = it->second;
    for (int i = 0; i < mov->cast.size(); i++) {
      for (int j = i + 1; j < mov->cast.size(); j++) {
        connectUpdateEdge(mov->cast[i], mov->cast[j], mov);
        connectUpdateEdge(mov->cast[j], mov->cast[i], mov);
      }
    }
   
    if (isConnectBFS(start, end)) {
      return mov->year;
    }
  }

  return 9999; 
}

void ActorGraph::connectUpdateEdge(ActorNode* start, ActorNode* end, Movie* mov)
{
  if (start->adj.find(start->name + end->name) == start->adj.end()) {
    ActorEdge* newEdge = new ActorEdge(start, end, mov);
    start->adj[start->name + end->name] = newEdge;
  }
  
  ActorEdge* currEdge = start->adj[start->name + end->name];
  if (currEdge->movie->year > mov->year) { 
    currEdge->movie = mov;
  }
}

bool ActorGraph::isConnectBFS(string start, string end) {
  init();
  ActorNode* first = actors[start];
  first->distance = 0;

  deque<ActorNode*> q;
  q.push_back(first);

  while(!q.empty()) {
    ActorNode* tmp = q.front();
    q.pop_front();
    
    if(tmp->name == end) {
      return true;
    }

    for (auto it = tmp->adj.begin(); it != tmp->adj.end(); it++)  {
      if (it->second->end->distance == INT_MAX) {
        it->second->end->distance = tmp->distance + 1;
        it->second->end->prev = tmp;
        q.push_back(it->second->end);
      }
    }
  }
  return false;
}

int ActorGraph::connectUF(string start, string end) {
  UnionFind uf(actors);
  for (auto it = ordered_movies.begin(); it != ordered_movies.end(); it++) {
    Movie* mov = it->second;
    for (int i = 1; i < mov->cast.size(); i++) {
      uf.unite(mov->cast[0], mov->cast[i]);
    }
   
    if (uf.find(actors[start]) == uf.find(actors[end])) {
      return mov->year;
    }
  }
  return 9999;
}
