#pragma once

#include <string>
#include<iostream>
using namespace std;


namespace family
{
    class node
    {
        public:
        string name;
        node*father;
        node*mother;
        node(string name);

    };
    class Tree
    { 
        public:
            node*root;
            Tree(string name);
            /*add father to the given name in the tree*/
            Tree& addFather(string name, string father);
            /*add mother to the given name in the tree*/
            Tree& addMother(string name, string mother);
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
