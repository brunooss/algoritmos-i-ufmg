#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

#define INF 1000000000000000000

class GraphDijkstra
{
public:
	long long V;

	vector<pair<long long, pair<long long, long long>>> *adjacents;

	GraphDijkstra(long long V);

	void addEdge(long long u, long long v, long long traversal, long long year);

	long long minimumPath(long long s);
};

GraphDijkstra::GraphDijkstra(long long V)
{
	this->V = V;
	adjacents = new vector<pair<long long, pair<long long, long long>>>[V];
}

void GraphDijkstra::addEdge(long long u, long long v, long long traversal, long long year)
{
	adjacents[u].push_back(make_pair(v, make_pair(traversal, year)));
	adjacents[v].push_back(make_pair(u, make_pair(traversal, year)));
}

long long GraphDijkstra::minimumPath(long long src)
{
	priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> pq;

	vector<pair<long long, long long>> dist(V);

	for (long long i = 0; i < V; i++)
	{
		dist[i].first = INF;
		dist[i].second = 0;
	}

	pq.push(make_pair(0, src));
	dist[src].first = 0;

	while (!pq.empty())
	{
		long long u = pq.top().second;
		pq.pop();

		vector<pair<long long, pair<long long, long long>>>::iterator i;
		for (i = adjacents[u].begin(); i != adjacents[u].end(); ++i)
		{
			long long v = (*i).first;
			long long weight = (*i).second.first;

			if (dist[v].first > dist[u].first + weight)
			{
				// Updating distance of v
				dist[v].first = dist[u].first + weight;
				dist[v].second = (*i).second.second;
				pq.push(make_pair(dist[v].first, v));
			}
		}
	}

	long long firstYear = -1;

	for (long long i = 0; i < V; ++i)
	{
		if (firstYear < dist[i].second)
		{
			firstYear = dist[i].second;
		}
		cout << dist[i].first << endl;
	}

	return firstYear;
}

class GraphKruskal
{
public:
	long long V, E;
	vector<pair<long long, pair<long long, long long>>> edges;

	GraphKruskal(long long V, long long E)
	{
		this->V = V;
		this->E = E;
	}

	void addEdge(long long u, long long v, long long w)
	{
		edges.push_back({w, {u, v}});
	}

	long long minimumCost();
	long long firstYear();
};

class DisjointSets
{
public:
	long long *parent, *rank;
	long long n;

	// Constructor.
	DisjointSets(long long n)
	{
		this->n = n;
		parent = new long long[n + 1];
		rank = new long long[n + 1];

		for (long long i = 0; i <= n; i++)
		{
			rank[i] = 0;

			parent[i] = i;
		}
	}

	long long find(long long u)
	{
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	void merge(long long x, long long y)
	{
		x = find(x), y = find(y);

		(rank[x] > rank[y]) ? parent[y] = x : parent[x] = y;

		if (rank[x] == rank[y])
			rank[y]++;
	}
};

long long GraphKruskal::firstYear()
{
	long long result = 0;

	sort(edges.begin(), edges.end());

	DisjointSets ds(V);

	vector<pair<long long, pair<long long, long long>>>::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		long long u = it->second.first;
		long long v = it->second.second;

		long long set_u = ds.find(u);
		long long set_v = ds.find(v);

		if (set_u != set_v)
		{
			result = it->first;

			ds.merge(set_u, set_v);
		}
	}

	return result;
}

long long GraphKruskal::minimumCost()
{
	long long result = 0;

	sort(edges.begin(), edges.end());

	DisjointSets ds(V);

	vector<pair<long long, pair<long long, long long>>>::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		long long u = it->second.first;
		long long v = it->second.second;

		long long set_u = ds.find(u);
		long long set_v = ds.find(v);

		if (set_u != set_v)
		{
			result += it->first;

			ds.merge(set_u, set_v);
		}
	}

	return result;
}

int main()
{

	long long verticesCount, edgesCount;

	std::cin >> verticesCount >> edgesCount;

	GraphDijkstra g(verticesCount);

	GraphKruskal g3(verticesCount, edgesCount), g4(verticesCount, edgesCount);

	for (long long i = 0; i < edgesCount; i++)
	{
		long long v1;
		long long v2;
		long long constructionYear;
		long long traversalTime;
		long long constructionCost;

		scanf("%lld %lld %lld %lld %lld", &v1, &v2, &constructionYear, &traversalTime, &constructionCost);

		g.addEdge(v1 - 1, v2 - 1, traversalTime, constructionYear);

		g3.addEdge(v1 - 1, v2 - 1, constructionYear);
		g4.addEdge(v1 - 1, v2 - 1, constructionCost);
	}

	// cout << "O TEMPO MINIMO PARA CADA UM E: " << endl
	long long firstYear = g.minimumPath(0);
	long long minor_year = g3.firstYear();
	long long minor_cost = g4.minimumCost();

	cout << firstYear << endl;
	cout << minor_year << endl;

	cout << minor_cost << endl;

	return 0;
}