#include <iostream>
#include <fstream>
#include <sstream>

#include <queue>
#include <stack>
#include <set>
#include <cstring>

#include "ActorGraph.h"

using namespace std;

/** Author: Dennis Vo
  * Date: 2/25/17
  * Assignment: PA4
  * Description: File that goes through ActorGraph and finds shortest path
  *              between two actors.
  */

int main (int argc, char* argv[]) {

  // Check for correct number of args
  if (argc != 5) {
    cout << "Incorrect # of args" << endl;
    return -1;
  }
  
  //Instantiate ActorGraph and i/o stream
  ActorGraph graph;
  ifstream in(argv[3]);
  ofstream out(argv[4]);

  // Check if we can open the files
  if (!in.is_open()) {
    cout << "Can't open input file " << argv[3] << endl;
    return -1;
  }

  if (!out.is_open()) {
    cout << "Can't open output file " << argv[4] << endl;
    return -1;
  }

  // Load the file of actors/movies
  graph.loadFromFile(argv[1], *argv[2] == 'w'); 

  out << "(actor)--[movie#@year]-->(actor)--..." << endl;
  bool have_header = false;
  
  while (in) {
    string s, start, end;

    if (!getline(in,s)) {
      break;
    }

    if (!have_header) {
      have_header = true;
      continue;
    }
   
    istringstream sstream(s);
    getline(sstream, start, '\t');
    getline(sstream, end, '\t');

    graph.init();
    
    if (*argv[2] == 'u') {
      graph.BFS(start,end);
    } else {
      graph.Dijkstra(start,end);
    }

    graph.printPath(start,end,out);
  }

  in.close();
  out.close();

  return 0;
}
