#include <iostream>
#include <utility>
#include <windows.h>
using namespace std;

//функция для нахождения НОД чисел
int NOD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//функция для нахождения НОК чисел
int NOK(int a, int b) {
    return (a * b) / NOD(a, b);
}

//функция для разложения на множители
int Factorization(int num) {
    cout << "Множители числа " << num << ": ";
    for (int divider = 2; divider <= num; divider++) {
        while (num % divider == 0) {
            std::cout << divider << " ";
            num /= divider;
        }
    }
    return num;
}

//функция для сокращения дроби
pair<int, int> simplifyFraction(int numerator, int denominator) {
    int commonDivisor = NOD(numerator, denominator);
    return { numerator / commonDivisor, denominator / commonDivisor };
}

//функция для сложения двух дробей
pair<int, int> addFractions(pair<int, int> fraction1, pair<int, int> fraction2) {
    int newNumerator = fraction1.first * fraction2.second + fraction2.first * fraction1.second;
    int newDenominator = fraction1.second * fraction2.second;
    return simplifyFraction(newNumerator, newDenominator);
}

//функция для вычитания двух дробей
pair<int, int> subtractFractions(pair<int, int> fraction1, pair<int, int> fraction2) {
    int newNumerator = fraction1.first * fraction2.second - fraction2.first * fraction1.second;
    int newDenominator = fraction1.second * fraction2.second;
    return simplifyFraction(newNumerator, newDenominator);
}

//функция для умножения двух дробей
pair<int, int> multiplyFractions(pair<int, int> fraction1, pair<int, int> fraction2) {
    int newNumerator = fraction1.first * fraction2.first;
    int newDenominator = fraction1.second * fraction2.second;
    return simplifyFraction(newNumerator, newDenominator);
}

//функция для деления двух дробей
pair<int, int> divideFractions(pair<int, int> fraction1, pair<int, int> fraction2) {
    int newNumerator = fraction1.first * fraction2.second;
    int newDenominator = fraction1.second * fraction2.first;
    return simplifyFraction(newNumerator, newDenominator);
}

int main() {
    setlocale(LC_ALL, "Russian");

    int num1, denom1, num2, denom2; //для дробей
    int num, a, b; //для чисел

    string messageInputNumber = "Введите числа a и b: ";
    string messageResult = "Результат: ";
    string messageError = "Неверная операция!";

    char decision;
    cout << "Над каким типом вы хотите проделать операцию? Введите 1, если над числом. Введите 2, если над дробью: ";
    cin >> decision;

    switch (decision) {
    case '1':
        char operationNum;
        cout << "Выберите операцию: NOD (1), NOK (2), Factorization (3): ";
        cin >> operationNum;
        switch (operationNum) {
        case '1':
            cout << messageInputNumber;
            cin >> a;
            cin >> b;

            std::cout << messageResult << NOD(a, b);
            break;
        case '2':
            cout << messageInputNumber;
            cin >> a;
            cin >> b;

            cout << messageResult << NOK(a, b);
            break;
        case '3':
            cout << "Введите число, которое вы хотите разложить на множители: ";
            cin >> num;
            cout << Factorization(num);

            break;
        default:
            cout << messageError;
            return 1;
        }
        return 0;

    case '2':
        //if (пустая строка или неверный тип введенных данных, выводить ошибку и заканчивать программу)
        //else cout... switch case:
        cout << "Введите первую дробь в формате <числитель знаменатель>: ";
        cin >> num1 >> denom1;

        cout << "Введите вторую дробь в формате <числитель знаменатель>: ";
        cin >> num2 >> denom2;

        pair<int, int> fraction1 = { num1, denom1 };
        pair<int, int> fraction2 = { num2, denom2 };

        pair<int, int> result;

        char operationFrac;
        cout << "Выберите операцию (+, -, *, /): ";
        cin >> operationFrac;

        switch (operationFrac) {
        case '+':
            result = addFractions(fraction1, fraction2);
            break;
        case '-':
            result = subtractFractions(fraction1, fraction2);
            break;
        case '*':
            result = multiplyFractions(fraction1, fraction2);
            break;
        case '/':
            result = divideFractions(fraction1, fraction2);
            break;
        default:
            cout << messageError;
            return 1;
        }

        cout << messageResult << result.first << "/" << result.second << endl;

        return 0;
    }
}
