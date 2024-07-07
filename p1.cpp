#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <conio.h>

using namespace std;

struct SinhVien {
    int maSV;
    char hoDem[50];
    char Ten[50];
    char gioiTinh[10];
    char ngaySinh[11];
};

struct HocPhan {
    char maHP[50];
    char tenMonHoc[100];
    int soTinChi;
};

struct DiemThi {
    char maHP[50];
    int maSV;
    float diem;
};

// Hàm nhập thông tin sinh viên
void nhapSinhVien(SinhVien& sv){
    cout << "Nhap ma sinh vien: ";
    cin >> sv.maSV;
    cin.ignore();
    cout << "Nhap ho dem sinh vien: ";
    cin.getline(sv.hoDem, sizeof(sv.hoDem));
    cout << "Nhap ten sinh vien: ";
    cin.getline(sv.Ten, sizeof(sv.Ten));
    cout << "Nhap gioi tinh: ";
    cin.getline(sv.gioiTinh, sizeof(sv.gioiTinh));
    cout << "Nhap ngay sinh (theo dang dd/mm/yyyy): ";
    cin.getline(sv.ngaySinh, sizeof(sv.ngaySinh));
}

// Hàm nhập thông tin học phần
void nhapHocPhan(HocPhan& hp) {
    cout << "Nhap ma hoc phan: ";
    cin >> hp.maHP;
    cin.ignore(); // Xóa bỏ ký tự newline
    cout << "Nhap ten mon hoc: ";
    cin.getline(hp.tenMonHoc, sizeof(hp.tenMonHoc));
    cout << "Nhap so tin chi: ";
    cin >> hp.soTinChi;
}

// Hàm nhập điểm thi
void nhapDiemThi(DiemThi& dt) {
    cout << "Nhap ma hoc phan: ";
    cin >> dt.maHP;
    cout << "Nhap ma sinh vien: ";
    cin >> dt.maSV;
cout<<"Nhap diem:";
cin>>dt.diem;
}

// Hàm ghi thông tin sinh viên vào file SV.BIN
void ghiSinhVien(const SinhVien& sv) {
    ofstream outFile("SV.BIN", ios::binary | ios::app);
    outFile.write(reinterpret_cast<const char*>(&sv), sizeof(SinhVien));
    outFile.close();
}

// Hàm ghi thông tin học phần vào file HP.BIN
void ghiHocPhan(const HocPhan& hp) {
    ofstream outFile("HP.BIN", ios::binary | ios::app);
    outFile.write(reinterpret_cast<const char*>(&hp), sizeof(HocPhan));
    outFile.close();
}

// Hàm ghi điểm thi vào file DIEMTHI.BIN
void ghiDiemThi(const DiemThi& dt) {
    ofstream outFile("DIEMTHI.BIN", ios::binary | ios::app);
    outFile.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));
    outFile.close();
}

// Hàm đọc thông tin sinh viên từ file SV.BIN
void docSinhVien() {
    ifstream inFile("SV.BIN", ios::binary);
    SinhVien sv;
    while (inFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        cout << "Ma SV: " << sv.maSV << endl;
        cout << "Ho dem: " << sv.hoDem << endl;
        cout << "Ten: " << sv.Ten << endl;
        cout << "Gioi tinh: " << sv.gioiTinh << endl;
        cout << "Ngay Sinh: " << sv.ngaySinh << endl;
        cout << endl;
    }
    inFile.close();
}

// Hàm đọc thông tin học phần từ file HP.BIN
void docHocPhan() {
    ifstream inFile("HP.BIN", ios::binary);
    HocPhan hp;
    while (inFile.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        cout << "Ma HP: " << hp.maHP << endl;
        cout << "Ten mon hoc: " << hp.tenMonHoc << endl;
        cout << "So tin chi: " << hp.soTinChi << endl;
        cout << endl;
    }
    inFile.close();
}

