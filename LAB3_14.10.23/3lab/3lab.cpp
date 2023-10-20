#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>
#include <string>
#include <functional>

using namespace std;


struct Point {
    string name;
    double x;
    double y;

    Point(const string& n, double xx, double yy) : name(n), x(xx), y(yy) {}
};


double distance(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}


bool isLetter(const string& str) {
    if (str.length() != 1) {
        return false;
    }
    char ch = str[0];
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}


bool isInteger(const string& str) {
    if (str.empty()) {
        return false;
    }
    for (char ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}


string getInput(const string& prompt, const string& errorMessage, const function<bool(const string&)>& validator) {
    string input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (validator(input)) {
            break;
        }
        cout << errorMessage << endl;
    }
    return input;
}

// Функция для нахождения кратчайшего пути 
vector<Point> findShortestPath(vector<Point>& points) {
    int n = points.size();
    vector<Point> path;
    vector<bool> used(n, false);

    int start = 0; 

    used[start] = true;
    path.push_back(points[start]);

    for (int i = 1; i < n; i++) {
        int next = -1;
        double minDist = numeric_limits<double>::max();

        for (int j = 0; j < n; j++) {
            if (!used[j]) {
                double dist = distance(path.back(), points[j]);
                if (dist < minDist) {
                    minDist = dist;
                    next = j;
                }
            }
        }

        used[next] = true;
        path.push_back(points[next]);
    }

    path.push_back(points[start]);

    return path;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int numPoints;
    cout << "Введите количество точек: ";
    cin >> numPoints;

    vector<Point> points;

    for (int i = 0; i < numPoints; i++) {
        string name;
        double x, y;

        name = getInput("\nВведите имя для точки " + to_string(i + 1) + " (A-Z): ", "Ошибка: Введите букву от A до Z", isLetter);
        x = stod(getInput("Введите координату X для точки " + name + ": ", "Ошибка: Введите целое число", isInteger));
        y = stod(getInput("Введите координату Y для точки " + name + ": ", "Ошибка: Введите целое число", isInteger));

        points.push_back(Point(name, x, y));
    }

    vector<Point> shortestPath = findShortestPath(points);


    ofstream outputFile("shortest_path.txt");
    if (!outputFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return 1;
    }


    cout << "\nКратчайший путь:" << endl;
    outputFile << "\nКратчайший путь:" << endl;

    double totalDistance = 0.0;
    for (size_t i = 0; i < shortestPath.size() - 1; i++) {
        cout << shortestPath[i].name << " -> ";
        outputFile << shortestPath[i].name << " -> ";
        totalDistance += distance(shortestPath[i], shortestPath[i + 1]);
    }
    cout << shortestPath.back().name << endl;
    outputFile << shortestPath.back().name << endl;

    cout << "\nДлина пути: " << totalDistance << endl;
    outputFile << "\nДлина пути: " << totalDistance << endl;

    outputFile.close();

    cout << "\nРезультаты сохранены в файле 'shortest_path.txt'" << endl;

    return 0;
}
