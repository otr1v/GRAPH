#pragma once
#include <stdio.h>

const int AMOUNT_OF_NODES = 10;
struct node
{
    int value;
};

struct edge
{
    node* src;
    node* dest;
};

struct graph
{
    struct edge head[AMOUNT_OF_NODES];
};

void AddNode(struct node base[]);
void AddEdge(struct graph grph);
int ReadCommands();
// typedef struct node
// {
//     char*        text;
//     struct node* left;
//     struct node* right;
// }Node;
