#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <iomanip>

using namespace std;

#include "Common.h"
#include "Graph.h"
#include "ThuVien.h"

int main()
{
	char filename[] = "dulieu.txt";
	Graph g;
	DocFile(filename, g);
	DisplayGraph(g);

	cout << "\nDuyet do thi theo chieu sau DFS de quy: \n";
	DFS_Recursion(g, 0);
	ResetFlags(g);

	cout << "\nDuyet do thi theo chieu sau DFS lap: \n";
	DFS_Loop(g, 0);
	ResetFlags(g);

	cout << "\nDuyet do thi theo chieu rong BFS lap: \n";
	BFS_Loop(g, 0);
	ResetFlags(g);
	cout << endl;

	Path danhSachDuong[MAX];
	Prim(g, danhSachDuong);
	PrintPrim(g, danhSachDuong);
	ResetFlags(g);

	cout << endl;
	Edge danhSachCanh[MAX];

	Kruskal(g, danhSachCanh);
	PrintKruskal(g, danhSachCanh);
	ResetFlags(g);

	cout << "\nDuong di ngan nhat voi Dijkstra:\n";
	Path duongDiNganNhat[MAX];
	Dijkstra(g, 0, duongDiNganNhat);
	PrintPath(g, duongDiNganNhat, 5);
	ResetFlags(g);

	cout << "\nDuong di ngan nhat voi Floyd:\n";
	Path route[MAX][MAX];
	Floyd(g, route);
	PrintFloyd(g, route, 0, 5);

	cout << endl << endl;
	system("pause");
	return 0;
}

