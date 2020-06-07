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

LableType GetLabel(Graph g, int idx)
{
	return g.Vertices[idx].Lable;
}

void LayThongTinDinhGanNhat(Graph g, int& minDistance, int& vertexIdx, int& parentIdx)
{
	minDistance = INF;
	vertexIdx = 0;
	parentIdx = 0;

	// Tim dinh gan nhat voi tat ca cac dinh da di qua
	for (int i = 0; i < g.NumVertices; i++)
	{
		if (g.Vertices[i].Visited)
		{
			for (int j = 0; j < g.NumVertices; j++)
			{
				if (IsConnected(g, i, j) && !g.Vertices[j].Visited && minDistance > g.Cost[i][j])
				{
					minDistance = g.Cost[i][j];
					vertexIdx = j;
					parentIdx = i;
				}
			}
		}
	}
}

void Prim(Graph g, Path paths[])
{
	g.Vertices[0].Visited = YES;

	int minDistance, minVertex, parentIdx;

	for (int i = 1; i < g.NumVertices; i++)
	{
		LayThongTinDinhGanNhat(g, minDistance, minVertex, parentIdx);

		paths[minVertex].Length = minDistance;
		paths[minVertex].Parent = parentIdx;

		g.Vertices[minVertex].Visited = YES;
	}
}

void PrintPrim(Graph g, Path paths[])
{
	int total = 0;
	cout << "\nDanh sach cac doan duong cua cay bao trum toi thieu: " << endl;
	for (int i = 1; i < g.NumVertices; i++)
	{
		Path p = paths[i];
		cout << GetLabel(g, i) << " --> " << GetLabel(g, p.Parent) << " | " << p.Length << endl;
		total += p.Length;
	}

	cout << "\nTong chieu dai cay bao trum toi thieu: " << total << endl;
}

int GetEdges(Graph g, Edge edges[])
{
	int counter = 0;

	for(int i =0; i < g.NumVertices; i++)
		for (int j = 0; j < i; j++)
			if (IsConnected(g, i, j))
			{
				Edge e;
				e.Source = i;
				e.Target = j;
				e.Weight = g.Cost[i][j];
				e.Marked = NO;

				edges[counter++] = e;
			}
	return counter;
}

void QSort_Edges(Edge edges[], int dau, int cuoi)
{
	int i = dau, j = cuoi;
	int mid = edges[(i + j) / 2].Weight;

	while (i <= j)
	{
		while (edges[i].Weight < mid) i++;
		while (edges[j].Weight > mid) j--;

		if (i <= j)
		{
			swap(edges[i], edges[j]);
			i++;
			j--;
		}
	}

	if (i < cuoi) QSort_Edges(edges, i, cuoi);
	if (j > dau) QSort_Edges(edges, dau, j);
}

void DisplayEdges(Edge edges[], int total)
{
	for (int i = 0; i < total; i++)
	{
		Edge e = edges[i];
		cout << e.Source << " --> " << e.Target << " | " << e.Weight << endl;
	}
	cout << endl;
}

int GetRootOf(int root[], int idx)
{
	while (idx != root[idx])
		idx = root[idx];

	return idx;
}

bool IsUnionable(int root[], Edge e)
{
	int sRoot = GetRootOf(root, e.Source);
	int tRoot = GetRootOf(root, e.Target);

	if (sRoot == tRoot)
		return false;

	if (sRoot < tRoot)
		root[sRoot] = tRoot;
	else
		root[tRoot] = sRoot;

	return true;
}

void Kruskal(Graph g, Edge edges[])
{
	int totalEdges = GetEdges(g, edges);
	QSort_Edges(edges, 0, totalEdges - 1);

	// DisplayEdges(edges, totalEdges);
	int root[MAX];
	for (int i = 0; i <= g.NumVertices; i++)
		root[i] = i;

	int counter = 0;
	for (int i = 0; i < totalEdges; i++)
	{
		if (IsUnionable(root, edges[i]))
		{
			edges[i].Marked = YES;

			counter++;
			if (counter == g.NumVertices - 1)
				break;
		}
	}
}

void PrintKruskal(Graph g, Edge edges[])
{
	int total = 0;
	cout << "\nDanh sach cac canh cua cay bao trum toi thieu: " << endl;
	for (int i = 0; i < g.NumEdges; i++)
	{
		Edge e = edges[i];
		if (e.Marked)
		{
			cout << GetLabel(g, e.Source) << " --> " << GetLabel(g, e.Target) << " | " << e.Weight << endl;
			total += e.Weight;
		}
	}

	cout << "\nTong chieu dai cay bao trum toi thieu: " << total << endl;
}


int GetDistance(Graph g, int source, int target)
{
	return g.Cost[source][target];
}

void Dijkstra(Graph g, int source, Path road[])
{
	int minDistance, minVertex, curVertex;
	int counter = 0;

	// Khoi tao gia tri do dai tu source den cac dinh
	for (int i = 0; i < g.NumVertices; i++)
	{
		road[i].Length = GetDistance(g, source, i);
		road[i].Parent = source;
	}

	g.Vertices[source].Visited = YES;
	counter++;
	curVertex = source;

	while (counter < g.NumVertices - 1)
	{
		minVertex = curVertex;
		minDistance = INF;

		for (int i = 0; i < g.NumVertices; i++)
			if (!g.Vertices[i].Visited)
			{
				if (road[i].Length > road[curVertex].Length + GetDistance(g, curVertex, i))
				{
					road[i].Length = road[curVertex].Length + GetDistance(g, curVertex, i);
					road[i].Parent = curVertex;
				}

				if (minDistance > road[i].Length)
				{
					minDistance = road[i].Length;
					minVertex = i;
				}
			}

		curVertex = minVertex;
		g.Vertices[curVertex].Visited = YES;
		counter++;
	}
}

void PrintDijkstraPath(Graph g, Path road[], int target)
{
	if (road[target].Parent != target)
		PrintDijkstraPath(g, road, road[target].Parent);

	cout << " --> " << GetLabel(g, target);
}

void Floyd(Graph g, Path route[MAX][MAX])
{
	int i, j, k;

	// Khoi tao chieu dai duong di giua cac cap dinh
	for (i = 0; i < g.NumVertices; i++)
		for (j = 0; j < g.NumVertices; j++)
		{
			route[i][j].Length = GetDistance(g, i, j);
			route[i][j].Parent = i;
		}

	// Tinh toan lai duong di
	for (k = 0; k < g.NumVertices; k++)
		for (i = 0; i < g.NumVertices; i++)
			for (j = 0; j < g.NumVertices; j++)
				if (route[i][j].Length > route[i][k].Length + route[k][j].Length)
				{
					route[i][j].Length = route[i][k].Length + route[k][j].Length;
					route[i][j].Parent = route[k][j].Parent;
				}
}

void PrintFloydPath(Graph g, Path route[MAX][MAX], int source, int target)
{
	if (route[source][target].Parent != target)
		PrintFloydPath(g, route, source, route[source][target].Parent);

	cout << " --> " << GetLabel(g, target);
}