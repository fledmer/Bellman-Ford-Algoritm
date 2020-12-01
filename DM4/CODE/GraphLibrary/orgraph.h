#ifndef ORGRAPH_H
#include "graph.h"
#define ORGRAPH_H


class Orgraph:public Graph
{
    string LoseConnectCotegory();
public:

    void Push(string fVert, string sVert, int weight);
    void Push(string fVert, string sVert);
     //Дочерние функции для анализа
    void pMatrixOfIncidence();
    int EdgeCount();
    void pMaximumDegree();
    string virtual ConnectCotegory();
     //Дочерние функции для анализа
};

#endif // ORGRAPH_H
