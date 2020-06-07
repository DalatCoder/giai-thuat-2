#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

#include "Common.h"
#include "Graph.h"
#include "ThuVien.h"

int main()
{
	char filename[] = "data.txt";
	Graph g = OpenGraph(filename);
	HienThiThongTinDoThi(g);

	cout << "\nDuyet theo chieu sau dung de quy: \n";
	DFS_Recursion(g, 0);
	ResetFlags(g);

	cout << "\nDuyet theo chieu sau dung vong lap: \n";
	DFS_Loop(g, 0);
	ResetFlags(g);

	cout << "\nDuyen theo chieu rong dung vong lap: \n";
	BFS_Loop(g, 0);
	ResetFlags(g);

	Path paths[MAX];
	cout << "\nTim cay bao trum toi thieu su dung Prim:" << endl;
	Prim(g, paths);
	PrintPrim(g, paths);

	Edge edges[MAX];
	cout << "\nTim cay bao trum toi thieu su dung Kruskal:" << endl;
	Kruskal(g, edges);
	PrintKruskal(g, edges);

	Path road[MAX];
	cout << "\nTim duong di ngan nhat voi Dijkstra" << endl;
	Dijkstra(g, 0, road);
	PrintDijkstraPath(g, road, 5);

	return 0;
}