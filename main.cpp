#include <iostream>
#include <cstring>
#include "Node.h"


using namespace std;

void add(Node* &root, Node* current, Node* newNode);
void print(Node* current, int count);
bool search(Node* current, int value);
void remove(Node* &root, Node* current, int value);

int main(){
    Node* root = NULL;

    bool stillRunning = true;
    while(stillRunning = true){
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
            if(method == 'c'){
                cout << "How many numbers will you be entering? " << endl;
                int numNums;
                cin >> numNums;
                cin.get();
                cout << "Enter your string of numbers: " << endl;
                for(int i = 0; i < numNums; i++){
                    int tempInt;
                    cout << "INSIDE?" << endl;
                    cin >> tempInt;
                    cout << tempInt << endl;
                    cout << "HI" << endl;
                    cin.get();
                    Node* newNode = new Node();
                    newNode->setInformation(tempInt);
                    add(root, root, newNode);
                }  
            
            }
            else if(method == 'f'){
                
            }
        }
        else if(strcmp(choice, "REMOVE") == 0){

        }
        else if(strcmp(choice, "SEARCH") == 0){


        }
        else if(strcmp(choice, "PRINT") == 0){

        }
        else if(strcmp(choice, "QUIT") == 0){

        }

    }
    
}

bool search(Node* current, int value){
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

void remove(Node* &root, Node* current, int value){
    cout << "VALUE: " << value << endl;
    if(root->getInformation() == value){
        if(root->getRight() == NULL && root->getLeft() == NULL){
            delete root;
        }
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
        else if(root->getRight() != NULL && root->getLeft() != NULL){
            Node* tempNode = root->getRight();
            while(tempNode->getLeft() != NULL){
                tempNode = tempNode->getLeft();
            }
            Node* tempNode2 = new Node();
            tempNode2->setInformation(tempNode->getInformation());
            remove(root, tempNode, tempNode->getInformation());
            tempNode2->setLeft(root->getLeft());
            tempNode2->setRight(root->getRight());
            root = tempNode2;
        }
    }
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

void add(Node* &root, Node* current, Node* newNode){
    if(root == NULL){
        root = newNode;
    }
    else if(current->getInformation() > newNode->getInformation()){
        if(current->getLeft() == NULL){
            current->setLeft(newNode);
        }
        else{
            add(root, current->getLeft(), newNode);
        }
    }
    else if(current->getInformation() < newNode->getInformation()){
        if(current->getRight() == NULL){
            current->setRight(newNode);
        }
        else{
            add(root, current->getRight(), newNode);
        }
    }

}

void print(Node* current, int count){
    if(current->getLeft() != NULL){
        print(current->getLeft(), count + 1);
    }
    for(int i = 0; i < count; i++){
        cout << '\t';
    }
    cout << current->getInformation() << endl;
    if(current->getRight() != NULL){
        print(current->getRight(), count + 1);
    }

}