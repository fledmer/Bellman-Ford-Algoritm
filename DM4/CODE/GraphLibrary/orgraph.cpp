#include "orgraph.h"
#include "graphvertex.h"
#include <iostream>

void Orgraph::Push(string fVert, string sVert)
{
    if(!Find(fVert)) //Проверяем наличие 1 вершины в графе
    {
        GraphVertex *Vert1 = new GraphVertex(fVert);
        Vert1->number = this->GraphsVertex.size()-1;
        GraphsVertex.push_back(Vert1); // Добавляем если не нашли
    }
    if(!Find(sVert))//Проверяем наличие 2 вершины в графе
    {
        GraphVertex *Vert2 = new GraphVertex(sVert);
        Vert2->number = this->GraphsVertex.size()-1;
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
        Vert1->number = this->GraphsVertex.size();
        GraphsVertex.push_back(Vert1); // Добавляем если не нашли
    }
    if(!Find(sVert))//Проверяем наличие 2 вершины в графе
    {
        GraphVertex *Vert2 = new GraphVertex(sVert);
        Vert2->number = this->GraphsVertex.size();
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

const int infinity = 10000;
bool negative_weight_find = false;
bool infinity_weight_find = false;

vector<int> Orgraph::FindShortestPath(int start_vertex)
{
    vector<int> path (GraphsVertex.size(),infinity);
    path[start_vertex] = 0;
    bool negative_weight_find = false;
    for(int i = 0; i < GraphsVertex.size()-1;++i)
    {
            for(int vertex = 0; vertex < GraphsVertex.size();++vertex)    //Идем по вершинам, чтоб найти ребра
            {
                GraphVertex *start = GraphsVertex[vertex];
                for(int edge = 0; edge < start->child.size(); ++edge)
                {
                    if(path[vertex] >= infinity)    break;
                    int edge_weight = start->edge_weight[edge];
                    if(edge_weight < 0)    negative_weight_find = true;
                    GraphVertex *end = start->child[edge];
                    path[end->number] = std::min(path[end->number],path[start->number] + edge_weight);
                    //cout << path[end->number] << "   " << path[start->number] + edge_weight << endl;

                }
            }
    }
    return path;
}

void Orgraph::pAllSortestPath()
{
    cout << " ";
    for(int x = 0; x < GraphsVertex.size();++x)
    {
        cout << " " <<GraphsVertex[x]->name;
    }
    cout << endl;
    for(int vertex_start = 0; vertex_start < GraphsVertex.size(); ++vertex_start)
    {
        cout << GraphsVertex[vertex_start]->name << " ";
        for(int x: FindShortestPath(vertex_start))
        {
            if(x == infinity)
            {
               cout << "I ";
               infinity_weight_find = true;
            }
            else
            {
                cout << x << " ";
            }
        }
        cout << endl;
    }
    if(negative_weight_find) cout << endl << "ATTENTION NAGATIVE WEIGHT WAS FOUNDED" << endl;
    if(infinity_weight_find) cout << endl << "ATTENTION INFINITY WEIGHT WAS FOUNDED" << endl;
}
//Дочернии функции оценки орграфа


void Orgraph::Analysis() //Производит анализ и его вывод.
{
    pMatrixOfIncidence();
    cout << endl;
    cout<< "Vertex: " << GraphsVertex.size() << " Arc: " << EdgeCount() << " Loop: " << LoopCount() << endl;
    cout << endl;
    pMaximumDegree();
    cout << endl;
    cout << ConnectCotegory() << endl;
    cout << endl;
    pAllSortestPath();
}
