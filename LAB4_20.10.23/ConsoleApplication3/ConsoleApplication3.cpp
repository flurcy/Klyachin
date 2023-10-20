#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <Windows.h>

using namespace std;

// Словарь анаграмм
vector<string> anagrams = {
    "слон",
    "кот",
    "дом",
    "мышь",
    "автомобиль",
    "банан",
    "компьютер",
    "гитара",
    "солнце",
    "книга"
};

// Функция для перемешивания букв в слове
string shuffleWord(string word) {
    random_shuffle(word.begin(), word.end());
    return word;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(static_cast<unsigned int>(time(nullptr))); //rand для загадки

    int score = 0;
    int totalAnagrams = anagrams.size();
    string playerName;

    cout << "Добро пожаловать в игру 'Анаграмма'!" << endl;
    cout << "Введите ваше имя: ";
    cin >> playerName;

    ofstream scoreFile("scores.txt", ios::app);

    cout << "Игра началась, " << playerName << "!" << endl;
    cout << "Введите 'q' для завершения игры." << endl;

    while (!anagrams.empty()) {
        int randomIndex = rand() % anagrams.size();
        string currentAnagram = anagrams[randomIndex];

        cout << "Анаграмма: " << shuffleWord(currentAnagram) << endl;
        string userAnswer;
        cin >> userAnswer;

        if (userAnswer == "q") {
            break;
        }

        if (userAnswer == currentAnagram) {
            cout << "Верно! +1 очко." << endl;
            score++;
        }
        else {
            cout << "Неправильно. Правильный ответ: " << currentAnagram << endl;
        }

        anagrams.erase(anagrams.begin() + randomIndex);
    }

    cout << "Игра окончена, " << playerName << "!" << endl;
    cout << "Ваш итоговый счет: " << score << " из " << totalAnagrams << " возможных." << endl; //доп. счет игры

    scoreFile << playerName << ": " << score << " из " << totalAnagrams << " возможных." << endl; //доп. сохранение рехультатов в файле
    scoreFile.close();

    cout << "\nРезультаты сохранены в файле 'scores.txt'." << endl;


    //доп. чтение данных из текстового файла и отображение в консоли
    ifstream dataFile("scores.txt");
    if (dataFile.is_open()) {
        string line;
        cout << "\nСодержимое файла 'scores.txt':\n";
        while (getline(dataFile, line)) {
            cout << line << endl;
        }
        dataFile.close();
    }
    else {
        cout << "Ошибка при открытии файла 'scores.txt'." << endl;
    }

    return 0;
}
