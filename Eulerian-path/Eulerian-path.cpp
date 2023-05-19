#include<iostream>
#include <list>
using namespace std;

//ненаправленный граф
class Graph
{
    int V;    
    list<int>* adj;    // массив смежных вершин
public:
    // констурктор и деструктор 
    Graph(int V) { this->V = V; adj = new list<int>[V]; }
    ~Graph() { delete[] adj; }

    // добавление ребра 
    void addEdge(int v, int w);

    // эйлеров граф или нет 
    int isEulerian();

    // если вершины соединены 
    bool isConnected();

    // Поиск в глубину начиная с V. 
    void DFSUtil(int v, bool visited[]);
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // граф ненаправленный 
}

void Graph::DFSUtil(int v, bool visited[])
{
    // отмечаем вершину как пройденную 
    visited[v] = true;

    // рассматриваем все вершины смежные с нашей 
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// проверка что ненулевые вершины соединены 
// обход поиск в глубину 
bool Graph::isConnected()
{
    // отмечаем все вершины что ещё не посещены 
    bool *visited= new bool [V];
    int i;
    for (i = 0; i < V; i++)
        visited[i] = false;

    // ищем не нулевую вершину 
    for (i = 0; i < V; i++)
        if (adj[i].size() != 0)
            break;

    // если нет ребёр то true 
    if (i == V)
        return true;

    // обход в глубину начиная с ненулевой вершины 
    DFSUtil(i, visited);

    //проверяем что все ненулевые вершины пройденны 
    for (i = 0; i < V; i++)
        if (visited[i] == false && adj[i].size() > 0)
            return false;

    return true;
}


int Graph::isEulerian()
{
    // проверяем что ненулевые вершины соединены 
    if (isConnected() == false)
        return 0;

    // считаем нечетные вершины 
    int odd = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1)
            odd++;

    // больше 2 значит не эйлеров 
    if (odd > 2)
        return 0;

    // 2 полу эйлеров .
    // 0 эйлеров 
    // никогда не 1 потому не направленный граф 
    return (odd) ? 1 : 2;
}


void test(Graph& g)
{
    int res = g.isEulerian();
    if (res == 0)
        cout << "graph is not Eulerian\n";
    else if (res == 1)
        cout << "graph has is Semi-Eulerian\n";
    else
        cout << "graph has a Euler cycle\n";
}


int main()
{
    
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    test(g1);

    Graph g2(5);
    g2.addEdge(1, 0);
    g2.addEdge(0, 2);
    g2.addEdge(2, 1);
    g2.addEdge(0, 3);
    g2.addEdge(3, 4);
    g2.addEdge(4, 0);
    test(g2);

    Graph g3(5);
    g3.addEdge(1, 0);
    g3.addEdge(0, 2);
    g3.addEdge(2, 1);
    g3.addEdge(0, 3);
    g3.addEdge(3, 4);
    g3.addEdge(1, 3);
    test(g3);

    
    Graph g4(3);
    g4.addEdge(0, 1);
    g4.addEdge(1, 2);
    g4.addEdge(2, 0);
    test(g4);

    
    Graph g5(3);
    test(g5);

    return 0;
}