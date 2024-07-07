#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
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
void nhapSinhVien(SinhVien& sv) {
    cout << "Nhap ma sinh vien: ";
    cin >> sv.maSV;
    cin.ignore();

    cout << "Nhap ho dem sinh vien: ";
    cin.getline(sv.hoDem, sizeof(sv.hoDem));

    cout<< "Nhap ten sinh vien: ";
    cin.getline(sv.Ten, sizeof(sv.Ten));

    cout << "Nhap gioi tinh: ";
    cin.getline(sv.gioiTinh, sizeof(sv.gioiTinh));

    bool ngaySinhHopLe = false;
    do {
        cout << "Nhap ngay sinh (theo dang dd/mm/yyyy): ";
    string ngaySinh;
        getline(cin, ngaySinh);

        // Kiểm tra và chuyển đổi định dạng ngày sinh
        int ngay, thang, nam;
        if (sscanf(ngaySinh.c_str(), "%d/%d/%d", &ngay, &thang, &nam) != 3) {
            cout << "Dinh dang ngay sinh khong hop le! Vui long nhap lai." << endl;
        } else {
            // Kiểm tra tính hợp lệ của ngày, tháng, năm
            // ... (có thể thêm kiểm tra logic theo quy tắc của ngày sinh)

            // Gán giá trị chuyển đổi vào trường ngaySinh của SinhVien
            sprintf(sv.ngaySinh, "%02d/%02d/%04d", ngay, thang, nam);
            ngaySinhHopLe = true;
        }
    } while (!ngaySinhHopLe);
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

    while (true) {
        cout << "Nhap diem (0.0 - 10.0): ";
        cin >> dt.diem;

        // Kiểm tra điểm hợp lệ
        if (dt.diem >= 0.0 && dt.diem <= 10.0 && static_cast<int>(dt.diem*10) % 5 == 0) {
            break; // Điểm hợp lệ, thoát khỏi vòng lặp
        } else {
            cout << "Diem khong hop le. Vui long nhap lai!" << endl;
        }
    }
}
// Hàm ghi thông tin sinh viên vào file SV.BIN
void ghiSinhVien(const SinhVien& sv) {
    ofstream outFile("SV.BIN", ios::binary | ios::app);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(&sv), sizeof(SinhVien));
        outFile.close();
        cout << "Ghi sinh vien vao file SV.BIN thanh cong." << endl;
    } else {
        cout << "Khong the mo file SV.BIN." << endl;
    }

    ofstream textFile("output.txt", ios::app);
    if (textFile.is_open()) {
        textFile << "Ma SV: " << sv.maSV << endl;
        textFile << "Ho dem: " << sv.hoDem << endl;
        textFile << "Ten: " << sv.Ten << endl;
        textFile << "Gioi tinh: " << sv.gioiTinh << endl;
        textFile << "Ngay Sinh: " << sv.ngaySinh << endl;
        textFile << endl;

        cout << "Ghi sinh vien vao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
    textFile.close();
}


// Hàm ghi thông tin học phần vào file HP.BIN
void ghiHocPhan(const HocPhan& hp) {
    ofstream outFile("HP.BIN", ios::binary | ios::app);
    outFile.write(reinterpret_cast<const char*>(&hp), sizeof(HocPhan));
    outFile.close();
    ofstream textFile("output.txt", ios::app);
    if (textFile.is_open()) {
        textFile << "Nhap ma hoc phan: " << hp.maHP << endl;
        textFile << "Nhap ten mon hoc: " << hp.tenMonHoc << endl;
        textFile << "Nhap so tin chi: " << hp.soTinChi << endl;
        cout << "Ghi hoc phan vao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
    textFile.close();
}

// Hàm ghi điểm thi vào file DIEMTHI.BIN
void ghiDiemThi(const DiemThi& dt) {
    ofstream outFile("DIEMTHI.BIN", ios::binary | ios::app);
    outFile.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));
    outFile.close();
    ofstream textFile("output.txt", ios::app);
    if (textFile.is_open()) {
        textFile << "Nhap ma hoc phan: " << dt.maHP << endl;
        textFile << "Nhap ma sinh vien: " << dt.maSV << endl;
        textFile << "Nhap diem: " << dt.diem << endl;

        cout<< "Ghi hoc phan vao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
    textFile.close();
}

