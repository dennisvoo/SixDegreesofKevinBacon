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
  
    /** Same as loadFromFile but doesn't account for edges
      * in_filename - input file we're reading
      *
      * returns true if file loaded successfully, false otherwise.
      */
    bool loadEmptyFromFile(const char* in_filename);

    /* Reads through file and adds edges to graph
     *
     * actor_name - name of actor node we're inserting
     * movie_title - the movie that the actor is in
     * movie_year - the year the movie was released
     */
    void insertGraph(string actor_name, string movie_title, int movie_year);

    /* Add edge between two nodes and update edge with newer movie
     *
     * start - first actor
     * end - second actor 
     * movie - movie they both are in
     */
    void updateEdge(ActorNode* start, ActorNode* end, Movie* movie);

    /** Initialize an empty graph by calling init for each node
     *  which sets each node to default values for BFS/Dijkstra 
     */
    void init();

    /* use BFS on graph
     *
     * start - first actor in the connection
     * end - actor we're trying to find connection with
     */
    void BFS(string start, string end);

    /* Use Dijkstra method to find shortest weighted path on graphs
     *
     * start - first actor in connection
     * end - actor we're trying to find connection with
     */
    void Dijkstra(string start, string end);

    /* Print path from start to end that we take 
     *
     * start - first actor in connection
     * end - actor we're trying to find connection with
     * out - output stream we're writing to
     */
    void printPath(string start, string end, ofstream& out);
  
    /* use BFS to check for connection between two actors
     *
     * start - first actor in connection
     * end - actor we're trying to find connection with
     *
     * returns an int represnting the earliest yea we can find a connection for
     * returns 9999 if a connection cannot be found between 2 actors
     */
    int connectBFS(string start, string end);

    /* Add edge between two nodes and update edge with older movie 
     * Used to update edge numbers with actorconnections
     *
     * start - first actor in connection
     * end - actor we're finding connection with
     * movie - movie they have in common
     */
    void connectUpdateEdge(ActorNode* start, ActorNode* end, Movie* movie);

    /* use BFS to check for connection between two actors
     * 
     * start - first actor
     * end - second actor
     *
     * returns true if we can find a connection between the two
     */
    bool isConnectBFS(string start, string end);

    /* disjoint set method used to check for connection between two actors
     * 
     * start - first actor
     * end - second actor
     *
     * returns true if we can find a connection between the two
     */
    int connectUF(string start, string end);

};


#endif // ACTORGRAPH_H
