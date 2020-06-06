void DocFile(char* filename, Graph& g)
{
	ifstream input(filename);

	if (input.is_open())
	{
		int soDinh;
		int soCanh;
		LableType nhanDinh;
		bool directed;

		input >> soDinh >> soCanh >> directed;

		g = InitGraph(directed);
		g.NumEdges = soCanh;

		for (int i = 0; i < soDinh; i++)
		{
			input >> nhanDinh;
			AddVertex(g, nhanDinh);
		}

		for (int i = 0; i < soDinh; i++)
		{
			for (int j = 0; j < soDinh; j++)
			{
				input >> g.Cost[i][j];
			}
		}
	}
	else
	{
		cout << "\nKhong the mo tap tin! Kiem tra lai ten tap tin!" << endl;
		exit(NULLDATA);
	}
}

void DisplayGraph(Graph g)
{
	cout << "So dinh: " << g.NumVertices << endl;
	cout << "So canh: " << g.NumEdges << endl;
	if (g.Directed) 
		cout << "Do thi co huong" << endl;
	else 
		cout << "Do thi vo huong" << endl;

	cout << "Ma tran trong so: " << endl;
	for (int i = 0; i < g.NumVertices; i++)
	{
		for (int j = 0; j < g.NumVertices; j++)
		{
			cout << "\t" << g.Cost[i][j]; 
		}
		cout << endl;
	}
}

void DFS_Recursion(Graph &g, int dinhHienTai)
{
	g.Vertices[dinhHienTai].Visited = YES;
	DisplayVertex(g, dinhHienTai);

	while (true)
	{
		int dinhLienKeDauTien = FindFirstAdjacentVertex(g, dinhHienTai);
		if (dinhLienKeDauTien == NULLDATA) break;
		else DFS_Recursion(g, dinhLienKeDauTien);
	}
}

void DFS_Loop(Graph& g, int dinhHienTai)
{
	stack<int> s;
	g.Vertices[dinhHienTai].Visited = YES;
	DisplayVertex(g, dinhHienTai);
	s.push(dinhHienTai);

	int chiSoDinhHienTai, chiSoDinhLienKeDauTien;
	while (!s.empty())
	{
		chiSoDinhHienTai = s.top();
		chiSoDinhLienKeDauTien = FindFirstAdjacentVertex(g, chiSoDinhHienTai);

		if (chiSoDinhLienKeDauTien == NULLDATA)
		{
			s.pop();
		}
		else
		{
			g.Vertices[chiSoDinhLienKeDauTien].Visited = YES;
			DisplayVertex(g, chiSoDinhLienKeDauTien);
			s.push(chiSoDinhLienKeDauTien);
		}
	}
}

void BFS_Loop(Graph& g, int dinhDauTien)
{
	g.Vertices[dinhDauTien].Visited = YES;
	queue<int> q;
	q.push(dinhDauTien);

	int chiSoDinhHienTai, chiSoDinhLienKeDauTien;
	while (!q.empty())
	{
		chiSoDinhHienTai = q.front();
		DisplayVertex(g, chiSoDinhHienTai);
		q.pop();

		while (true)
		{
			chiSoDinhLienKeDauTien = FindFirstAdjacentVertex(g, chiSoDinhHienTai);
			if (chiSoDinhLienKeDauTien == NULLDATA)
				break;
			else {
				g.Vertices[chiSoDinhLienKeDauTien].Visited = YES;
				q.push(chiSoDinhLienKeDauTien);
			}
		}
	}
}

int LayThongTinCacCanh(Graph g, Edge danhSachCanh[MAX])
{
	int counter = 0;
	for (int i = 0; i < g.NumVertices; i++)
		for (int j = 0; j < i; j++)
			if (IsConnected(g, i, j))
			{
				Edge canh;
				canh.Source = i;
				canh.Target = j;
				canh.Marked = NO;
				canh.Weight = GetDistance(g, i, j);

				danhSachCanh[counter++] = canh;
			}

	return counter;
}

