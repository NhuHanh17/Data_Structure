#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#define MAX 100

struct Sinhvien {
	int MSSV;
	string Hovaten;
	char Ngaysinh[11];
	string Quequan;
	double DiemTB;
};

struct DsSv {
	Sinhvien* sv;
	int n;
};

void Nhap1sv(Sinhvien& sv) {
	cout << "Nhap ma so sinh vien:";
	cin >> sv.MSSV;
	cin.ignore();
	cout << "Nhap ho va ten:";
	getline(cin, sv.Hovaten);
	cout << "Nhap ngay sinh:";
	cin.getline(sv.Ngaysinh, 11);
	cout << "Nhap que quan: ";
	getline(cin, sv.Quequan);
	cout << "Nhap diem trung binh:";
	cin >> sv.DiemTB;
}

void xuat1sv(Sinhvien sv) {
	cout << "==========================\n"
		<< "MSSV: " << sv.MSSV << endl
		<< "Ho va ten: " << sv.Hovaten << endl
		<< "Ngay sinh: " << sv.Ngaysinh << endl
		<< "Que quan: " << sv.Quequan << endl
		<< "Diem trung binh: " << sv.DiemTB << endl;
}

void NhapsvtuFile(DsSv& ds, string fileName) {
	ifstream inFile(fileName);
	if (inFile.is_open()) {
		inFile >> ds.n;
		Sinhvien sv;
		ds.sv = new Sinhvien[ds.n];
		for (int i = 0; i < ds.n; i++){
			inFile >> ds.sv[i].MSSV;
			inFile.ignore();
			getline(inFile, ds.sv[i].Hovaten, '#');
			inFile.getline(ds.sv[i].Ngaysinh, 11, '#');
			getline(inFile, ds.sv[i].Quequan,'#');
			inFile >> ds.sv[i].DiemTB;
		}
		inFile.close();
	}
}

void xuatSinhvien(DsSv ds) {
	for (int i = 0; i < ds.n; i++) {
		xuat1sv(ds.sv[i]);
	}
}

int search(DsSv ds, int key) {
	for (int i = 0; i < ds.n; i++)
		if (ds.sv[i].MSSV == key)
			return i;
	return -1;
}

int search(DsSv ds, string key) {
	for (int i = 0; i < ds.n; i++)
		if (ds.sv[i].Hovaten == key || ds.sv[i].Quequan == key)
			return i;
	return -1;
}

void swap(Sinhvien& a, Sinhvien& b) {
	Sinhvien tmp = a;
	a = b; 
	b = tmp;
}

void sort(DsSv &ds) {
	int chon;
	cout << "Chon kieu sap xep \n"
		<< "1.Theo MSSV \n"
		<< "2.Theo Ho va ten \n"
		<< "3.Theo Que quan \n";
	cout << "-->Lua chon: ";
	cin >> chon;
	switch (chon) {
	case 1:
		for (int i = 0; i < ds.n - 1; i++) {
			for (int j = i + 1; j < ds.n; j++) {
				if (ds.sv[i].MSSV > ds.sv[j].MSSV)
					swap(ds.sv[i], ds.sv[j]);
			}
		}
		break;
	case 2:
		for (int i = 0; i < ds.n - 1; i++) {
			for (int j = i + 1; j < ds.n; j++) {
				if (ds.sv[i].Hovaten > ds.sv[j].Hovaten)
					swap(ds.sv[i], ds.sv[j]);
			}
		}
		break;
	case 3:
		for (int i = 0; i < ds.n - 1; i++) {
			for (int j = i + 1; j < ds.n; j++) {
				if (ds.sv[i].Quequan > ds.sv[j].Quequan)
					swap(ds.sv[i], ds.sv[j]);
			}
		}
		break;
	default:
		cout << "Lua chon khong hop le! \n";
	}
}

void delSinhvien(DsSv& ds, int mssv) {
	int key = search(ds, mssv);
	if (key == -1) {
		cout << "Ma so sinh vien khong ton tai \n";
		return;
	}
	for (int i = key; i < ds.n - 1; i++)
		ds.sv[i] = ds.sv[i + 1];
	ds.n--;
}

void insertSinhvien(DsSv& ds) {
	if (ds.n >= MAX){
		cout << "Danh sach da day \n";
		return;
	}
	Nhap1sv(ds.sv[ds.n++]);
	cout << " Them thanh cong \n";
	system("pause");
}

void xuatTungSinhvien(DsSv ds) {
	int cont  = 1;
	for (int i = 0; i < ds.n; i++) {
		switch (cont) {
		case 1:
			system("cls");
			xuat1sv(ds.sv[i]);
			cout << "Tiep tuc (1/0): ";
			cin >> cont;
			break;
		case 0:
			return;
		default:
			cout << "Lua chon khong hop le\n";
			break;
		}
	}
}

int main() {
	DsSv ds;
	NhapsvtuFile(ds, "Sinhvien.txt");
	xuatTungSinhvien(ds);
	system("pause");
	return 0;
}
