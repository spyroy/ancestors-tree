#include <string>
#include<iostream>
using namespace std;


namespace family
{
    class Tree
    { 
        public:
            string value;
            Tree *father,*mother;
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
    };
};
