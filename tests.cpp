#include "headgraph.h"

int main()
{
    struct Graph* graph = NULL;

    struct Test* test = (struct Test*) malloc(sizeof(struct Test));
    FILE* base = NULL;
    Tests(graph, test, base);
    free(test);
    return 0;
}
