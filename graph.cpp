#include "headgraph.h"
int main()
{
    struct Graph* graph = CreateGraph();
    ReadCommands(graph, stdin, stdout, 0);
    DestroyGraph(graph);

    return 0;
}
