#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


#define CHECK_ERR(condition, message_error)           \
                do{                                    \
                        if (condition){                 \
                            printf("%s", message_error); \
                        }                                 \
                } while(0)


const int START_NUMNODES   = 8;
const int POISON           = -2281337;
const int MAX_COMMAND_SIZE = 15;
struct PostOrder
{
    int* visited;
    int* base;
    int counter;
};
struct Graph
{
    
    int* vertices;
    int numnodes;       // max amount of nodes not to do reallocation
    int curnumnodes; // current amount of nodes 
    bool** edges;       // adjacency matrix
    int root;
    struct PostOrder postorder;
};

struct Test
{
    FILE* answer;
    int* neededresult;
    int* programresult;
};
struct Graph* CreateGraph();
void AddNode(struct Graph* graph, FILE* base, bool testflag);
void AddEdge(struct Graph* graph, FILE* base);
bool HasNode(struct Graph* graph, int* vertice);
void ReallocGraph(struct Graph* graph);
void RemoveNode(struct Graph* graph, FILE* base);
void RemoveEdge(struct Graph* graph, FILE* base);
void Root(struct Graph* graph, FILE* base);
void RPO(struct Graph* graph, int curnode);
void PrintRPO(struct Graph* graph, FILE* answer);
bool IsVisited(struct Graph* graph, int index);
void ReadCommands(struct Graph* grph, FILE* base, FILE* answer, bool testflag);
void PrintGraph(struct Graph* graph);
void Tests(struct Graph* graph, struct Test* test, FILE* base);
bool Verifier(struct Graph* graph, struct Test* test, FILE* base);
void DestroyGraph(struct Graph* graph);
