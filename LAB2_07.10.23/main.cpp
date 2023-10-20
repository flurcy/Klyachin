#include <iostream>
#include <utility>
using namespace std;


//функция для проверки знаменателя
bool CheckNonZeroDenominator(int denominator) {
    if (denominator == 0) {
        std::cout << "Ошибка! Знаменатель не может быть равен нулю." << std::endl;
        return true;
    }
    return false;
}

//функция для проверки ввода пользователя
bool HandleInputError(const std::string& messageErrorInput) {
    if (!std::cin.good()) {
        std::cout << messageErrorInput;
        return true;
    }
    return false;
}

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
    std::cout << "Множители числа " << num << ": ";
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
    int resultCalculations; //результат вычисления

    string messageInputNumber = "Введите числа a и b: ";
    string messageError = "Неверная операция!";
    string messageErrorInput = "Ошибка! Некорректный ввод. Введите целые числа.";
    
    char decision;
    std::cout << "Над каким типом вы хотите проделать операцию? Введите 1, если над числом. Введите 2, если над дробью: ";
    std::cin >> decision;
        
    switch (decision) {
        case '1':
            char operationNum;
            std::cout << "Выберите операцию: NOD (1), NOK (2), Factorization (3): ";
            std::cin >> operationNum;
            switch (operationNum) {
            case '1':
                std::cout << messageInputNumber;
                std::cin >> a;
                std::cin >> b;

                if (HandleInputError(messageErrorInput)) {
                    return 1;
                }

                cout << "НОД чисел: " << NOD(a, b);

                break;
            case '2':
                std::cout << messageInputNumber;
                std::cin >> a;
                std::cin >> b;

                if (HandleInputError(messageErrorInput)) {
                    return 1;
                }

                cout << "НОК чисел: " << NOK(a, b);

                break;
            case '3':
                std::cout << "Введите число, которое вы хотите разложить на множители: ";
                std::cin >> num;

                if (HandleInputError(messageErrorInput)) {
                    return 1;
                }

                cout << Factorization(num);

                break;
            default:
                std::cout << messageError;
            }
            return 0;

        case '2':
            std::cout << "Введите первую дробь в формате <числитель знаменатель>: ";
            std::cin >> num1 >> denom1;

            if (HandleInputError(messageErrorInput) || CheckNonZeroDenominator(denom1)) {
                return 1;
            }

            std::cout << "Введите вторую дробь в формате <числитель знаменатель>: ";
            std::cin >> num2 >> denom2;

            if (HandleInputError(messageErrorInput) || CheckNonZeroDenominator(denom2)) {
                return 1;
            }


            pair<int, int> fraction1 = { num1, denom1 };
            pair<int, int> fraction2 = { num2, denom2 };

            pair<int, int> result;

            char operationFraction;
            std::cout << "Выберите операцию (+, -, *, /): ";
            std::cin >> operationFraction;

            switch (operationFraction) {
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
                std::cout << messageError;
            }
            std::cout << "Результат: " << result.first << "/" << result.second << endl;
    }

    return 0;
}


