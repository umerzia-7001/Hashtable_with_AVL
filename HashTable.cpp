//
// Created by Umer on 04/02/2021.

// Importing requirements
#ifndef AVL_AVL_cpp
#define AVL_AVL_cpp
#include <algorithm>
#include <fstream>
#include <iostream>
// importing AVL
#include "AVL.cpp"
using namespace std;

// hashtable class
class hashTable{
    // declaring hashtable of buckets 8
    AVL_Tree<string>* hashArr[8];
    int count;
    int load;

private:

public:
    // constructor
    hashTable(string path){
        for(int i=0;i<=8;i++){
            hashArr[i]=new AVL_Tree<string>();// initializing hashTable with nodes of AVL type
        }
        count=0;
        load=12;    // load= Items/no buckets
        if (path != "")
            populate(path); // filling AVL with data
    }
    // Add data into specific place in hashTable
    void insert(const string name){
        // getting hash value for the name
        int position =hash(name);
        while(true){
            hashArr[position]->InsertNode(name);// // avl Insert node function
            count++;
            break;
        }

    }
    // printing elements of hashtable : Postorder
    void postOrder() {
        for (int i = 0; i < 8; i++) {
            cout << "HashTable[ " << i << " ] => {";
            hashArr[i]->PostOrderTraversal();
            cout << "}\n\n";
        }
    }
    // printing elements of hashtable : Inorder
    void InOrder() {
        for (int i = 0; i < 8; i++) {
            cout << "HashTable[ " << i << " ] => {";
            hashArr[i]->InOrderTraversal();
            cout << "}\n\n";
        }
    }
    // printing elements of hashtable : preorder
    void preOrder() {
        for (int i = 0; i < 8; i++) {
            cout << "HashTable[ " << i << " ] => {";
            hashArr[i]->PreOrderTraversal();
            cout << "}\n\n";
        }
    }

    // hash function
    int hash(const string name ){
        int index= name[0];
        return index & 7;
        // ASCII value of first digit 4 bits
    }

    // populate AVL with data
    void populate(string pathToFile) {
        if(pathToFile==""){
            cout<<"incorrect file path"<<endl;// if no path entered
        }
        string line;// read line by line text file
        ifstream dict_file(pathToFile);

        while (getline(dict_file, line)) {
            insert(line);
        }

        dict_file.close();
    }

    // deleting data
    void deleteName(string name){
        int hashpos = hash(name);
        while(true){
            hashArr[hashpos]->remove(name);// avl remove function
            count--;
        }
    }
};
#endif