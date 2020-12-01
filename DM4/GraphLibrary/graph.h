#ifndef GRAPH_H
#include <vector>
#include <string>
#include "graphvertex.h"
#define GRAPH_H

using namespace std;

class Graph
{
protected:

    //Дочернии функции для анализа
    void FindHamiltoniaCycle(GraphVertex *vertex,vector<string> name_of_passed_vertex);
    void virtual pMatrixOfIncidence();
    int virtual EdgeCount();
    int LoopCount();
    void virtual pMaximumDegree();
    bool FindPath(GraphVertex *start, GraphVertex *end,vector<string> storage);
    bool FindPath(vector<GraphVertex *> GraphsVertex, GraphVertex *start, GraphVertex *end,vector<string> storage);
    void PrintHamiltonianCycles();
    //Дочернии функции для анализа
public:
    Graph(){};
    ~Graph()
    {
        ClearGraphsVertex();
    }
    vector<GraphVertex *> GraphsVertex; // Вершины графа
    int HamiltonianCycleCount = 0;
    void virtual Push(string fVert, string sVert);
    void virtual Push(string fVert, string sVert,int weight);
    void virtual Push(string Vert);
    string virtual ConnectCotegory();

    //Основные функции
    void Input();
    void Analysis();
    GraphVertex* Find(string name);
    GraphVertex* Find(GraphVertex *Vert);
    //Основные функции
    void ClearGraphsVertex();

};

#endif // GRAPH_H
