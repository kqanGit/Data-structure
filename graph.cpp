#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#define task "test"
using namespace std;

void init()
{
    freopen(task".in", "r", stdin);
    freopen(task".out", "w", stdout);
}

vector<int> bfs(vector<vector<int>> edge, int n, int start, int destination)
{
    queue<int> q;
    vector<int> path;
    vector<int> visit(n, 0);
    vector<int> parent(n, -1);
    q.push(start);
    visit[start] = true;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u == destination)
        {
            break;
        }

        for (int i = 0; i < edge[u].size(); i++)
        {
            if (visit[edge[u][i]] == false)
            {
                q.push(edge[u][i]);
                visit[edge[u][i]] = true;
                parent[edge[u][i]] = u;
            }
        }
    }

    int vertice = destination;
    while(vertice != -1)
    {
        path.push_back(vertice);
        vertice = parent[vertice];
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<int> dfs(vector<vector<int>> edge, int n, int start, int destination)
{
    stack<int> stack;
    vector<bool> visit(n, false);
    vector<int> parent(n, -1);
    vector<int> path;
    visit[start] = true;
    stack.push(start);
    
    while(!stack.empty())
    {
        int u = stack.top();
        stack.pop();
        visit[u] = true;
        
        for (int i = 0; i < edge[u].size(); i++)
        {
            int v = edge[u][i];
            if (visit[v] == false)
            {
                visit[v] = true;
                stack.push(v);
                parent[v] = u;
            }
        }
    }

    int vertice = destination;
    while(vertice != -1)
    {
        path.push_back(vertice);
        vertice = parent[vertice];
    }
    reverse(path.begin(), path.end());
    return path;
}

void printEdgeList(vector<vector<int>> edge, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << i << " - ";                                        
        for (int j = 0; j < edge[i].size(); j++)
        {
            cout << edge[i][j] << ' ';
        }
        cout << endl;
    }
}
                  
int main()
{
    init();
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edge(n);
    vector<bool> visit(n, 0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    
    // printEdgeList(edge, n);
    vector<int> path = dfs(edge, n, 0, 2);

    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i] << ' ';
    }
}