#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include "ActorGraph.h"

using namespace std;

/** Author: Dennis Vo
  * Date: 3/10/17
  * Assignment: PA4
  * Description: Finds connections between two actors. Will use BFS or
  *              Disjoint Set ADT to find these connetions.
  */

int main (int argc, char** argv) {
  bool bfsflag = false;  // checks if we run bfs or ufind
  bool printMethod = false; // check if we've printed method we used yet

  /* Check for correct # of args */
  if (argc < 4 || argc > 5 ) {
    cout << "Incorrect # of args" << endl;
    return -1;
  }

  ifstream in(argv[2]);
  ofstream out(argv[3]);

  /* Check if we can open input and output files */
  if (!in.is_open()) {
    cout << "Cannot open file" << argv[2] << endl;
    return -1;
  }
  if (!out.is_open()) {
    cout << "Cannot open file" << argv[3] << endl;
    return -1;
  }

  out << "Actor1\t" << "Actor2\t" << "Year" << endl;
  bool have_header = false;

  while (in) {
    string str, start, end;
    if (!getline(in, str)) {
      break;
    }
    
    if (!have_header) {
      // skip header
      have_header = true;
      continue;
    }
  
    istringstream sstream(str);
    getline(sstream, start, '\t');
    getline(sstream, end, '\t');

    if (argc == 4) {
      bfsflag = false;
    } else {
      // check if we specified bfs to set bfsflag to true
      if (strcmp(argv[4], "bfs") == 0) {
        bfsflag = true;
      }
    }   

    /* Decide which method to use */
    if (!bfsflag) {
      if (!printMethod) {
        cout << "Running Union Find" << endl;
        printMethod = true;
      }
      ActorGraph* graph = new ActorGraph;
      graph->loadEmptyFromFile(argv[1]);
      out << start << "\t" << end << "\t" << graph->connectUF(start,end) <<endl;
      delete graph;
    } else {
      if (!printMethod) {
        cout << "Running BFS" << endl;
        printMethod = true;
      }
      ActorGraph* graph = new ActorGraph;
      graph->loadEmptyFromFile(argv[1]);
      cout<<"This Line"<<endl;
      out << start << "\t" << end << "\t" << graph->connectBFS(start,end)<<endl;
      delete graph;
    } 

  }

  in.close(); 
  out.close();

  return 0;
}

