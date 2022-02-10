#include "graph.h"
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <queue>

std::vector<Arc> Graph::GetArce()
{
    return arce;
}

std::vector<Node> Graph::GetNoduri()
{
    return noduri;
}


void Graph::AddNod(Node n)
{
    n.setNumber(noduri.size());
    noduri.push_back(n);
}

void Graph::AddArc(Arc n)
{
    for(auto index:arce)
    {
        if(index.getFirstPoint().getNumber()==n.getFirstPoint().getNumber()&&index.getSecondPoint().getNumber()==n.getSecondPoint().getNumber())
        {
            return;
           }
    }
    arce.push_back(n);
}
void Graph::topologicalSortVerif(int nod, bool visited[], std::stack<int>& stack)
{

    visited[nod] = true;

    std::list<int>::iterator i;
    for (i = adj[nod].begin(); i != adj[nod].end(); ++i)
        if (!visited[*i])
            topologicalSortVerif(*i, visited, stack);
    stack.push(nod);
}
bool Graph::hasCycleVerif(int nod, bool visited[], bool* recStack)
{
    if (visited[nod] == false)
    {
        visited[nod] = true;
        recStack[nod] = true;
        std::list<int>::iterator i;
        for (i = adj[nod].begin(); i != adj[nod].end(); ++i)
        {
            if (!visited[*i] && hasCycleVerif(*i, visited, recStack))
                return true;
            else if (recStack[*i])
                return true;
        }

    }
    recStack[nod] = false;
    return false;
}


bool Graph::hasCycle()
{
    int nr=getNumberofNodes();
    bool* visited = new bool[nr];
    bool* recStack = new bool[nr];
    for (int i = 0; i < nr; i++)
    {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < nr; i++)
        if (hasCycleVerif(i, visited, recStack))
            return true;

    return false;
}

void Graph::topologicalSort(std::vector<int>&topo)
{
    std::stack<int> stack;
    int nr=getNumberofNodes();
    bool* visited = new bool[nr];
    for (int index2 = 0; index2 < nr; index2++)
        visited[index2] = false;

    for (int index = 0; index < nr; index++)
        if (visited[index] == false)
            topologicalSortVerif(index, visited, stack);

    while (stack.empty() == false) {
        topo.push_back(stack.top());
        stack.pop();
    }
}

/*void Graph::ListaAdiacenta()
{
        listaAdiacenta.reserve(noduri.size());
        for(int i=0;i<noduri.size();i++)
            lista[i].reserve(noduri.size());
        for(auto& arc: arce)
        {
            int i,j;
            i=arc.getFirstPoint().getNumber();
            j=arc.getSecondPoint().getNumber();
            lista[i].push_back(j);
        }

}
*/


Node Graph::GetLastNode()
{
    return noduri[noduri.size()-1];
}

int Graph::getNumberofNodes()
{
    return noduri.size();
}

void Graph::setNrOfNodes(int x)
{
    nr_noduri=x;
}

/*void Graph::readAdjList(QFile& f,std::vector<std::vector<int>> arce_int)
{
    QString number;
        QTextStream in(&f);
        in >> number;
        int matSize = number.toInt();
        while (!in.atEnd()) {
            QString line = in.readLine();
            if(!line.isEmpty()){
                QStringList numsStr = line.split(" ");
                for(int i(0); i < 2; ++i){
                        arce_int[numsStr[i].toInt()]=numsStr[i+1].toInt();
                        break;
                    }
                }
            }
}
*/
void Graph::GenerareMatriceAdiacenta()
{

}

void Graph::GenerareListaAdiacenta()
{
    listaAdiacenta=GetArce();

}

