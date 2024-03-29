/*
 Author: Vikram Vasudevan
 Date: 3/18/2024
 Description: This program takes data inputs and sorts them into a binary search tree. The user is able to add to the tree, remove from the tree, search in the tree, and print out the tree.

 */

#include <iostream>
#include <cstring>
#include "Node.h"
#include <vector>
#include <fstream>
using namespace std;

//function prototypes
void add(Node* &root, Node* current, Node* newNode);
void print(Node* current, int count);
bool search(Node* current, int value);
void remove(Node* &root, Node* current, int value);

//main
int main(){
  //initializing variables
    Node* root = NULL;

    bool stillRunning = true;
    //while loop where body of code runs.
    while(stillRunning == true){
      //prompting user for input
        cout << "What would you like to do? ADD, REMOVE, SEARCH, PRINT, or QUIT " << endl;
        char choice[50];
        cin.get(choice, 50);
        cin.get();
        if(strcmp(choice, "ADD") == 0){
            char input[50];
            char method;
            cout << "Would you like to enter by file (f) or by console (c)? " << endl;
            cin >> method;
            cin.get();
	    //entering data by console
            if(method == 'c'){
                cout << "How many numbers will you be entering? " << endl;
                int numNums;
                cin >> numNums;
                cin.get();
                cout << "Enter your string of numbers: " << endl;
		//storing data in nodes and adding it to the list.
                for(int i = 0; i < numNums; i++){
                    int tempInt;
                    cin >> tempInt;
                    cin.get();
                    Node* newNode = new Node();
                    newNode->setInformation(tempInt);
                    add(root, root, newNode);
                }  
            
            }
	  //entering data by file
            else if(method == 'f'){
                vector<int> nums;
                fstream first_stream;
                first_stream.open("nums.txt");
                int num;
		//placing numbers in vector.
                while(first_stream >> num){
                    nums.push_back(num);
                }
                vector <int> ::iterator iter = nums.begin();
		//storing numbers in nodes and adding them to tree.
		for(iter = nums.begin(); iter < nums.end(); iter++){
                    Node* newNode = new Node();
                    newNode->setInformation(*iter);
                    add(root, root, newNode);
                }
            }
        }
      
        else if(strcmp(choice, "REMOVE") == 0){
	  //prompting for which value to remove, and calling the remove function.
            int value;
            cout << "What number would you like to remove? " << endl;
            cin >> value;
            cin.get();
            remove(root, root, value);
        }
        else if(strcmp(choice, "SEARCH") == 0){
	  //prompting for which value to search for.
            int value;
            cout << "What number would you like to search for? " << endl;
            cin >> value;
            cin.get();
            if(search(root, value) == true){
                cout << "That value exists in the tree" << endl;
            }
            else{
                cout << "That value doesn't exist in the tree" << endl;
            }
        }
        else if(strcmp(choice, "PRINT") == 0){
	  //calling print
            print(root, 0);
        }
        else if(strcmp(choice, "QUIT") == 0){
	  //exiting the while loop.
            stillRunning = false;
        }

    }
}

