#include <iostream>
#include <GraphLibrary/graph.h>
#include <GraphLibrary/orgraph.h>

using namespace std;

int main()
{
    cout << "Hello, Work Made by Mikhalev N. 2012" << endl << endl;
    cout << endl;
    Orgraph* orgraph = new Orgraph();
    orgraph->Input();
    orgraph->Analysis();
    string end;
    cin >> end;
    return 0;
}
