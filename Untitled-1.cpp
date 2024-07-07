#include <iostream>
#include <fstream>
#include <string>

void hienThiNoiDungFileNhiPhan(const char* tenFile) {
    std::ifstream file(tenFile, std::ios::binary);

    if (!file) {
        std::cout << "Khong the mo file." << std::endl;
        return;
    }

    // Di chuyển con trỏ đọc file đến cuối file
    file.seekg(0, std::ios::end);

    // Lấy kích thước file
    std::streampos fileSize = file.tellg();

    // Di chuyển con trỏ đọc file về đầu file
    file.seekg(0, std::ios::beg);

    // Đọc dữ liệu từ file vào một vector unsigned char

    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

    // Hiển thị nội dung của vector dưới dạng chuỗi ký tự
    std::string content(buffer.begin(), buffer.end());
    std::cout << content << std::endl;

    file.close();
}

int main() {
    const char* tenFile = "data.bin";
    hienThiNoiDungFileNhiPhan(tenFile);

    return 0;
}
