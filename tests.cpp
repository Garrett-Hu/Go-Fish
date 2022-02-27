#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  CardBST *player1 = new CardBST;
  CardBST *player2 = new CardBST;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    player1->insert(line);
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    player2->insert(line);
  }
  cardFile2.close();
  cout << "player1 preorder ";
  player1->printPreOrder();
  cout << endl << "player2 preorder ";
  player2->printPreOrder();


  //FIXME: maybe should output is suit/num format
  cout << endl << "the predecessor (p1) of 36 is " << player1->getPredecessor(36) << endl;
  cout << "the predecessor (p2) of 15 is " << player2->getPredecessor(15) << endl;

  cout << "the successor (p1) of 11 is " << player1->getSuccessor(11) << endl;
  cout << "the successor (p2) of 9 is " << player2->getSuccessor(9) << endl;
  

  return 0;
}
