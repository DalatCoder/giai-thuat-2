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
	OpenGraph(g, "TextA.txt");
	cout << "\nDoc xong do thi A" << endl;
	BFS(g, 0);
	cout << endl;

	OpenGraph(g, "TextB.txt");
	cout << "\nDoc xong do thi B" << endl;
	BFS(g, 0);
	cout << endl;

	OpenGraph(g, "TextC.txt");
	cout << "\nDoc xong do thi C" << endl;
	BFS(g, 0);
	cout << endl;

	OpenGraph(g, "TextD.txt");
	cout << "\nDoc xong do thi D" << endl;
	BFS(g, 0);
	cout << endl;

	OpenGraph(g, "TextE.txt");
	cout << "\nDoc xong do thi E" << endl;
	BFS(g, 0);
	cout << endl;

	OpenGraph(g, "TextF.txt");
	cout << "\nDoc xong do thi F" << endl;
	BFS(g, 0);
	cout << endl;

	system("Pause");
	return 0;
}