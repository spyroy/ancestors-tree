#include <string>
using namespace std;


namespace family{
    struct Node
    {
        string data; 
        struct Node* father, *mother;  
    };
    class Tree
    { 
       private:
        Node root;
       public: 
        /*constructor*/
        Tree(string name){
            root.data = name;
            root.father = NULL;
            root.mother = NULL;
        }
        /*add father to the given name in the tree*/
        Tree addFather(string name, string father){return Tree(" ");}
        /*add mother to the given name in the tree*/
        Tree addMother(string name, string mother){return Tree("");}
        /*displays the tree in a human-friendly format*/
        void display(){;}
        /*returns the relation of given name in the tree
        if the name not found in the tree returns "unrelated"*/
        string relation(string name){return "";}
        /*returns who is the "relation" given*/
        string find(string name){return "";}
        /*removes the given name from the tree*/
        void remove(string name){}
    };
};
