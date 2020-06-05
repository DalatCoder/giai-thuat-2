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

/*
void Prim(Graph g, Path tree[MAX]) {
	// Khởi tạo cây ban đầu có tất cá các cạnh
	// xuất phát từ đỉnh đầu tiên
	for (size_t i = 1; i < g.NumVertices; i++)
	{
		tree[i].Length = g.Cost[0][i];
		tree[i].Parent = 0;
	}

	CostType min; // luu canh co trong so be nhat
	int minVertext; // luu dinh cuoi cua canh do

	// Tim n - 1 canh cho cay con bao trum
	for (int i = 1; i < g.NumVertices; i++) {
		min = INF;
		minVertext = 1;

		for (int j = 2; j < g.NumVertices; j++) {
			if (g.Vertices[j].Visited == NO && tree[j].Length < min) {
				min = tree[j].Length;
				minVertext = j;
			}
		}

		// Danh dau dinh cuoi cua canh min la da xet
		g.Vertices[minVertext].Visited = YES;

		// Cap nhat lai trong soo cua cac canh
		// voi dinh nguon bay gio la minVertex
		for (int j = 0; j < g.NumVertices; j++) {
			if (g.Vertices[j].Visited == NO && g.Cost[minVertext][j] < tree[j].Length) {
				tree[j].Length = g.Cost[minVertext][j];
				tree[j].Parent = minVertext;
			}
		}
	}
}
*/

void Prim(Graph &g, Path tree[MAX])
{
	for (int i = 0; i < g.NumVertices; i++)		//Khởi tạo cây ban đầu
	{
		tree[i].Length = g.Cost[0][i];
		tree[i].Parent = 0;
	}
	CostType min;		//Lưu cạnh có trọng số nhỏ nhất
	int minVertex;		//Lưu đỉnh cuối của cạnh đó
	for (size_t i = 0; i < g.NumVertices; i++)		//Tìm n-1 cạnh cho cây
	{
		/*min = tree[i].Length;*/
		min = INF;
		minVertex = 1;
		for (size_t j = 1; j < g.NumVertices; j++)	//Tìm cạnh min
			if (g.Vertices[j].Visited == NO && tree[j].Length < min)
			{
				min = tree[j].Length;
				minVertex = j;
			}
		g.Vertices[minVertex].Visited = YES;
		for (size_t j = 0; j < g.NumVertices; j++)	//Thêm vào cây
			if (g.Vertices[j].Visited == NO && g.Cost[minVertex][j] < tree[j].Length)
			{
				tree[j].Length = g.Cost[minVertex][j];
				tree[j].Parent = minVertex;
			}
	}
}

void PrintPrimMST(Graph g, Path tree[MAX]) {
	cout << endl << "Cay bao trum gom cac canh sau: " << endl;
	CostType sum = 0;

	for (int i = 1; i < g.NumVertices; i++) {
		sum += tree[i].Length;
		cout << GetLabel(g, i) << " --> " << GetLabel(g, tree[i].Parent) << " | " << tree[i].Length << endl;
	}

	cout << endl << "Cay bao trum ngan nhat co chieu dai: " << sum << endl;
}

/**/
int LayThongTinCanh(Graph g, Edge list[MAX])
{
	int count = 0;

	for (int i = 0; i < g.NumVertices; i++)
	{
		for (int j = 0; j < i; j++) 
		{
			if (IsConnected(g, i, j))
			{
				Edge canh;
				canh.Source = i;
				canh.Target = j;
				canh.Weight = g.Cost[i][j];
				canh.Marked = NO;

				list[count] = canh;
				count++;
			}
		}
	}

	return count;
}

void SapXepTangDanTheoTrongSo(Edge list[MAX], int tongSoCanh)
{
	for (int i = 0; i < tongSoCanh - 1; i++)
	{
		for (int j = i + 1; j < tongSoCanh; j++)
		{
			if (list[j].Weight < list[i].Weight)
			{
				Edge t = list[i];
				list[i] = list[j];
				list[j] = t;
			}
		}
	}
}

void QSort(Edge list[MAX], int dau, int cuoi)
{
	int i = dau, j = cuoi;

	// Gia tri o giua mang
	CostType midValue = list[(dau + cuoi) / 2].Weight;

	while (i <= j)
	{
		while (list[i].Weight < midValue) i++;
		while (list[j].Weight > midValue) j--;

		if (i <= j)
		{
			Edge t = list[i];
			list[i] = list[j];
			list[j] = t;
			i++;
			j--;
		}
	}

	if (i < cuoi) QSort(list, i, cuoi);
	if (dau < j) QSort(list, dau, j);
}

void InThongTinCanh(Edge list[MAX], int tongSoCanh)
{
	for (int i = 0; i < tongSoCanh; i++)
	{
		cout << list[i].Source << " --> " << list[i].Target << " | " << list[i].Weight << endl;
	}
}

int FindRootOf(int root[MAX], int currVertex)
{
	while (currVertex != root[currVertex])
		currVertex = root[currVertex];

	return currVertex;
}

bool IsUnionAble(int root[MAX], Edge canh)
{
	int sourceRoot = FindRootOf(root, canh.Source);
	int targetRoot = FindRootOf(root, canh.Target);

	// Tao thanh chu trinh => false
	if (sourceRoot == targetRoot)
		return false;
	else if (sourceRoot < targetRoot)
		root[sourceRoot] = targetRoot;
	else
		root[targetRoot] = sourceRoot;
	return true;
}
void Kruskal(Graph g, Edge danhSanhCanh[MAX])
{
	int tongSoCanh = LayThongTinCanh(g, danhSanhCanh);

	// Sap xep canh tang dan
	// SapXepTangDanTheoTrongSo(danhSanhCanh, tongSoCanh);
	QSort(danhSanhCanh, 0, tongSoCanh - 1);

	int root[MAX];
	for (int i = 0; i <= g.NumVertices; i++)
		root[i] = i;

	int count = 0;
	for (int i = 0; i < tongSoCanh; i++)
	{
		Edge canhHienTai = danhSanhCanh[i];

		if (IsUnionAble(root, canhHienTai))
		{
			canhHienTai.Marked = YES;
			count++;
			danhSanhCanh[i] = canhHienTai;

			if (count == g.NumVertices - 1)
				break;
		}
	}
}


void PrintKrusKalMST(Graph g, Edge danhSachCanh[MAX])
{
	cout << "Cay bao trum gom cac canh sau: " << endl;
	CostType sum = 0;

	for (int i = 0; i < g.NumEdges; i++)
	{
		Edge canhHienTai = danhSachCanh[i];

		if (canhHienTai.Marked == YES)
		{
			cout << GetLabel(g, canhHienTai.Source) << " --> " << GetLabel(g, canhHienTai.Target) << " | " << canhHienTai.Weight << endl;
			sum += canhHienTai.Weight;
		}
	}

	cout << "Tong chieu dai cay bao trum la: " << sum << endl;
}



