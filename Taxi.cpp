// Taxi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <vector>
#include <queue>
#include <iterator>
#include <list>
#include <algorithm>
using namespace std;

#define debug printf("DEBUG: On Line #: %d\n",__LINE__);
#define ll long long
#define VMAX 610
#define INF 1000000000
#define absol(x) (((x)>=0)? (x) : -1*(x))
int p, t, s, c, source, sink;
pair<int, int> person[405];
vector <int> G[VMAX];	// Graph
int pre[VMAX], cap[VMAX][VMAX];
int flow[VMAX][VMAX];

int bfs() {
	int i, j, k, l;
	int current[VMAX];
	memset(current, 0, sizeof(current));
	memset(pre, -1, sizeof(pre));
	pre[source] = -2;
	current[source] = INF;

	queue<int> Q;
	Q.push(source);
	while (!Q.empty()) {
		int from = Q.front();
		Q.pop();
		for (i = 0; i<G[from].size(); i++) {
			int to = G[from][i];
			if (pre[to] == -1 && cap[from][to] - flow[from][to]>0) {	
				pre[to] = from;
				current[to] = min(cap[from][to] - flow[from][to], current[from]);
				if (to == sink)
					return current[sink];
				Q.push(to);
			}
		}
	}
	return 0;
}

inline void edmonds_karp() {
	int i, j, k, l, x, y = 0, z;
	memset(flow, 0, sizeof(flow));
	while (1) {
		x = bfs();
		if (!x) break;
		y += x;

		k = sink;
		while (k != source) {
			flow[pre[k]][k] += x;
			flow[k][pre[k]] -= x;
			k = pre[k];
		}
	}
	printf("%d\n", y);
}

inline bool reachable(int x1, int y1, int x2, int y2) {	// Taxi reachability
	int dist = (absol(x1 - x2) + absol(y1 - y2)) * 200;
	ll prod = 1LL * s * c;
	return (prod >= dist);
}
int main() {
	int i, j, k, l, T, x, y;
	scanf("%d", &T);
	while (T--) {
		for (i = 0; i<VMAX; i++) G[i].clear();
		memset(cap, 0, sizeof(cap));

		scanf("%d%d%d%d", &p, &t, &s, &c);

		source = 0;
		sink = p + t + 2;
		for (i = 1; i <= p; i++) {
			scanf("%d%d", &x, &y);
			person[i] = make_pair(x, y);

			cap[t + i][sink] = 1;
			G[t + i].push_back(sink);
			G[sink].push_back(t + i);
		}
		for (i = 1; i <= t; i++) {
			scanf("%d%d", &x, &y);
			G[source].push_back(i);
			G[i].push_back(source);
			cap[source][i] = 1;

			for (j = 1; j <= p; j++) {
				if (reachable(person[j].first, person[j].second, x, y)) {
					G[i].push_back(t + j);
					G[t + j].push_back(i);
					cap[i][t + j] = 1;
				}
			}
		}
		edmonds_karp();
	}

	return 0;
}
