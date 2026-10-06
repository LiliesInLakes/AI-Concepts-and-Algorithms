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

void destroyEdge(graph * g, int src, int dest){
    // printf("in addEdge %d %d\n", src, dest);
    node *temp;
    node *b4temp;
    b4temp= g->arr[src];
    if(b4temp->val!= dest){
        temp= b4temp->next;
        while(temp->val!= dest){
            temp= temp->next;
            b4temp= b4temp->next;
        }
        // node *node2del;
        // node2del= temp;
        b4temp->next= temp->next;
        free(temp);
    }
    else{
        g->arr[src]= b4temp->next;
        free(b4temp);
    }
    

    b4temp= g->arr[dest];
    if(b4temp->val!= src){
        temp= b4temp->next;
        while(temp->val!= src){
            temp= temp->next;
            b4temp= b4temp->next;
        }
        b4temp->next= temp->next;
        free(temp);
    }
    else{
        g->arr[dest]= b4temp->next;
        free(b4temp);
    }
}

void bfs(graph* g, int size, int startVertice){
    int start=0, end=0;
    int *visited, *q;
    node *temp;
    q = malloc(sizeof(int)*size*(size+1)/2);
    visited= malloc(sizeof(int)*size);
    q[end++]=  startVertice;
    while(end>start){
        if(!visited[q[start]]){
            visited[q[start]]=1;
            printf("%d", q[start]);
            start++;
            temp= g->arr[q[start]];
            while(temp){
                if(!visited[temp->val])
                    q[end++]= temp->val;
                temp= temp->next;
            }
        }
    }
}

void dfs(graph* g, int size, int startVertice){
    int top=0;
    int *visited, *q;
    node *temp;
    q = malloc(sizeof(int)*size*(size+1)/2);
    visited= malloc(sizeof(int)*size);
    q[top++]= startVertice;
    while(top){
        if(!visited[q[top-1]]){
            top-=1;
            printf("%d ", q[top]);
            visited[q[top]]=1;
            temp= g->arr[q[top]];
            while(temp){
                if(!visited[temp->val])
                    q[top++]= temp->val;
                temp= temp->next;
            }
        }
        // else{
        //     top-=1;
        //     printf("%d ", q[top]);
        // }
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
    addEdge(g, 3, 0);
    addEdge(g, 0, 4);
    printGraph(g);
    // printf("going in destroy\n");
    // destroyEdge(g, 0, 4);
    // destroyEdge(g, 3, 1);
    // printGraph(g);

    bfs(g, size, 0);
    printf("\n");
    dfs(g, size, 0);
}