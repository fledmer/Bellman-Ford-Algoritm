#include "graph.h"
#include "graphvertex.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


GraphVertex* Graph::Find(string name)
{
    for(auto x : GraphsVertex)
    {
        if(x->name == name)
        {
            return x;
        }
    }
    return NULL;
}
GraphVertex* Graph::Find(GraphVertex *Vert)
{
    for(auto x : GraphsVertex)
    {
        if(x->name == Vert->name)
        {
            return x;
        }
    }
    return NULL;
}

void Graph::ClearGraphsVertex()
{
    for(int i = GraphsVertex.size()-1;i >= 0;i--)
    {
        delete(GraphsVertex[i]);    //Удаляем вершины из памяти
        GraphsVertex.pop_back(); //Удаляем вершины из вектора
    }
}

void Graph::Push(string fVert, string sVert)
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
    svert->Push(fvert); //Добавляем связь вершин.
}
void Graph::Push(string Vert)
{
    if(!Find(Vert))
    {
        GraphVertex *nVert = new GraphVertex(Vert);
        GraphsVertex.push_back(nVert); // Если вершины нет в графе, добавяем
    }
}

void Graph::Push(string Vert1, string Vert2, int weight)
{
    return;
}

void Graph::Input() //Отвечает за ПОЛНЫЙ ввод данных.
{
    string input;
    cout << "List the connections of the graph, like this: A-B:5. Or simply: A.\n Where A,B vertices and 5 is weight " << endl;
    do // Начало ввода
    {
        string first_arg = "";
        string second_arg = "";
        string sweight = "";    //представление числа в виде строки
        input = "";
        int position = 0;
        int weight = -1;
        getline(cin,input);
        while(input[position] && input[position] != '-' )
        {
            first_arg+= input[position];
            position++;
        }
        while(input[position] && input[position] != ':')
        {
            second_arg+= input[position];
            position++;
        }
        second_arg = second_arg.erase(0,1);
        while(input[position])
        {
            sweight+= input[position];
            position++;
        }
        sweight = sweight.erase(0,1);
        weight = atoi(sweight.c_str());

        if(first_arg == "" && second_arg != "")
            Push(second_arg);
        else if(first_arg != "" && second_arg == "")
            Push(first_arg);
        else if(first_arg != "" && second_arg != "" && sweight != "" )
            Push(first_arg,second_arg,weight);
        else
            cout << "Incorrect input" << endl;
    }while(input != ""); //Конец ввода

    for(GraphVertex *x : GraphsVertex)
    {
        cout << x->name << ": ";
        string output = "";
        for(GraphVertex *t : x->child)
        {
           output += (t->name + ",");
        }
        if(output != "")
            output = output.erase(output.size()-1,1);
        cout <<  output << endl;
    }
}
void Graph::Analysis() //Производит анализ и его вывод.
{
    pMatrixOfIncidence();
    cout << endl;
    cout<< "Vertex: " << GraphsVertex.size() << " Arc: " << EdgeCount() << " Loop: " << LoopCount() << endl;
    cout << endl;
    pMaximumDegree();
    cout << endl;
    cout << ConnectCotegory() << endl;
}

//Дочернии функции оценки графа
void Graph::pMatrixOfIncidence()
{
    vector<vector<string>> Matrix;
    for(int i = 0; i < GraphsVertex.size();i++)   //Заполняем матрицу.
    {
        for(int _i = i; _i < GraphsVertex.size();_i++)
        {
            if(GraphsVertex[i]->Find(GraphsVertex[_i]))
            {
                vector<string> arr(GraphsVertex.size());
                for(int c = 0; c < GraphsVertex.size(); c++)
                    arr[c] = "0";
                arr[i] = "1";
                arr[_i] = "1";
                arr.push_back(GraphsVertex[i]->name + "-" + GraphsVertex[_i]->name);
                Matrix.push_back(arr);
            }
        }
    }
     cout << endl;
    for(int i = 0; i < GraphsVertex.size();i++)
    {
        cout << " "<< GraphsVertex[i]->name;
    }
    cout << endl;
    for(int i = 0; i < Matrix.size();i++)
    {
        for(int _i = 0; _i < Matrix[i].size();_i++)
        {
           cout << " " << Matrix[i][_i];
        }
        cout << endl;
    }
}

int Graph::EdgeCount()
{
    int edgeCount;
    for(auto vertex : GraphsVertex)
    {
        for(auto child_vertex : vertex->child )
            edgeCount++;
    }
    return edgeCount/2;
}

int Graph::LoopCount()
{
    int loopCout = 0;
    for(auto vertex : GraphsVertex)
    {
        for(auto child_vertex : vertex->child)
        {
            if(child_vertex->name == vertex->name)
                loopCout++;
        }
    }
    return loopCout;
}

void Graph::pMaximumDegree()
{
    int maximumDegree = 0;
    string name = "";
    for(auto vertex : GraphsVertex)
    {
        if(vertex->child.size() > maximumDegree)
        {
            maximumDegree = vertex->child.size();
            name = vertex->name;
        }
    }
    cout <<"Maximum Degree: " << maximumDegree << " Name: " << name << endl;
}

bool Graph::FindPath(GraphVertex *start, GraphVertex *end,vector<string> storage)
{
    if(start->name == end->name)
    {
        return true;
    }
    storage.push_back(start->name);
    for(int i = 0;i < start->child.size();i++)
    {
        GraphVertex *u = start ->child[i];
        if(find(storage.begin(),storage.end(),u->name) == storage.end())
        {
                if(FindPath(u,end,storage))
                    return true;
        }
    }
    return false;

}

string Graph::ConnectCotegory()
{
    for(int i = 0; i < GraphsVertex.size();i++)
    {
        for(int _i = 0; _i < GraphsVertex.size();_i++)
        {
            if(i!=_i)
            {
                vector<string> m;
                if(!FindPath(GraphsVertex[i],GraphsVertex[_i],m))
                    return "NonConnected";
            }
        }
    }
    return "Connected";
}
//Дочернии функции оценки графа


void Graph::FindHamiltoniaCycle(GraphVertex *vertex,vector<string>  name_of_passed_vertex)
{
        name_of_passed_vertex.push_back(vertex->name);
        if(name_of_passed_vertex.size() == GraphsVertex.size()) //Если все вершины обошли, то закругляемся
        {
            if(find(vertex->child.begin(),vertex->child.end(),GraphsVertex[0])
                                == vertex->child.end()) //Если финальная вершина не содержит путь
                return;                                                              //к начальной вершине, то цикл не найден.

            HamiltonianCycleCount++;
            for(string name : name_of_passed_vertex)
            {
                cout << name << " -> ";
            }
            cout << GraphsVertex[0]->name << endl; //Закрываем цикл a->b->c->a
            return;
        }

        for(int i = 0; i < vertex->child.size();i++)
        {
            if( find(name_of_passed_vertex.begin(),name_of_passed_vertex.end(),vertex->child[i]->name)
                    == name_of_passed_vertex.end())
            {
                FindHamiltoniaCycle(vertex->child[i],name_of_passed_vertex);
            }
        }

        return;
}

void Graph::PrintHamiltonianCycles()
{

    cout << endl << "Hamiltonian cycles: " << endl << endl;
    vector<string> name_of_passed_vertex;
    FindHamiltoniaCycle(GraphsVertex[0],name_of_passed_vertex);
    cout << endl;
    cout << "Count of Hamiltonian Cycle: " << HamiltonianCycleCount << endl;
    if(!HamiltonianCycleCount)
         cout << "No Hamiltonian cycles found" << endl;
}
