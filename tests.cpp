#include "headgraph.h"

int main()
{
    struct Graph* graph = {};

    struct Test* test = (struct Test*) malloc(sizeof(struct Test));
    FILE* base = {};
    Tests(graph, test, base);
    free(test);
    return 0;
}
