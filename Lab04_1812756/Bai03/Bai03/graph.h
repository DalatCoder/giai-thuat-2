// Tạo một đỉnh có nhãn lab
Vertex CreateVertex(LabelType lab)
{
	Vertex v;
	v.Label = lab;
	v.Visited = NO;
	return v;
}

// Hiển thị thông tin đỉnh thứ pos trong đồ thị
void DisplayVertex(Graph g, int pos)
{
	cout << g.Vertices[pos].Label << "\t";
}

// Khởi tạo một đồ thị
// directed = true: Đồ thị có hướng
Graph InitGraph(bool directed)
{
	Graph graph;

	graph.NumEdges = 0;
	graph.NumVertices = 0; 
	graph.Directed = directed;

	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			if (i == j)
				graph.Cost[i][j] = 0;
			else
				graph.Cost[i][j] = INF;

	return graph;
}

// Thiết lập lại trạng thái của các đỉnh
void ResetFlags(Graph &g)
{
	for (int i = 0; i < MAX; i++)
		g.Vertices[i].Visited = NO;
}

// Kiểm tra hai đỉnh start và end có được nối với nhau bởi 1 cạnh hay không
bool IsConnected(Graph g, int start, int end)
{
	return (g.Cost[start][end] == 0 || g.Cost[start][end] == INF);
}

// Thêm một đỉnh có nhãn lab vào đồ thị g
void AddVertex(Graph &g, LabelType lab)
{
	Vertex v = CreateVertex(lab);
	g.Vertices[g.NumVertices] = v;
	g.NumVertices += 1;
}

// Thêm một cạnh có trọng số là weight bắt đầu
// từ đỉnh start và kết thúc tại đỉnh end
// directed=false: Thêm cạnh vô hướng
void AddEdge(Graph &g, int start, int end, CostType weight, bool directed)
{
	if (!IsConnected(g, start, end))
	{
		g.NumEdges += 1;
		g.Cost[start][end] = weight;
	}

	if (directed == NO)
		g.Cost[end][start] = weight;
}

// Thêm một cạnh có trọng số là weight bắt đầu
// từ đỉnh start và kết thúc tại đỉnh end
void AddEdge(Graph &g, int start, int end, CostType weight)
{
	AddEdge(g, start, end, weight, g.Directed);
}

// Thêm một cạnh bắt đầu từ đỉnh start và kết thúc tại
// đỉnh end. Dùng cho đồ thị không có trọng số.
void AddEdge(Graph &g, int start, int end)
{
	AddEdge(g, start, end, 1);
}

// Lưu đồ thị xuống file
void SaveGraph(Graph g, char *fileName)
{
	// Khai báo biến và mở tập tin để ghi
	ofstream os(fileName);

	// Lưu số đỉnh
	os << g.NumVertices << '\n';

	// Lưu số cạnh
	os << g.NumEdges << '\n';

	// Lưu loại đồ thị
	os << g.Directed << '\n';

	// Lưu tên các đỉnh
	for (int i = 0; i<g.NumVertices; i++)
		os << g.Vertices[i].Label << '\n';

	// Lưu ma trận kề
	for (int i = 0; i<g.NumVertices; i++)
	{
		for (int j = 0; j<g.NumVertices; j++)
		{
			os << g.Cost[i][j] << '\t';
		}
		os << '\n';
	}

	// Đóng tập tin
	os.close();
}

// Đọc dữ liệu từ file để tạo đồ thị
void OpenGraph(Graph &g, char* fileName)
{
	ifstream input(fileName);

	if (!input)
	{
		cout << "\nLoi doc file nhap lai ten file\n";
		system("pause");
		exit(-1);
	}

	int numVertices = 0;
	int numEdges = 0;
	bool directed = false;
	LabelType label;

	input >> numVertices;
	input >> numEdges;
	input >> directed;

	g = InitGraph(directed);
	g.NumEdges = numEdges;
	
	// Khởi tạo nhãn của các đỉnh
	for (int i = 0; i < numVertices; i++)
	{
		input >> label;
		AddVertex(g, label);
	}

	for (int i = 0; i < numVertices; i++)
		for (int j = 0; j < numVertices; j++)
			input >> g.Cost[i][j];

	input.close();
}

// Tìm đỉnh đầu tiên kề với curr mà chưa xét
int FindFirstAdjacentVertex(Graph g, int curr)
{
	for (int i = 0; i < g.NumVertices; i++)
		if (g.Vertices[i].Visited == NO)
			if (IsConnected(g, curr, i))
				return i;

	return NULLDATA;
}

// Duyệt đồ thị theo chiều sâu dạng đệ quy
void DFS_Recursion(Graph &g, int start)
{
	g.Vertices[start].Visited = YES;
	DisplayVertex(g, start);

	while (true)
	{
		int pos = FindFirstAdjacentVertex(g, start);
		if (pos == NULLDATA)
			break;
		else
			DFS_Recursion(g, pos);
	}
}

// Duyệt đồ thị theo chiều sâu (Depth First Search)
// Dạng lặp, sử dụng Stack
void DFS_Loop(Graph g, int start)
{
	g.Vertices[start].Visited = YES;
	DisplayVertex(g, start);

	stack <int> s;
	s.push(start);

	int curr, adj;

	while (!s.empty())
	{
		curr = s.top();

		adj = FindFirstAdjacentVertex(g, curr);
		if (adj == NULLDATA)
			s.pop();
		else
		{
			g.Vertices[adj].Visited = YES;
			DisplayVertex(g, adj);

			s.push(adj);
		}
	}
}

// Duyệt đồ thị theo chiều rộng
void BFS(Graph g, int start)
{
	g.Vertices[start].Visited = YES;
	queue<int> q;
	q.push(start);

	int curr, adj;
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		DisplayVertex(g, curr);

		while (true)
		{
			adj = FindFirstAdjacentVertex(g, curr);
			if (adj == NULLDATA)
				break;
			else
			{
				g.Vertices[adj].Visited = YES;
				q.push(adj);
			}
		}
	}
}