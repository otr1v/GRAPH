#include "headgraph.h"
// int ConstructNode()
// {

// }
void AddNode(struct node base[])
{
    int value = 0;
    scanf("%d", &value);

    for (int idx = 0; idx < AMOUNT_OF_NODES; idx++)
    {
        if (base[idx].value == value)
        {
            printf("Node with num %d is already exist", value);
            break;
        }
    }
    
    static int FREE_CELL = 0;
    //base[FREE_CELL++] = (node) malloc()
    base[FREE_CELL++].value = value;
}

void AddEdge(struct graph grph)
{
    int src = 0;
    int dest = 0;
    scanf("%d%d", &src, &dest);
    static int FREE_SPACE = 0;
    grph.head[FREE_SPACE].src->value  = src;
    grph.head[FREE_SPACE].dest->value = dest;
    FREE_SPACE++;
}
int ReadCommands()
{
    
}