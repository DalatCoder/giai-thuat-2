#define MAX 100

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void TaoMaTranNgauNhien(int mat[MAX][MAX], int n);
int GhiDuLieuVaoFile(int mat[MAX][MAX], int n, char path[]);
void XuatMaTran(int arr[MAX][MAX], int n);

int main()
{
	int mat[MAX][MAX];
	int n;
	char path[30];

	cout << "\nNhap cap cua ma tran vuong: ";
	cin >> n;

	TaoMaTranNgauNhien(mat, n);

	cout << "\nMa tran vuong hien tai: \n";
	XuatMaTran(mat, n);

	cout << "\nNhap ten tap tin de mo: ";
	cin >> path;
	int kq = GhiDuLieuVaoFile(mat, n, path);
	if (kq)
		cout << "\nGhi du lieu vao tap tin thanh cong.";
	else
		cout << "\nLoi mo tap tin.";

	return 0;
}

void TaoMaTranNgauNhien(int mat[MAX][MAX], int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		mat[i][j] = rand() % 10;
}

int GhiDuLieuVaoFile(int mat[MAX][MAX], int n, char path[])
{
	ofstream out(path);
	if (!out)
		return 0;

	out << n << '\n';

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			out << mat[i][j] << '\t';
		out << '\n';
	}

	out.close();
	return 1;
}

void XuatMaTran(int arr[MAX][MAX], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << arr[i][j] << '\t';
		cout << endl;
	}
}