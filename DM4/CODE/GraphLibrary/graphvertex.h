#ifndef GRAPHVERTEX_H
#include <string>
#include <vector>
#include <iostream>
#define GRAPHVERTEX_H

class GraphVertex
{
public:
    GraphVertex(std::string name);
    ~GraphVertex(){};
    std::string name;
    int number;
    std::vector <GraphVertex *> child; // вершины связанные с данной.
    std::vector <int> edge_weight;
    void Push(GraphVertex *Vert);
    void Push(std::string name);
    void Push(std::string name,int weight);
    void Push(GraphVertex *Vert,int weight);
    GraphVertex* Find(GraphVertex *Vert);
    GraphVertex* Find(std::string name);

};

#endif // GRAPHVERTEX_H
