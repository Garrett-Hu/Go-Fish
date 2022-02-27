//cards.h
//Authors: Garrett Hu
//All class declarations go here

#ifndef CARDS_H
#define CARDS_H

#include <iostream>

using namespace std;

class CardBST {

 public:
    // ctor, dtor, insert and one print method already done in intbst.cpp:
    CardBST();                   // constructor
    ~CardBST();                  // destructor
    bool insert(string cardName);     // insert value; return false if duplicate

    bool contains(int value) const;  // true if value is in tree
    int count() const;

    int getPredecessor(int value) const;       // returns the predecessor value of the given value or 0 if there is none
    int getSuccessor(int value) const;         // returns the successor value of the given value or 0 if there is none
    bool remove(int value);                    // deletes the Node containing the given value from the tree
    void printPreOrder() const;
    void printInOrder() const;

    void game(CardBST *bob);

    char getSuit() const;
    int getNum() const;

    int minimum() const;
    int maximum() const;

    //Node* getRoot() const;

 private:
    //FIXME: Consider moving these definitions/constructors to .cpp to avoid clutter
    struct Card { 
        int cardValue;
        int weight;
        char suit;
        int cardNum;
        
        Card(string s = "c a") {
            string tempString = s.substr(2,2); //stores card number as a string, used during checks for face cards
            suit = s[0];
                     
            if(tempString == "k") {
                cardNum = 13;
            }else if(tempString == "q") {
                cardNum = 12;
            }else if(tempString == "j") {
                cardNum = 11;
            }else if(tempString == "a") {
                cardNum = 1;
            }else {
                cardNum = stoi(tempString);
            }

            if(suit == 'c') {
                weight = 0;
            }else if(suit == 'd') {
                weight = 13;
            }else if(suit == 's') {
                weight = 26;
            }else if(suit == 'h') {
                weight = 39;
            }

            cardValue = cardNum + weight;
        }
    };
    struct Node {
        Card c;
        Node *left, *right, * parent;

        Node(Card c1) {
            c.cardValue = c1.cardValue;
            c.weight = c1.weight;
            c.suit = c1.suit;
            c.cardNum = c1.cardNum;
            left = right = parent = nullptr;
        }    
    };

    Node *root;



    // recursive utility functions for use by public methods above
    Node* getNodeFor(int value, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(Card c, Node *n); // note overloading names for simplicity
    int count(Node *n) const;


    Node* getSuccessorNode(int value) const;
    Node* getPredecessorNode(int value) const;

    //game funcs
    void alicePlay(Node* aliceMinimum, Node* bobMaximum, CardBST *alice, CardBST *bob);
    void bobPlay(Node* aliceMinimum, Node* bobMaximum, CardBST *alice, CardBST *bob);


    //private since node is unidentified?
    void printPreOrder(Node *n) const;
    void printInOrder(Node *n) const;
};


#endif