#include "headgraph.h"

struct Graph* CreateGraph()
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    CHECK_ERR(graph == NULL, "NOT ENOUGH MEMORY");
    
    graph->numnodes = START_NUMNODES;
    graph->curnumnodes = 0;
    graph->edges = (bool**) calloc(sizeof(bool*), graph->numnodes);
    CHECK_ERR(graph->edges == NULL, "NOT ENOUGH MEMORY");

    for (int idx = 0; idx < graph->numnodes; idx++)
    {
        graph->edges[idx] = (bool*) calloc(sizeof(bool), graph->numnodes);
        CHECK_ERR(graph->edges[idx] == NULL, "NOT ENOUGH MEMORY");
    }

    graph->postorder.base = (int*) calloc(sizeof(int), START_NUMNODES);
    graph->postorder.visited = (int*) calloc(sizeof(int), START_NUMNODES);
    graph->postorder.counter = 0;
    graph->root = 0;
    graph->vertices = (int*) calloc(sizeof(int), START_NUMNODES);
    for (int idx = 0; idx < graph->numnodes; idx++)
    {
        graph->vertices[idx] = POISON;
    }
    return graph;
}

//======================================================

void AddNode(struct Graph* graph, FILE* base, bool testflag)    // if testflag == 1 -> FREE_CELL = 0
{
    CHECK_ERR(graph == NULL, "graph == null");
    int value = 0;
    fscanf(base, "%d", &value);
   
    static int FREE_CELL = 0;
    if (testflag == true)
    {
        FREE_CELL = 0;
    }
    for (int idx = 0; idx < graph->curnumnodes; idx++)
    {
        if (graph->vertices[idx] == value)
        {
            printf("Node with num %d is already exist\n", value);
            return;
        }
    }

    bool flag = false;
    
    for (int idx = 0; idx < FREE_CELL; idx++)
    {
        if (graph->vertices[idx] == POISON)
        {
            graph->vertices[idx] = value;
            flag = true;

            break;
        }
    }
    if (flag == false)
    {
        graph->vertices[FREE_CELL++] = value;
        graph->curnumnodes++;
    }
    if (FREE_CELL >= graph->numnodes)
    {
        ReallocGraph(graph);
    }
}

//================================================================

void AddEdge(struct Graph* graph, FILE* base)
{
    CHECK_ERR(graph == NULL, "graph == null");
    int src  = 0;
    int dest = 0;
    int idx1 = 0;
    int idx2 = 0;
    fscanf(base, "%d%d", &idx1, &idx2);
    src = idx1;
    dest = idx2;
    if (!HasNode(graph, &idx1) || !HasNode(graph, &idx2))
    {
        printf("one vertex doesn't exist to create an edge");
        return;
    }

    if (graph->edges[idx1][idx2] == 1)
    {
        printf("edge from %d to %d is already exist", src, dest);
        return;
    }

    
    graph->edges[idx1][idx2] = 1;
}

//==================================================================
bool HasNode(struct Graph* graph, int* vertice)
{
    CHECK_ERR(graph == NULL, "graph == null");
    for (int idx = 0; idx < graph->curnumnodes; idx++)
    {
        if (graph->vertices[idx] == *vertice)
        {  
            *vertice = idx;
            return true;
        }
    }
    return false;
}

//=====================================================================

void ReallocGraph(struct Graph* graph)
{
    CHECK_ERR(graph == NULL, "graph == null");

    int old_numnodes = graph->numnodes;
    graph->numnodes *= 2;

    for (int idx = 0; idx < old_numnodes; idx++)
    {
        graph->edges[idx] = (bool*) realloc(graph->edges[idx], sizeof(bool) * graph->numnodes);
        CHECK_ERR(graph->edges[idx] == NULL, "NOT ENOUGH MEMORY");
    }

    graph->edges = (bool**) realloc(graph->edges, sizeof(bool*) * graph->numnodes);
    CHECK_ERR(graph->edges == NULL, "NOT ENOUGH MEMORY");

    for (int idx = old_numnodes; idx < graph->numnodes; idx++)
    {
        graph->edges[idx] = (bool*) calloc(sizeof(bool), graph->numnodes);
        CHECK_ERR(graph->edges[idx] == NULL, "NOT ENOUGH MEMORY");
    }
    
    graph->vertices = (int*) realloc(graph->vertices, graph->numnodes);
}

//===================================================================

void RemoveNode(struct Graph* graph, FILE* base)
{
    CHECK_ERR(graph == NULL, "graph == null");
    int value = 0;
    int valuenode = 0;
    fscanf(base, "%d", &value);
    valuenode = value;
    if (!HasNode(graph, &value))
    {
        printf("Node with num %d is not exist", valuenode);
        return;
    }
    int deleteElem= 0; 
    for(deleteElem = 0; deleteElem < graph->curnumnodes; deleteElem++)
    {
        if (graph->vertices[deleteElem] == value)
        {
            graph->vertices[deleteElem] = POISON;
        }
    }
   // graph->curnumnodes--;
    for(int idx = 0; idx < graph->numnodes; idx++)
    {
        graph->edges[idx][deleteElem] = 0;
        graph->edges[deleteElem][idx] = 0;
    }
}

//=======================================================

