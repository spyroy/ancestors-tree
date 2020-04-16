#include "FamilyTree.hpp"

using namespace family;


node::node(string name)
{
    this->child=name;
    this->father=this->mother=nullptr;
    this->gender="";
}
Tree::Tree(string name)
{
    this->root=new node(name);
}
/*----------------------------------*/
//Search section
node* Tree::search_name(string name)
{
    return search_name(this->root,name);
}
node* Tree::search_name(node* root,string name)
{
    if(root==NULL)
        return nullptr;
    if(root->child.compare(name)==0)
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
/*----------------------------------*/

/*----------------------------------*/
//Add section

Tree& Tree::addFather(string child,string father)
{
    node* node_child=search_name(child);
    if(node_child==nullptr)//If the given name does not exist in the tree
        throw("The tree doesn't contain the name: %s",child);
    if(node_child->father==NULL)//If the given name exists, but has no father - add the new father
    {
        node_child->father=new node(father);
        node_child->father->gender="male"; 
        return *this;
    }
    else
        throw("%s already has a father, his name is: %s",child,node_child->father->child);
}
Tree& Tree::addMother(string child,string mother)
{
    node* node_child=search_name(child);
    if(node_child==nullptr)//If the given name does not exist in the tree
        throw("The tree doesn't contain the name: %s",child);
    if(node_child->mother==NULL)//If the given name exists, but has no mother - add the new mother
    {
        node_child->mother=new node(mother);
        node_child->mother->gender="female";
        return *this; 
    }
    else
        throw("%s already has a mother, her name is: %s",child,node_child->mother->child);
}




/*----------------------------------*/
//Relation section

//Source: GeeksForGeeks
int Tree::level(node*root,string data,int level)
{
    if(root==NULL)
        return 0;
    if(root->child.compare(data)==0)
        return level;
    
    int down=Tree::level(root->mother,data,level+1);
    if(down!=0)
        return down;
    
    //Else, we need to return level of father
    down=Tree::level(root->father,data,level+1);
    return down;
}

string Tree::relation(string name)//Return relation of the given name, starting from the root of the tree
{
    if(search_name(name)==NULL);
        return "unrelated";
    
    if(this==NULL)
        return NULL;
    
    else
    {
        int level=Tree::level(this->root,name,1);
        node*found=search_name(name);
        if(level!=1&&found!=NULL)
            return "me";
        
        if(found->gender=="male")
        {
            if(level==2)
                return "father";
            if(level==3)
                return "grandfather";

            //If we reached here, we need to count great---> ...great grand
            string ans="grandfather";
            for(int i=0;i<level-3;++i)
                ans.insert(0,"great-");
            return ans;
        }

        else if(found->gender=="female")
        {
            if(level==2)
                return "mother";
            if(level==3)
                return "grandmother";

            //If we reached here, we need to count great---> ...great grand
            string ans="grandmother";
            for(int i=0;i<level-3;++i)
                ans.insert(0,"great-");
            return ans;
        }

    }
    return "unrelated";
    
}
node* Tree::findRelate(node*root,string relate)
{
    if(root==NULL)
        return NULL;
    if(Tree::relation(root->child).compare(relate)==0)
        return root;
    
    node* mother_side=findRelate(root->mother,relate);
    node* father_side=findRelate(root->father,relate);

    if(mother_side!=NULL)
        return mother_side;
    if(father_side!=NULL)
        return father_side;
    return NULL;

}
string Tree::find(string name)
{
    //need to return relation
    if(this==NULL)
        return "NULL";
    node* found=findRelate(this->root,name);
    if(found==NULL)
        throw("There is no relation: "+name);
    return found->child;
}


/*----------------------------------*/
//Displaying tree
//Source: Stackoverflow
void Tree::displayTree(const std::string& prefix,node*node,bool isLeft)
{
    if( node != nullptr )
    {
        cout << prefix;
        cout << (isLeft ? "├──" : "└──" );
        cout << node->child << endl;
        displayTree( prefix + (isLeft ? "│   " : "    "), node->mother, true);
        displayTree( prefix + (isLeft ? "│   " : "    "), node->father, false);
    }
}
void Tree::display()
{
    displayTree("",this->root,false);
}


/*----------------------------------*/
//Remove node section

void free_node(node* person)
{
    if(person==NULL)
        return;
    if(person->father==NULL&&person->mother==NULL)
        delete(person);
    free_node(person->father);
    free_node(person->mother);
}
node* remove_node_from_tree(node* root, string name)
{
    if(root==NULL)
        return NULL;
    if(root->child.compare(name)==0)//Found the relevant person - and it's the temporary root
    {
        free_node(root);
        return NULL;
    }
    root->father=remove_node_from_tree(root->father,name);
    root->mother=remove_node_from_tree(root->mother,name);
    return root;
    
}
void Tree::remove(string name)
{
    this->root=remove_node_from_tree(this->root,name);
}
/*----------------------------------*/
