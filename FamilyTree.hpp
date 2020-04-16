#pragma once

#include <string>
#include<iostream>
using namespace std;


namespace family
{
    class node
    {
        
        public:
        string child;
        node*father;
        node*mother;
        string gender;
        node(string name);

    };
    class Tree
    { 
        private:
            void free_node(node* person);
            node* remove_node_from_tree(node* root, string name);
            node* findRelate(node*n,string relate);
            void displayTree(const std::string& prefix,node*root,bool isLeft);
            int level(node*node,string data,int level);
        public:
            node*root;
            Tree(string name);
            /*add father to the given name in the tree*/
            Tree& addFather(string child, string father);
            /*add mother to the given name in the tree*/
            Tree& addMother(string child, string mother);
            /*displays the tree in a human-friendly format*/
            void display();
            /*returns the relation of given name in the tree
            if the name not found in the tree returns "unrelated"*/
            string relation(string name);
            /*returns who is the "relation" given*/
            string find(string name);
            /*removes the given name from the tree*/
            void remove(string name);
            node* search_name(node* root,string name);
            node* search_name(string name);
    };
};
