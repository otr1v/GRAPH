#include "headgraph.h"

int main()
{
    struct Graph* graph = CreateGraph();
    
    ReadCommands(graph, stdin, stdout);
    DestroyGraph(graph);

    return 0;
}
