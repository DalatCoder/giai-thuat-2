#define MAX 100

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void TaoMangNgauNhien(int arr[], int n);
void XuatMang(int arr[], int n);
int GhiMangVaoFile(int arr[], int n, char path[]);

int main()
{
	int arr[MAX];
	int n;
	char path[30];

	cout << "\nNhap so phan tu cua mang: ";
	cin >> n;

	TaoMangNgauNhien(arr, n);

	cout << "\nMang ngau nhien vua tao: \n";
	XuatMang(arr, n);

	cout << "\nGhi ten tap tin de luu: ";
	cin >> path;

	int kq = GhiMangVaoFile(arr, n, path);

	if (kq)
		cout << "\nLuu du lieu thanh cong.";
	else
		cout << "\nTap tin khong ton tai.";

	system("pause");
	return 0;
}

void TaoMangNgauNhien(int arr[], int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		arr[i] = rand() % 100;
}

void XuatMang(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << '\t';
	cout << endl;
}

int GhiMangVaoFile(int arr[], int n, char path[])
{
	ofstream out(path);
	if (!out)
		return 0; // loi mo file

	out << n << '\n';

	for (int i = 0; i < n; i++)
		out << arr[i] << '\t';

	out.close();
	return 1; // ghi file thanh cong
}

