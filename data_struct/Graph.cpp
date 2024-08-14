#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// O(|E| + |V|) = O(so canh + so dinh)
void bfs(long long s, vector<bool> &visited, vector<vector<long long>> &road)
{
    queue <long long> q;
    q.push(s);
    while (!q.empty())
    {
        long long u = q.front();
        q.pop();
        visited[u] = true;
        // Sth here
        for (auto v : road[u])
            if (!visited[v])
                q.push(v);
    }
}

// O(|E| + |V|) = O(so canh + so dinh)
void dfs(long long u, vector<bool> &visited, vector<vector<long long>> &road){
    // Sth here
    visited[u] = 1;
    for(auto v : road[u])
        if(!visited[v])
            dfs(v, visited, road);
}

long long countSeparated(long long n, vector<vector<long long>> &road)
{
    long long c = 0;
    vector<bool> visited(n+1, false);
    for (long long i = 1; i <= n; i++)
        if (!visited[i])
        {   
            ++c;
            dfs(i, visited, road);
        }
    return c;
}

int main()
{
    long long n, m, c_lib, c_road;
    cin >> n >> m >> c_lib >> c_road;
    vector<vector<long long>> road(n+1);
    for (long long i = 0; i < m; i++)
    {
        long long a, b;
        cin >> a >> b;
        road[a].push_back(b);
        road[b].push_back(a);
    }

    cout << countSeparated(n, road) << '\n';

    return 0;
}