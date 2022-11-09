//https://courses.fortlewis.edu/courses/25275/assignments/422414
#include<iostream>
#include <cstdarg>

const int MAXCONNECTIONS = 5;
struct Node{
    Node *connected[MAXCONNECTIONS] = {NULL}; //initialize a set of nodes that can be connected
    int weights[MAXCONNECTIONS] = {0}; //initialize a set of weights to tie to the connections
    std::string name;
};

class Graph{
    private:
        Node* curent = NULL; //track the last used node so you can't lose the graph so easy
        int adjacentIndex=0;
       
        void addAdjacentcy(Node* node1, Node* node2){
            adjacent[adjacentIndex][0] = node1;
            adjacent[adjacentIndex][1] = node2;
            adjacentIndex++;
        }
    public:
        Node* adjacent[MAXCONNECTIONS*10][2] = {0}; // adjacenty list
        int adjacentSize(){
            return adjacentIndex;
        }
        void insertNode(int *weight, int numArgs, ...){ //if someone can think of a better way to attach connections and weights then it is welcome
            if(numArgs>=MAXCONNECTIONS){ //Check to make sure that this node can be supported
                    std::cout<<"overflow on number of connections allowed ("<<MAXCONNECTIONS<<")"<<std::endl;
                    return;
                }
            va_list valist; // enables the input of multiple arguments
            Node *new_node = new Node; // creates the new node
            va_start(valist,numArgs); // initializes the iterator for the variable arguments
            Node *temp; //holds the curent variable argument
            for(int i=0;i<numArgs;i++){

                temp = va_arg(valist,Node*); //sets the curent variable argument
                new_node->connected[i] = temp; //add the connection to the new node
                new_node->weights[i] = weight[i]; // add the weight to the connection
                addAdjacentcy(new_node,temp); // updates the adjacency list
                for(int j=0;j<MAXCONNECTIONS;j++){ // add the connection to the attached node for double connection 
                    if(temp->connected[j]==NULL){
                        temp->connected[j] = new_node;
                        temp->weights[j] = weight[i];
                    break;
                    }
                }
            }
            va_end(valist); // deconstruct the variable argument array
            curent = new_node; //update the curent node
        }

        Node* get_curent(){
            return curent;
        }
        

};

main(){
    int weights[MAXCONNECTIONS]={6,4,5,6,7};
    Graph graphy;
    //check for inserting a new node
    graphy.insertNode(0,0);
    std::cout<<"first: "<<graphy.get_curent()<< " weight: "<< graphy.get_curent()->weights[0] << std::endl;
    Node *first = graphy.get_curent();
    std::cout << "Connection check:" << ((first->connected[0]==NULL) ? "Success":"Fail") << std::endl;
    
    //check for attaching a node to the previous node
    graphy.insertNode(weights,1,first);
    std::cout<<"second: "<<graphy.get_curent() << " weight: "<< graphy.get_curent()->weights[0] << std::endl;
    std::cout << "Connection check:" << ((graphy.get_curent()->connected[0]==first) ? "Success":"Fail") << std::endl;
    
    //check for attaching a node to both the previous nodes
    Node *second = graphy.get_curent();
    weights[0] = 5;
    weights[1] = 4;
    graphy.insertNode(weights,2,first,graphy.get_curent());
    std::cout<<"third: "<<graphy.get_curent() << " weight: "<< graphy.get_curent()->weights[0] << ", " << graphy.get_curent()->weights[1] << std::endl;
    std::cout << "Connection check:" << ((graphy.get_curent()->connected[0]==first)&(graphy.get_curent()->connected[1]==second) ? "Success":"Fail") << std::endl;
    
    //adjacentcy
    std::cout<<"adjacentcy list" << std::endl;
    for(int i=0;i<graphy.adjacentSize();i++){
        std::cout << graphy.adjacent[i][0] << "-" << graphy.adjacent[i][1] << ", ";
    }

    return 0;
}