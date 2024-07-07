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
    // Kiểm tra độ dài ngày sinh
    if (strlen(ngay_sinh) != 10) {
        cout << "Dinh dang ngay sinh khong hop le! Vui long nhap lai." << endl;
        return false;
    }

    // Kiểm tra và chuyển đổi định dạng ngày sinh
    int ngay, thang, nam;
    if (sscanf(ngay_sinh, "%d/%d/%d", &ngay, &thang, &nam) != 3) {
        cout << "Dinh dang ngay sinh khong hop le! Vui long nhap lai." << endl;
        return false;
    }

    // Kiểm tra tính hợp lệ của ngày, tháng, năm
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
    return (diem >= 0.0 && diem <= 10.0 && fmod(diem * 10, 5) == 0);
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
    cout << "Nhap ma so sinh vien: " << endl;
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
// Hàm nhập thông tin học phần
HocPhan nhap_hp() {
    HocPhan hp;
    cout << "Nhap ma hoc phan: ";
    cin >> hp.mahp;
    cin.ignore(); // Xóa bỏ ký tự newline
    cout << "Nhap ten mon hoc: ";
    cin.getline(hp.ten_mon_hoc, 50);
    cout << "Nhap so tin chi: ";
    cin >> hp.so_tc;
    return hp;
}

// Hàm nhập điểm thi
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

