#include "FamilyTree.hpp"



using namespace family;

Tree::Tree(string name){}
Tree& Tree::addFather(string name, string father){return *this;}
Tree& Tree::addMother(string name, string mother){return *this;}
void display(){}
string relation(string name){return " ";}
string find(string name){return " ";}
void remove(string name){}