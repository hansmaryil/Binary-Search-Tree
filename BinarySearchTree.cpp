#include "BinarySearchTree.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

// Implement the functions here.
BinarySearchTree::Node::Node(DataType newval){
    val = newval;
    left =  NULL;
    right =  NULL;
}

BinarySearchTree::BinarySearchTree(){
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree(){
    while (root_ != NULL){
        remove(root_ -> val);
    }
}

bool BinarySearchTree::insert(DataType val){
    
    Node *newNode = new Node(val);
    
    if (root_ == NULL){
        root_ = newNode;
        size_++;
        return true;
    } 
    
    Node *temp = root_;
    
    while(true){
        
        if (val > temp -> val){
            if (temp -> right == NULL){
                temp -> right = newNode;  
                break;
            }
            temp = temp -> right;
        }
        else if (val < temp -> val){
            if (temp -> left == NULL){
                temp -> left = newNode;  
                break;
            }
            temp = temp -> left;
        }
        else{
            return false;
        }
    }
    size_++;
    return true;
}

bool BinarySearchTree::remove(DataType val){
    
    if (size_ == 0){
        return false;
    }
    
    Node *temp = root_, *del = NULL, *delRoot;
    
    //get the node to delete and its parent 
    if (root_ -> val == val){ //if the node to delete is the root node
        delRoot = NULL;
        del = root_;
    }
    else{ // if the node to delete is any other node
        //while (temp -> left != NULL || temp -> right != NULL){
        while (temp != NULL){

            if (temp -> left != NULL && temp -> left -> val == val){
                //cout << " left";
                del = temp -> left;
                delRoot = temp;
                break;
            }
            else if (temp -> right != NULL && temp -> right -> val == val){
                //cout << " right";
                del = temp -> right;
                delRoot = temp;
                break;
            }
            if (val > temp -> val){
                //cout << temp -> val << ", ";
                temp = temp -> right;
            }
            else if (val < temp -> val){
                //cout << temp -> val << ", ";
                temp = temp -> left;
            }
        }
        if (del == NULL){// if a the node with that value cannot be found
            return false;
        }
    }
    
    //cout << " Del:" << del -> val << " ";
    //if (delRoot != NULL)
        //cout << " DelRoot:" <<delRoot -> val << "   ";
    
    size_--;
    
    //if del is a leaf
    if (del -> left == NULL && del -> right == NULL){
        //cout << "1";
        if (delRoot == NULL){
            //cout << "A";
            root_ = NULL;
        }
        else if (delRoot -> left != NULL &&  delRoot -> left -> val == val){
            //cout << "B";
            delRoot -> left = NULL;
        }
        else { //delRoot -> right == val
            //cout << "C";
            delRoot -> right = NULL;
        }
        delete del;
        return true;
    }
    
    // only has child on the right
    if (del -> left == NULL){
        //cout << "2";
        if (delRoot == NULL){
            //cout << "A";
            root_ = root_ -> right;
        }
        else if (delRoot -> left != NULL && delRoot -> left -> val == val){
            //cout << "B";
            delRoot -> left = del -> right;
        }
        else { //delRoot -> right == val
            //cout << "C";
            delRoot -> right = del -> right;
        }
        delete del;
        return true;
    }
    
    // only has child on the left
    if (del -> right == NULL){
        //cout << "3";
        if (delRoot == NULL){
            //cout << "A";
            root_ = root_ -> left;
        }
        else if (delRoot -> left != NULL && delRoot -> left -> val == val){
            //cout << "B";
            delRoot -> left = del -> left;
        }
        else { //delRoot -> right == val
            //cout << "C";
            delRoot -> right = del -> left;
        }
        delete del;
        return true;
    }
    
    //cout << "4";
    // find the min of the right tree
    Node *minRoot = del -> right, *min;
    
    if (minRoot -> left == NULL){
        //cout << "A";
        min = minRoot;
        minRoot = NULL;
    }
    else{
        //cout << "B";
        while (minRoot -> left -> left != NULL){
            minRoot = minRoot -> left;
        }
        min = minRoot -> left;
    }
    
    //cout << " Min:" << min -> val << " "; 
    //if (minRoot != NULL)
        //cout << " MinRoot:" << minRoot -> val << " ";
    
    //swap the min with the root to delete
    //Note the min left is always going to be NULL
    Node *minRight = min -> right;
    
    if (delRoot == NULL){
        //cout << "A";
        root_ = min;
    }
    else if (delRoot -> left != NULL && delRoot -> left -> val == val){
        //cout << "B";
        delRoot -> left = min;
    }
    else {
        //cout << "C";
        delRoot -> right = min;
    }
    min -> left = del -> left;
    min -> right = del -> right;
    delete del;
    
    // if min is a leaf
    // reconnect the tree after the min is gone
    if (minRoot == NULL){
        //cout << "A";
        min -> right = minRight;
    }
    else{
        //cout << "B";
        minRoot -> left = minRight;
    }
    
    return true;
}

bool BinarySearchTree::exists(DataType val) const{
    Node *temp = root_;
    
    while (temp != NULL){
        if (val > temp -> val){
            temp = temp -> right;
        }
        else if (val < temp -> val){
            temp = temp -> left;
        }
        else{
            return true;
        }
    }
    return false;
}

DataType BinarySearchTree::min() const{
    
    Node *temp = root_;
    
    while (temp -> left != NULL){
        temp = temp -> left;
    }
    
    return temp -> val;
}

DataType BinarySearchTree::max() const{
    
    Node *temp = root_;
    
    while (temp -> right != NULL){
        temp = temp -> right;
    }
    
    return temp -> val;
}

unsigned int BinarySearchTree::size() const{
    return size_;
}

unsigned int BinarySearchTree::depth() const{
    return getNodeDepth(root_);
}

int BinarySearchTree::getNodeDepth(Node* n) const{
    if (n-> left == NULL && n-> right == NULL){
        return 0;
    }
    if (n -> left == NULL){
        return 1 + getNodeDepth(n -> right);
    }
    if (n -> right == NULL){
        return 1 + getNodeDepth(n -> left);
    }
    
    int leftDepth = getNodeDepth(n -> left);
    int rightDepth = getNodeDepth(n -> right);
        
    if (leftDepth >= rightDepth){
        return 1 + leftDepth;
    }
    return 1 + rightDepth;
}

void printNode(Node *node){
    
    if (node == NULL){
         return;
    }
    
    printNode(node -> left);
    
    cout << node -> val << " ";
    
    printNode(node -> right);
}

void BinarySearchTree::print() const{
    cout << "[";
    if (root_ == NULL){
        cout << "EMPTY BST";
    }
    else{
        printNode(root_);
    }
    cout << "]";
    cout << endl;
}
