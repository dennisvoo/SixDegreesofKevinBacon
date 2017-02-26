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

void ActorGraph::insertGraph(string actor_name, string movie_title,
                             int movie_year) {
  if (actors.find(actor_name) == actors.end()) {
    ActorNode* n = new ActorNode(actor_name, -1);
    actors[actor_name] = n;
  }
  ActorNode* currActor = actors[actor_name];
 
  if (ordered_movies.find(movie_title) == ordered_movies.end()) {
    Movie* m = new Movie(movie_title, movie_year);
    ordered_movies[movie_title] = m;
  }
  Movie* currMov = ordered_movies[movie_title];

  for (auto it = currMov->cast.begin(); it != currMov->cast.end(); it++) {
    updateEdge(currActor, *it, currMov);
    updateEdge(*it, currActor, currMov);
  }
  currMov->cast.push_back(currActor);
}

void ActorGraph::updateEdge(ActorNode* start, ActorNode* end, Movie* mov) {
  if (start->adj.find(start->name + end->name) == start->adj.end()) {
    ActorEdge* e = new ActorEdge(start, end, mov);
    start->adj[start->name + end->name] = e;
  }

  ActorEdge* currEdge = start->adj[start->name + end->name];
  if (currEdge->movie->year < mov->year) {
    currEdge->movie = mov;
  }
}

void ActorGraph::init() {
  for (auto it = actors.begin(); it != actors.end(); it++) {
    it->second->init();
  }
}

void ActorGraph::BFS(string start, string end) {
  init();
  ActorNode* beg = actors[start];
  beg->distance = 0;
 
  queue<ActorNode*> q;
  q.push(beg);
  
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
  cout << "NOT IMPLEMENTED YET" << endl;
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
