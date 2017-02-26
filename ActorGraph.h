/*
 * ActorGraph.h
 * Author: Dennis Vo
 * Date:   2/25/17
 * Assignment: PA4
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <unordered_map>
#include <map>

#include "ActorNode.h"
#include "ActorEdge.h"
#include "Movie.h"
#include "UnionFind.hpp"

using namespace std;

class ActorGraph {
protected:
  
  bool isWeighted;
  unordered_map<string, ActorNode*> actors;
  unordered_map<string, Movie*> unordered_movies;
  map<string, Movie*> ordered_movies;

public:
    /* Constructor */
    ActorGraph(void);

    /* Deconstuctor */
    ~ActorGraph();
  
    /* Initialize an empty graph */
    void init();

    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  
    /* Same as loadFromFile but doesn't account for edges */
    bool loadEmptyFromFile(const char* in_filename);

    /* Reads through file and adds edges to graph */
    void insertGraph(string actor_name, string movie_title, int movie_year);

    /* Add edge between two nodes, while updating edge with newer movie */
    void updateEdge(ActorNode* start, ActorNode* end, Movie* movie);

    /* Add edge between two nodes, while updating edge with older movie */
    void updateEdgeConnect(ActorNode* start, ActorNode* end, Movie* movie);

    /* runs BFS */
    void BFS(string start, string end);

    /* use BFS to check for connection between two actors */   
    int BFSconnect(string start, string end);

    /* use BFS to check for connection between two actors */
    bool BFSconnectCore(string start, string end);

    /* Use Dijkstra method to find path */
    void Dijkstra(string start, string end);

    /* Print path from start to end */
    void printPath(string start, string end, ofstream& out);
  
    /* Search for connected actors for a specific actor */
    void search(string actor, ofstream& out);

    /* disjoint set method used to check for connection between two actors */
    int UFconnect(string start, string end);
};


#endif // ACTORGRAPH_H
