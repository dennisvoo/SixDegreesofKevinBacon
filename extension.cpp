#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "FBGraph.cpp"

using namespace std;

/** Author: Dennis Vo
  * Date: 3/14/17
  * Assignment: PA4
  * Description: Implements extension using list of facebook friends where we
  *              can print mutual friends between two friends.
  */

int main ( int argc, char** argv) {

  /* Check for arg count */
  if (argc != 5) {
    cout << "Incorrect # of args" << endl;
    return -1;
  }

  FBGraph fb;
  ifstream in(argv[2]);
  ofstream out(argv[3]);

  if (!out.is_open()) {
    cout << "Can't open file " << argv[3] << endl;
    return -1;
  }

  fb.loadFromFile(argv[1]);

  bool have_header = false;
  while (in) {
    string s, start, end;

    if (!have_header) {
      have_header = true;
      continue;
    }

    istringstream ss(s);
    getline(ss, start, '\t');
    getline(ss, end, '\t');

    fb.printMutualFriends(start, end, out);

  }

  in.close();
  out.close();

  return 0;
}
