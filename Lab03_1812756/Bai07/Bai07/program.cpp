#define MAX 100

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct NhanVien
{
	char maNV[8];
	char hoTen[30];
	int namSinh;
	char diaChi[15];
	double luong;
};

int GhiDuLieuVaoTapTin(NhanVien nv[], int n, char path[]);

int main()
{
	NhanVien nv[MAX] = 
	{
		{ "123456", "Tran_Tuan", 1960, "Da_Lat", 12500000 },
		{ "103456", "Truong_Tuan_Hoc", 1961, "Sai_Gon", 12500000 },
		{ "123450", "Nguyen_Van_Nam", 1970, "Nha_Trang", 20200000 }

	};

	int n = 3;

	char path[15];

	cout << "\nNhap ten tap tin de luu: ";
	cin >> path;

	int kq = GhiDuLieuVaoTapTin(nv, n, path);
	if (kq)
	{
		cout << "\nLuu tap tin thanh cong.";
	}
	else
	{
		cout << "\nKhong the mo tap tin.";
	}

	system("pause");
	return 0;
}

int GhiDuLieuVaoTapTin(NhanVien nv[], int n, char path[])
{
	ofstream out(path);
	if (!out)
		return 0;

	for (int i = 0; i < n; i++)
	{
		out << nv[i].maNV << ' ';
		out << nv[i].hoTen << ' ';
		out << nv[i].namSinh << ' ';
		out << nv[i].diaChi << ' ';
		out << setiosflags(ios::fixed) << setprecision(0) << nv[i].luong << endl;
	}

	out.close();
	return 1;
}
