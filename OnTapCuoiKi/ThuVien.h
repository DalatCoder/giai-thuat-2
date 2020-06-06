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

void Prim(Graph g, Path path[MAX])
{
	g.Vertices[0].Visited = YES;
	path[0].Parent = 0;
	path[0].Length = 0;

	int minDistance, minVertex, parentVertex;
	int counter = 0;
	while (true)
	{
		TimDinhGanNhat(g, minDistance, minVertex, parentVertex);
		path[minVertex].Parent = parentVertex;
		path[minVertex].Length = minDistance;

		g.Vertices[minVertex].Visited = YES;

		counter++;
		if (counter == g.NumVertices - 1)
			break;
	}
}

void PrintPrim(Graph g, Path path[MAX])
{
	int total = 0;

	cout << "\nDanh sach cac canh cua cay bao trum toi thieu: " << endl;
	for (int i = 0; i < g.NumVertices; i++)
	{
		Path p = path[i];
		cout << GetLabel(g, p.Parent) << " --> " << GetLabel(g, i) << " | " << p.Length << endl;
		total += p.Length;
	}

	cout << "\nTong do dai duong di cua cay bao trum toi thieu: " << total << endl;
}

int LayThongTinCanh(Graph g, Edge edges[MAX])
{
	int counter = 0;

	for (int i =0 ; i < g.NumVertices; i++ )
		for (int j = 0; j < i; j++)
			if (IsConnected(g, i, j))
			{
				Edge e;
				e.Source = i;
				e.Target = j;
				e.Weight = GetDistance(g, i, j);
				e.Marked = NO;

				edges[counter++] = e;
			}

	return counter;
}

void SapXepCanhTangDan(Edge edges[MAX], int dau, int cuoi)
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

	if (i < cuoi) SapXepCanhTangDan(edges, i, cuoi);
	if (j > dau) SapXepCanhTangDan(edges, dau, j);
}

int GetRootOf(int root[MAX], int vertex)
{
	while (vertex != root[vertex])
		vertex = root[vertex];

	return vertex;
}

bool IsUnionable(int root[MAX], Edge e)
{
	int sRoot = GetRootOf(root, e.Source);
	int tRoot = GetRootOf(root, e.Target);

	if (sRoot == tRoot) return false;

	if (sRoot < tRoot)
		root[sRoot] = tRoot;
	else
		root[tRoot] = sRoot;
	return true;
}

void Kruskal(Graph g, Edge edges[MAX])
{
	int tongSoCanh = LayThongTinCanh(g, edges);
	SapXepCanhTangDan(edges, 0, tongSoCanh - 1);

	int root[MAX];
	for (int i = 0; i <= g.NumVertices; i++)
		root[i] = i;

	int counter = 0;
	for (int i = 0; i < tongSoCanh; i++)
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

void PrintKruskal(Graph g, Edge edges[MAX])
{
	int total = 0;

	for (int i = 0; i < g.NumEdges; i++)
	{
		Edge e = edges[i];
		if (e.Marked)
		{
			cout << GetLabel(g, e.Source) << " --> " << GetLabel(g, e.Target) << " | " << e.Weight << endl;
			total += e.Weight;
		}
	}

	cout << "\nTong do dai duong di cua cay bao trum toi thieu: " << total << endl;
}

void Dijkstra(Graph g, int source, Path road[MAX])
{
	CostType min;
	int counter, minVertex, curr;

	for (int i = 0; i < g.NumVertices; i++)
	{
		road[i].Length = g.Cost[source][i];
		road[i].Parent = source;
	}

	g.Vertices[source].Visited = YES;
	counter = 1;
	curr = source;

	while (counter < g.NumVertices - 1)
	{
		min = INF;
		minVertex = curr;

		for (int i = 0; i < g.NumVertices; i++)
		{
			if (!g.Vertices[i].Visited)
			{
				if (road[i].Length > road[curr].Length + GetDistance(g, curr, i))
				{
					road[i].Length = road[curr].Length + GetDistance(g, curr, i);
					road[i].Parent = curr;
				}

				if (min > road[i].Length)
				{
					min = road[i].Length;
					minVertex = i;
				}
			}
		}

		curr = minVertex;
		g.Vertices[curr].Visited = YES;
		counter++;
	}
}

void PrintPath(Graph g, Path road[MAX], int target)
{
	if (road[target].Parent != target)
		PrintPath(g, road, road[target].Parent);
	cout << '\t' << GetLabel(g, target);
}

void Floyd(Graph g, Path route[MAX][MAX])
{
	int i, j, k;

	for (i = 0; i < g.NumVertices; i++)
		for (j = 0; j < g.NumVertices; j++)
		{
			route[i][j].Length = GetDistance(g, i, j);
			route[i][j].Parent = i;
		}

	for (k = 0; k < g.NumVertices; k++)
		for (i = 0; i < g.NumVertices; i++)
			for (j = 0; j < g.NumVertices; j++)
				if (route[i][j].Length > route[i][k].Length + route[k][j].Length)
				{
					route[i][j].Length = route[i][k].Length + route[k][j].Length;
					route[i][j].Parent = route[k][j].Parent;
				}
}

void PrintFloyd(Graph g, Path route[MAX][MAX], int source, int target)
{
	if (route[source][target].Parent != target)
		PrintFloyd(g, route, source, route[source][target].Parent);

	cout << " --> " << GetLabel(g, target);
}