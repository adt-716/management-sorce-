#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw_menu(int current_row) {
    system("cls");
    cout << "Menu:" << endl;
    cout << (current_row == 0 ? "> " : "  ") << "Option 1" << endl;
    cout << (current_row == 1 ? "> " : "  ") << "Option 2" << endl;
    cout << (current_row == 2 ? "> " : "  ") << "Option 3" << endl;
    cout << (current_row == 3 ? "> " : "  ") << "Exit" << endl;
}

int main() {
    int current_row = 0;
    char key;

    while (true) {
        draw_menu(current_row);

        key = _getch();
        if (key == 224) {
            key = _getch(); // Extended ASCII code
            if (key == 72 && current_row > 0) { // Up arrow
                current_row--;
            } else if (key == 80 && current_row < 3) { // Down arrow
                current_row++;
            }
        } else if (key == 13) { // Enter key
            if (current_row == 3) {
                break; // Exit
            } else {
                ofstream file("menu_choices.txt", ios::app); // Mở file để ghi và giữ nội dung cũ
                if (file.is_open()) {
                    file << "Selected option: " << current_row + 1 << endl;
                    file.close();
                } else {
                    cout << "Failed to open file." << endl;
                }
            }
        }
    }

    return 0;
}