void RemoveEdge(struct Graph* graph, FILE* base)
{
    CHECK_ERR(graph == NULL, "graph == null");
    int src = 0;
    int dest = 0;
    int idx1 = 0;
    int idx2 = 0;
    fscanf(base, "%d%d", &idx1, &idx2);
    src  = idx1;
    dest = idx2;
    if (!HasNode(graph, &idx1) || !HasNode(graph, &idx2))
    {
        printf("one vertex doesn't exist to delete an edge");
        return;
    }   
    if (graph->edges[idx1][idx2] == 0)
    {
        printf("edge from %d to %d is not exist", src, dest);
        return;
    }
    graph->edges[idx1][idx2] = 0;
}

//=======================================================-

void Root(struct Graph* graph, FILE* base)
{
    CHECK_ERR(graph == NULL, "graph == null");
    int root = 0;   
    fscanf(base, "%d", &root);
    graph->root = root;
}

//=========================================================

void RPO(struct Graph* graph, int curnode)
{
    CHECK_ERR(graph == NULL, "graph == null");
    graph->postorder.visited[graph->postorder.counter++] = curnode;
    for (int idx = 0; idx < graph->curnumnodes; idx++)
    {
        if (!IsVisited(graph, idx) && graph->edges[curnode][idx])
        {
            RPO(graph, idx);
        }
        else if (IsVisited(graph, idx) && graph->edges[curnode][idx])
        {
            printf("found loop %d -> %d\n", graph->vertices[curnode], graph->vertices[idx]);
        }
    }
}

//==================================================

void PrintRPO(struct Graph* graph, FILE* answer)
{
    CHECK_ERR(graph == NULL, "graph == null");
    for (int idx = 0; idx < graph->curnumnodes; idx++)
    {
        fprintf(answer, "%d ", graph->vertices[graph->postorder.visited[idx]]);
    }
  
}

//=============================================

bool IsVisited(struct Graph* graph, int index)
{
    CHECK_ERR(graph == NULL, "graph == null");
    for (int isvisit = 0; isvisit < graph->curnumnodes; isvisit++)
        {
            if (graph->postorder.visited[isvisit] == index)
            {
                return true;
            }
        } 
    return false;
}

//============================================================

void ReadCommands(struct Graph* graph, FILE* base, FILE* answer, bool testflag)
{
    CHECK_ERR(graph == NULL, "graph == null");
    char command[MAX_COMMAND_SIZE] = "";
    fscanf(base, "%s", command);
    while (strcmp("END", command) != 0)
    {
        
        if (strcmp(command, "ADD_NODE") == 0)
        {
            AddNode(graph, base, testflag);
            testflag = false;
        }
        else if (strcmp(command, "ADD_EDGE") == 0)
        {
            AddEdge(graph, base);
        }
        else if (strcmp(command, "REMOVE_NODE") == 0)
        {
            RemoveNode(graph, base);
        }
        else if (strcmp(command, "REMOVE_EDGE") == 0)
        {
            RemoveEdge(graph, base);
        }
        else if (strcmp(command, "ROOT") == 0)
        {
            Root(graph, base);
        }
        else if (strcmp(command, "PRINT_RPO") == 0)
        {
            RPO(graph, graph->root);
            PrintRPO(graph, answer);
        }
        else
        {
            printf("SYNTAX_ERROR");
        }
        fscanf(base, "%s", command);
    }
}

//==========================================================

void PrintGraph(struct Graph* graph)
{
    CHECK_ERR(graph == NULL, "graph == null");
    for (int idx1 = 0; idx1 < graph->curnumnodes; idx1++)
    {
        for (int idx2 = 0; idx2 < graph->curnumnodes; idx2++)
        {
            if (graph->edges[idx1][idx2] == 1)
            {
                printf("%d -> %d\n", graph->vertices[idx1], graph->vertices[idx2]);
            }
        }
    }
}

//================================================================

void Tests(struct Graph* graph, struct Test* test, FILE* base)
{
    base = fopen("tests.txt", "r"); // number of tests is the first number of file
    int numtests = 0;
    fscanf(base, "%d", &numtests);
    for (int idx = 0; idx < numtests; idx++)
    {
        bool testflag = false;
        if (idx > 0)    testflag = true;        // TO MAKE FREE_CELL = 0;

        graph = CreateGraph();
        test->answer = fopen("answer.txt", "w");

        ReadCommands(graph, base, test->answer, testflag); 
        RPO(graph, graph->root);
        PrintRPO(graph, test->answer);
         
        test->programresult = (int*) calloc(graph->curnumnodes, sizeof(int));
        test->neededresult  = (int*) calloc(graph->curnumnodes, sizeof(int));
        fclose(test->answer);

        test->answer = fopen("answer.txt", "r");
        bool result = Verifier(graph, test, base);
        if (result == true)   printf("Test %d successfully completed\n", idx + 1 );
        else                  printf("Test %d failed\n", idx + 1);

        DestroyGraph(graph);
        fclose(test->answer);
        
        free(test->programresult);
        free(test->neededresult);
    }
    fclose(base);
}                      

//=========================================================

bool Verifier(struct Graph* graph, struct Test* test, FILE* base)
{
    for (int idx = 0; idx < graph->curnumnodes; idx++)
    {
        fscanf(test->answer, "%d", &test->programresult[idx]);
    
        fscanf(base, "%d", &test->neededresult[idx]);
        if (test->neededresult[idx] != test->programresult[idx])
        {   
            return false;
        }
    }
    return true;
}
//========================================================

void DestroyGraph(struct Graph* graph)
{
    for (int idx = 0; idx < graph->numnodes; idx++)
    {
        free(graph->edges[idx]);
    }
    free(graph->postorder.base);
    free(graph->postorder.visited);
    free(graph->edges);
    free(graph->vertices);
    free(graph);
}