// ghi sinh vien vao file SV.BIN
void ghiSinhVien(const SinhVien& sv) {
    ofstream file("SV.BIN", ios::binary | ios::app);
    if(file.is_open()) {
        file.write(reinterpret_cast<const char*>(&sv), sizeof(SinhVien));
        file.close();
        cout << "Ghi sinh vien vao file SV.BIN thanh cong" << endl;
    }else cout<<"khong the mo file SV.BIN" << endl ;
    ofstream textFile("output.txt", ios::app);
    if (textFile.is_open()) {
        textFile << "Ma so sinh vien: " << sv.mssv << endl;
        textFile << "Ho dem: " << sv.hodem << endl;
        textFile << "Ten: " << sv.ten_sv << endl;
        textFile << "Gioi tinh: " << sv.gioi_tinh << endl;
        textFile << "Ngay Sinh: " << sv.ngay_sinh << endl;
        textFile << endl;
        cout << "Ghi sinh vien vao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
    textFile.close();
    
}
// đọc sinh vien vào file SV.BIN
void docSinhVien() {
    ifstream file("SV.BIN", ios::binary);
    ofstream outputFile("output.txt",ios::app);
    SinhVien sv;
    while (file.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        outputFile << "MSSV: " << sv.mssv << endl;
        outputFile << "Ho dem: " << sv.hodem << endl;
        outputFile << "Ten sinh vien: " << sv.ten_sv << endl;
        outputFile << "Gioi tinh: " << sv.gioi_tinh << endl;
        outputFile << "Ngay sinh: " << sv.ngay_sinh << endl;
        outputFile << endl;
    }
    file.close();
}

void ghiHocPhan(const HocPhan& hp) {
    ofstream file("HP.BIN", ios::binary | ios::app);
    file.write(reinterpret_cast<const char*>(&hp), sizeof(HocPhan));
    file.close();
    ofstream textFile("output.txt", ios::app);
    if (textFile.is_open()) {
        textFile << "Nhap ma hoc phan: " << hp.mahp << endl;
        textFile << "Nhap ten mon hoc: " << hp.ten_mon_hoc << endl;
        textFile << "Nhap so tin chi: " << hp.so_tc << endl;
        cout << "Ghi hoc phan vao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
    textFile.close();
}

void docHocPhan() {
    ifstream file("HP.BIN", ios::binary) ;
    ofstream outputFile("output.txt",ios::app); 
    HocPhan hp;
    while (file.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        outputFile << "Ma hoc phan: " << hp.mahp << endl;
        outputFile << "Ten mon hoc: " << hp.ten_mon_hoc << endl;
        outputFile << "So tin chi: " << hp.so_tc << endl;
        outputFile << endl;
    }

    file.close();
}

void ghiDiemThi(const DiemThi& dt) {
    ofstream file("DIEMTHI.BIN", ios::binary | ios::app);
    file.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));
    file.close();
    ofstream outputFile("output.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << "Nhap ma hoc phan: " << dt.mahp << endl;
        outputFile << "Nhap ma sinh vien: " << dt.mssv << endl;
        outputFile << "Nhap diem: " << dt.diem << endl;

        cout << "Ghi hoc phan vao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
    outputFile.close();
}

void docDiemThi() {
    ifstream file("DIEMTHI.BIN", ios::binary);
    ofstream outputFile("output.txt",ios::app);
    DiemThi dt;
    while (file.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        outputFile << "Ma hoc phan: " << dt.mahp << endl;
        outputFile << "Ma so sinh vien: " << dt.mssv << endl;
        outputFile<< "Diem thi: " << dt.diem << endl;
        outputFile << endl;
    }
    file.close();
    outputFile.close() ;
}
void bosungSV() {
    ofstream outputFile("output.txt", ios::app) ;
    SinhVien sv = NhapSV();
    
    // kiểm tra mã số sinh viên đã tồn tại hay chưa?
    if (checkDuplicateMSSV(sv.mssv)) {
        outputFile<< "Ma so Sinh Vien da ton tai. Khong the bo sung du lieu." << endl;
        return ;
    }
    ghiSinhVien(sv);
    outputFile << "Da them sinh vien " << sv.mssv << " vao file SV.BIN" << sv.mssv<< endl;
    outputFile.close() ;
}
void bosungHP() {
    ofstream outputFile("output.txt",ios::app);
    HocPhan hp = nhap_hp();
    // kiểm tra học phần tồn tại hay chưa
    if (checkDuplicateMaHP(hp.mahp)) {
        outputFile << "Ma hoc phan da ton tai. Khong the bo sung du lieu." << endl;
        return ;
    }
    ghiHocPhan(hp);
    outputFile << "Da them hoc phan " << hp.mahp << " vao file HP.BIN" << hp.mahp<<endl;
    outputFile.close() ;
}
void bosungDiem() {
    ofstream outputFile("output.txt",ios::app);
    DiemThi dt = nhap_diem_thi();
    // kiểm tra tồn tại mã học phần
    if (!checkDuplicateMaHP(dt.mahp)) {
        outputFile << "Ma hoc phan khong ton tai trong file HP.BIN." << endl;
        return;
    }
    // kiểm tra tồn tại mã số sinh viên
    if (!checkDuplicateMSSV(dt.mssv)) {
        outputFile << "Ma sinh vien khong ton tai trong file SV.BIN." << endl;
        return;
    }
    // kiểm tra tồn tại mã học phần và mã sinh viên 
    if (checkDuplicateDiem(dt.mahp, dt.mssv)) {
        outputFile << "Diem thi da ton tai. Khong the bo sung du lieu." << endl;
    }
    ghiDiemThi(dt);
    cout << "Da them diem thi vao file DIEMTHI.BIN" << endl;
    outputFile.close() ;
}
void xoaSinhVien(const char* mssv) {
    ifstream inFile("SV.BIN", ios::binary);
    ofstream tempFile("temp.BIN", ios::binary); // File tạm
    ofstream outputFile("output.txt",ios::app);
    SinhVien sv;
    while (inFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        if (strcmp(sv.mssv, mssv) != 0) {
            tempFile.write(reinterpret_cast<const char*>(&sv), sizeof(SinhVien));
        }
    }
    inFile.close();
    tempFile.close();
    // Xóa file SV.BIN cũ
    remove("SV.BIN");
    // Đổi tên file temp.BIN thành SV.BIN mới
    rename("temp.BIN", "SV.BIN");
    outputFile << "Da xoa thong tin sinh vien co mssv: " << mssv << endl;
    outputFile.close() ;
}
void xoaHocPhan(const char* mahp) {
    ifstream inFile("HP.BIN", ios::binary);
    ofstream tempFile("temp.BIN", ios::binary);  // File tạm
    ofstream outputFile("output.txt") ;
    HocPhan hp;
    while (inFile.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        if (strcmp(hp.mahp, mahp) != 0) {
            tempFile.write(reinterpret_cast<const char*>(&hp), sizeof(HocPhan));
        }
    }

    inFile.close();
    tempFile.close();

    // Xóa file HP.BIN cũ
    remove("HP.BIN");
    // Đổi tên file temp.BIN thành HP.BIN mới
    rename("temp.BIN", "HP.BIN");

    outputFile << "Da xoa thong tin hoc phan" << mahp << endl;
    outputFile.close() ;
}
void xoaDiemThi(const char* mahp, const char* mssv) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    ofstream tempFile("temp.BIN", ios::binary);  // File tạm
    ofstream outputFile("output.txt",ios::app);
    DiemThi dt;
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.mahp, mahp) != 0 || strcmp(dt.mssv, mssv) != 0) {
            tempFile.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));
        }
    }

    inFile.close();
    tempFile.close();

    // Xóa file DIEMTHI.BIN cũ
    remove("DIEMTHI.BIN");
    // Đổi tên file temp.BIN thành DIEMTHI.BIN mới
    rename("temp.BIN", "DIEMTHI.BIN");
    outputFile << "Da xoa thong tin diem thi hoc phan "  <<dt.mahp << " cua sinh vien " << dt.mssv << endl;
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
            // Đặt con trỏ đọc/ghi về vị trí đầu bản ghi cần sửa
            file.seekp(-static_cast<int>(sizeof(SinhVien)), ios::cur);
            // Ghi thông tin sinh viên đã sửa vào vị trí hiện tại
            file.write(reinterpret_cast<const char*>(&sv), sizeof(SinhVien));
            outputFile << "Da sua thong tin sinh vien" << endl;
            outputFile << "Thong tin sinh vien sau khi sua:" << endl;
            outputFile << "Ma SV: " << sv.mssv << endl;
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

            // Đặt con trỏ đọc/ghi về vị trí đầu bản ghi cần sửa
            file.seekp(-static_cast<int>(sizeof(HocPhan)), ios::cur);

            // Ghi thông tin hoc phan đã sửa vào vị trí hiện tại
            file.write(reinterpret_cast<const char*>(&hp), sizeof(HocPhan));

            outputFile << "Da sua thong tin hoc phan " << hp.mahp << endl;
            outputFile << "Thong tin hoc phan sau khi sua:" << endl;
            outputFile << "Ma HP: " << hp.mahp << endl;
            outputFile << "Ten HP: " << hp.ten_mon_hoc << endl;
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
            outputFile << "Nhap thong tin diem thi moi: " << endl;
            DiemThi dt = nhap_diem_thi();

            // Đặt con trỏ đọc/ghi về vị trí đầu bản ghi cần sửa
            file.seekp(-static_cast<int>(sizeof(DiemThi)), ios::cur);

            // Ghi thông tin diem thi đã sửa vào vị trí hiện tại
            file.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));
            outputFile << "Da sua thong tin diem thi co ma hoc phan " <<dt.mahp << " diem" << dt.diem << endl;
            outputFile << "Thong tin diem thi sau khi sua:" << endl;
            outputFile << "Ma HP: " << dt.mahp << endl;
            outputFile << "Ma SV: " << dt.mssv << endl;
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
float tinhDTB(const char* mssv) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    
    if (!inFile) {
        cout << "Khong the doc file DIEMTHI.BIN" << endl;
        return 0.0f;
    }

    DiemThi dt;
    float tong = 0.0f;
    int so_tc = 0;

    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.mssv, mssv) != 0) {
            continue;
        }

        HocPhan hp;
        ifstream hpFile("HP.BIN", ios::binary);

        while (hpFile.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
            if (strcmp(dt.mahp, hp.mahp) == 0) {
                so_tc += hp.so_tc;
                break;
            }
        }

        hpFile.close();
        tong += dt.diem * hp.so_tc;
    }

    inFile.close();

    // Kiểm tra nếu không có học phần nào thỏa mãn
    if (so_tc == 0) {
        cout << "Khong tim thay sinh vien co MSSV la: " << mssv << endl;
        return 0.0f;
    }

    // Tính điểm trung bình trên thang điểm 4
    float dtb = (tong / so_tc) / 2.5f;
    int dtb_rounded = static_cast<int>(round(dtb * 100)) % 100;
    dtb = static_cast<float>(dtb_rounded) / 100.0f;
    return dtb;
}



