/* Function prototypes */
// Util functions
int GetDistance(Graph g, int source, int target);
LableType GetLable(Graph g, int idx);
int GetIndex(Graph g, LableType label);
int NhapDinh(Graph g);

int OpenFile(Graph &g, char filename[]);
void DisplayGraphInfo(Graph g);
void DFS_Recursion(Graph& g, int startIdx);
void DFS_Loop(Graph g, int startIdx);
void BFS_Loop(Graph g, int startIdx);

// Prim
void TimDinhGanNhat(Graph g, int& minDistance, int& minVertex, int& minParent);
void Prim(Graph g, Path path[]);
void PrintPrim(Graph g, Path path[]);

// Kruskal
int GetEdges(Graph g, Edge edges[]);
void QSort_Edges(Edge edges[], int dau, int cuoi);
void DisplayEdges(Edge edges[], int total);
int FindRootOf(int root[], int vertexIdx);
bool IsUnionable(int root[], Edge e);
void Kruskal(Graph g, Edge edges[]);
void PrintKruskal(Graph g, Edge edges[]);

// Dijkstra
void Dijkstra(Graph g, int source, Path road[]);
void PrintDijkstraPath(Graph g, Path road[], int target);

// Floyd
void Floyd(Graph g, Path route[MAX][MAX]);
void PrintFloydPath(Graph g, Path route[MAX][MAX], int source, int target);





/* Function definitions */

int GetDistance(Graph g, int source, int target)
{
	return g.Cost[source][target];
}
LableType GetLable(Graph g, int idx)
{
	return g.Vertices[idx].Lable;
}
int GetIndex(Graph g, LableType label)
{
	for (int i = 0; i < g.NumVertices; i++)
		if (GetLable(g, i) == label)
			return i;
	return NULLDATA;
}
int NhapDinh(Graph g)
{
	LableType label;
	int idx;

	while (true)
	{
		cout << "Nhap vao ten 1 dinh >> ";
		cin >> label;

		idx = GetIndex(g, label);
		if (idx != NULLDATA)
			break;

		cout << "Dinh '" << label << "' khong ton tai trong do thi! " << endl;
	}

	return idx;
}

int OpenFile(Graph &g, char filename[])
{
	ifstream input(filename);
	if (!input.is_open())
		return 0;
	
	int soDinh, soCanh, huong;
	input >> soDinh >> soCanh >> huong;

	g = InitGraph(huong);
	g.NumEdges = soCanh;

	LableType label;
	for (int i = 0; i < soDinh; i++)
	{
		input >> label;
		AddVertex(g, label);
	}

	for (int i = 0; i < soDinh; i++)
		for (int j = 0; j < soDinh; j++)
			input >> g.Cost[i][j];

	input.close();
	return 1;
}

void DisplayGraphInfo(Graph g)
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
			cout << g.Cost[i][j] << '\t';
		cout << endl;
	}
	cout << endl;
}

void DFS_Recursion(Graph& g, int startIdx)
{
	DisplayVertex(g, startIdx);
	g.Vertices[startIdx].Visited = YES;

	int adjVertex;
	while (true)
	{
		adjVertex = FindFirstAdjacentVertex(g, startIdx);
		if (adjVertex == NULLDATA)
			break;

		DFS_Recursion(g, adjVertex);
	}
}

void DFS_Loop(Graph g, int startIdx)
{
	DisplayVertex(g, startIdx);
	g.Vertices[startIdx].Visited = YES;

	stack<int> s;

	s.push(startIdx);

	int curIdx;
	int adjVertex;
	while (true)
	{
		curIdx = s.top();		
		adjVertex = FindFirstAdjacentVertex(g, curIdx);

		if (adjVertex == NULLDATA)
		{
			s.pop();
			if (s.empty())
				break;
		}
		else
		{
			DisplayVertex(g, adjVertex);

			s.push(adjVertex);
			g.Vertices[adjVertex].Visited = YES;
		}
	}
}

void BFS_Loop(Graph g, int startIdx)
{
	g.Vertices[startIdx].Visited = YES;
	queue<int> q;

	q.push(startIdx);

	int curIdx, adjVertex;
	while (true)
	{
		curIdx = q.front();
		q.pop();

		DisplayVertex(g, curIdx);

		while (true)
		{
			adjVertex = FindFirstAdjacentVertex(g, curIdx);
			if (adjVertex == NULLDATA)
				break;

			q.push(adjVertex);
			g.Vertices[adjVertex].Visited = YES;
		}

		if (q.empty())
			break;
	}
}