// Hàm đọc thông tin sinh viên từ file SV.BIN
void docSinhVien() {
    ifstream inFile("SV.BIN", ios::binary);
    ofstream outputFile("output.txt",ios::app);
    SinhVien sv;
    while (inFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        outputFile << "Ma SV: " << sv.maSV << endl;
        outputFile << "Ho dem: " << sv.hoDem << endl;
        outputFile << "Ten: " << sv.Ten << endl;
        outputFile << "Gioi tinh: " << sv.gioiTinh << endl;
        outputFile << "Ngay Sinh: " << sv.ngaySinh << endl;
        outputFile << endl;
    }
    inFile.close();
    outputFile.close();
}

// Hàm đọc thông tin học phần từ file HP.BIN
void docHocPhan() {
    ifstream inFile("HP.BIN", ios::binary);
    ofstream outputFile("output.txt",ios::app);
    HocPhan hp;
    while (inFile.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        outputFile << "Ma HP: " << hp.maHP << endl;
        outputFile << "Ten mon hoc: " << hp.tenMonHoc << endl;
        outputFile<< "So tin chi: " << hp.soTinChi << endl;
        outputFile << endl;
    }
    inFile.close();
    outputFile.close();
}

// Hàm đọc điểm thi từ file DIEMTHI.BIN
void docDiemThi() {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    ofstream outputFile("output.txt",ios::app);
    DiemThi dt;
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        outputFile << "Ma HP: " << dt.maHP << endl;
        outputFile << "Ma SV: " << dt.maSV << endl;
        outputFile << "Diem: " << dt.diem << endl;
        outputFile << endl;
    }
    inFile.close();
    outputFile.close();
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
    ofstream outputFile("output.txt", ios::app);  // Mở tệp ở chế độ ghi tiếp
    SinhVien sv;
    nhapSinhVien(sv);

    if (maSinhVienDaTonTai(sv.maSV)) {
        ofstream outputFile("output.txt",ios::app);
        outputFile << "Ma sinh vien da ton tai trong file SV.BIN." << endl;
        outputFile.close();
        return;
    }

    ghiSinhVien(sv);

    
    cout << "Da them sinh vien vao file SV.BIN" << endl;
    outputFile.close();
}


