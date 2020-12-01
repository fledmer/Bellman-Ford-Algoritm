#ifndef ORGRAPH_H
#include "graph.h"
#include <vector>
#define ORGRAPH_H

class Orgraph:public Graph
{
    string LoseConnectCotegory();
    //Дочерние функции для анализа
   void pMatrixOfIncidence();
   int EdgeCount();
   void pMaximumDegree();
   string ConnectCotegory();
   void pAllSortestPath();
   std::vector<int> FindShortestPath(int start_vertex);
    //Дочерние функции для анализа
public:
   void Push(string fVert, string sVert, int weight);
   void Push(string fVert, string sVert);
    void Analysis();
};

#endif // ORGRAPH_H
