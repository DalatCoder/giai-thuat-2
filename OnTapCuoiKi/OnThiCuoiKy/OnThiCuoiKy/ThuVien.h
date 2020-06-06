Graph OpenGraph(char filename[])
{
	ifstream input(filename);
	if (input.is_open() == false)
	{
		cout << "\nMo file khong thanh cong! Vui long kiem tra lai ten tap tin!" << endl;
		system("PAUSE"); // dung chuong trinh
		exit(NULLDATA); // thoat chuong trinh - ma loi = -1
	}

	cout << "\nMo file thanh cong!" << endl;

	int soDinh, soCanh, huong;
	input >> soDinh;
	input >> soCanh;
	input >> huong;

	Graph dothi = InitGraph(huong);
	// dothi.NumVertices = soDinh;
	dothi.NumEdges = soCanh;

	LableType label;
	for (int i = 0; i < soDinh; i++)
	{
		input >> label;
		AddVertex(dothi, label);
	}

	for (int i = 0; i < soDinh; i++)
		for (int j = 0; j < soDinh; j++)
			input >> dothi.Cost[i][j];

	input.close();
	return dothi;
}

void HienThiThongTinDoThi(Graph g)
{
	cout << "So dinh: " << g.NumVertices << endl;
	cout << "So canh: " << g.NumEdges << endl;
	if (g.Directed == true)
		cout << "Do thi co huong" << endl;
	else
		cout << "Do thi vo huong" << endl;

	cout << "Ma tran trong so:" << endl;
	for (int i = 0; i < g.NumVertices; i++)
	{
		for (int j = 0; j < g.NumVertices; j++)
			cout << g.Cost[i][j] << '\t';
		cout << endl;
	}

	cout << endl;
}

void DFS_Recursion(Graph& g, int startIdx)
{
	// Hien thi thong tin dinh tai vi tri startIdx
	DisplayVertex(g, startIdx);

	// Danh dau da di qua dinh tai vi tri startIdx
	g.Vertices[startIdx].Visited = YES;

	int dinhLienKeDauTien;

	while (true)
	{
		dinhLienKeDauTien = FindFirstAdjacentVertex(g, startIdx);
		if (dinhLienKeDauTien == NULLDATA)
			break;

		DFS_Recursion(g, dinhLienKeDauTien);
	}
}

void DFS_Loop(Graph g, int startIdx)
{
	// Hien thi thong tin dinh tai vi tri startIdx
	DisplayVertex(g, startIdx);

	// Danh dau da di qua dinh tai vi tri startIdx
	g.Vertices[startIdx].Visited = YES;

	// Khai bao stack
	stack<int> s;

	s.push(startIdx);

	int curIdx; // dinh hien tai dang xet
	int dinhLienKeDauTien;

	while (true)
	{
		curIdx = s.top();
		
		dinhLienKeDauTien = FindFirstAdjacentVertex(g, curIdx);
		if (dinhLienKeDauTien == NULLDATA)
		{
			s.pop();
			if (s.size() == 0)
				break;
		}
		else 
		{
			// Hien thi thong tin dinh lien ke dau tien
			DisplayVertex(g, dinhLienKeDauTien);
			g.Vertices[dinhLienKeDauTien].Visited = YES;

			s.push(dinhLienKeDauTien);
		}
	}
}

void BFS_Loop(Graph g, int startIdx)
{
	g.Vertices[startIdx].Visited = YES;

	queue<int> q;
	q.push(startIdx);

	int curIdx;
	int dinhLienKe;

	while (true)
	{
		// Lay phan tu dau tien khoi hang doi
		curIdx = q.front();

		// Xoa phan tu dau tien khoi hang doi
		q.pop();

		// Hien thi thong tin cua dinh hien tai
		DisplayVertex(g, curIdx);

		// Them tat ca cac dinh lien ke voi dinh hien tai vao hang doi
		while (true)
		{
			dinhLienKe = FindFirstAdjacentVertex(g, curIdx);
			if (dinhLienKe == NULLDATA)
				break;

			q.push(dinhLienKe);
			g.Vertices[dinhLienKe].Visited = YES;
		}

		// Neu hang doi khong con phan tu thi thoat
		if (q.empty() == true)
			break;
	}
}

