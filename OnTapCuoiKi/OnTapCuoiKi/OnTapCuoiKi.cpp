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

	Path danhSachDuong[MAX];
	Prim(g, danhSachDuong);
	PrintPrimMST(g, danhSachDuong);
	ResetFlags(g);

	cout << endl;
	Edge danhSachCanh[MAX];

	Kruskal(g, danhSachCanh);
	PrintKrusKalMST(g, danhSachCanh);

	cout << endl << endl;
	system("pause");
	return 0;
}