// Hàm ghi điểm trung bình tích lũy (GPA) vào file DTB.BIN
void ghiDTB(const char* mssv, const float dtb) {
    ofstream outFile("DTB.BIN", ios::binary | ios::app);
    if (!outFile) {
        cout << "Khong the ghi file DTB.BIN" << endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(mssv), strlen(mssv) + 1);
    outFile.write(reinterpret_cast<const char*>(&dtb), sizeof(float));
    outFile.close();
    ofstream outputFile("output.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << "Ma so sinh vien: " << mssv << endl;
        outputFile << "DTCTL: " << dtb << endl;
        outputFile << endl;
        outputFile.close();
        cout << "Ghi diem trung binh tich luyvao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
    outputFile.close() ;
}
// Hàm đọc điểm trung bình tích lũy (GPA) vào file DTB.BIN
void docDTB() {
    ifstream inFile("DTB.BIN", ios::binary);
    ofstream outputFile("output.txt", ios::app);
    if (!inFile) {
        cout << "Khong the doc file DTB.BIN" << endl;
        return;
    }

    if (outputFile.is_open()) {
        int mssv;
        float dtb;
        while (inFile.read(reinterpret_cast<char*>(&mssv), sizeof(int)) && inFile.read(reinterpret_cast<char*>(&dtb), sizeof(float))) {
            outputFile << "Ma so sinh vien: " << mssv << endl;
            outputFile << "Diem trung binh tich luy: " << dtb << endl;
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
    if (outputFile.is_open()) {
        while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
            if (strcmp(dt.mahp, mahp) == 0) {
                ifstream svFile("SV.BIN", ios::binary);
                SinhVien sv;
                while (svFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
                    if (strcmp(sv.mssv ,dt.mssv) ==0) {
                        outputFile << "Ma so sinh vien: " << sv.mssv << endl;
                        outputFile << "Ho dem: " << sv.hodem << endl;
                        outputFile << "Ten: " << sv.ten_sv << endl;
                        outputFile << "Diem: " << dt.diem << endl;
                        outputFile << endl;
                   }
                }
            svFile.close() ;
            found = true;
            }
        }
        outputFile.close() ;
    } else cout << "khong the mo file output.txt" << endl;
    inFile.close();

    if (!found) {
        cout << "Khong tim thay thong tin diem thi cho hoc phan nay." << endl;
    }
}
void hien_thi_sinh_vien_khong_dat_hp(const char* mahp) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    DiemThi dt;

    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.mahp, mahp) == 0) {
            ifstream svFile("SV.BIN", ios::binary);
            SinhVien sv;
            while (svFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
                if (strcmp(dt.mssv, sv.mssv) == 0) {
                    if (dt.diem <= 4) {
                        cout << "Ma SV: " << sv.mssv << endl;
                        cout << "Ho dem: " << sv.hodem << endl;
                        cout << "Ten: " << sv.ten_sv << endl;
                        cout << "Diem: " << dt.diem << endl;
                        cout << endl;
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
void hienThiDTB(const char* mssv) {
    ofstream outputFile("output.txt", ios::app);
    float dtb;
    if (tinhDTB(mssv)) {
        dtb = tinhDTB(mssv);
        if (outputFile.is_open()) {
        outputFile << "Ma so sinh vien: " << mssv << endl;
        outputFile << "Diem trung binh tich luy: " << dtb << endl;
        } else{
            outputFile <<"Khong the mo file output.txt" << endl;
        }
    } else {
        cout << "Ma so sinh vien khong ton tai." << endl;
    }
}
#include <windows.h>

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
    cout << "4. Hien thi thong tin sinh vien hoc phan" << endl;
    
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
    cout << "8. Sinh vien" << endl;
    
    cout << (luaChon == 9 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 9 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "9. Hoc phan" << endl;
    
    cout << (luaChon == 10 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 10 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "10. Diem thi" << endl;
    
    cout << (luaChon == 0 ? "\x1B[1;32m-> \033[0m" : "  ");
    SetConsoleTextAttribute(hConsole, luaChon == 0 ? 10 : 15); // Màu xanh lá cây hoặc mặc định
    cout << "0. Quay lai" << endl;
    
    SetConsoleTextAttribute(hConsole, 15); // Đặt màu chữ về mặc định
    
    cout << "\x1B[1;32m==================================================\033[0m" << endl;
    cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
    cout << "Nhan Enter de chon mot lua chon" << endl;
}

#include <windows.h>

void menuNhapDuLieu(int luaChon) {
    system("cls");
    cout << "\x1B[1;32m============ Menu Nhap Du Lieu ===================\033[0m" << std::endl;
    
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
                    NhapSV() ;
                    ghiSinhVien(sv);
                    break;
                case 2:
                    nhap_hp() ;
                    ghiHocPhan(hp) ;
                    break;
                case 3:
                    nhap_diem_thi() ;
                    ghiDiemThi(dt) ;
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
                    bosungSV();
                    break;
                case 2:
                    bosungHP();
                    break;
                case 3:
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
                    char mssv[10] ;
                    cout << "Nhap ma sinh vien can xoa: ";
                    cin.getline(mssv, 10) ;
                    xoaSinhVien(mssv);
                    break;
                }
                case 2: {
                    char mahp[10];
                    cout << "Nhap ma hoc phan can xoa: ";
                    cin.ignore();
                    cin.getline(mahp,10);
                    xoaHocPhan(mahp);
                    break;
                }
                case 3: {
                    char mahp[10];
                    char mssv[10];
                    cout << "Nhap ma hoc phan can xoa diem: ";
                    cin.ignore();
                    cin.getline(mahp, 10);
                    cout << "Nhap ma sinh vien can xoa diem: ";
                    cin.getline(mssv,10);
                    xoaDiemThi(mahp, mssv);
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
        std::cout << "\033[1;32m=============== Menu Sua ==============\033[0m" << std::endl;

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
                    char mssv[10] ;
                    cout << "Nhap ma sinh vien can sua: ";
                    cin.getline(mssv,10);
                    suaSinhVien(mssv);
                    break;
                }
                case 2: {
                    char mahp[10];
                    cout << "Nhap ma hoc phan can sua: ";
                    cin.getline(mahp,10);
                    suaHocPhan(mahp);
                    break;
                }
                case 3: {
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

    std::cout << "\x1B[1;32m============= Menu bo sung xoa sua =============\033[0m" << std::endl;

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
            char mssv[10];
            cout << "Nhap ma sinh vien: ";
            cin >> mssv;
            float dtb = tinhDTB(mssv);
            cout << "Ma so sinh vien: " << mssv << endl;
            cout << "GPA: " << dtb << endl;
            break;

        }
        case 4: {
            char mahp[10];
            cout << "Nhap ma hoc phan: ";
            cin >> mahp;
            hien_thi_sv_theo_hp(mahp);
            break;
        }
        case 5: {
            char mahp[10];
            cout << "Nhap ma hoc phan: ";
            cin >> mahp;
            hien_thi_sinh_vien_khong_dat_hp(mahp);
            break;
        }
        case 6:{
            cout << " Danh sach hoc phan chua dat " << endl;

            hien_thi_hoc_phan_chua_dat();
            break;
        }
        case 7:{
            char mssv[10] ;
            cout << "Nhap ma so sinh vien: ";
            cin >> mssv;
            hienThiDTB(mssv);
            break;
            
        }
        case 8:
            cout << "======= Danh sach sinh vien =======" << endl;
            docSinhVien();
            break;
        case 9:
            cout << "======= Danh sach hoc phan =======" << endl;
            docHocPhan();
            break;
        case 10:
            cout << "======= Danh sach diem =======" << endl;
            docDiemThi();
            break;
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


