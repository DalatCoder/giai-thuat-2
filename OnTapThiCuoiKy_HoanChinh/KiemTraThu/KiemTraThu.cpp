#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

#include "Common.h"
#include "Graph.h"
#include "ThuVien.h"
#include "Menu.h"

void ChayChuongTrinh();

int main()
{
	ChayChuongTrinh();
	return 0;
}

void ChayChuongTrinh()
{
	int tongSoMenu = 8;
	int menu;
	Graph g;

	g = InitGraph(0);

	while (true)
	{
		menu = ChonMenu(tongSoMenu);
		XuLyMenu(g, menu);

		if (menu == 0)
			break;
	}

	cout << "\nCam on da su dung chuong trinh!" << endl;
}

