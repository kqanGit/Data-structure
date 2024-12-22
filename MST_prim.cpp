#include <iostream>
#include <vector>
#include <queue>
#define task "test"
#define fi first 
#define se second
using namespace std;
const int INF = 1e9 + 7;
void init()
{
    freopen(task".in", "r", stdin);
    freopen(task".out", "w", stdout);
}

struct Edge
{
    int w;
    int u;
    int v;
};

struct cmp
{
    bool operator() (Edge a, Edge b)
    {
        return a.w > b.w;
    }
};

vector<pair<int, int>> prim(vector<vector<pair<int, int>>> edge, int n)
{
    int start = 0;
    priority_queue<Edge, vector<Edge>, cmp> queue;
    vector<bool> visit(n, 0);
    vector<int> d(n, INF);
    vector<pair<int, int>> res;

    d[start] = 0;
    queue.push({d[start], start, start});
    
    while(!queue.empty())
    {
        int w = queue.top().w;
        int u = queue.top().v;
        int k = queue.top().u;
        queue.pop();
        
        if (visit[u] == true)
        {
            continue;
        }
        
        visit[u] = true;
        if (u != start)
        {
            res.push_back({k, u});
        }

        for (int i = 0; i < edge[u].size(); i++)
        {
            int v = edge[u][i].fi;
            int c = edge[u][i].se;
            if (d[v] > c)
            {
                d[v] = c;
                queue.push({d[v], u, v});
            }
        }
    }
    return res;
} 

int main()
{
    init();
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> edge(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].push_back({v, w});
    }

    vector<pair<int, int>> res = prim(edge, n);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i].fi << ' ' << res[i].se << endl;
    }
}