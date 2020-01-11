#ifndef _GRAPH_
#define _GRAPH_

// Định nghĩa hằng số
#define UPPER		100		// Số ptử tối đa
#define ZERO		0		// Giá trị 0
#define MAX			20		// Số đỉnh tối đa
#define INF			1000	// Vô cùng
#define YES			1		// Đã xét
#define NO			0		// Chưa xét
#define NULLDATA	-1		// Giả giá trị rỗng

// Định nghĩa các kiểu dữ liệu
typedef char LabelType;
typedef int CostType;
typedef CostType MaTrix[MAX][MAX]; // Ma trận

// Định nghĩa cấu trúc của một đỉnh
struct Vertex
{
	LabelType Label; // Nhãn của đỉnh
	int Visited; // Trạng thái
};

// Định nghĩa cấu trúc một cạnh
struct Edge
{
	int Source; // Đỉnh đầu
	int Target; // Đỉnh cuối
	CostType Weight; // Trọng số
	int Marked; // Trạng thái
};

// Định nghĩa cấu trúc một đoạn đường đi
struct Path
{
	CostType Length; // Độ dài đi
	int Parent; // Đỉnh trước
};

// Định nghĩa kiểu dữ liệu đồ thị
struct Graph
{
	bool Directed; // ĐT có hướng?
	int NumVertices; // Số đỉnh
	int NumEdges; // Số cạnh
	MaTrix Cost; // MTrận kề
	Vertex Vertices[MAX]; // DS đỉnh
};

#endif