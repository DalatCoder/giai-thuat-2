#define MAX 100

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct Date
{
	int ngay;
	int thang;
	int nam;
};

struct Name
{
	char ho[15];
	char tLot[15];
	char ten[15];
};

struct NhanVien
{
	char ma[8];
	Name hoTen;
	Date ntnSinh;
	char diaChi[15];
	double luong;
};

int DocMangCauTruc(NhanVien nv[], int &n, char path[]);
void Xuat_1_NV(NhanVien nv);
void Xuat_DS(NhanVien nv[], int n);

int main()
{
	NhanVien nv[MAX];
	int n;
	char path[30];

	cout << "\nNhap ten tap tin de mo: ";
	cin >> path;

	int kq = DocMangCauTruc(nv, n, path);

	if (kq)
	{
		cout << "\nDanh sach nhan vien hien tai: \n";
		Xuat_DS(nv, n);
	}
	else
	{
		cout << "\nKhong the mo tap tin.";
	}

	system("pause");
	return 0;
}

int DocMangCauTruc(NhanVien nv[], int &n, char path[])
{
	ifstream in(path);
	if (!in)
		return 0;

	n = 0;
	while (!in.eof())
	{
		in >> nv[n].ma;
		in >> nv[n].hoTen.ho;
		in >> nv[n].hoTen.tLot;
		in >> nv[n].hoTen.ten;
		in >> nv[n].ntnSinh.ngay;
		in >> nv[n].ntnSinh.thang;
		in >> nv[n].ntnSinh.nam;
		in >> nv[n].diaChi;
		in >> nv[n].luong;

		n++;
	}

	in.close();
	return 1;
}

void Xuat_1_NV(NhanVien nv)
{
	cout << nv.ma << '\t'
		<< nv.hoTen.ho << " "
		<< nv.hoTen.tLot << " "
		<< nv.hoTen.ten << "\t"
		<< nv.ntnSinh.nam << "/"
		<< nv.ntnSinh.thang << "/"
		<< nv.ntnSinh.nam << '\t'
		<< nv.diaChi << "\t"
		<< setiosflags(ios::fixed) << setprecision(0) << nv.luong << endl;
}

void Xuat_DS(NhanVien nv[], int n)
{
	for (int i = 0; i < n; i++)
		Xuat_1_NV(nv[i]);
	cout << endl;
}

