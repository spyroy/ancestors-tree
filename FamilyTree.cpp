#include "FamilyTree.hpp"

using namespace family;


node::node(string name)
{
    this->name=name;
    this->father=this->mother=nullptr;
}
Tree::Tree(string name)
{
    this->root=new node(name);
}
node* Tree::search_name(string name)
{
    return search_name(this->root,name);
}
node* Tree::search_name(node* root,string name)
{
    if(root==NULL)
        return nullptr;
    if(root->name.compare(name)==0)
        return root;
    //Else - return the first one to find
    node* result_from_fatherSide=search_name(root->father,name);
    if(result_from_fatherSide!=nullptr)
        return result_from_fatherSide;
    node* result_from_motherSide=search_name(root->mother,name);
    if(result_from_motherSide!=nullptr)
        return result_from_motherSide;
    
    //If we reached here - the name is not found
    return nullptr;

}
Tree& Tree::addFather(string child,string father)
{
    node* node_child=search_name(child);
    if(node_child!=nullptr)
        node_child->father=new node(father);
    
    return *this;
    
}
Tree& Tree::addMother(string child,string mother)
{
    node* node_child=search_name(child);
    if(node_child!=nullptr)
        node_child->mother=new node(mother);
    
    return *this;
}
string Tree::relation(string name)
{
    return "";
}
string Tree::find(string name)
{
    //need to return relation
    return "";
}

void Tree::display()
{

}
void Tree::remove(string name)
{

}