//https://courses.fortlewis.edu/courses/25275/assignments/422414
#include<iostream>
#include <cstdarg>

const int MAXCONNECTIONS = 5;
struct Node{
    Node *connected[MAXCONNECTIONS] = {NULL,NULL,NULL,NULL,NULL};
    int weight;
};

class Graph{
    private:
        Node* curent;
    public:
        Graph(){
            curent = NULL;
        }
        void insertNode(int weight, int numArgs, ...){
            va_list valist;
            Node *new_node = new Node;
            new_node->weight = weight;
            va_start(valist,numArgs);
            Node *temp;
            for(int i=0;i<numArgs;i++){
                if(i>=MAXCONNECTIONS){
                    std::cout<<"overflow on number of connections allowed ("<<MAXCONNECTIONS<<")"<<std::endl;
                    break;
                }
                temp = va_arg(valist,Node*);
                new_node->connected[i] = temp;
                for(int i=0;i<MAXCONNECTIONS;i++){
                    if(temp->connected[i]==NULL){
                        temp->connected[i] = new_node;
                    break;
                    }
                    }
            }
            va_end(valist);
            curent = new_node;
        }
        Node* get_curent(){
            return curent;
        }

};

main(){
    Graph graphy;
    graphy.insertNode(5,0);
    std::cout<<"first: "<<graphy.get_curent()<< " weight: "<< graphy.get_curent()->weight << std::endl;
    Node *head = graphy.get_curent();
    std::cout << "Connection check:" << ((head->connected[0]==NULL) ? "Success":"Fail") << std::endl;
    graphy.insertNode(6,1,head);
    std::cout<<"second: "<<graphy.get_curent() << " weight: "<< graphy.get_curent()->weight << std::endl;
    std::cout << "Connection check:" << ((graphy.get_curent()->connected[0]==head) ? "Success":"Fail") << std::endl;
    return 0;
}