// Hàm đọc điểm thi từ file DIEMTHI.BIN
void docDiemThi() {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    DiemThi dt;
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        cout << "Ma HP: " << dt.maHP << endl;
        cout << "Ma SV: " << dt.maSV << endl;
        cout << "Diem: " << dt.diem << endl;
        cout << endl;
    }
    inFile.close();
}
bool maSinhVienDaTonTai(int maSV) {
    ifstream inFile("SV.BIN", ios::binary);
    SinhVien sv;
    while (inFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        if (sv.maSV == maSV) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}
bool maHocPhanDaTonTai(const char* maHP) {
    ifstream inFile("HP.BIN", ios::binary);
    HocPhan hp;
    while (inFile.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        if (strcmp(hp.maHP, maHP) == 0) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}
bool diemThiDaTonTai(const char* maHP, int maSV) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    DiemThi dt;
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.maHP, maHP) == 0 && dt.maSV == maSV) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}
void bosungSinhVien() {
    SinhVien sv;
    nhapSinhVien(sv);

    if (maSinhVienDaTonTai(sv.maSV)) {
        cout << "Ma sinh vien da ton tai trong file SV.BIN." << endl;
        return;
    }

    ghiSinhVien(sv);
    cout << "Da them sinh vien vao file SV.BIN" << endl;
}
void bosungHocPhan() {
    HocPhan hp;
    nhapHocPhan(hp);

    if (maHocPhanDaTonTai(hp.maHP)) {
        cout << "Ma hoc phan da ton tai trong file HP.BIN." << endl;
        return;
    }

    ghiHocPhan(hp);
    cout << "Da them hoc phan vao file HP.BIN" << endl;
}
void bosungDiemThi() {
    DiemThi dt;
    nhapDiemThi(dt);

    if (!maHocPhanDaTonTai(dt.maHP)) {
        cout << "Ma hoc phan khong ton tai trong file HP.BIN." << endl;
        return;
    }

    if (!maSinhVienDaTonTai(dt.maSV)) {
        cout << "Ma sinh vien khong ton tai trong file SV.BIN." << endl;
        return;
    }

    if (diemThiDaTonTai(dt.maHP, dt.maSV)) {
        cout << "Diem thi da ton tai trong file DIEMTHI.BIN." << endl;
        return;
    }

    ghiDiemThi(dt);
    cout << "Da them diem thi vao file DIEMTHI.BIN" << endl;
}
void capNhatDiemThi() {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    ofstream tempFile("temp.BIN", ios::binary);  // File tạm

    DiemThi dt;
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (maHocPhanDaTonTai(dt.maHP) && maSinhVienDaTonTai(dt.maSV)) {
            tempFile.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));
        }
    }

    inFile.close();
    tempFile.close();

    // Xóa file DIEMTHI.BIN cũ
    remove("DIEMTHI.BIN");
    // Đổi tên file temp.BIN thành DIEMTHI.BIN mới
    rename("temp.BIN", "DIEMTHI.BIN");

    cout << "Da cap nhat file DIEMTHI.BIN" << endl;
}