void SapXepCanhTangDan(Edge danhSachCanh[MAX], int dau, int cuoi)
{
	int i = dau;
	int j = cuoi;
	int mid = danhSachCanh[(i + j) / 2].Weight;

	while (i <= j)
	{
		while (danhSachCanh[i].Weight < mid) i++;
		while (danhSachCanh[j].Weight > mid) j--;

		if (i <= j)
		{
			swap(danhSachCanh[i], danhSachCanh[j]);
			i++;
			j--;
		}
	}

	if (i < cuoi) SapXepCanhTangDan(danhSachCanh, i, cuoi);
	if (j > dau) SapXepCanhTangDan(danhSachCanh, dau, j);
}

int GetRootOf(int root[MAX], int vertex)
{
	while (vertex != root[vertex])
		vertex = root[vertex];
	return vertex;
}

bool IsUnionable(int root[MAX], Edge canh)
{
	int sourceRoot = GetRootOf(root, canh.Source);
	int targetRoot = GetRootOf(root, canh.Target);

	if (sourceRoot == targetRoot)
		return false;

	if (sourceRoot < targetRoot)
		root[targetRoot] = sourceRoot;
	else
		root[sourceRoot] = targetRoot;

	return true;
}

void HienThiCanh(Edge dsCanh[MAX], int n)
{
	for (int i = 0; i < n; i++)
	{
		Edge canh = dsCanh[i];
		cout << canh.Source << " --> " << canh.Target << " | " << canh.Weight << endl;
	}
}

void Kruskal(Graph g, Edge danhSachCanh[MAX])
{
	int tongSoCanh = LayThongTinCacCanh(g, danhSachCanh);
	SapXepCanhTangDan(danhSachCanh, 0, tongSoCanh - 1);

	// HienThiCanh(danhSachCanh, tongSoCanh);

	int root[MAX];
	for (int i = 0; i <= tongSoCanh; i++)
		root[i] = i;

	int counter = 0;
	for (int i = 0; i < tongSoCanh; i++)
	{
		if (IsUnionable(root, danhSachCanh[i]))
		{
			danhSachCanh[i].Marked = YES;
			counter++;

			if (counter == tongSoCanh - 1)
				break;
		}
	}
}


void PrintKruskal(Graph g, Edge danhSachCanh[MAX])
{
	int total = 0;

	cout << "\nDanh sach cac canh:\n";
	for (int i = 0; i < g.NumEdges; i++)
	{
		Edge canh = danhSachCanh[i];
		if (canh.Marked)
		{
			cout << GetLabel(g, canh.Source) << " --> " << GetLabel(g, canh.Target) << " | " << canh.Weight << endl;
			total += canh.Weight;
		}
	}

	cout << "\nTong do dai cay bao trum toi thieu: " << total << endl;
}

void TimDinhGanNhat(Graph g, int& minDistance, int& minVertex, int& parentVertex)
{
	minDistance = INF;
	minVertex = 0;
	parentVertex = 0;

	for (int i = 0; i < g.NumVertices; i++)
	{
		if (g.Vertices[i].Visited)
		{
			for (int j = 0; j < g.NumVertices; j++)
			{
				if (IsConnected(g, i, j) && !g.Vertices[j].Visited && minDistance > GetDistance(g, i, j))
				{
					minDistance = GetDistance(g, i, j);
					minVertex = j;
					parentVertex = i;
				}
			}
		}
	}
}

void Prim(Graph g, Path danhSachDuongDi[MAX])
{
	g.Vertices[0].Visited = YES;

	int minVertex;
	int minDistance;
	int parentIdx;

	for (int i = 1; i < g.NumVertices; i++)
	{
		TimDinhGanNhat(g, minDistance, minVertex, parentIdx);
		danhSachDuongDi[minVertex].Parent = parentIdx;
		danhSachDuongDi[minVertex].Length = minDistance;

		g.Vertices[minVertex].Visited = YES;
	}
}

void PrintPrim(Graph g, Path danhSachDuongDi[MAX])
{
	int sum = 0;

	cout << "\nDanh sach cac canh:\n";
	for (int i = 1; i < g.NumVertices; i++)
	{
		cout << GetLabel(g, danhSachDuongDi[i].Parent) << " --> " << GetLabel(g, i) << " | " << danhSachDuongDi[i].Length << endl;
		sum += danhSachDuongDi[i].Length;
	}

	cout << "\nTong chieu dai cua cay bao trum toi thieu: " << sum << endl;
}
