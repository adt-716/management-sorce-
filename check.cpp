#include <iostream>
#include <fstream>
#include <cmath>
#include <conio.h> // Thêm thư viện conio.h để sử dụng getch()

using namespace std;

double f(double A[], double n, double x)
{
    double f0x = 0;
    n++;
    for (int i = 0; i < n; i++)
    {
        f0x += A[i] * pow(x, i);
    }
    return f0x;
}

double f1(double A[], double n, double x)
{
    double f1x = 0;
    n++;
    for (int i = 0; i < n; i++)
    {
        f1x += A[i] * pow(x, i - 1) * i;
    }
    return f1x;
}

double f2(double A[], double n, double x)
{
    double f2x = 0;
    n++;
    for (int i = 0; i < n; i++)
    {
        f2x += A[i] * i * (i - 1) * pow(x, i - 2);
    }
    return f2x;
}

double giaipt(double A[], double n, double a, double b, double e)
{
    double c, d, x0;
    if (f1(A, n, a) * f2(A, n, a) > 0)
    {
        d = b;
        x0 = a;
    }
    else
    {
        d = a;
        x0 = b;
    }
    ofstream outputFile("output.txt");
    if (outputFile.is_open())
    {
        outputFile << "Nhap bac cua da thuc: " << n << endl;
        for (int i = n; i >= 0; i--)
        {
            outputFile << "He so cua x^" << i << ": ";
            outputFile << A[i] << endl;
        }
        outputFile << "Nhap khoang cach li" << endl;
        outputFile << "a= " << a << endl;
        outputFile << "b= " << b << endl;
        outputFile << "Nhap epsilon: " << e << endl;
        
        do
        {
            x0 = x0 - (f(A, n, x0) * (x0 - d)) / (f(A, n, x0) - f(A, n, d));
            c = f(A, n, x0);
            outputFile << fixed << x0 << endl;
        } while (abs(c) > e);
        
        outputFile.close();
    }
    return x0;
}

void printMenu(int choice)
{
    system("cls"); // Xóa màn hình console (chỉ hoạt động trên Windows)
    cout << "Menu:" << endl;
    cout << (choice == 1 ? "-> " : "   ") << "1. Nhap da thuc" << endl;
    cout << (choice == 2 ? "-> " : "   ") << "2. Giai phuong trinh" << endl;
    cout << (choice == 3 ? "-> " : "   ") << "3. Thoat" << endl;
}

int main()
{
    ofstream outputFile("output.txt");
    if (outputFile.is_open())
    {
        int n = 0;
        double A[100];
        double a, b, e;
        bool polynomialEntered = false;
        int choice = 1;
        
        while (true)
        {
            printMenu(choice);
            
            // Nhận phím từ bàn phím
            char key = _getch();
            
            switch (key)
            {
                case 'W': // Di chuyển lên
                case 'w':
                    if (choice > 1)
                        choice--;
                    break;
                    
                case 'S': // Di chuyển xuống
                case 's':
                    if (choice < 3)
                        choice++;
                    break;
                    
                case 'Q': // Thoát khỏi chương trình
                case 'q':
                    outputFile.close();
                    return 0;
                
                case 13: // Phím Enter
                    if (choice == 1)
                    {
                        cout << "Nhap bac cua da thuc: ";
                        cin >> n;
                        for (int i = n; i >= 0; i--)
                        {
                            cout << "He so cua x^" << i << ": ";
                            cin >> A[i];
                        }
                        polynomialEntered = true;
                    }
                    else if (choice == 2)
                    {
                        if (polynomialEntered)
                        {
                            cout << "Nhap khoang cach li" << endl;
                            cout << "a= ";
                            cin >> a;
                            cout << "b= ";
                            cin >> b;
                            cout << "Nhap epsilon: ";
                            cin >> e;
                            
                            outputFile << "Nhap bac cua da thuc: " << n << endl;
                            for (int i = n; i >= 0; i--)
                            {
                                outputFile << "He so cua x^" << i << ": ";
                                outputFile << A[i] << endl;
                            }
                            outputFile << "Nhap khoang cach li" << endl;
                            outputFile << "a= " << a << endl;
                            outputFile << "b= " << b << endl;
                            outputFile << "Nhap epsilon: " << e << endl;
                            
                            double result = giaipt(A, n, a, b, e);
                            cout << fixed << result << endl;
                            outputFile << fixed << result << endl;
                        }
                        else
                        {
                            cout << "Vui long nhap da thuc truoc khi giai phuong trinh." << endl;
                        }
                    }
                    else if (choice == 3)
                    {
                        outputFile.close();
                        return 0;
                    }
                    break;
            }
        }
        
        outputFile.close();
    }
    else
    {
        cout << "Khong the mo file output.txt" << endl;
    }

    return 0;
}
