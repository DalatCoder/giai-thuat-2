#define MAX 100

#include <iostream>
#include <fstream>

using namespace std;

int DocMaTranVuong(int arr[MAX][MAX], int &n, char path[]);
void XuatMaTran(int arr[MAX][MAX], int n);

int main()
{
	int mat[MAX][MAX];
	int n;
	char path[30];

	cout << "\nGhi ten tap tin can mo: ";
	cin >> path;

	int kq = DocMaTranVuong(mat, n, path);

	if (kq)
	{
		cout << "\nMa tran vuong vua tao tu tap tin: \n";
		XuatMaTran(mat, n);
	}
	else
	{
		cout << "\nTap tin khong ton tai.";
	}

	system("pause");
	return 0;
}

int DocMaTranVuong(int arr[MAX][MAX], int &n, char path[])
{
	ifstream in(path);
	if (!in)
		return 0; // mo tap tin that bai

	in >> n;

	for (int i = 0; i < n;i++)
		for (int j = 0; j < n; j++)
			in >> arr[i][j];

	in.close();
	return 1; // mo tap tin thanh cong
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