void bosungHocPhan() {
    ofstream outputFile("output.txt",ios::app);
    HocPhan hp;
    nhapHocPhan(hp);

    if (maHocPhanDaTonTai(hp.maHP)) {
        outputFile << "Ma hoc phan da ton tai trong file HP.BIN." << endl;
        return;
    }

    ghiHocPhan(hp);
    cout << "Da them hoc phan vao file HP.BIN" << endl;
    outputFile.close() ;
}
void bosungDiemThi() {
    ofstream outputFile("output.txt",ios::app);
    DiemThi dt;
    nhapDiemThi(dt);

    if (!maHocPhanDaTonTai(dt.maHP)) {
        outputFile << "Ma hoc phan khong ton tai trong file HP.BIN." << endl;
        return;
    }

    if (!maSinhVienDaTonTai(dt.maSV)) {
        cout << "Ma sinh vien khong ton tai trong file SV.BIN." << endl;
        return;
    }

    if (diemThiDaTonTai(dt.maHP, dt.maSV)) {
        outputFile << "Diem thi da ton tai trong file DIEMTHI.BIN." << endl;
        return;
    }

    ghiDiemThi(dt);
    outputFile << "Da them diem thi vao file DIEMTHI.BIN" << endl;
    outputFile.close() ;
}
void capNhatDiemThi() {
    ifstream inFile("DIEMTHI.BIN", ios::binary|ios::app);
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

void xoaSinhVien(int maSV) {
    ifstream inFile("SV.BIN", ios::binary);
    ofstream tempFile("temp.BIN", ios::binary);  // File tạm
    ofstream outputFile("output.txt",ios::app);
    SinhVien sv;
    while (inFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        if (sv.maSV != maSV) {
            tempFile.write(reinterpret_cast<const char*>(&sv), sizeof(SinhVien));
        }
    }

    inFile.close();
    tempFile.close();

    // Xóa file SV.BIN cũ
    remove("SV.BIN");
    // Đổi tên file temp.BIN thành SV.BIN mới
    rename("temp.BIN", "SV.BIN");

    outputFile << "Da xoa thong tin sinh vien" << endl;
    outputFile.close() ;
}

void xoaHocPhan(const char* maHP) {
    ifstream inFile("HP.BIN", ios::binary);
    ofstream tempFile("temp.BIN", ios::binary);  // File tạm
    ofstream outputFile("output.txt") ;
    HocPhan hp;
    while (inFile.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        if (strcmp(hp.maHP, maHP) != 0) {
            tempFile.write(reinterpret_cast<const char*>(&hp), sizeof(HocPhan));
        }
    }

    inFile.close();
    tempFile.close();

    // Xóa file HP.BIN cũ
    remove("HP.BIN");
    // Đổi tên file temp.BIN thành HP.BIN mới
    rename("temp.BIN", "HP.BIN");

    outputFile << "Da xoa thong tin hoc phan" << endl;
    outputFile.close() ;
}

void xoaDiemThi(const char* maHP, int maSV) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    ofstream tempFile("temp.BIN", ios::binary);  // File tạm
    ofstream outputFile("output.txt",ios::app) ;
    DiemThi dt;
    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.maHP, maHP) != 0 || dt.maSV != maSV) {
            tempFile.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));
        }
    }

    inFile.close();
    tempFile.close();

    // Xóa file DIEMTHI.BIN cũ
    remove("DIEMTHI.BIN");
    // Đổi tên file temp.BIN thành DIEMTHI.BIN mới
    rename("temp.BIN", "DIEMTHI.BIN");

    outputFile << "Da xoa thong tin diem thi" << endl;
    outputFile.close() ;
}
void suaSinhVien(int maSV) {
    fstream file("SV.BIN", ios::binary | ios::in | ios::out);
    ofstream outputTextFile("output.txt",ios::app);
    SinhVien sv;
    while (file.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
        if (sv.maSV == maSV) {
            outputTextFile << "Nhap thong tin sinh vien moi: " << endl;
            nhapSinhVien(sv);

            // Đặt con trỏ đọc/ghi về vị trí đầu bản ghi cần sửa
            file.seekp(-static_cast<int>(sizeof(SinhVien)), ios::cur);

            // Ghi thông tin sinh viên đã sửa vào vị trí hiện tại
            file.write(reinterpret_cast<const char*>(&sv), sizeof(SinhVien));

            outputTextFile << "Da sua thong tin sinh vien" << endl;

            outputTextFile << "Thong tin sinh vien sau khi sua:" << endl;
            outputTextFile << "Ma SV: " << sv.maSV << endl;
            outputTextFile << "Ho dem: " << sv.hoDem << endl;
            outputTextFile << "Ten: " << sv.Ten << endl;
            outputTextFile << "Gioi tinh: " << sv.gioiTinh << endl;
            outputTextFile << "Ngay Sinh: " << sv.ngaySinh << endl;
            outputTextFile << endl;

            file.close();
            outputTextFile.close();
            return;
        }
    }

    outputTextFile << "Khong tim thay sinh vien co ma so " << maSV << endl;
    file.close();
    outputTextFile.close();
}

void suaHocPhan(const char* maHP) {
    fstream file("HP.BIN", ios::binary | ios::in | ios::out);
    ofstream outputTextFile("output.txt",ios::app);
    HocPhan hp;
    while (file.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
        if (strcmp(hp.maHP, maHP) == 0) {
            outputTextFile << "Nhap thong tin hoc phan moi: " << endl;
            nhapHocPhan(hp);

            // Đặt con trỏ đọc/ghi về vị trí đầu bản ghi cần sửa
            file.seekp(-static_cast<int>(sizeof(HocPhan)), ios::cur);

            // Ghi thông tin hoc phan đã sửa vào vị trí hiện tại
            file.write(reinterpret_cast<const char*>(&hp), sizeof(HocPhan));

            outputTextFile << "Da sua thong tin hoc phan" << endl;

            outputTextFile << "Thong tin hoc phan sau khi sua:" << endl;
            outputTextFile << "Ma HP: " << hp.maHP << endl;
            outputTextFile << "Ten HP: " << hp.tenMonHoc << endl;
            outputTextFile << "So tin chi: " << hp.soTinChi << endl;
            outputTextFile << endl;

            file.close();
            outputTextFile.close();
            return;
        }
    }

    outputTextFile << "Khong tim thay hoc phan co ma " << maHP << endl;
    file.close();
    outputTextFile.close();
}


