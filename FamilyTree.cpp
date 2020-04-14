#include "FamilyTree.hpp"

using namespace family;

Tree::Tree(string name)
{
    value=name;
    father=mother=NULL;
}
Tree& Tree::addFather(string child,string father)
{
    if(value=="" || value==child)
    {
        *this->father=father;
        return *this;
    }
    //Searching for the child (temp root - can be in left side or right side) - Finding reference to the relevant "node"
    if(*this->father!=NULL)
        return this->father->addFather(child,father);
    if(value!="")
        return this->mother->addFather(child,father);
    
}
Tree& Tree::addMother(string child,string mother){return *this;}
string Tree::relation(string name){return "";}
string Tree::find(string name)
{
    return "";
}

void Tree::display(){}
void Tree::remove(string name){}