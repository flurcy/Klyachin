#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

//Функция для подсчета суммы цифр в числе
int SumOfDigits(int number) {
    int sum = 0;
    while (number != 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

int main() {
    //setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(CP_UTF8);
    int year;

    cout << "Введите год: ";
    cin >> year;

    bool isItLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    const int daysInMonth[] = {0, 31, (isItLeapYear ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Количество дней в каждом месяце

    for (int month = 1; month <= 12; ++month) {
        for (int day = 1; day <= daysInMonth[month]; ++day) {
            int date = day * 100 + month * 10000 + year; //DDMMYYYY
            int sum = SumOfDigits(date);
            cout << day << "." << month << "." << year << ": " << sum << "\n";
        }
        cout << "\n";
    }
    return 0;
}