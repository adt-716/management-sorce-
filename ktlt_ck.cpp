#include<iostream>
#include<fstream>
#include<cstring>
#include <conio.h>
#include<cmath>
#include<windows.h>
using namespace std;
struct SinhVien{
    char mssv[10];
    char hodem[50] ;
    char ten_sv[50];
    char gioi_tinh[10];
    char ngay_sinh[11];
};
struct HocPhan{
    char mahp[10] ;
    char ten_mon_hoc[50];
    int so_tc;
};
struct DiemThi{
    char mahp[10];
    char mssv[10];
    float diem;
};
bool KiemTraNgaySinh(const char* ngay_sinh) {
    if (strlen(ngay_sinh) != 10) {
        cout << "Dinh dang ngay sinh khong hop le! Vui long nhap lai." << endl;
        return false;
    }
    int ngay, thang, nam;
    if (sscanf(ngay_sinh, "%d/%d/%d", &ngay, &thang, &nam) != 3) {
        cout << "Dinh dang ngay sinh khong hop le! Vui long nhap lai." << endl;
        return false;
    }
    if (thang < 1 || thang > 12 || ngay < 1 || ngay > 31 || nam < 1900) {
        cout << "Ngay sinh khong hop le! Vui long nhap lai." << endl;
        return false;
    } else if ((thang == 4 || thang == 6 || thang == 9 || thang == 11) && ngay > 30) {
        cout << "Ngay sinh khong hop le! Vui long nhap lai." << endl;
        return false;
    } else if (thang == 2) {
        bool namNhuan = (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
        if ((namNhuan && ngay > 29) || (!namNhuan && ngay > 28)) {
            cout << "Ngay sinh khong hop le! Vui long nhap lai." << endl;
            return false;
        }
    }

    return true;
}
bool kiemTraDiem(float diem) {
    if (diem >= 0.0 && diem <= 10.0 && static_cast<int>(diem * 10) % 5 == 0) {
        return true;
    } else {
        return false;
    }
}
bool checkDuplicateMSSV(const char* mssv) {
    ifstream inFile("SV.BIN", ios::binary);
    SinhVien sv;
    while (inFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        if (strcmp(sv.mssv, mssv) == 0) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}
bool checkDuplicateMaHP(const char* mahp) {
    ifstream file("HP.BIN", ios::binary);
    HocPhan hp;
    while (file.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        if (strcmp(hp.mahp, mahp) == 0) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
bool checkDuplicateDiem(const char* mahp, const char* mssv) {
    ifstream file("DIEMTHI.BIN", ios::binary);
    DiemThi dt;
    while (file.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.mahp, mahp) == 0 && strcmp(dt.mssv, mssv) == 0) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
SinhVien NhapSV() {
    SinhVien sv;
    cout << "Nhap ma so sinh vien: " ;
    cin >> sv.mssv;
    cin.ignore();
    cout << "Nhap ho dem sinh vien: ";
    cin.getline(sv.hodem, 50);
    cout << "Nhap ten sinh vien: ";
    cin.getline(sv.ten_sv, 50);
    cout << "Nhap gioi tinh: ";
    cin.getline(sv.gioi_tinh, 10);
    bool hopLe = false ;
    do {
        cout << "Nhap ngay sinh (theo dang dd/mm/yyyy): ";
        cin.getline(sv.ngay_sinh, 11);
        hopLe = KiemTraNgaySinh(sv.ngay_sinh);
    } while (!hopLe) ;
    return sv;
}
HocPhan nhap_hp() {
    HocPhan hp;
    cout << "Nhap ma hoc phan: ";
    cin >> hp.mahp;
    cin.ignore(); 
    cout << "Nhap ten mon hoc: ";
    cin.getline(hp.ten_mon_hoc, 50);
    cout << "Nhap so tin chi: ";
    cin >> hp.so_tc;
    return hp;
}
DiemThi nhap_diem_thi() {
    DiemThi dt;
    cout << "Nhap ma hoc phan: ";
    cin >> dt.mahp;
    cout << "Nhap ma sinh vien: ";
    cin >> dt.mssv;
    bool hopLe = false ;
    do {
        cout << "Nhap diem (0.0 - 10.0): ";
        cin >> dt.diem ;
        hopLe = kiemTraDiem(dt.diem) ;
    }while (!hopLe)  ;
    return dt;
}
void ghiSinhVien(const SinhVien& sv) {
    ofstream binFile("SV.BIN", ios::binary | ios::app);
    if (binFile.is_open()) {
        binFile.write(reinterpret_cast<const char*>(&sv), sizeof(SinhVien));
        binFile.close();
        cout << "Ghi sinh vien vao file SV.BIN thanh cong" << endl;
    } else {
        cout << "Khong the mo file SV.BIN" << endl;
    }
    ofstream txtFile("output.txt", ios::app);
    if (txtFile.is_open()) {
        txtFile << "Ma so sinh vien: " << sv.mssv << endl;
        txtFile << "Ho dem: " << sv.hodem << endl;
        txtFile << "Ten: " << sv.ten_sv << endl;
        txtFile << "Gioi tinh: " << sv.gioi_tinh << endl;
        txtFile << "Ngay Sinh: " << sv.ngay_sinh << endl;
        txtFile << endl;
        cout << "Ghi sinh vien vao file output.txt thanh cong." << endl;
        txtFile.close();
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
}
void ghiHocPhan(const HocPhan& hp) {
    ofstream binFile("HP.BIN", ios::binary | ios::app);
    if (binFile.is_open()) {
        binFile.write(reinterpret_cast<const char*>(&hp), sizeof(HocPhan));
        binFile.close();
        cout << "Ghi hoc phan vao file HP.BIN thanh cong" << endl;
    } else {
        cout << "Khong the mo file HP.BIN" << endl;
    }
    ofstream txtFile("output.txt", ios::app);
    if (txtFile.is_open()) {
        txtFile << "Nhap ma hoc phan: " << hp.mahp << endl;
        txtFile << "Nhap ten mon hoc: " << hp.ten_mon_hoc << endl;
        txtFile << "Nhap so tin chi: " << hp.so_tc << endl;
        txtFile << endl;
        cout << "Ghi hoc phan vao file output.txt thanh cong." << endl;
        txtFile.close();
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
}
void ghiDiemThi(const DiemThi& dt) {
    ofstream binFile("DIEMTHI.BIN", ios::binary | ios::app);
    if (binFile.is_open()) {
        binFile.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));
        binFile.close();
        cout << "Ghi diem thi vao file DIEMTHI.BIN thanh cong" << endl;
    } else {
        cout << "Khong the mo file DIEMTHI.BIN" << endl;
    }
    ofstream txtFile("output.txt", ios::app);
    if (txtFile.is_open()) {
        txtFile << "Nhap ma hoc phan: " << dt.mahp << endl;
        txtFile << "Nhap ma sinh vien: " << dt.mssv << endl;
        txtFile << "Nhap diem: " << dt.diem << endl;
        txtFile << endl;
        cout << "Ghi diem thi vao file output.txt thanh cong." << endl;
        txtFile.close();
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
}
void docSinhVien() {
    ifstream binFile("SV.BIN", ios::binary);
    ofstream txtFile("output.txt", ios::app);
    SinhVien sv;
    while (binFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        txtFile << "MSSV: " << sv.mssv << endl;
        txtFile << "Ho dem: " << sv.hodem << endl;
        txtFile << "Ten sinh vien: " << sv.ten_sv << endl;
        txtFile << "Gioi tinh: " << sv.gioi_tinh << endl;
        txtFile << "Ngay sinh: " << sv.ngay_sinh << endl;
        txtFile << endl;
    }
    binFile.close();
    txtFile.close();
}
void docHocPhan() {
    ifstream binFile("HP.BIN", ios::binary);
    ofstream txtFile("output.txt", ios::app);
    HocPhan hp;
    while (binFile.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        txtFile << "Ma hoc phan: " << hp.mahp << endl;
        txtFile << "Ten mon hoc: " << hp.ten_mon_hoc << endl;
        txtFile << "So tin chi: " << hp.so_tc << endl;
        txtFile << endl;
    }
    binFile.close();
    txtFile.close();
}
void docDiemThi() {
    ifstream binFile("DIEMTHI.BIN", ios::binary);
    ofstream txtFile("output.txt", ios::app);
    DiemThi dt;
    while (binFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        txtFile << "Ma hoc phan: " << dt.mahp << endl;
        txtFile << "Ma so sinh vien: " << dt.mssv << endl;
        txtFile << "Diem thi: " << dt.diem << endl;
        txtFile << endl;
    }
    binFile.close();
    txtFile.close();
}
void bosungSV() {
    ofstream outputFile("output.txt", ios::app) ;
    SinhVien sv = NhapSV();
    if (checkDuplicateMSSV(sv.mssv)) {
        outputFile<< "Ma so Sinh Vien da ton tai. Khong the bo sung du lieu." << endl;
        return ;
    }
    ghiSinhVien(sv);
    cout << "Da them sinh vien " << sv.mssv << " vao file SV.BIN" <<  endl;
    outputFile.close() ;
}
void bosungHP() {
    ofstream outputFile("output.txt",ios::app);
    HocPhan hp = nhap_hp();
    if (checkDuplicateMaHP(hp.mahp)) {
        outputFile << "Ma hoc phan da ton tai. Khong the bo sung du lieu." << endl;
        return ;
    }
    ghiHocPhan(hp);
    cout << "Da them hoc phan " << hp.mahp << " vao file HP.BIN" << endl;
    outputFile.close() ;
}
void bosungDiem() {
    ofstream outputFile("output.txt",ios::app);
    DiemThi dt = nhap_diem_thi();
    if (!checkDuplicateMaHP(dt.mahp)) {
        outputFile << "Ma hoc phan khong ton tai trong file HP.BIN." << endl;
        return;
    }
    if (!checkDuplicateMSSV(dt.mssv)) {
        outputFile << "Ma sinh vien khong ton tai trong file SV.BIN." << endl;
        return;
    } 
    if (checkDuplicateDiem(dt.mahp, dt.mssv)) {
        outputFile << "Diem thi da ton tai. Khong the bo sung du lieu." << endl;
    }
    ghiDiemThi(dt);
    cout << "Da them diem thi vao file DIEMTHI.BIN" << endl;
    outputFile.close() ;
}
void xoaSinhVien(const char* mssv) {
    ifstream inFile("SV.BIN", ios::binary);
    ofstream tempFile("temp.BIN", ios::binary);
    ofstream outputFile("output.txt",ios::app);
    SinhVien sv;
    while (inFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        if (strcmp(sv.mssv, mssv) != 0) {
            tempFile.write(reinterpret_cast<const char*>(&sv), sizeof(SinhVien));
        }
    }
    inFile.close();
    tempFile.close();
    remove("SV.BIN");
    rename("temp.BIN", "SV.BIN");
    cout << "Da xoa thong tin sinh vien co mssv: " << mssv << endl;
    outputFile.close() ;
}
void xoaHocPhan(const char* mahp) {
    ifstream inFile("HP.BIN", ios::binary);
    ofstream tempFile("temp_HP.BIN", ios::binary); // Sử dụng tên tập tin tạm riêng biệt
    ofstream outputFile("output.txt", ios::app);
    HocPhan hp;
    while (inFile.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        if (strcmp(hp.mahp, mahp) != 0) {
            tempFile.write(reinterpret_cast<const char*>(&hp), sizeof(HocPhan));
        }
    }
    inFile.close();
    tempFile.close();
    remove("HP.BIN");
    rename("temp_HP.BIN", "HP.BIN"); // Sử dụng tên tập tin tạm riêng biệt
    cout << "Da xoa thong tin hoc phan " << mahp << endl;
    outputFile.close();
}

void xoaDiemThi(const char* mahp, const char* mssv) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    ofstream tempFile("temp.BIN", ios::binary);  
    ofstream outputFile("output.txt",ios::app);

    DiemThi dt;
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.mahp, mahp) != 0 || strcmp(dt.mssv, mssv) != 0) {
            tempFile.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));
        }
    }
    inFile.close();
    tempFile.close();
    remove("DIEMTHI.BIN");
    rename("temp.BIN", "DIEMTHI.BIN");
    cout << "Da xoa thong tin diem thi hoc phan "  <<dt.mahp << " cua sinh vien " << dt.mssv << endl;
    outputFile.close() ;
}

