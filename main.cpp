//game runs through main

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

  CardBST *alice = new CardBST;
  CardBST *bob = new CardBST;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    alice->insert(line);
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    bob->insert(line);
  }
  cardFile2.close();

  int aliceMin = alice->minimum();
  int bobMax = bob->maximum();
  int tempAlice, tempBob;
  bool aliceIterate = true, bobIterate = true;

  int maxIterations = alice->count();
  int temp = 0;
  char suit = 0;
  int cardNum = 0;

  for(int i = 0; i <= maxIterations; i++) {
    while(aliceIterate && aliceMin != 0) {    
      if(bob->contains(aliceMin)) {
        temp = aliceMin;
        tempAlice = alice->getSuccessor(aliceMin);
   
        alice->remove(aliceMin);
        bob->remove(aliceMin);
        
        aliceMin = tempAlice;

        if(temp / 13 == 0) {
          suit = 'c';
        }else if(temp / 13 == 1) {
          suit = 'd';
          if(temp % 13 == 0) {
            suit = 'c';
          }
        }else if(temp / 13 == 2) {
          suit = 's';
          if(temp % 13 == 0) {
            suit = 'd';
          }
        }else {
          suit = 'h';
          if(temp % 13 == 0 && temp != 52) {
            suit = 's';
          }
        }
        cardNum = temp % 13;
        if(cardNum == 11) {
          cout << "Alice picked matching card " << suit << " j" << endl;
        }else if(cardNum == 12) {
          cout << "Alice picked matching card " << suit << " q" << endl;
        }else if(cardNum == 0) {
          cout << "Alice picked matching card " << suit << " k" << endl;
        }else if(cardNum == 1) {
          cout << "Alice picked matching card " << suit << " a" << endl;
        }else {
          cout << "Alice picked matching card " << suit << " " << cardNum << endl;
        }
        
        aliceIterate = false;
        bobIterate = true;
        break;
      }else {
        aliceMin = alice->getSuccessor(aliceMin);
      }
    }

    while(bobIterate && bobMax != 0) {
      if(alice->contains(bobMax)) {
        temp = bobMax;
        tempBob = bob->getPredecessor(bobMax);

        alice->remove(bobMax);
        bob->remove(bobMax);
        
        bobMax = tempBob;

        if(temp / 13 == 0) {
          suit = 'c';
        }else if(temp /13 == 1) {
          suit = 'd';
          if(temp % 13 == 0) {
            suit = 'c';
          }
        }else if(temp /13 == 2) {
          suit = 's';
          if(temp % 13 == 0) {
            suit = 'd';
          }
        }else {
          suit = 'h';
          if(temp % 13 == 0 && temp != 52) {
            suit = 's';
          }
        }
        cardNum = temp % 13;
        if(cardNum == 11) {
          cout << "Bob picked matching card " << suit << " j" << endl;
        }else if(cardNum == 12) {
          cout << "Bob picked matching card " << suit << " q" << endl;
        }else if(cardNum == 0) {
          cout << "Bob picked matching card " << suit << " k" << endl;
        }else if(cardNum == 1) {
          cout << "Bob picked matching card " << suit << " a" << endl;
        }else {
          cout << "Bob picked matching card " << suit << " " << cardNum << endl;
        }

        
        bobIterate = false;
        aliceIterate = true;
        break;
      }else {
        bobMax = bob->getPredecessor(bobMax);
      }
    }
  }

  cout << endl << "Alice's cards:" << endl;
  alice->printInOrder();
  
  cout << endl << "Bob's cards:" << endl;
  bob->printInOrder();

  return 0;
}