void suaDiemThi(const char* maHP, int maSV) {
    fstream file("DIEMTHI.BIN", ios::binary | ios::in | ios::out);
    ofstream outputTextFile("output.txt",ios::app);
    DiemThi dt;
    while (file.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (strcmp(dt.maHP, maHP) == 0 && dt.maSV == maSV) {
            outputTextFile << "Nhap thong tin diem thi moi: " << endl;
            nhapDiemThi(dt);

            // Đặt con trỏ đọc/ghi về vị trí đầu bản ghi cần sửa
            file.seekp(-static_cast<int>(sizeof(DiemThi)), ios::cur);

            // Ghi thông tin diem thi đã sửa vào vị trí hiện tại
            file.write(reinterpret_cast<const char*>(&dt), sizeof(DiemThi));

            outputTextFile << "Da sua thong tin diem thi" << endl;

            outputTextFile << "Thong tin diem thi sau khi sua:" << endl;
            outputTextFile << "Ma HP: " << dt.maHP << endl;
            outputTextFile << "Ma SV: " << dt.maSV << endl;
            outputTextFile << "Diem thi: " << dt.diem << endl;
            outputTextFile << endl;

            file.close();
            outputTextFile.close();
            return;
        }
    }

    outputTextFile << "Khong tim thay diem thi cho hoc phan " << maHP << " va sinh vien co ma so " << maSV << endl;
    file.close();
    outputTextFile.close();
}

// Hàm Tính điểm trung bình chung tích lũy theo thang điểm 4 của từng sinh viên
float tinhDTBCTL(const int maSV) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);

    if (!inFile) {
        cout << "Khong the doc file DIEMTHI.BIN" << endl;
        return 0.0f;
    }

    DiemThi dt;
    float tongDiem = 0.0f;
    int soTinChi = 0;

    while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
        if (dt.maSV != maSV) {
            continue;
        }

        HocPhan hp;
        ifstream hpFile("HP.BIN", ios::binary);

        while (hpFile.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
            if (strcmp(dt.maHP, hp.maHP) == 0) {
                soTinChi += hp.soTinChi;
                break;
            }
        }

        hpFile.close();
        tongDiem += dt.diem * hp.soTinChi;
    }

    inFile.close();

    // Tính điểm trên thang điểm 4
    float dtctl = (tongDiem / soTinChi) / 2.5f;

    return dtctl;
}
// Hàm ghi điểm trung bình tích lũy (GPA) vào file DTCTL.BIN
void ghiDTBCTL(const int maSV, const float dtctl) {
    ofstream outFile("DTCTL.BIN", ios::binary | ios::app);
    outFile.write(reinterpret_cast<const char*>(&maSV), sizeof(int));
    outFile.write(reinterpret_cast<const char*>(&dtctl), sizeof(float));
    outFile.close();

    ofstream outputTextFile("output.txt", ios::app);
    if (outputTextFile.is_open()) {
        outputTextFile << "Ma SV: " << maSV << endl;
        outputTextFile << "DTCTL: " << dtctl << endl;
        outputTextFile << endl;
        outputTextFile.close();
        cout << "Ghi DTBCTL vao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }
}


// Hàm đọc điểm trung bình tích lũy (GPA) từ file DTCTL.BIN
void docDTBCTL() {
    ifstream inFile("DTBCTL.BIN", ios::binary);

    if (!inFile) {
        cout << "Khong the doc file DTBCTL.BIN" << endl;
        return;
    }

    ofstream outputTextFile("output.txt", ios::app);
    if (outputTextFile.is_open()) {
        int maSV;
        float dtctl;

        while (inFile.read(reinterpret_cast<char*>(&maSV), sizeof(int)) && inFile.read(reinterpret_cast<char*>(&dtctl), sizeof(float))) {
            outputTextFile << "Ma SV: " << maSV << endl;
            outputTextFile << "DTCTL: " << dtctl << endl;
            outputTextFile << endl;
        }

        outputTextFile.close();
        cout << "Ghi thong tin DTBCTL vao file output.txt thanh cong." << endl;
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }

    inFile.close();
}

void timKiemDiemThiTheoHocPhan(const char* maHP) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    DiemThi dt;
    bool found = false;

    ofstream outputTextFile("output.txt", ios::app);
    if (outputTextFile.is_open()) {
        while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
            if (strcmp(dt.maHP, maHP) == 0) {
                ifstream svFile("SV.BIN", ios::binary);
                SinhVien sv;
                while (svFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
                    if (sv.maSV == dt.maSV) {
                        outputTextFile << "Ma SV: " << sv.maSV << endl;
                        outputTextFile << "Ho dem: " << sv.hoDem << endl;
                        outputTextFile << "Ten: " << sv.Ten << endl;
                        outputTextFile << "Diem: " << dt.diem << endl;
                        outputTextFile << endl;
                    }
                }
                svFile.close();
                found = true;
            }
        }
        outputTextFile.close();
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }

    inFile.close();

    if (!found) {
        cout << "Khong tim thay thong tin diem thi cho hoc phan nay." << endl;
    }
}

