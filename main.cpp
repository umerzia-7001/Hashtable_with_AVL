//
// Created by Umer on 04/02/2021.

// Importing requirements
#include <iostream>
#include "HashTable.cpp"
#include "AVL.cpp"
using namespace std;

// Add a name into hashTable
void insert(hashTable avlHashTable){
    string inputData;
    cout << "Enter Data you want to enter:";
    getline(cin, inputData);
    cin.ignore();
    avlHashTable.insert(inputData);

}
// delete name from hashTable
void deleteName(hashTable avlHashTable) {
    string inputData;
    cout << "Enter Data you want to remove:";
    getline(cin, inputData);
    cin.ignore();
    avlHashTable.deleteName(inputData);
}


int main() {
    int option;
    bool again = true;

    cout << "Populating..." << endl;
    // put path to text file here
    hashTable table("/Users/apple/Downloads/NamesToHash.txt");

    while (again) {
        cout << "\nSelect Option from below:\n"
                "1. Insert\n"
                "2. Remove\n"
                "3. Print Pre-Order\n"
                "4. Print In-Order\n"
                "5. Print Post-Order\n"
                "6. Exit\n"
                "Enter Option >> ";
        cin >> option;
        cin.ignore();
        switch (option) {
            case 1:
                insert(table);
                break;
            case 2:
                deleteName(table);
                break;
            case 3:
                table.preOrder();
                break;
            case 4:
                table.InOrder();
                break;
            case 5:
                table.postOrder();
                break;
            case 6:
                again = false;
                break;
            default:
                cout << "Select correct option(1-6)" << endl;
                continue;
        }
    }
};

// end