// Hàm tìm kiếm và hiển thị danh sách sinh viên theo mã học phần
void timKiemDiemThiTheoHocPhan(const char* maHP) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    DiemThi dt;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.maHP, maHP) == 0) {
            ifstream svFile("SV.BIN", ios::binary);
            SinhVien sv;
            while (svFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
                if (sv.maSV == dt.maSV) {
                    cout << "Ma SV: " << sv.maSV << endl;
                    cout << "Ho dem: " << sv.hoDem << endl;
                    cout << "Ten: " << sv.Ten << endl;
                    cout << "Diem: " << dt.diem << endl;
                    cout << endl;
                }
            }
            
            svFile.close();
            found = true;
        }
    }
    inFile.close();

    if (!found) {
        cout << "Khong tim thay thong tin diem thi cho hoc phan nay." << endl;
    }
}
//Hàm tìm kiếm và hiển thị danh sách sinh viên không đạt học phần này (điểm <4)
void timKiemSinhVienKhongDat(const char*maHP){
    ifstream inFile("DIEMTHI.BIN",ios::binary);
    DiemThi dt;
    bool found=false;
    while(inFile.read(reinterpret_cast<char*>(&dt),sizeof(DiemThi))){
        if(strcmp(dt.maHP,maHP)==0){
            ifstream svFile("SV.BIN",ios::binary);
            SinhVien sv;
            while(svFile.read(reinterpret_cast<char*>(&sv),sizeof(SinhVien))){
                if(sv.maSV==dt.maSV){
                    if(dt.diem<=4){
                        cout<<"Ma SV:"<<sv.maSV<<endl;
                        cout<<"Ho dem:"<<sv.hoDem<<endl;
                        cout<<"Ten:"<<sv.Ten<<endl;
                        cout<<"Diem:"<<dt.diem<<endl;
                        cout<<endl;
                    }
                }
            }
            svFile.close();
            found=true;
        }
    }
    inFile.close();

    if (!found) {
        cout << "Khong tim thay thong tin diem thi cho hoc phan nay." << endl;
    }
}
void hienThiMenu(int luaChon) {
    system("cls");
    cout << "CHUONG TRINH QUAN LY SINH VIEN - MENU" << endl;
    cout << "-----------------------------------" << endl;
    cout << (luaChon == 1 ? "-> " : "  ") << "1. Nhap thong tin sinh vien" << endl;
    cout << (luaChon == 2 ? "-> " : "  ") << "2. Nhap thong tin hoc phan" << endl;
    cout << (luaChon == 3 ? "-> " : "  ") << "3. Nhap diem thi" << endl;
    cout << (luaChon == 4 ? "-> " : "  ") << "4. Hien thi thong tin sinh vien" << endl;
    cout << (luaChon == 5 ? "-> " : "  ") << "5. Hien thi thong tin hoc phan" << endl;
    cout << (luaChon == 6 ? "-> " : "  ") << "6. Hien thi diem thi" << endl;
    cout << (luaChon == 7 ? "-> " : "  ") << "7. Tim kiem diem thi theo hoc phan" << endl;
    cout << (luaChon == 8 ? "-> " : "  ") << "8. Tim kiem sinh vien khong dat hoc phan" << endl;
    cout << (luaChon == 0 ? "-> " : "  ") << "0. Thoat" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
    cout << "Nhan Enter de chon mot lua chon" << endl;
}

void xuLyLuaChon(int luaChon) {
    switch (luaChon) {
        case 1:
            bosungSinhVien();
            break;
        case 2:
            bosungHocPhan();
            break;
        case 3:
            bosungDiemThi();
            break;
        case 4:
            cout << "======= Danh sach sinh vien =======" << endl;
            docSinhVien();
            break;
        case 5:
            cout << "======= Danh sach hoc phan =======" << endl;
            docHocPhan();
            break;
        case 6:
            cout << "======= Danh sach diem thi =======" << endl;
            docDiemThi();
            break;
        case 7: {
            char maHP[50];
            cout << "Nhap ma hoc phan: ";
            cin >> maHP;
            timKiemDiemThiTheoHocPhan(maHP);
            break;
        }
         case 8: {
            char maHP[50];
            cout << "Nhap ma hoc phan: ";
            cin >> maHP;
            timKiemSinhVienKhongDat(maHP);
            break;
        }
        case 0:
            cout << "Thoat chuong trinh. Tam biet!" << endl;
            break;
        default:
            cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
            break;
    }

    if (luaChon != 0) {
        cout << endl << "Nhan phim bat ky de quay lai menu." << endl;
        _getch();
        capNhatDiemThi();
    }
}
int main(int argc, char* argv[]) {
    int luaChon = 1;
    int phim;

    while (true) {
        hienThiMenu(luaChon);

        phim = _getch();
        if (phim == 0 || phim == 224) {
            phim = _getch();
            switch (phim) {
                case 72:  // Mui ten len
                    luaChon--;
                    if (luaChon < 0) luaChon = 7;
                    break;
                case 80:  // Mui ten xuong
                    luaChon++;
                    if (luaChon > 8) luaChon = 0;
                    break;
            }
        } else if (phim == 13) {
            xuLyLuaChon(luaChon);
            if (luaChon == 0) break;
        }
    }

    return 0;
}