void timKiemSinhVienKhongDat(const char* maHP) {
    ifstream inFile("DIEMTHI.BIN", ios::binary);
    DiemThi dt;
    bool found = false;
    ofstream outputTextFile("output.txt", ios::app);
    if (outputTextFile.is_open()) {
        while (inFile.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
            if (strcmp(dt.maHP, maHP) == 0) {
                ifstream svFile("SV.BIN", ios::binary);
                SinhVien sv;
                while (svFile.read(reinterpret_cast<char*>(&sv), sizeof(SinhVien))) {
                    if (sv.maSV == dt.maSV) {
                        if (dt.diem <= 4) {
                            outputTextFile << "Ma SV: " << sv.maSV << endl;
                            outputTextFile << "Ho dem: " << sv.hoDem << endl;
                            outputTextFile << "Ten: " << sv.Ten << endl;
                            outputTextFile << "Diem: " << dt.diem << endl;
                            outputTextFile << endl;
                        }
                    }
                }
                svFile.close();
                found = true;
            }
        }
        outputTextFile.close();
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }

    inFile.close();

    if (!found) {
        cout << "Khong tim thay thong tin diem thi cho hoc phan nay." << endl;
    }
}

void docHocPhanChuaDat() {
    int maSV;
    cout << "Nhap ma so sinh vien: ";
    cin >> maSV;

    ifstream inFileDiem("DIEMTHI.BIN", ios::binary);
    ifstream inFileHocPhan("HP.BIN", ios::binary);

    if (!inFileDiem || !inFileHocPhan) {
        cout << "Khong the doc file DIEMTHI.BIN hoac HP.BIN hoac SV.BIN" << endl;
        return;
    }

    SinhVien sv;
    DiemThi dt;
    HocPhan hp;

    bool found = false;
    ofstream outputTextFile("output.txt", ios::app);
    if (outputTextFile.is_open()) {
        outputTextFile << "Danh sach hoc phan chua dat cua sinh vien ma SV: " << maSV << endl;

        while (inFileDiem.read(reinterpret_cast<char*>(&dt), sizeof(DiemThi))) {
            if (dt.maSV == maSV && dt.diem < 4.0f) {
                while (inFileHocPhan.read(reinterpret_cast<char*>(&hp), sizeof(HocPhan))) {
                    if (strcmp(dt.maHP, hp.maHP) == 0) {
                        outputTextFile << "Ma HP: " << hp.maHP << endl;
                        outputTextFile << "Ten mon hoc: " << hp.tenMonHoc << endl;
                        outputTextFile << "So tin chi: " << hp.soTinChi << endl;
                        outputTextFile << "Diem: " << dt.diem << endl;
                        outputTextFile << endl;
                        found = true;
                        break;
                    }
                }
                inFileHocPhan.clear();
                inFileHocPhan.seekg(0, ios::beg);
            }
        }
        outputTextFile.close();
    } else {
        cout << "Khong the mo file output.txt." << endl;
    }

    inFileDiem.close();
    inFileHocPhan.close();

    if (!found) {
        cout << "Khong co hoc phan nao chua dat cho sinh vien ma SV: " << maSV << endl;
    }
}

