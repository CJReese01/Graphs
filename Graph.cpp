//https://courses.fortlewis.edu/courses/25275/assignments/422414
#include<iostream>
#include <cstdarg>
#include <stack>

const int MAXCONNECTIONS = 5;
struct Node{
    Node *connected[MAXCONNECTIONS] = {NULL}; //initialize a set of nodes that can be connected
    int weights[MAXCONNECTIONS] = {0}; //initialize a set of weights to tie to the connections
    std::string name;
    int index;
};

class Graph{
    private:
        Node* curent = NULL; //track the last used node so you can't lose the graph so easy
        int nodeIndex=0;
       
    public:
        Node *nodes[MAXCONNECTIONS*5];
        int nodeSize(){
            return nodeIndex;
        }

        void addEdge(Node *node1, Node *node2, int weight){
            for(int i=0;i<MAXCONNECTIONS;i++){ // add the connection to the attached node for double connection 
                if(node1->connected[i]==NULL){
                    node1->connected[i] = node2;
                    node1->weights[i] = weight;
                break;
                }
            }
            for(int i=0;i<MAXCONNECTIONS;i++){ // add the connection to the attached node for double connection 
                if(node2->connected[i]==NULL){
                    node2->connected[i] = node1;
                    node2->weights[i] = weight;
                break;
                }
            }
        }
        void modifyEdge(Node *node1, Node *node2, int weight){
            for(int i=0;i<MAXCONNECTIONS;i++){ // add the connection to the attached node for double connection 
                if(node1->connected[i]==node2){
                    node1->weights[i] = weight;
                break;
                }
            }
            for(int i=0;i<MAXCONNECTIONS;i++){ // add the connection to the attached node for double connection 
                if(node2->connected[i]==node1){
                    node2->weights[i] = weight;
                break;
                }
            }
        }
        void removeEdge(Node *node1, Node *node2){
            int index = 0;
            for(;index<MAXCONNECTIONS;index++){ // add the connection to the attached node for double connection 
                if(node1->connected[index]==NULL){
                    break;
                }
            }
            for(;index<MAXCONNECTIONS-1;index++){ // add the connection to the attached node for double connection 
                node1->connected[index] = node1->connected[index+1];
            }
            index = 0;
            for(;index<MAXCONNECTIONS;index++){ // add the connection to the attached node for double connection 
                if(node2->connected[index]==NULL){
                    break;
                }
            }
            for(;index<MAXCONNECTIONS-1;index++){ // add the connection to the attached node for double connection 
                node2->connected[index] = node2->connected[index+1];
            }
        }

        void addNode(std::string name){
            Node *new_node = new Node;
            new_node->name = name;
            nodes[nodeIndex] = new_node;
            new_node->index=nodeIndex;
            nodeIndex++;
            curent = new_node;
        }

        void insertNode(std::string name, int *weight, int numArgs, ...){ //if someone can think of a better way to attach connections and weights then it is welcome
            if(numArgs>=MAXCONNECTIONS){ //Check to make sure that this node can be supported
                    std::cout<<"overflow on number of connections allowed ("<<MAXCONNECTIONS<<")"<<std::endl;
                    return;
                }
            va_list valist; // enables the input of multiple arguments
            Node *new_node = new Node; // creates the new node
            
            // addNode() here posssibly? I see the same function here
            new_node->name = name;
            nodes[nodeIndex]=new_node;
            new_node->index=nodeIndex;
            nodeIndex++;
            va_start(valist,numArgs); // initializes the iterator for the variable arguments
            Node *temp; //holds the curent variable argument
            for(int i=0;i<numArgs;i++){
                temp = va_arg(valist,Node*); //sets the curent variable argument
                addEdge(new_node,temp,weight[i]);
            }
            va_end(valist); // deconstruct the variable argument array
            curent = new_node; //update the curent node
        }
        
        void removeNode(Node *node){
            int index=0;
            for(;index<nodeIndex;index++){
                if(nodes[index]==node)
                    break;
                if(index==nodeIndex-1)
                    return;
            }
            nodeIndex--;
            for(;index<nodeIndex;index++){
                nodes[index]=nodes[index+1];
                node[index].index=index;
            }
            for(int i=0;i<MAXCONNECTIONS;i++){ // add the connection to the attached node for double connection 
                if(node->connected[i] != NULL){
                    curent = node->connected[i];
                    for(int j=0;j<MAXCONNECTIONS;j++){
                        if(node->connected[i]->connected[j]==node){
                                node->connected[i]->connected[j] = NULL;
                                node->connected[i]->weights[j] = 0;
                                break;
                        }
                    }
                }
            }
            delete node;
        }

        Node* get_curent(){
            return curent;
        }
        void display(){
            for(int i=0;i<nodeSize();i++){
                std::cout << nodes[i]->name << ", ";
                for(int j=0; j<MAXCONNECTIONS;j++){
                    if(nodes[i]->connected[j]==NULL)
                        break;
                    std::cout << nodes[i]->connected[j]->name << "-" << nodes[i]->weights[j] << ", ";
                }
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
        }

        std::stack<Node*> DFS(Node *node1, Node *node2){
            std::stack<Node*> path;
            bool visited[nodeIndex] = {false};
            path.push(node1);
            visited[node1->index]=true;
            while(path.top()!=node2){
                for(int i=0; i<MAXCONNECTIONS; i++){
                    if(path.top()->connected[i]==NULL){
                        path.pop();
                        break;
                    }
                    if(visited[path.top()->connected[i]->index]==true){
                        continue;
                    }
                    else{
                        path.push(path.top()->connected[i]);
                        break;
                    }
                    
                }
            }
            return path;
        }
};

main(){
    int weights[MAXCONNECTIONS]={6,4,5,6,7};
    Graph graphy;
    //check for inserting a new node
    graphy.addNode("Durango");
    std::cout<<"first: "<<graphy.get_curent()->name << " weight: "<< graphy.get_curent()->weights[0] << std::endl;
    std::cout << "Connection check:" << ((graphy.nodes[0]->connected[0]==NULL) ? "Success":"Fail") << std::endl;
    
    //check for attaching a node to the previous node
    graphy.addNode("Farmington");
    graphy.addEdge(graphy.nodes[0],graphy.nodes[1],3);
    std::cout<<"second: "<<graphy.get_curent()->name << " weight: "<< graphy.get_curent()->weights[0] << std::endl;
    std::cout << "Connection check:" << ((graphy.get_curent()->connected[0]==graphy.nodes[0]) ? "Success":"Fail") << std::endl;
    
    //check for attaching a node to both the previous nodes
    graphy.insertNode("Aztec",weights,2,graphy.nodes[0],graphy.get_curent());

    graphy.display();
    std::stack<Node*> path = graphy.DFS(graphy.nodes[0],graphy.nodes[2]);
    while(!path.empty()){
        std::cout<<path.top()->name<<std::endl;
        path.pop();
    }
    std::cout<<std::endl;

    graphy.removeNode(graphy.get_curent());
    std::cout<<"Remove Aztec"<<std::endl;
    graphy.display();
    return 0;
}
