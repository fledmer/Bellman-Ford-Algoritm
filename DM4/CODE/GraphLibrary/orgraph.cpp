#include "orgraph.h"
#include "graphvertex.h"
#include <iostream>

void Orgraph::Push(string fVert, string sVert)
{
    if(!Find(fVert)) //Проверяем наличие 1 вершины в графе
    {
        GraphVertex *Vert1 = new GraphVertex(fVert);
        GraphsVertex.push_back(Vert1); // Добавляем если не нашли
    }
    if(!Find(sVert))//Проверяем наличие 2 вершины в графе
    {
        GraphVertex *Vert2 = new GraphVertex(sVert);
        GraphsVertex.push_back(Vert2); // Добавляем если не нашли
    }
    auto fvert = Find(fVert);
    auto svert = Find(sVert);
    fvert->Push(svert); //Добавляем связь вершин.
}

void Orgraph::Push(string fVert, string sVert, int weight)
{
    if(!Find(fVert)) //Проверяем наличие 1 вершины в графе
    {
        GraphVertex *Vert1 = new GraphVertex(fVert);
        GraphsVertex.push_back(Vert1); // Добавляем если не нашли
    }
    if(!Find(sVert))//Проверяем наличие 2 вершины в графе
    {
        GraphVertex *Vert2 = new GraphVertex(sVert);
        GraphsVertex.push_back(Vert2); // Добавляем если не нашли
    }
    GraphVertex *fvert = Find(fVert);
    GraphVertex *svert = Find(sVert);
    fvert->Push(svert,weight); //Добавляем связь вершин.
}

//Дочернии функции оценки орграфа
void Orgraph::pMatrixOfIncidence()
{
    vector<vector<string>> Matrix;
    for(int i = 0; i < GraphsVertex.size();i++)   //Заполняем матрицу.
    {
        for(int _i = 0; _i < GraphsVertex.size();_i++)
        {
            if(GraphsVertex[i]->Find(GraphsVertex[_i]))
            {
                vector<string> arr(GraphsVertex.size());
                for(int c = 0; c < GraphsVertex.size(); c++)
                    arr[c] = "0";
                arr[i] = "-1";
                arr[_i] = "1";
                arr.push_back(GraphsVertex[i]->name + "-" + GraphsVertex[_i]->name);
                Matrix.push_back(arr);
            }
        }
    }
     cout << endl;
    for(int i = 0; i < GraphsVertex.size();i++)
    {
        cout << "  "<< GraphsVertex[i]->name;
    }
    cout << endl;
    for(int i = 0; i < Matrix.size();i++)
    {
        for(int _i = 0; _i < Matrix[i].size();_i++)
        {
            if(Matrix[i][_i] != "-1")
            cout << "  " << Matrix[i][_i];
            else
            cout << " " << Matrix[i][_i];
        }
        cout << endl;
    }
}

int Orgraph::EdgeCount()
{
    int edgeCount = 0;
    for(auto vertex : GraphsVertex)
    {
        for(auto child_vertex : vertex->child )
            edgeCount++;
    }
    return edgeCount;
}

string Orgraph::LoseConnectCotegory()
{
    Graph *graph = new Graph(); //Строим граф на основе орграфа
    for(auto vertex : GraphsVertex)
    {
        graph->Push(vertex->name); //Переносим  вершины
        for(auto child_vert : vertex->child)
        {
            graph->Push(vertex->name,child_vert->name); //Переносим ребра
        }
    }
    string cotegory = graph->ConnectCotegory(); // Проверяем его свзяность
    delete(graph); //Удаляем граф
    if(cotegory == "Connected")
    {
        return "\nWeakly connected ";
    }
    return "\n NonConnected";
}

string Orgraph::ConnectCotegory()
{
    bool Coherent = true;
    for(int i = 0; i < GraphsVertex.size(); i++)
    {
        for(int _i = 0; _i < GraphsVertex.size();_i++)
        {
            if(i!=_i)
            {
                vector<string> m; //Контейнер для избежания зацикливаний при поиске нужной вершины.
                if(!FindPath(GraphsVertex[i],GraphsVertex[_i],m))   //Если не нашли путь от a к b, то ищем от b к a
                {
                    if(!FindPath(GraphsVertex[_i],GraphsVertex[i],m)) //Если и он не найдее, будем строить и исследовать граф
                    {
                        return LoseConnectCotegory();
                    }
                    Coherent -= Coherent;   // Если хоть 1 путь не найден, то связь не сильная.
                }
            }
        }
    }
    if(Coherent)
        return "Connected";
    return "One-way connected";
}

void Orgraph::pMaximumDegree()
{
    int maximumDegreeOUT = 0;
    string nameOUT = "";
    int maximumDegreeIN = 0;
    string nameIN = "";
    for(auto vertex : GraphsVertex)
    {
        if(vertex->child.size() > maximumDegreeOUT) //Ищем максимальную степень по выходам
        {
            maximumDegreeOUT = vertex->child.size();
            nameOUT = vertex->name;
        }

        int count_of_in_degree = 0;
        for(auto altvertex : GraphsVertex)//Ищем максимальную степень по заходам
        {
            if(altvertex->Find(vertex))
                count_of_in_degree++;
        }
        if(count_of_in_degree > maximumDegreeIN)
        {
            maximumDegreeIN = count_of_in_degree;
            nameIN = vertex->name;
        }
    }
    cout <<"Maximum Degree IN: " <<maximumDegreeOUT << " Name: " << nameOUT << endl;
    cout <<"Maximum Degree OUT: " <<maximumDegreeIN << " Name: " << nameIN << endl;
}
//Дочернии функции оценки орграфа
