#ifndef _GRAPH_

#define MAX 20
#define NO 0
#define YES 1
#define INF 1000
#define NULLDATA -1

typedef char LableType;
typedef int CostType;
typedef CostType Matrix[MAX][MAX];

struct Vertex
{
	LableType Lable;
	int Visited;
};

struct Edge
{
	int Source;
	int Target;
	CostType Weight;
	int Marked;
};

struct Path
{
	CostType Length;
	int Parent;
};

struct Graph
{
	bool Directed;
	int NumVertices;
	int NumEdges;
	Matrix Cost;
	Vertex Vertices[MAX];
};

#endif