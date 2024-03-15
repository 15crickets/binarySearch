#include <iostream>
#include <cstring>
#include "Node.h"


using namespace std;

void add(Node* &root, Node* current, Node* newNode);
void print(Node* current, int count);
bool search(Node* current, int value);
void remove(Node* &root, Node* current, int value);

int main(){
    char input[50];
    char method;
    cout << "Would you like to enter by file (f) or by console (c)? " << endl;
    cin >> method;
    cin.get();
    Node* root = NULL;
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
        print(root, 0); 
        if(search(root, 4) == true){
            cout << "That value exists!" << endl;
        }
        else{
            cout << "That value doesn't exist" << endl;
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
    if(root->getInformation() == value){

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
            else if(current->getLeft()->getLeft() != NULL){
                Node* tempNode = current->getLeft()->getLeft();
                while(tempNode->getRight() != NULL){
                    tempNode = tempNode->getRight();
                }
                Node* tempNode2 = new Node();
                tempNode2->setInformation(tempNode->getInformation());
                tempNode = NULL;
                

            }
        }
    }
    else if(current->getInformation() < value){

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