void hienThiDTBCTL(const int maSV) {
    float dtbctl;
    if (tinhDTBCTL(maSV)) {
        dtbctl = tinhDTBCTL(maSV);
        ofstream outputTextFile("output.txt", ios::app);
        if (outputTextFile.is_open()) {
            outputTextFile << "Ma SV: " << maSV << endl;
            outputTextFile << "DTBCTL: " << dtbctl << endl;
            outputTextFile.close();
        } else {
            cout << "Khong the mo file output.txt." << endl;
        }
    } else {
        cout << "Ma sinh vien khong ton tai." << endl;
    }
}


void hienThiMenu(int luaChon) {
    system("cls");
    cout << "CHUONG TRINH QUAN LY SINH VIEN - MENU" << endl;
    cout << "-----------------------------------" << endl;
    cout << (luaChon == 1 ? "-> " : "  ") << "1. Menu nhap du lieu cho file nhi phan" << endl;
    cout << (luaChon == 2 ? "-> " : "  ") << "2. Bo sung/Xoa/Sua chua" << endl;
    cout << (luaChon == 3 ? "-> " : "  ") << "3. Tinh diem trung binh tich luy" << endl;
    cout << (luaChon == 4 ? "-> " : "  ") << "4. Tim kiem diem thi theo hoc phan" << endl;
    cout << (luaChon == 5 ? "-> " : "  ") << "5. Tim kiem sinh vien khong dat hoc phan" << endl;
    cout << (luaChon == 6 ? "-> " : "  ") << "6. Hien thi hoc phan chua dat" << endl;
    cout << (luaChon == 7 ? "-> " : "  ") << "7. Hien thi diem trung binh tich luy cua sinh vien" << endl;
    cout << (luaChon == 8 ? "-> " : "  ") << "8. Hien thi thong tin sinh vien" << endl;
    cout << (luaChon == 9 ? "-> " : "  ") << "9. Hien thi thong tin hoc phan" << endl;
    cout << (luaChon == 10 ? "-> " : "  ") << "10. Hien thi diem thi" << endl;
    cout << (luaChon == 0 ? "-> " : "  ") << "0. Thoat" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
    cout << "Nhan Enter de chon mot lua chon" << endl;
}
void xuLyMenuBoSung() {
    int luaChon = 1;
    int phim;
    bool tiepTuc = true;

    while (tiepTuc) {
        system("cls");
        cout << "BO SUNG - MENU" << endl;
        cout << "--------------" << endl;
        cout << (luaChon == 1 ? "-> " : "  ") << "1. Bo sung thong tin sinh vien" << endl;
        cout << (luaChon == 2 ? "-> " : "  ") << "2. Bo sung thong tin hoc phan" << endl;
        cout << (luaChon == 3 ? "-> " : "  ") << "3. Bo sung diem thi" << endl;
        cout << (luaChon == 0 ? "-> " : "  ") << "0. Quay lai" << endl;
        cout << "--------------" << endl;
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
                    bosungSinhVien() ;
                    break;
                case 2:
                    bosungHocPhan();
                  
                    break;
                case 3:
                    bosungDiemThi();
                   
                    break;
                case 0:
                    cout << "Quay lai Menu bo sung/xoa/sua chua." << endl;
                    tiepTuc = false;
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
                    break;
            }

            if (tiepTuc) {
                cout << "Nhan phim bat ky de tiep tuc." << endl;
                _getch();
            }
        }
    }
}
void xuLyMenuXoa() {
    int luaChon = 1;
    int phim;

    while (true) {
        system("cls");
        cout << "Chon loai du lieu muon xoa:" << endl;
        cout << (luaChon == 1 ? "-> " : "  ") << "1. Xoa thong tin sinh vien" << endl;
        cout << (luaChon == 2 ? "-> " : "  ") << "2. Xoa thong tin hoc phan" << endl;
        cout << (luaChon == 3 ? "-> " : "  ") << "3. Xoa diem thi" << endl;
        cout << (luaChon == 0 ? "-> " : "  ") << "0. Quay lai" << endl;
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
                    int maSV;
                    cout << "Nhap ma sinh vien can xoa: ";
                    cin >> maSV;
                    xoaSinhVien(maSV);
                    
                    break;
                }
                case 2: {
                    char maHP[50];
                    cout << "Nhap ma hoc phan can xoa: ";
                    cin.ignore();
                    cin.getline(maHP, sizeof(maHP));
                    xoaHocPhan(maHP);
                    break;
                }
                case 3: {
                    char maHP[50];
                    int maSV;
                    cout << "Nhap ma hoc phan can xoa diem: ";
                    cin.ignore();
                    cin.getline(maHP, sizeof(maHP));
                    cout << "Nhap ma sinh vien can xoa diem: ";
                    cin >> maSV;
                    xoaDiemThi(maHP, maSV);
                    break;
                }
                case 0:
                    cout << "Quay lai Menu bo sung/xoa/sua chua." << endl;
                    return;  // Quay lai truc tiep
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
                    break;
            }

            cout << "Nhan phim bat ky de tiep tuc." << endl;
            _getch();
        }
    }
}
void xuLyMenuSuaChua() {
    int luaChon = 1;
    int phim;
    bool tiepTucMenuSuaChua = true;

    while (tiepTucMenuSuaChua) {
        system("cls");
        cout << "SUA CHUA - MENU" << endl;
        cout << "---------------" << endl;
        cout << (luaChon == 1 ? "-> " : "  ") << "1. Sua thong tin sinh vien" << endl;
        cout << (luaChon == 2 ? "-> " : "  ") << "2. Sua thong tin hoc phan" << endl;
        cout << (luaChon == 3 ? "-> " : "  ") << "3. Sua diem thi" << endl;
        cout << (luaChon == 0 ? "-> " : "  ") << "0. Quay lai" << endl;
        cout << "---------------" << endl;
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
                    int maSV;
                    cout << "Nhap ma sinh vien can sua: ";
                    cin >> maSV;
                    suaSinhVien(maSV);
                    break;
                }
                case 2: {
                    char maHP[50];
                    cout << "Nhap ma hoc phan can sua: ";
                    cin >> maHP;
                    suaHocPhan(maHP);
                    break;
                }
                case 3: {
                    char maHP[50];
                    int maSV;
                    cout << "Nhap ma hoc phan can sua diem: ";
                    cin >> maHP;
                    cout << "Nhap ma sinh vien can sua diem: ";
                    cin >> maSV;
                    suaDiemThi(maHP, maSV);
                    break;
                }
                case 0:
                    cout << "Quay lai Menu bo sung/xoa/sua chua." << endl;
                    tiepTucMenuSuaChua = false; // Kết thúc vòng lặp khi chọn 0
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
                    break;
            }

            if (tiepTucMenuSuaChua && luaChon != 0) {
                cout << "Nhan phim bat ky de tiep tuc." << endl;
                _getch();
                system("cls");
            }
        }
    }
}
void hienThiMenuBoSungXoaSua(int luaChon) {
    system("cls");
    cout << "BoSungXoaSua- MENU" << endl;
    cout << "-------------------------------------" << endl;
    cout << (luaChon == 1 ? "-> " : "  ") << "1. Bo sung" << endl;
    cout << (luaChon == 2 ? "-> " : "  ") << "2. Xoa" << endl;
    cout << (luaChon == 3 ? "-> " : "  ") << "3. Sua chua" << endl;
    cout << (luaChon == 0 ? "-> " : "  ") << "0. Quay lai" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
    cout << "Nhan Enter de chon mot lua chon" << endl;
}
void xuLyMenuBoSungXoaSua(int luaChon) {
    int phim;
    int luaChonBoSungXoaSua = 1;
    bool tiepTucBoSungXoaSua = true;

    while (tiepTucBoSungXoaSua) {
        system("cls");
        hienThiMenuBoSungXoaSua(luaChonBoSungXoaSua);

        phim = _getch();
        if (phim == 0 || phim == 224) {
            phim = _getch();
            switch (phim) {
                case 72:  // Mui ten len
                    luaChonBoSungXoaSua--;
                    if (luaChonBoSungXoaSua < 0) luaChonBoSungXoaSua = 3;
                    break;
                case 80:  // Mui ten xuong
                    luaChonBoSungXoaSua++;
                    if (luaChonBoSungXoaSua > 3) luaChonBoSungXoaSua = 0;
                    break;
            }
        } else if (phim == 13) {
            switch (luaChonBoSungXoaSua) {
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
                    tiepTucBoSungXoaSua = false;
                    break;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!" << endl;
                    break;
            }
            if (tiepTucBoSungXoaSua) {
                cout << "Nhan phim bat ky de tro ve Menu chinh." << endl;
                _getch();
            }
        }
    }
    }