// Thuat toan PRIM tim cay bao trum toi thieu
void TimDinhGanNhat(Graph g, int& minDistance, int& minVertex, int& minParent)
{
	minDistance = INF;
	minVertex = 0;
	minParent = 0;

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
					minParent = i;
				}
			}
		}
	}
}

void Prim(Graph g, Path path[])
{
	g.Vertices[0].Visited = YES;

	int minDistance, minVertex, parentIdx;
	for (int i = 1; i < g.NumVertices; i++)
	{
		TimDinhGanNhat(g, minDistance, minVertex, parentIdx);
		path[minVertex].Length = minDistance;
		path[minVertex].Parent = parentIdx;

		g.Vertices[minVertex].Visited = YES;
	}
}

void PrintPrim(Graph g, Path path[])
{
	int total = 0;

	cout << "\nDanh sach cac canh cua cay bao trum toi thieu:" << endl;
	for (int i = 1; i < g.NumVertices; i++)
	{
		Path p = path[i];
		cout << GetLable(g, p.Parent) << " --> " << GetLable(g, i) << " | " << p.Length << endl;
		total += p.Length;
	}

	cout << "\nTong chieu dai cua cay bao trum toi thieu: " << total << endl;
}

// Thuat toan KRUSKAL tim cay bao trum toi thieu
int GetEdges(Graph g, Edge edges[])
{
	int counter = 0;

	for (int i = 0; i < g.NumVertices; i++)
		for (int j = 0; j < i; j++)
			if (IsConnected(g, i, j))
			{
				Edge e;
				e.Source = i;
				e.Target = j;
				e.Marked = NO;
				e.Weight = GetDistance(g, i, j);

				edges[counter] = e;
				counter++;
			}
	return counter;
}

void QSort_Edges(Edge edges[], int dau, int cuoi)
{
	int i = dau;
	int j = cuoi;

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

int FindRootOf(int root[], int vertexIdx)
{
	while (vertexIdx != root[vertexIdx])
	{
		vertexIdx = root[vertexIdx];
	}

	return vertexIdx;
}

bool IsUnionable(int root[], Edge e)
{
	int sRoot = FindRootOf(root, e.Source);
	int tRoot = FindRootOf(root, e.Target);

	if (sRoot == tRoot)
		return false;

	if (sRoot < tRoot)
		root[tRoot] = sRoot;
	else
		root[sRoot] = tRoot;

	return true;
}

void Kruskal(Graph g, Edge edges[])
{
	int total = GetEdges(g, edges);
	QSort_Edges(edges, 0, total - 1);

	// DisplayEdges(edges, total);

	int root[MAX];
	for (int i = 0; i <= g.NumVertices; i++)
		root[i] = i;

	int counter = 0;
	for (int i = 0; i < total; i++)
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

	cout << "\nCay bao trum toi thieu gom cac canh sau:" << endl;
	for (int i = 0; i < g.NumEdges; i++)
	{
		Edge e = edges[i];
		if (e.Marked)
		{
			cout << GetLable(g, e.Source) << " --> " << GetLable(g, e.Target) << " | " << e.Weight << endl;
			total += e.Weight;
		}
	}

	cout << "\nTong chieu dai cua cay bao trum toi thieu: " << total << endl;
}

void Dijkstra(Graph g, int source, Path road[])
{
	CostType min;
	int counter;
	int minVertex;
	int curIdx;

	for (int i = 0; i < g.NumVertices; i++)
	{
		road[i].Length = g.Cost[source][i];
		road[i].Parent = source;
	}

	g.Vertices[source].Visited = YES;
	counter = 1;
	curIdx = source;

	while (true)
	{
		min = INF;
		minVertex = curIdx;

		for (int i = 0; i < g.NumVertices; i++)
		{
			if (!g.Vertices[i].Visited)
			{
				if (road[i].Length > road[curIdx].Length + GetDistance(g, curIdx, i))
				{
					road[i].Length = road[curIdx].Length + GetDistance(g, curIdx, i);
					road[i].Parent = curIdx;
				}

				if (min > road[i].Length)
				{
					min = road[i].Length;
					minVertex = i;
				}
			}
		}

		curIdx = minVertex;
		g.Vertices[minVertex].Visited = YES;
		counter++;

		if (counter == g.NumVertices - 1)
			break;
	}
}

void PrintDijkstraPath(Graph g, Path road[], int target)
{
	if (road[target].Parent != target)
		PrintDijkstraPath(g, road, road[target].Parent);

	cout << " --> " << GetLable(g, target);
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

void PrintFloydPath(Graph g, Path route[MAX][MAX], int source, int target)
{
	if (route[source][target].Parent != target)
		PrintFloydPath(g, route, source, route[source][target].Parent);
	cout << " --> " << GetLable(g, target);
}