//search function, which moves through the tree until it either finds or doesn't find the value.
bool search(Node* current, int value){
  if(current == NULL){
    return false;

  }
  if(value > current->getInformation()){
        if(current->getRight() != NULL){
            return search(current->getRight(), value);
        }
    }
    else if(value < current->getInformation()){
        if(current->getLeft() != NULL){
            return search(current->getLeft(), value);
        }
    }
    else if(value == current->getInformation()){
        return true;
    }
    return false;
}
//delete function
void remove(Node* &root, Node* current, int value){
  //dealing with if the root is getting deleted.
    if(root->getInformation() == value){
      //if the root has no children, just delete it.
        if(root->getRight() == NULL && root->getLeft() == NULL){
            delete root;
        }
	//if it only has one child, delete the root and move that child up to become the root.
        else if(root->getRight() != NULL && root->getLeft() == NULL){
            Node* tempNode = root->getRight();
            delete root;
            root = tempNode;
        }
	
        else if(root->getRight() == NULL && root->getLeft() != NULL){
            Node* tempNode = root->getLeft();
            delete root;
            root = tempNode;
        }
	//if both children exist.
        else if(root->getRight() != NULL && root->getLeft() != NULL){
	  //move over to one of the children, then move in the opposite direction as far as you can.
            Node* tempNode = root->getRight();
            while(tempNode->getLeft() != NULL){
                tempNode = tempNode->getLeft();
            }
	    //the node you end up will move up into the deleted node's position.
            Node* tempNode2 = new Node();
            tempNode2->setInformation(tempNode->getInformation());
	    //remove that node from its initial position.
	    remove(root, root, tempNode->getInformation());
	    //set the left and right of the new node.
            tempNode2->setLeft(root->getLeft());
            tempNode2->setRight(root->getRight());
            root = tempNode2;
        }
    }
    //this is essentially the same as the root function. If the current is > value, move to the left. Check to see if current->getLeft()->getInformation() is correct. If not, recurse. If it is, run the same function as with the root.
    else if(current->getInformation() > value){
        if(current->getLeft()->getInformation() != value){
            remove(root, current->getLeft(), value);
        }
        else{
            if(current->getLeft()->getLeft() == NULL && current->getLeft()->getRight() == NULL){
                delete current->getLeft();
                current->setLeft(NULL);
            }
            else if(current->getLeft()->getLeft() != NULL && current->getLeft()->getRight() == NULL){
                Node* tempNode = current->getLeft()->getLeft();
                delete current->getLeft();
                current->setLeft(tempNode);
            }
            else if(current->getLeft()->getLeft() == NULL && current->getLeft()->getRight()!= NULL){
                Node* tempNode = current->getLeft()->getRight();
                delete current->getLeft();
                current->setLeft(tempNode);
            }
            else if(current->getLeft()->getLeft() != NULL && current->getLeft()->getRight() != NULL){
                Node* tempNode = current->getLeft()->getLeft();
                while(tempNode->getRight() != NULL){
                    tempNode = tempNode->getRight();
                }                
                Node* tempNode2 = new Node();
                tempNode2->setInformation(tempNode->getInformation());
                remove(root, current, tempNode->getInformation());
                tempNode2->setLeft(current->getLeft()->getLeft());
                tempNode2->setRight(current->getLeft()->getRight());
                current->setLeft(tempNode2);
            }
        }
    }
    //this chunk of the code is also the same, just moving right instead of left.
    else if(current->getInformation() < value){
        if(current->getRight()->getInformation() != value){
            remove(root, current->getRight(), value);
        }
        else{
            if(current->getRight()->getLeft() == NULL && current->getRight()->getRight() == NULL){
                delete current->getRight();
                current->setRight(NULL);
            }
            else if(current->getRight()->getLeft() != NULL && current->getRight()->getRight() == NULL){
                Node* tempNode = current->getRight()->getLeft();
                delete current->getRight();
                current->setRight(tempNode);
            }
            else if(current->getRight()->getLeft() == NULL && current->getRight()->getRight()!= NULL){
                Node* tempNode = current->getRight()->getRight();
                delete current->getRight();
                current->setRight(tempNode);
            }
            else if(current->getRight()->getLeft() != NULL && current->getRight()->getRight() != NULL){
                Node* tempNode = current->getRight()->getRight();
                while(tempNode->getLeft() != NULL){
                    tempNode = tempNode->getLeft();
                }                
                Node* tempNode2 = new Node();
                tempNode2->setInformation(tempNode->getInformation());
                remove(root, current, tempNode->getInformation());
                tempNode2->setLeft(current->getRight()->getLeft());
                tempNode2->setRight(current->getRight()->getRight());
                current->setRight(tempNode2);
            }
    }
    }
}

//add function, which adds values to the tree.
void add(Node* &root, Node* current, Node* newNode){
  //setting the root
    if(root == NULL){
        root = newNode;
    }
    //if the current node is greater than the new node, the new node goes to the left of the current node.
    else if(current->getInformation() >= newNode->getInformation()){
        if(current->getLeft() == NULL){
            current->setLeft(newNode);
        }
        else{
            add(root, current->getLeft(), newNode);
        }
    }
    //if the current node is less than the new node, the new node goes to the right of the current node.
    else if(current->getInformation() < newNode->getInformation()){
        if(current->getRight() == NULL){
            current->setRight(newNode);
        }
        else{
            add(root, current->getRight(), newNode);
        }
    }

}
//print function
void print(Node* current, int count){
  if(current == NULL){
    cout << "NOTHING IN THE TREE" << endl;
    return;
  }
  //iterates to extreme left of tree.
  else if(current->getRight() != NULL){
      print(current->getRight(), count + 1);
    }
    //prints out appropriate number of tabs
  for(int i = 0; i < count; i++){
        cout << '\t';
    }
    //prints
    cout << current->getInformation() << endl;
    //runs on the right side
  if(current->getLeft() != NULL){
        print(current->getLeft(), count + 1);
    }

}