void hienThiMenuNhapDuLieu(int luaChon) {
    system("cls");
    cout << "NHAP DU LIEU CHO FILE NHAP PHAN - MENU" << endl;
    cout << "-------------------------------------" << endl;
    cout << (luaChon == 1 ? "-> " : "  ") << "1. Nhap thong tin sinh vien" << endl;
    cout << (luaChon == 2 ? "-> " : "  ") << "2. Nhap thong tin hoc phan" << endl;
    cout << (luaChon == 3 ? "-> " : "  ") << "3. Nhap diem thi" << endl;
    cout << (luaChon == 0 ? "-> " : "  ") << "0. Quay lai" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Su dung phim mui ten len/xuong de di chuyen trong menu" << endl;
    cout << "Nhan Enter de chon mot lua chon" << endl;
}

void xuLyMenuNhapDuLieu(int luaChon) {
    int phim;
    int luaChonNhapDuLieu = 1;
    bool tiepTucNhapDuLieu = true;

    while (tiepTucNhapDuLieu) {
        system("cls");
        hienThiMenuNhapDuLieu(luaChonNhapDuLieu);

        phim = getch();
        if (phim == 0 || phim == 224) {
            phim = getch();
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
                    bosungSinhVien() ;
                    break;
                case 2:
                    bosungHocPhan();

                    break;
                case 3:
                    bosungDiemThi();

                    break;
                case 0:
                    cout << "Quay lai Menu chinh." << endl;
                    tiepTucNhapDuLieu = false;
                    break;
            }

            if (luaChonNhapDuLieu != 0) {
                cout << "Nhan phim bat ky de tiep tuc nhap du lieu." << endl;
                getch();
                system("cls");
            }
        }
    }
}


