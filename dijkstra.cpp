#include <iostream>
#include <vector>
#include <queue>
#define task "test"
using namespace std;
const int INF = 1e9 + 7;

void init()
{
    freopen(task".in", "r", stdin);
    freopen(task".out", "w", stdout);
}

struct Edge
{
    int v;
    int w;
};

struct Node
{
    int u;
    int dist;
};

struct cmp
{
    bool operator() (Node a, Node b)
    {
        return a.dist > b.dist;
    }
};

vector<int> reverse(vector<int> a)
{
    vector<int> res(a.size());
    for (int i = a.size() - 1; i >= 0; i--)
    {
        res[a.size() - i - 1] = a[i];
    }
    return res;
}

void dijkstra(vector<vector<Edge>> edge, int n, vector<int>& d, vector<int>& trace, int start)
{
    priority_queue<Node, vector<Node>, cmp> queue;
    vector<int> p(n, 0);
    d[start] = 0;
    queue.push({start, d[start]});

    while(!queue.empty())
    {
        Node x = queue.top();
        queue.pop();
        int u = x.u;
        if (p[u] == true)
        {
            continue;
        }
        p[u] = true;
        for (int i = 0; i < edge[u].size(); i++)
        {
            int v = edge[u][i].v;
            int w = edge[u][i].w;
            if (d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                queue.push({v, d[v]});
                trace[v] = u;
            }
        }
    }
}

vector<int> traceBack(vector<int> trace, int start, int end)
{
    int curr = end;
    vector<int> res;
    while(curr != -1)
    {
        res.push_back(curr);
        curr = trace[curr];
    }

    res = reverse(res);
    return res;
}


int main()
{
    init();
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> edge(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].push_back({v, w});
    }
    
    vector<int> d(n, INF);
    vector<int> trace(n, -1);
    dijkstra(edge, n, d, trace, 4);
    vector<int> path = traceBack(trace, 4, 3);
    for (int i : path)
    {
        cout << i << ' ';
    }
    cout << endl;
    cout << d[4];
}