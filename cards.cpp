//cards.cpp
//Authors: Garrett Hu
//Implementation of the classes defined in cards.h

#include "cards.h"

CardBST::CardBST() : root(nullptr){ }

CardBST::~CardBST() {
    clear(root);
}

void CardBST::clear(Node *n) {
    if (n) {
	clear(n->left);
	clear(n->right);
	delete n;
    }
}

bool CardBST::insert(string cardName) {
    if(!root) {
        root = new Node(Card(cardName)); //fix to make node then node have card...do i have to make a new card as well?
        //cout << root->c.suit << " " << root->c.cardNum << " | ";
        return true;
    }
    Card c(cardName);
    return insert(c,root); //overloaded
}

bool CardBST::insert(Card c, Node *n) {
    if(c.cardValue == n->c.cardValue) {
        return false;
    }else if(c.cardValue < n->c.cardValue) {
        if(n->left) {
            return insert(c, n->left);
        }else {
            n->left = new Node(c); //FIXME: pretty sure i cant create a card like this, wait should be fine, but Node(Card(c)) weird
            n->left->parent = n;
            return true;
        }
    }else {
        if(n->right) {
            return insert(c, n->right);
        }else {
            n->right = new Node(c);
            n->right->parent = n;
            return true;
        }
    }
}

int CardBST::count() const {
    return count(root);
}

int CardBST::count(Node *n) const {
    if(!n) {
        return 0;
    }
    
    return 1 + count(n->left) + count(n->right);
}

CardBST::Node* CardBST::getNodeFor(int value, Node* n) const {
    Node *p = n;
    while(p) {
        if(value == p->c.cardValue) {
            return p;
        }else if(value < p->c.cardValue) {
            p = p->left;
        }else {
            p = p->right;
        }
    }
    return NULL;
}

bool CardBST::contains(int value) const { //FIXME: ENSURE VALUE IS FOR CARDVALUE
    Node *n = getNodeFor(value, root);
    if(n) {
        return true;
    }
    return false;    
}

int CardBST::getPredecessor(int value) const {
    Node *n = getPredecessorNode(value);
    if(!n){return 0;}
    return n->c.cardValue;
}

CardBST::Node* CardBST::getPredecessorNode(int value) const {
    if(!contains(value)) {
        return 0;
    }
    Node *n = getNodeFor(value, root);
    if(n->left) {     //the next largest value (less than n) is the largest value in n's left subtree (if it exists)
        n = n->left;
        while(n->right) {
            n = n->right;
        }
        return n;
    }else { //go to parent until one is smaller than original value
        while(n->parent) {
            n = n->parent;
            if(n->c.cardValue < value) {
                return n;
            }
        }
        return NULL;
    }
}

int CardBST::getSuccessor(int value) const {
    Node *n = getSuccessorNode(value);
    if(!n){return 0;}
    return n->c.cardValue;
}

CardBST::Node* CardBST::getSuccessorNode(int value) const {
    if(!contains(value)) {
        return 0;
    }
    Node *n = getNodeFor(value, root);
    if(n->right) {     //the next largest (greater than n) value is the smallest value in n's right subtree (if it exists)
        n = n->right;
        while(n->left) {
            n = n->left;
        }
        return n;
    }else { //go to parent until one is smaller than original value
        while(n->parent) {
            n = n->parent;
            if(n->c.cardValue > value) {
                return n;
            }
        }
        return NULL;
    }
}

bool CardBST::remove(int value) {

    Node *n = getNodeFor(value, root);
    
    if(!n) {return false;} //if node doesnt exist

    if(!(n->left) && !(n->right)) { //leaf node case
        if(n->parent == NULL) {
            root = NULL;
        }else if(n == n->parent->left) {
            n->parent->left = NULL;
        }else {
            n->parent->right = NULL;
        }        
        
        delete n;
        return true;
    }else if(!(n->left)) {
        if(n->parent == NULL) { //n == root
            n->right->parent = NULL;
            root = n->right;
        }else if(n == n->parent->left) { //right is the only child, and this is parent's left child
            n->parent->left = n->right;
            n->right->parent = n->parent;
        }else { //right is the only child, and this is parent's right child
            n->parent->right = n->right;
            n->right->parent = n->parent;
        }
        
        delete n;
        return true;
    }else if(!(n->right)) {
        if(n->parent == NULL) {
            n->left->parent = NULL;
            root = n->left;
        }else if(n == n->parent->left) { //left is the only child, and this is parent's left child
            n->parent->left = n->left;
            n->left->parent = n->parent;
        }else { //left is the only child, and this is parent's right child
            n->parent->right = n->left;
            n->left->parent = n->parent;
        }
        
        delete n;
        return true;
    }else {
        Node *x = getSuccessorNode(n->c.cardValue);
        /*
        n->c.cardValue = x->c.cardValue;
        n->c.cardNum = x->c.cardNum;
        n->c.suit = x->c.suit;
        n->c.weight = x->c.weight;
        */
        Card c2 = x->c;
        
        remove(x->c.cardValue);
        
        n->c = c2;
    }
    return true;
}
/*
char CardBST::getSuit() const {
    Node *n = getNodeFor();
}

int CardBST::getNum() const;
*/
int CardBST::minimum() const {
    Node *n = root;
    while(n->left) {
        n = n->left;
    }
    return n->c.cardValue;
}

int CardBST::maximum() const {
    Node *n = root;
    while(n->right) {
        n = n->right;
    }
    return n->c.cardValue;
}




void CardBST::printPreOrder() const {
    printPreOrder(root);
}

//for testing purposes rn
void CardBST::printPreOrder(Node *n) const {
    if (n) {
        //cout << root->c.suit << " " << root->c.cardNum << " | ";
        //cout << n->c.suit << " " << n->c.cardNum << " | "; //preorder
        //cout << n->c.cardValue << ","; //preorder values
        printPreOrder(n->left);
        cout << n->c.suit << " " << n->c.cardNum << " | "; //inorder
        printPreOrder(n->right);
    }
}

void CardBST::printInOrder() const {
    printInOrder(root);
}

//for testing purposes rn
void CardBST::printInOrder(Node *n) const {
    if (n) {
        printInOrder(n->left);
        cout << n->c.suit << " ";
        if(n->c.cardNum == 11) {
            cout << "j" << endl;
        }else if(n->c.cardNum == 12) {
            cout << "q" << endl;
        }else if(n->c.cardNum == 13) {
            cout << "k" << endl;
        }else if(n->c.cardNum == 1) {
            cout << "a" << endl;
        }else {
            cout << n->c.cardNum << endl;
        }
        printInOrder(n->right);
    }
}

/*
Node* CardBST::getRoot() const {
    return root;
} */