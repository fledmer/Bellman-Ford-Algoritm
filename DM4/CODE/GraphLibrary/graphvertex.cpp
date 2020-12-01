#include "graphvertex.h"
#include <string>
#include <algorithm>

GraphVertex::GraphVertex(std::string name)
{
    this->name = name;
}

GraphVertex* GraphVertex::Find(GraphVertex *Vert)
{
    for(auto x: child)
    {
        if(Vert->name == x->name)
        {
            return x;
        }
    }
    return NULL;
}

GraphVertex* GraphVertex::Find(std::string name)
{
    for(auto x: child)
    {
        if(x->name == name)
        {
            return x;
        }
    }
    return NULL;
}

void GraphVertex::Push(GraphVertex *Vert)
{
    if(!Find(Vert)) //Проверяем имеет ли наша верншина связь с новой
        child.push_back(Vert); // если не имеет, то добавляем новую
}

void GraphVertex::Push(std::string name)
{
    if(!Find(name)) //Проверяем имеет ли наша верншина связь с новой
    {
        GraphVertex *Vert = new GraphVertex(name);
         child.push_back(Vert); // если не имеет, то добавляем новую
    }
}

void GraphVertex::Push(GraphVertex *Vert, int weight)
{
    if(!Find(name)) //Проверяем имеет ли наша верншина связь с новой
    {
         child.push_back(Vert); // если не имеет, то добавляем новую
         edge_weight.push_back(weight); // И добавляем ей вес.
    }
}