void suaSinhVien(const char* mssv) {
    fstream file("SV.BIN", ios::binary | ios::in | ios::out);
    ofstream outputFile("output.txt",ios::app);
    SinhVien sv;
    while (file.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        if (strcmp(sv.mssv ,mssv) == 0) {
            outputFile << "Nhap thong tin sinh vien moi: " << endl;
            SinhVien sv = NhapSV();
            file.seekp(-static_cast<int>(sizeof(SinhVien)), ios::cur);
            file.write(reinterpret_cast<const char*>(&sv), sizeof(SinhVien));
            cout << "Da sua thong tin sinh vien " <<sv.mssv<< endl;
            outputFile << "Thong tin sinh vien sau khi sua:" << endl;
            outputFile << "Ma so sinh vien: " << sv.mssv << endl;
            outputFile << "Ho dem: " << sv.hodem << endl;
            outputFile << "Ten: " << sv.ten_sv << endl;
            outputFile << "Gioi tinh: " << sv.gioi_tinh << endl;
            outputFile << "Ngay Sinh: " << sv.ngay_sinh << endl;
            outputFile << endl;
            file.close();
            outputFile.close();
            return;
        }
    }
    outputFile << "Khong tim thay sinh vien co ma so " << mssv << endl;
    file.close();

}
void suaHocPhan(const char* mahp) {
    fstream file("HP.BIN", ios::binary | ios::in | ios::out);
    ofstream outputFile("output.txt",ios::app);
    HocPhan hp;
    while (file.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        if (strcmp(hp.mahp, mahp) == 0) {
            cout << "Nhap thong tin hoc phan moi: " << endl;
            HocPhan hp  = nhap_hp();
            file.seekp(-static_cast<int>(sizeof(HocPhan)), ios::cur);
            file.write(reinterpret_cast<const char*>(&hp), sizeof(HocPhan));
            cout << "Da sua thong tin hoc phan " << hp.mahp << endl;
            outputFile << "Thong tin hoc phan sau khi sua:" << endl;
            outputFile << "Ma hoc phan: " << hp.mahp << endl;
            outputFile << "Ten hoc phan: " << hp.ten_mon_hoc << endl;
            outputFile << "So tin chi: " << hp.so_tc << endl;
            outputFile << endl;
            file.close();
            outputFile.close();
            return;
        }
    }
    outputFile << "Khong tim thay hoc phan co ma " << mahp << endl;
    file.close();
    outputFile.close();
} 
void suaDiemThi(const char* mahp, const char* mssv) {
    fstream file("DIEMTHI.BIN", ios::binary | ios::in | ios::out);
    ofstream outputFile("output.txt",ios::app);
    DiemThi dt;
    while (file.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.mahp, mahp) == 0 && strcmp(dt.mssv, mssv) == 0) {
            cout << "Nhap thong tin diem thi moi: " << endl;
            DiemThi dt = nhap_diem_thi();
            file.seekp(-static_cast<int>(sizeof(DiemThi)), ios::cur);
            file.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));
            cout << "Da sua thong tin diem thi co ma hoc phan " <<dt.mahp << " va mssv la "<< dt.mssv<< " diem " << dt.diem << endl;
            outputFile << "Thong tin diem thi sau khi sua:" << endl;
            outputFile << "Ma hoc phan: " << dt.mahp << endl;
            outputFile << "Ma so sinh vien: " << dt.mssv << endl;
            outputFile << "Diem thi: " << dt.diem << endl;
            outputFile << endl;
            file.close();
            return;
        }
    }
    outputFile << "Khong tim thay diem thi cho hoc phan " << mahp << " va sinh vien co ma so " << mssv << endl;
    file.close();
    outputFile.close() ;
}
float tinhDiemThangDiem4(float diem) {
    if (diem >= 8.5 && diem <= 10)
        return 4.0;
    else if (diem >= 8.0 && diem <= 8.4)
        return 3.5;
    else if (diem >= 7.0 && diem <= 7.9)
        return 3.0;
    else if (diem >= 6.5 && diem <= 6.9)
        return 2.5;
    else if (diem >= 5.5 && diem <= 6.4)
        return 2.0;
    else if (diem >= 5.0 && diem <= 5.4)
        return 1.5;
    else if (diem >= 4.0 && diem <= 4.9)
        return 1.0;
    else
        return 0.0;
}
float tinhGPA(const char* mssv) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    if (!inFile) {
        cout << "Khong the doc file DIEMTHI.BIN" << endl;
        return 0.0f;
    }
    DiemThi dt;
    float tongDiem = 0.0f;
    int tongSoTC = 0;
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.mssv, mssv) != 0) {
            continue;
        }
        HocPhan hp;
        ifstream hpFile("HP.BIN", ios::binary);

        while (hpFile.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
            if (strcmp(dt.mahp, hp.mahp) == 0) {
                tongSoTC += hp.so_tc;
                break;
            }
        }
        hpFile.close();

        float diem4 = tinhDiemThangDiem4(dt.diem);
        tongDiem += diem4 * hp.so_tc;
    }
    inFile.close();
    if (tongSoTC == 0) {
        cout << "Khong tim thay sinh vien co MSSV la: " << mssv << endl;
        return 0.0f;
    }
    float gpa = tongDiem / tongSoTC;
    gpa = roundf(gpa * 100) / 100;
    return gpa;
}
void ghiGPA(const char* mssv, const float gpa) {
    ofstream outFile("GPA.BIN", ios::binary | ios::app);
    if (!outFile) {
        cout << "Khong the ghi file GPA.BIN" << endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(mssv), strlen(mssv) + 1);
    outFile.write(reinterpret_cast<const char*>(&gpa), sizeof(float));
    outFile.close();
    cout << "Ma so sinh vien: " << mssv << endl;
    cout << "Diem trung binh tich luy: " << gpa << endl;
    ofstream outputFile("output.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << "Ma so sinh vien: " << mssv << endl;
        outputFile << "Diem trung binh tich luy: " << gpa << endl;
        outputFile << endl;
        outputFile.close();
        cout << "Ghi diem trung binh tich luy vao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
}
void docGPA() {
    ifstream inFile("GPA.BIN", ios::binary);
    if (!inFile) {
        cout << "Khong the doc file GPA.BIN" << endl;
        return;
    }
    ofstream outputFile("output.txt", ios::app);
    if (outputFile.is_open()) {
        char mssv[10];
        float gpa;
        while (inFile.read(reinterpret_cast<char*>(mssv), sizeof(mssv)) && inFile.read(reinterpret_cast<char*>(&gpa), sizeof(float))) {
            outputFile << "Ma so sinh vien: " << mssv << endl;
            outputFile << "Diem trung binh tich luy: " << gpa << endl;
            outputFile << endl;
        }
        outputFile.close();
        cout << "Ghi thong tin diem trung binh tich luy vao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
    inFile.close();
}
void hien_thi_sv_theo_hp(const char* mahp) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    DiemThi dt;
    bool found = false;
    ofstream outputFile("output.txt", ios::app);
    
    if (!outputFile.is_open()) {
        cout << "Khong the mo file output.txt" << endl;
        return;
    }
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.mahp, mahp) == 0) {
            ifstream svFile("SV.BIN", ios::binary);
            SinhVien sv;
            while (svFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
                if (strcmp(sv.mssv, dt.mssv) == 0) {
                    cout << "Ma so sinh vien: " << sv.mssv << endl;
                    cout << "Ho dem: " << sv.hodem << endl;
                    cout << "Ten: " << sv.ten_sv << endl;
                    cout << "Diem: " << dt.diem << endl;
                    cout << endl;
                    
                    // Ghi thông tin vào file "output.txt"
                    outputFile << "Ma so sinh vien: " << sv.mssv << endl;
                    outputFile << "Ho dem: " << sv.hodem << endl;
                    outputFile << "Ten: " << sv.ten_sv << endl;
                    outputFile << "Diem: " << dt.diem << endl;
                    outputFile << endl;
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
    outputFile.close();
}

void hien_thi_sinh_vien_khong_dat_hp(const char* mahp) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    DiemThi dt;
    bool found = false;
    ofstream outputFile("output.txt", ios::app);
    if (!outputFile.is_open()) {
        cout << "Khong the mo file output.txt" << endl;
        return;
    }
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.mahp, mahp) == 0) {
            ifstream svFile("SV.BIN", ios::binary);
            SinhVien sv;
            while (svFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
                if (strcmp(dt.mssv, sv.mssv) == 0) {
                    if (dt.diem <= 4) {
                        cout << "Ma so sinh vien: " << sv.mssv << endl;
                        cout << "Ho dem: " << sv.hodem << endl;
                        cout << "Ten: " << sv.ten_sv << endl;
                        cout << "Diem: " << dt.diem << endl;
                        cout << endl;
                        outputFile << "Ma so sinh vien: " << sv.mssv << endl;
                        outputFile << "Ho dem: " << sv.hodem << endl;
                        outputFile << "Ten: " << sv.ten_sv << endl;
                        outputFile << "Diem: " << dt.diem << endl;
                        outputFile << endl;
                        found = true;
                    }
                }
            }
            svFile.close();
        }
    }
    inFile.close();
    if (!found) {
        cout << "Khong tim thay thong tin diem thi cho hoc phan nay." << endl;
    }
    outputFile.close() ;
}
void hien_thi_hoc_phan_chua_dat() {
    char mssv[10] ;
    cout << "Nhap ma so sinh vien " << endl ;
    cin >> mssv ;
    ifstream FileDiem("DIEMTHI.BIN", ios::binary);
    ifstream FileHP("HP.BIN", ios::binary);
    ofstream outputFile("output.txt", ios::app);
    if (!FileDiem || !FileHP) {
        cout << "Khong the doc file DIEMTHI.BIN hoac HP.BIN" << endl;
        return;
    }
    SinhVien sv ;
    DiemThi dt;
    HocPhan hp;
    bool found = false;
    if (outputFile.is_open()) {
       cout << "Danh sach hoc phan chua dat cua sinh vien ma SV: " << mssv << endl;
       while (FileDiem.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
            if (strcmp(dt.mssv, mssv) == 0 && dt.diem < 4.0f) {
                while (FileHP.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
                    if (strcmp(dt.mahp, hp.mahp) == 0) {
                        cout << "Ma hoc phan: " << hp.mahp << endl;
                        cout << "Ten mon hoc: " << hp.ten_mon_hoc << endl;
                        cout << "So tin chi: " << hp.so_tc << endl;
                        cout << "Diem: " << dt.diem << endl;
                        outputFile << "Ma hoc phan: " << hp.mahp << endl;
                        outputFile << "Ten mon hoc: " << hp.ten_mon_hoc << endl;
                        outputFile << "So tin chi: " << hp.so_tc << endl;
                        outputFile << "Diem: " << dt.diem << endl;
                        outputFile << endl;
                        found = true;
                        break;
                    }
                }
                FileHP.clear();
                FileHP.seekg(0, ios::beg);
            }
        }
        outputFile.close() ;
    }
    FileDiem.close();
    FileHP.close();
    if (!found) {
        cout << "Khong co hoc phan nao chua dat cho sinh vien ma SV: " << mssv << endl;
    }
}
void hienThiGPA(const char* mssv) {
    ofstream outputFile("output.txt", ios::app);
    float gpa;
    if (tinhGPA(mssv)) {
        gpa = tinhGPA(mssv);
        if (outputFile.is_open()) {
        cout << "Ma so sinh vien: " << mssv << endl;
        cout << "Diem trung binh tich luy: " << gpa << endl;
        outputFile << "Ma so sinh vien: " << mssv << endl;
        outputFile << "Diem trung binh tich luy: " << gpa << endl;
        outputFile << endl;
        } else{
            outputFile <<"Khong the mo file output.txt" << endl;
        }
    } else {
        cout << "Ma so sinh vien khong ton tai." << endl;
    }
}
void menu(int luaChon) {
    system("cls");
    cout << "\x1B[1;32m==================== Menu chinh ====================\033[0m" << endl;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Lấy handle của console
    cout << (luaChon == 1 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 1 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "1. Nhap du lieu cho cac file nhi phan" << endl;
    cout << (luaChon == 2 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 2 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "2. Bo sung, xoa, sua chua" << endl;
    cout << (luaChon == 3 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 3 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "3. Tinh diem trung binh tich luy theo thang diem 4" << endl;
    cout << (luaChon == 4 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 4 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "4. Hien thi sinh vien theo hoc phan" << endl;
    cout << (luaChon == 5 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 5 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "5. Hien thi danh sach sinh vien khong dat hoc phan" << endl;
    cout << (luaChon == 6 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 6 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "6. Hien thi danh sach hoc phan sinh vien chua dat" << endl;
    cout << (luaChon == 7 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 7 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "7. Hien thi diem trung binh tich luy sinh vien" << endl;
    cout << (luaChon == 8 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 8 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "0. Quay lai" << endl;
    SetConsoleTextAttribute(hConsole, 15); // Đặt màu chữ về mặc định
    cout << "\x1B[1;32m==================================================\033[0m" << endl;
    cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
    cout << "Nhan Enter de chon mot lua chon" << endl;
}
void menuNhapDuLieu(int luaChon) {
    system("cls");
    cout << "\x1B[1;32m============ Menu Nhap Du Lieu ===================\033[0m" << endl;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Lấy handle của console
    cout << (luaChon == 1 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 1 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "1. Nhap file SV.BIN" << endl;
    cout << (luaChon == 2 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 2 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "2. Nhap file HP.BIN" << endl;
    cout << (luaChon == 3 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 3 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "3. Nhap file DIEMTHI.BIN" << endl;
    cout << (luaChon == 0 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 0 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "0. Quay lai" << endl;
    SetConsoleTextAttribute(hConsole, 15); // Đặt màu chữ về mặc định
    cout << "\x1B[1;32m==================================================\033[0m" << endl;
    cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
    cout << "Nhan Enter de chon mot lua chon" << endl;
}
void ghiLuaChonVaoFile(const string& luaChonText) {
    ofstream file("output.txt", ios::app); // Mở file để ghi và giữ nội dung cũ
    if (file.is_open()) {
        file << luaChonText << endl;
        file.close();
    } else {
        cout << "Failed to open file." << endl;
    }
}
void xuLyMenuNhapDuLieu(int luaChon) {
    int phim;
    int luaChonNhapDuLieu = 1;
    bool tiepTuc= true;
    SinhVien sv ;
    HocPhan hp ;
    DiemThi dt ;
    while (tiepTuc) {
        system("cls");
        menuNhapDuLieu(luaChonNhapDuLieu);
        phim = _getch();

        if (phim == 0 || phim == 224) {
            phim = _getch();
            switch (phim) {
                case 72:  // Mui ten len
                    luaChonNhapDuLieu--;
                    if (luaChonNhapDuLieu < 0) luaChonNhapDuLieu = 3;
                    break;
                case 80:  // Mui ten xuong
                    luaChonNhapDuLieu++;
                    if (luaChonNhapDuLieu > 3) luaChonNhapDuLieu = 0;
                    break;
            }
        } else if (phim == 13) {
            switch (luaChonNhapDuLieu) {
                case 1:
                    ghiLuaChonVaoFile("1. Nhap du lieu vao file SV.BIN") ;
                    bosungSV() ;
                    break;
                case 2:
                    ghiLuaChonVaoFile("2. Nhap du lieu vao file HP.BIN") ;
                    bosungHP() ;
                    break;
                case 3:
                    ghiLuaChonVaoFile("3. Nhap du lieu vao file DIEM.BIN") ;
                    bosungDiem() ;
                    break;
                case 0:
                    cout << "Quay lai Menu chinh." << endl;
                    tiepTuc = false;
                    break;
            }
            if (luaChonNhapDuLieu != 0) {
                cout << "Nhan phim bat ky de tiep tuc nhap du lieu." << endl;
                _getch();
                system("cls");
            }
        }
    }
}
void xuLyMenuBoSung() {
    int luaChon = 1;
    int phim;
    do {
        system("cls");
        cout << "\x1B[1;32m============= Menu Bo Sung ============\033[0m" << endl;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Lấy handle của console
        cout << (luaChon == 1 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 1 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "1. Bo sung thong tin sinh vien" << endl;
        cout << (luaChon == 2 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 2 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "2. Bo sung thong tin hoc phan" << endl;
        cout << (luaChon == 3 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 3 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "3. Bo sung diem thi" << endl;
        cout << (luaChon == 0 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 0 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "0. Quay lai" << endl;
        SetConsoleTextAttribute(hConsole, 15); // Đặt màu chữ về mặc định
        cout << "\033[32m=======================================\033[0m" << endl;
        cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
        cout << "Nhan Enter de chon mot lua chon" << endl;
        phim = _getch();
        if (phim == 0 || phim == 224) {
            phim = _getch();
            switch (phim) {
                case 72:  // Mui ten len
                    luaChon--;
                    if (luaChon < 0) luaChon = 3;
                    break;
                case 80:  // Mui ten xuong
                    luaChon++;
                    if (luaChon > 3) luaChon = 0;
                    break;
            }
        } else if (phim == 13) {
            switch (luaChon) {
                case 1:
                    ghiLuaChonVaoFile("1. Bo sung sinh vien") ;
                    bosungSV();
                    break;
                case 2:
                    ghiLuaChonVaoFile("2. Bo sung hoc phan") ;
                    bosungHP();
                    break;
                case 3:
                    ghiLuaChonVaoFile("3. Bo sung diem") ;
                    bosungDiem();
                    break;
                case 0:
                    cout << "Quay lai Menu bo sung/xoa/sua chua." << endl;
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
                    break;
            }
            if (luaChon != 0) {
                cout << "Nhan phim bat ky de tiep tuc." << endl;
                _getch();
                system("cls");
            }
        }
    } while (luaChon != 0);
}
void xuLyMenuXoa() {
    int luaChon = 1;
    int phim;
    do {
        system("cls");
        cout << "\x1B[1;32m=============== Menu Xoa ==============\033[0m" << endl;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Lấy handle của console
        cout << (luaChon == 1 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 1 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "1. Xoa sinh vien" << endl;
        cout << (luaChon == 2 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 2 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "2. Xoa hoc phan" << endl;
        cout << (luaChon == 3 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 3 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "3. Xoa diem thi" << endl;
        cout << (luaChon == 0 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 0 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "0. Quay lai" << endl;
        SetConsoleTextAttribute(hConsole, 15); // Đặt màu chữ về mặc định
        cout << "\x1B[32m=====================================\033[0m" << endl;
        cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
        cout << "Nhan Enter de chon mot lua chon" << endl;
        phim = _getch();
        if (phim == 0 || phim == 224) {
            phim = _getch();
            switch (phim) {
                case 72:  // Mui ten len
                    luaChon--;
                    if (luaChon < 0) luaChon = 3;
                    break;
                case 80:  // Mui ten xuong
                    luaChon++;
                    if (luaChon > 3) luaChon = 0;
                    break;
            }
        } else if (phim == 13) {
            switch (luaChon) {
                case 1: {
                    ghiLuaChonVaoFile("1. Xóa sinh vien") ;
                    char mssv[10] ;
                    cout << "Nhap ma sinh vien can xoa: ";
                    cin.getline(mssv, 10) ;
                    xoaSinhVien(mssv);
                    ghiLuaChonVaoFile("Danh sach con lai la") ;
                    docSinhVien() ;
                    break;
                }
                case 2: {
                    ghiLuaChonVaoFile("2. Xoa hoc phan") ;
                    char mahp[10];
                    cout << "Nhap ma hoc phan can xoa: ";
                    cin.getline(mahp,10);
                    xoaHocPhan(mahp);
                    ghiLuaChonVaoFile("Danh sach con lai la") ;
                    docHocPhan() ;
                    break;
                }
                case 3: {
                    ghiLuaChonVaoFile("3. Xoa diem thi") ;
                    char mahp[10];
                    char mssv[10];
                    cout << "Nhap ma hoc phan can xoa diem: ";
                    cin.getline(mahp, 10);
                    cout << "Nhap ma sinh vien can xoa diem: ";
                    cin.getline(mssv,10);
                    xoaDiemThi(mahp, mssv);
                    ghiLuaChonVaoFile("Danh sach con lai la") ;
                    docDiemThi() ;
                    break;
                }
                case 0:
                    cout << "Quay lai Menu bo sung/xoa/sua chua." << endl;
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
                    break;
            }

            if (luaChon != 0) {
                cout << "Nhan phim bat ky de tiep tuc." << endl;
                _getch();
                system("cls");
            }
        }
    } while (luaChon != 0);
}
void xuLyMenuSuaChua() {
    int luaChon = 1;
    int phim;
    do {
        system("cls");
        cout << "\033[1;32m=============== Menu Sua ==============\033[0m" << endl;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Lấy handle của console
        cout << (luaChon == 1 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 1 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "1. Sua sinh vien" << endl;
        cout << (luaChon == 2 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 2 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "2. Sua hoc phan" << endl;
        cout << (luaChon == 3 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 3 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "3. Sua diem thi" << endl;
        cout << (luaChon == 0 ? "\x1B[1;32m-> \033[0m" : "  ");
        SetConsoleTextAttribute(hConsole, luaChon == 0 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
        cout << "0. Quay lai" << endl;
        SetConsoleTextAttribute(hConsole, 15); // Đặt màu chữ về mặc định
        cout << "\x1B[32m=====================================\033[0m" << endl;
        cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
        cout << "Nhan Enter de chon mot lua chon" << endl;
        phim = _getch();
        if (phim == 0 || phim == 224) {
            phim = _getch();
            switch (phim) {
                case 72:  // Mui ten len
                    luaChon--;
                    if (luaChon < 0) luaChon = 3;
                    break;
                case 80:  // Mui ten xuong
                    luaChon++;
                    if (luaChon > 3) luaChon = 0;
                    break;
            }
        } else if (phim == 13) {
            switch (luaChon) {
                case 1: {
                    ghiLuaChonVaoFile("1. Sua sinh vien") ;
                    char mssv[10] ;
                    cout << "Nhap ma sinh vien can sua: ";
                    cin.getline(mssv,10);
                    suaSinhVien(mssv);
                    break;
                }
                case 2: {
                    ghiLuaChonVaoFile("2. Sua hoc phan") ;
                    char mahp[10];
                    cout << "Nhap ma hoc phan can sua: ";
                    cin.getline(mahp,10);
                    suaHocPhan(mahp);
                    break;
                }
                case 3: {
                    ghiLuaChonVaoFile("3. Sua diem thi") ;
                    char mahp[10];
                    char mssv[10] ;
                    cout << "Nhap ma hoc phan can sua diem: ";
                    cin.getline(mahp,10) ;
                    cout << "Nhap ma sinh vien can sua diem: ";
                    cin.getline(mssv,10);
                    suaDiemThi(mahp, mssv);
                    break;
                }
                case 0:
                    cout << "Quay lai Menu bo sung/xoa/sua chua." << endl;
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
                    break;
            }

            if (luaChon != 0) {
                cout << "Nhan phim bat ky de tiep tuc." << endl;
                _getch();
                system("cls");
            }
        }
    } while (luaChon != 0);
}
void hienThiMenuBoSungXoaSua(int luaChon) {
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Lấy handle của console
    cout << "\x1B[1;32m============= Menu bo sung xoa sua =============\033[0m" << endl;
    cout << (luaChon == 1 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 1 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "1. Bo sung" << endl;
    cout << (luaChon == 2 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 2 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "2. xoa" << endl;
    cout << (luaChon == 3 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 3 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "3. sua chua" << endl;
    cout << (luaChon == 0 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 0 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "0. Quay lai" << endl;
    SetConsoleTextAttribute(hConsole, 15); // Đặt màu chữ về mặc định
    cout << "\x1B[32m=====================================\033[0m" << endl;
    cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
    cout << "Nhan Enter de chon mot lua chon" << endl;
}
void xuLyMenuChinh() {
    // Đoạn mã để hiển thị menu chính ở đây
}
void xuLyMenuBoSungXoaSua(int luaChon) {
    int phim;
    int luaChonBXS = 1;
    do {
        system("cls");
        hienThiMenuBoSungXoaSua(luaChonBXS);

        phim = _getch();
        if (phim == 0 || phim == 224) {
            phim = _getch();
            switch (phim) {
                case 72:  // Mui ten len
                    luaChonBXS--;
                    if (luaChonBXS < 0) luaChonBXS = 3;
                    break;
                case 80:  // mui ten xuong
                    luaChonBXS++;
                    if (luaChonBXS > 3) luaChonBXS = 0;
                    break;
            }
        } else if (phim == 13) {
            switch (luaChonBXS) {
                case 1:
                    xuLyMenuBoSung();
                    break;
                case 2:
                    xuLyMenuXoa();
                    break;
                case 3:
                    xuLyMenuSuaChua();
                    break;
                case 0:
                    cout << "Quay lai Menu chinh." << endl;
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
                    break;
            }
            if (luaChonBXS != 0) {
                cout << "Nhan phim bat ky de tro ve Menu chinh." << endl;
                _getch();
            }
        }
    } while (luaChonBXS != 0);
    xuLyMenuChinh(); // Hiển thị lại menu chính sau khi thoát vòng lặp
}
void xuLyLuaChon(int luaChon) {
    switch (luaChon) {
        case 1: {
            int nhapDL;
            do {
                menuNhapDuLieu(nhapDL);
                nhapDL = _getch() - '0';
                xuLyMenuNhapDuLieu(nhapDL);
                if (nhapDL != 0) {
                    cout << "Nhan phim bat ky de tiep tuc nhap du lieu." << endl;
                    _getch();
                    system("cls");
                }
            } while (nhapDL != 0);
            break;
        }
        case 2: {
            int bxs;
            do {
                hienThiMenuBoSungXoaSua(bxs);
                bxs = _getch() - '0';
                xuLyMenuBoSungXoaSua(bxs);
                if (bxs != 0) {
                    cout << "Nhan phim bat ky de tiep tuc." << endl;
                    _getch();
                    system("cls");
                }
            } while (bxs != 0);
            break;
        }
       case 3: {
            ghiLuaChonVaoFile("3. Tinh diem trung binh tich luy cua sinh vien ") ;
            char mssv[10];
            cout << "Nhap ma sinh vien: ";
            cin >> mssv;
            float gpa = tinhGPA(mssv);
            ghiGPA(mssv, gpa);
            break;

        }
        case 4: {
            ghiLuaChonVaoFile("4. Hien thi sinh vien theo hoc phan") ;
            char mahp[10];
            cout << "Nhap ma hoc phan: ";
            cin >> mahp;
            hien_thi_sv_theo_hp(mahp);
            break;
        }
        case 5: {
            ghiLuaChonVaoFile("5. Hien thi danh sach sinh vien chua dat hoc phan ") ;
            char mahp[10];
            cout << "Nhap ma hoc phan: ";
            cin >> mahp;
            hien_thi_sinh_vien_khong_dat_hp(mahp);
            break;
        }
        case 6:{
            ghiLuaChonVaoFile("6. Hien thi danh sach hoc phan sinh vien chua dat ") ;
            cout << " Danh sach hoc phan chua dat " << endl;
            hien_thi_hoc_phan_chua_dat();
            break;
        }
        case 7:{
            ghiLuaChonVaoFile("7. Hien thi GPA sinh vien ") ;
            char mssv[10] ;
            cout << "Nhap ma so sinh vien: ";
            cin >> mssv;
            hienThiGPA(mssv);
            break;
        }
        case 0: {
            cout << "Thoat chuong trinh" << endl;
            break;
        }
        default:{
            cout << "Lua chon khong hop le, vui long nhap lai!" << endl;
            break;
        }
    }
    if (luaChon != 0) {
        cout << endl << "Nhan phim bat ky de quay lai menu." << endl;
        _getch();
        system("cls");
        menu(luaChon);
    }
}
int main(int argc, char* argv[]) {
    int luaChon = 1;
    int phim;
    while (true) {
        menu(luaChon);
        phim = _getch();
        if (phim == 0 || phim == 224) {
            phim = _getch();
            switch (phim) {
                case 72:  // Mui ten len
                    luaChon--;
                    if (luaChon < 0) luaChon = 8;
                    break;
                case 80:  // Mui ten xuong
                    luaChon++;
                    if (luaChon > 10) luaChon = 0;
                    
                    break;
            }
        } else if (phim == 13) {
            if (luaChon == 1) {
                xuLyMenuNhapDuLieu(luaChon);
            } else if (luaChon == 2) {
                xuLyMenuBoSungXoaSua(luaChon);
            } else {
                xuLyLuaChon(luaChon);
            }
            if (luaChon == 0) {
                cout << "Thoat chuong trinh." << endl;
                break;
            }
        }
    }
    return 0;
}


