#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

#include "common.h"
#include "graph.h"

int main()
{
	Graph g;
	Path tree[MAX];

	/*
	OpenGraph(g, "TextA.txt");
	cout << "\nDoc xong do thi A" << endl;
	Prim(g, tree);
	PrintPrimMST(g, tree);
	cout << endl;

	OpenGraph(g, "TextB.txt");
	cout << "\nDoc xong do thi B" << endl;
	Prim(g, tree);
	PrintPrimMST(g, tree);
	cout << endl;
	*/

	OpenGraph(g, "TextC.txt");
	cout << "\nDoc xong do thi C" << endl;
	Prim(g, tree);
	PrintPrimMST(g, tree);
	cout << endl;

	/*
	OpenGraph(g, "TextD.txt");
	cout << "\nDoc xong do thi D" << endl;
	Prim(g, tree);
	PrintPrimMST(g, tree);
	cout << endl;

	OpenGraph(g, "TextE.txt");
	cout << "\nDoc xong do thi E" << endl;
	Prim(g, tree);
	PrintPrimMST(g, tree);
	cout << endl;

	OpenGraph(g, "TextF.txt");
	cout << "\nDoc xong do thi F" << endl;
	Prim(g, tree);
	PrintPrimMST(g, tree);
	cout << endl;
	*/

	return 0;
}
