//
// Created by Umer on 04/02/2021.

// Importing requirements
#ifndef AVL_AVL
#define AVL_AVL
#include <iostream>
using namespace std;

// using template for generic data type for AVL
template<typename T>
class AVL_Node{
public:
    string data;    // string data
    AVL_Node<T> *leftChild;
    AVL_Node<T> *rightChild;
    int height;

};

template<typename T>
class AVL_Tree{

    // check if AVL is empty
    bool IsEmpty(){
        return root==NULL;
    }
    //  ***     ---     ---     ---     ---     ---      ---    ***
    // functions for rotating left, right for AVL nodes
    AVL_Node<T> *LeftRotate(AVL_Node<T> *x){
        cout<<"Rotating node "<<x->data<<endl;
        AVL_Node<T> *temp = x->rightChild;
        AVL_Node<T> *temp2 = temp->leftChild;

        temp->leftChild=x;
        x->rightChild=temp2;

        x->height= (1+max(Height(x->leftChild),Height(x->rightChild)));
        temp->height = (1+max(Height(temp->leftChild),Height(temp->rightChild)));
        cout<<"Returning node "<<temp->data<<endl;
        return temp;
    }
    AVL_Node<T> * RightRotate(AVL_Node<T> *x){
        cout<<"Rotating node "<<x->data<<endl;
        AVL_Node<T> *temp = x->leftChild;
        AVL_Node<T> *temp2 = temp->rightChild;

        temp->rightChild = x;
        x->leftChild = temp2;

        x->height=(1+max(Height(x->leftChild),Height(x->rightChild)));
        temp->height=(1+max(Height(temp->leftChild),Height(temp->rightChild)));
        cout<<"Returning node "<<temp->data<<endl;
        return temp;
    }
    AVL_Node<T> *RightLeftRotate(AVL_Node<T> *x){
        AVL_Node<T> *temp=x;
        x->rightChild = RightRotate(x->rightChild);
        return LeftRotate(temp);
    }
    AVL_Node<T> *LeftRightRotate(AVL_Node<T> *x){
        AVL_Node<T> *temp=x;
        x->leftChild = LeftRotate(x->leftChild);
        return RightRotate(temp);
    }

    //  ***     ---     ---     ---     ---     ---      ---    ***

    AVL_Node<T>* findMin(AVL_Node<T>*x){
        if(x == NULL)
            return NULL;
        else if(x->leftChild == NULL)
            return x;
        else
            return findMin(x->leftChild);
    }
    // using given node with value to add it in avl
    AVL_Node<T> *insert(T value,AVL_Node<T> *node){
        if(node==NULL){
            node = new AVL_Node<T>();
            node->data=value;
            node->height=0;
            node->leftChild=node->rightChild=NULL;

        }else if(value <= node->data){
            node->leftChild=insert(value,node->leftChild);
            int balance = BalanceFactor(node);
            //cout<<balance<<endl;
            if(balance == 2){
                if(value<=node->leftChild->data){
                    node = RightRotate(node);
                }else{
                    node = LeftRightRotate(node);
                }
            }

        }else if(value > node->data){
            node->rightChild=insert(value,node->rightChild);
            int balance = BalanceFactor(node);
            //cout<<balance<<endl;
            if(balance==-2){
                if(value>node->rightChild->data){
                    node = LeftRotate(node);
                }else{
                    node = RightLeftRotate(node);
                }
            }
        }

        node->height=max(Height(node->leftChild),Height(node->rightChild));
        return node;

    }

public:
    AVL_Tree<T>(){
        root=NULL;
    }
    AVL_Node<T> *root=NULL;
    void DeleteNode(T value){
        root = remove(value,root);
    }

    int Height(AVL_Node<T> *node){  // getting the height of AVL
        if (node == NULL){
            return 0;
        }
        return (node->height);
    }

    int HeightOfTree(AVL_Node<T> *treeNode){
        if(treeNode == NULL){
            return -1;
        }else{  // height function
            return 1+max(HeightOfTree(treeNode->leftChild),HeightOfTree(treeNode->rightChild));
        }
    }
    // getting balance, if balance>1 or balance<-1 we rotate the child nodes
    int BalanceFactor(AVL_Node<T> *node){
        if (node == NULL){
            return 0;
        }
        return (HeightOfTree(node->leftChild)-HeightOfTree(node->rightChild));
    }

    int remove(string word){
        root = remove(word,root);
        return root->height;

    }
    // deleting node with data
    AVL_Node<T>* remove(T value,AVL_Node<T> *node){
        AVL_Node<T>* temp=NULL;

        if(node == NULL){
            return NULL;
        }

        else if(value < node->data){
            node->leftChild = remove(value, node->leftChild);
        }

        else if(value > node->data){
            node->rightChild = remove(value, node->rightChild);
        }

        else if(node->leftChild && node->rightChild){
            temp = findMin(node->rightChild);
            node->data = temp->data;
            node->rightChild = remove(node->data, node->rightChild);
        }

        else{
            temp = node;
            if(node->leftChild == NULL){
                node = node->rightChild;
            }

            else if(node->rightChild == NULL){
                node = node->leftChild;
            }

            delete temp;
        }
        if(node == NULL){
            return node;
        }

        node->height = max(Height(node->leftChild), Height(node->rightChild))+1;

        // If node is unbalanced left node is deleted, right case
        if(Height(node->leftChild) - Height(node->rightChild) == -2)
        {

            if(Height(node->rightChild->rightChild) - Height(node->rightChild->leftChild) == 1){
                return LeftRotate(node);
            }
            else{
                return LeftRightRotate(node);
            }

        }
            // If right node is deleted, left case
        else if(Height(node->rightChild) - Height(node->leftChild) == 2)
        {

            if(Height(node->leftChild->leftChild) - Height(node->leftChild->rightChild) == 1){
                return RightRotate(node);
            }
            else{
                return RightLeftRotate(node);
            }

        }
        return node;
    }
    // Inserting node and data
    void InsertNode(T value){
        cout<<"Inserting "<<value<<endl;
        root = insert(value,root);
    }
    //  ***     ---     ---     ---     ---     ---      ---    ***

    // Transversals for AVL
    void PreOrderTraversal(){
        PreOrderTraversal(root);
    }

    void PreOrderTraversal(AVL_Node<T> *root){
        if(root!=NULL){
            cout<<root->data<<endl;
            PreOrderTraversal(root->leftChild);
            PreOrderTraversal(root->rightChild);
        }
    }
    void InOrderTraversal(){
        InOrderTraversal(root);
    }
    void InOrderTraversal(AVL_Node<T> *root){
        if(root!=NULL){
            InOrderTraversal(root->leftChild);
            cout<<root->data<<endl;
            InOrderTraversal(root->rightChild);
        }
    }
    void PostOrderTraversal(){
        PostOrderTraversal(root);
    }
    void PostOrderTraversal(AVL_Node<T> *root){
        if(root!=NULL){
            PostOrderTraversal(root->leftChild);
            PostOrderTraversal(root->rightChild);
            cout<<root->data<<endl;
        }
    }
    void RunnerFunction(){// for filling and testing the avl
        for(int i=0;i<50;i++){
            InsertNode(rand()%100);
        }
    }
};
#endif