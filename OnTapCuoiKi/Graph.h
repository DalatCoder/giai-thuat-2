Vertex CreateVertex(LableType lab);
void DisplayVertex(Graph g, int pos);
Graph InitGraph(bool d);
void ResetFlags(Graph &g);
int IsConnected(Graph g, int start, int end);
void AddVertex(Graph &g, LableType lab);
void AddEdge(Graph &g, int start, int end, CostType weight, bool directed);
int FindFirstAdjacentVertex(Graph g, int curr);

Vertex CreateVertex(LableType lab)
{
	Vertex v;
	v.Lable = lab;
	v.Visited = NO;
	return v;
}
void DisplayVertex(Graph g, int pos)
{
	cout << g.Vertices[pos].Lable << "\t";
}
Graph InitGraph(bool d)
{
	Graph g;
	g.Directed = d;
	g.NumVertices = 0;
	g.NumEdges = 0;
	for (int i = 0; i < MAX; i++)
	for (int j = 0; j < MAX; j++)
	if (i == j) g.Cost[i][j] = 0;
	else g.Cost[i][j] = INF;
	return g;
}

void ResetFlags(Graph &g)
{
	for (int i = 0; i < g.NumVertices; i++)
		g.Vertices[i].Visited = NO;
}

int IsConnected(Graph g, int start, int end)
{
	if (!g.Cost[start][end] || g.Cost[start][end] == INF) return 0;
	else return 1;
}

void AddVertex(Graph &g, LableType lab)
{
	Vertex v = CreateVertex(lab);
	g.Vertices[g.NumVertices++] = v;
}

void AddEdge(Graph &g, int start, int end, CostType weight, bool directed)
{
	if (IsConnected(g, start, end)) g.NumEdges++;
	g.Cost[start][end] = weight;
	if (!directed) g.Cost[end][start] = weight;
}
int FindFirstAdjacentVertex(Graph g, int curr)
{
	for (int i = 0; i < g.NumVertices; i++)
	{
		if (!g.Vertices[i].Visited && IsConnected(g, curr, i))
			return i;
	}
	return NULLDATA;
}

LableType GetLabel(Graph g, int idx)
{
	return g.Vertices[idx].Lable;
}

CostType GetDistance(Graph g, int source, int target)
{
	return g.Cost[source][target];
}