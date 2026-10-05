#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node{
    int val;
    struct Node * next;
}node;

typedef struct graph{
    int v;
    node ** arr;
}graph;

node * addNode(int data){
    // printf("    in addNode %d\n", data);
    node * new;
    new= malloc(sizeof(node));
    new->val= data;
    new->next= NULL;
    return new;
}

bool addEdge(graph * g, int src, int dest){
    // printf("in addEdge %d %d\n", src, dest);
    node *myNode;
    myNode= addNode(src);
    if(!myNode) return false;
    myNode->next = g->arr[dest];
    g->arr[dest] = myNode;
    // printf("in addedge going to dest node %d\n", dest);
    myNode= addNode(dest);
    if(!myNode) return false;
    myNode->next = g->arr[src];
    g->arr[src] = myNode;
    return true;
}

void printGraph( graph *g){
    node *temp;
    // printf("in printing\n");
    for(int i=0; i<g->v; i++){
        temp= g->arr[i];
        while(temp){
            printf("%d ", temp->val);
            temp= temp->next;
        }
        printf("\n");
    }
}

int main(){
    graph * g;
    int size;
    size = 5;
    g= malloc(sizeof(graph));
    g->v= size;
    g->arr= calloc(size, sizeof(node *));
    // printf("graph is initialised\n");
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 4, 3);
    addEdge(g, 0, 4);
    printGraph(g);
}