void xuLyLuaChon(int luaChon) {
    switch (luaChon) {
        case 1: {
            int menuNhapDuLieu;
            do {
                hienThiMenuNhapDuLieu(menuNhapDuLieu);
                menuNhapDuLieu = _getch() - '0';
                xuLyMenuNhapDuLieu(menuNhapDuLieu);
                if (menuNhapDuLieu != 0) {
                    cout << "Nhan phim bat ky de tiep tuc nhap du lieu." << endl;
                    _getch();
                    system("cls");
                }
            } while (menuNhapDuLieu != 0);
            break;
        }
        case 2: {
            int menuBoSungXoaSua;
            do {
                hienThiMenuBoSungXoaSua(menuBoSungXoaSua);
                menuBoSungXoaSua = _getch() - '0';
                xuLyMenuBoSungXoaSua(menuBoSungXoaSua);
                if (menuBoSungXoaSua != 0) {
                    cout << "Nhan phim bat ky de tiep tuc." << endl;
                    _getch();
                    system("cls");
                }
            } while (menuBoSungXoaSua != 0);
            break;
        }
       case 3: {
    int maSV;
    cout << "Nhap ma sinh vien: ";
    cin >> maSV;
    float dtbctl = tinhDTBCTL(maSV);
    cout << "Ma SV: " << maSV << endl;
    cout << "GPA: " << dtbctl << endl;
    break;
}
        case 4: {
            char maHP[50];
            cout << "Nhap ma hoc phan: ";
            cin >> maHP;
            timKiemDiemThiTheoHocPhan(maHP);
            break;
        }
        case 5: {
            char maHP[50];
            cout << "Nhap ma hoc phan: ";
            cin >> maHP;
            timKiemSinhVienKhongDat(maHP);
            break;
        }
        case 6:
    cout << "======= Danh sach hoc phan chua dat =======" << endl;
    docHocPhanChuaDat();
    break;
        case 7:
            {
    int maSV;
    cout << "Nhap ma sinh vien: ";
    cin >> maSV;
    hienThiDTBCTL(maSV);
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
            cout << "======= Danh sach diem thi =======" << endl;
            docDiemThi();
            break;
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
        system("cls");
        hienThiMenu(luaChon);
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
                xuLyMenuBoSungXoaSua(luaChon); // Gọi hàm xử lý menu "BoSungXoaSua"
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
