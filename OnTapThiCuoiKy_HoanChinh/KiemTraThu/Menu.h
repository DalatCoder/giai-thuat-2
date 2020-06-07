void HienThiMenu();
int ChonMenu(int tongSoMenu);
void XuLyMenu(Graph &g, int menu);

void HienThiMenu()
{
	cout << "\nCHUONG TRINH XU LY DO THI" << endl;
	cout << "0. Thoat chuong trinh" << endl;
	cout << "1. Doc tap tin" << endl;
	cout << "2. Duyet chieu sau dung vong lap" << endl;
	cout << "3. Duyet chieu sau dung de quy" << endl;
	cout << "4. Duyet chieu rong dung vong lap" << endl;
	cout << "5. Tim cay bao trum toi thieu bang PRIM" << endl;
	cout << "6. Tim cay bao trum toi thieu bang KRUSKAL" << endl;
	cout << "7. Tim duong di ngan nhat bang DIJKSTRA" << endl;
	cout << "8. Tim duong di ngan nhat bang FLOYD" << endl;
}

int ChonMenu(int total)
{
	int menu;
	while (true)
	{
		system("CLS");
		HienThiMenu();

		cout << "Chon chuc nang >> ";
		cin >> menu;

		if (menu >= 0 && menu <= total)
			break;
	}
	return menu;
}

void XuLyMenu(Graph &g, int menu)
{
	char filename[MAX];
	int vertexIdx;
	Path paths[MAX];
	Edge edges[MAX];
	int sourceIdx, targetIdx;
	Path route[MAX][MAX];

	if (g.NumVertices == 0)
	{
		cout << "\nDo thi trong! Vui long tao du lieu do thi!" << endl;
		system("PAUSE");
		menu = 1;
	}

	system("CLS");
	switch (menu)
	{
	case 0:
		cout << "0. Thoat chuong trinh" << endl;
		break;
	case 1:
		cout << "1. Doc tap tin" << endl;
		cout << "\nNhap ten tap tin >> ";
		cin >> filename;

		if (OpenFile(g, filename) == 0)
		{
			cout << "\nKhong the mo tap tin! Vui long kiem tra lai duong dan tap tin!" << endl;
			system("PAUSE");
			return;
		}

		cout << "\nMo tap tin thanh cong!" << endl;
		cout << "Thong tin chi tiet ve do thi: ";
		DisplayGraphInfo(g);
		
		break;

	case 2:
		cout << "2. Duyet chieu sau dung vong lap" << endl;
		cout << "Nhap dinh bat dau duyet: " << endl;
		vertexIdx = NhapDinh(g);

		ResetFlags(g);
		DFS_Loop(g, vertexIdx);
		break;

	case 3:
		cout << "3. Duyet chieu sau dung de quy" << endl;
		cout << "Nhap dinh bat dau duyet: " << endl;
		vertexIdx = NhapDinh(g);

		ResetFlags(g);
		DFS_Recursion(g, vertexIdx);
		break;

	case 4:
		cout << "4. Duyet chieu rong dung vong lap" << endl;
		cout << "Nhap dinh bat dau duyet: " << endl;
		vertexIdx = NhapDinh(g);

		ResetFlags(g);
		BFS_Loop(g, vertexIdx);
		break;

	case 5:
		cout << "5. Tim cay bao trum toi thieu bang PRIM" << endl;
		Prim(g, paths);
		PrintPrim(g, paths);
		break;

	case 6:
		cout << "6. Tim cay bao trum toi thieu bang KRUSKAL" << endl;
		Kruskal(g, edges);
		PrintKruskal(g, edges);
		break;

	case 7:
		cout << "7. Tim duong di ngan nhat bang DIJKSTRA" << endl;
		cout << "Nhap ten dinh bat dau: " << endl;
		sourceIdx = NhapDinh(g);
		cout << "Nhap ten dinh ket thuc: " << endl;
		targetIdx = NhapDinh(g);

		cout << "Duong di ngan nhat tu dinh '" << GetLable(g, sourceIdx) << "' ---> '" << GetLable(g, targetIdx) << "':" << endl;
		Dijkstra(g, sourceIdx, paths);
		PrintDijkstraPath(g, paths, targetIdx);

		break;

	case 8:
		cout << "8. Tim duong di ngan nhat bang FLOYD" << endl;
		cout << "Nhap ten dinh bat dau: " << endl;
		sourceIdx = NhapDinh(g);
		cout << "Nhap ten dinh ket thuc: " << endl;
		targetIdx = NhapDinh(g);

		cout << "Duong di ngan nhat tu dinh '" << GetLable(g, sourceIdx) << "' ---> '" << GetLable(g, targetIdx) << "':" << endl;
		Floyd(g, route);
		PrintFloydPath(g, route, sourceIdx, targetIdx);

		break;
	}

	cout << endl;
	system("PAUSE");
}
