//https://courses.fortlewis.edu/courses/25275/assignments/422414
#include<iostream>
#include <cstdarg>

const int MAXCONNECTIONS = 5;
struct Node{
    Node *connected[MAXCONNECTIONS] = {NULL,NULL,NULL,NULL,NULL};
    int weights[MAXCONNECTIONS] = {0,0,0,0,0};
};

class Graph{
    private:
        Node* curent;
    public:
        Graph(){
            curent = NULL;
        }
        void insertNode(int *weight, int numArgs, ...){
            va_list valist;
            Node *new_node = new Node;
            va_start(valist,numArgs);
            Node *temp;
            for(int i=0;i<numArgs;i++){
                if(i>=MAXCONNECTIONS){
                    std::cout<<"overflow on number of connections allowed ("<<MAXCONNECTIONS<<")"<<std::endl;
                    break;
                }
                temp = va_arg(valist,Node*);
                new_node->connected[i] = temp;
                new_node->weights[i] = weight[i];
                for(int j=0;j<MAXCONNECTIONS;j++){
                    if(temp->connected[j]==NULL){
                        temp->connected[j] = new_node;
                        temp->weights[j] = weight[i];
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
    int weights[MAXCONNECTIONS]={6};
    Graph graphy;
    graphy.insertNode(0,0);
    std::cout<<"first: "<<graphy.get_curent()<< " weight: "<< graphy.get_curent()->weights[0] << std::endl;
    Node *head = graphy.get_curent();
    std::cout << "Connection check:" << ((head->connected[0]==NULL) ? "Success":"Fail") << std::endl;
    graphy.insertNode(weights,1,head);
    std::cout<<"second: "<<graphy.get_curent() << " weight: "<< graphy.get_curent()->weights[0] << std::endl;
    std::cout << "Connection check:" << ((graphy.get_curent()->connected[0]==head) ? "Success":"Fail") << std::endl;
    weights[0] = 5;
    weights[1] = 4;
    graphy.insertNode(weights,2,head,graphy.get_curent());
    std::cout<<"third: "<<graphy.get_curent() << " weight: "<< graphy.get_curent()->weights[0] << ", " << graphy.get_curent()->weights[1] << std::endl;
    std::cout << "Connection check:" << ((graphy.get_curent()->connected[0]==head) ? "Success":"Fail") << std::endl;
    return 0;
}