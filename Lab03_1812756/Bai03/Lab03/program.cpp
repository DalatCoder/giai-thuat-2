#define MAX 100

#include <iostream>
#include <fstream>

using namespace std;

int DocMangTuFile(int arr[], int &n, char path[]);
void XuatMang(int arr[], int n);

int main()
{
	int arr[MAX];
	int n;
	char path[30];

	cout << "\nNhap ten tap tin de mo: ";
	cin >> path;

	int kq = DocMangTuFile(arr, n, path);
	if (kq)
	{
		cout << "\nDanh sach cac phan tu hien tai: \n";
		XuatMang(arr, n);
	}
	else
	{
		cout << "\nTap tin khong ton tai.";
	}

	system("pause");
	return 0;
}

int DocMangTuFile(int arr[], int &n, char path[])
{
	ifstream in(path);
	if (!in)
		return 0;

	n = 0;
	while (!in.eof())
	{
		in >> arr[n];
		n++;
	}

	in.close();
	return 1;
}

void XuatMang(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << '\t';
	cout << endl;
}
