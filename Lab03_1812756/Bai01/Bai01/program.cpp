#define MAX 100

#include <iostream>
#include <fstream>

using namespace std;

int DocMangTuFile(int arr[], int &n, char path[]);
void XuatMang(int arr[], int n);

int main()
{
	int arr[MAX] = { 0 };
	char path[30];
	int n; 

	cout << "\nNhap ten tap tin de mo: ";
	cin >> path;

	int kq = DocMangTuFile(arr, n, path);

	if (kq)
	{
		cout << "\nDanh sach phan tu hien tai: \n";
		XuatMang(arr, n);
	}
	else
		cout << "\nTap tin khong ton tai.";

	system("Pause");
	return 0;
}

int DocMangTuFile(int arr[], int &n, char path[])
{
	ifstream input(path);
	if (!path)
		return 0; // khong the mo tap tin

	input >> n;

	for (int i = 0; i < n; i++)
		input >> arr[i];
	input.close();

	return 1; // mo tap tin thanh cong
}

void XuatMang(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << '\t';
	cout << endl;
}