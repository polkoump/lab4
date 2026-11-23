// Лабораторная работа №4. Вариант 22.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <deque>
#include <list>
#include <algorithm> // copy, sort
#include <utility>   // move
using namespace std;

class Credit // Класс - банковский кредит
{
    string name;     // Название кредита
    double amount;   // Сумма кредита
    string currency; // Тип валюты
    double rate;     // Ставка в % годовых
public:
    Credit() // Конструктор без параметров (нужен для list, который создается заранее нужного размера)
    {
        name = "";
        amount = 0;
        currency = "";
        rate = 0;
    }
    Credit(string name, double amount, string currency, double rate) // Конструктор для инициализации полей
    {
        this->name = name;
        this->amount = amount;
        this->currency = currency;
        this->rate = rate;
    }
    
    bool operator <(const Credit & c) const // Сравнение по сумме кредита (для сортировки sort)
    {
        return amount < c.amount;
    }
    friend ostream & operator <<(ostream & out, const Credit & c); // Дружественная функция вставки в поток
};
ostream & operator <<(ostream & out, const Credit & c) // Вставка объекта в поток
{
    out << c.name << ", amount " << fixed << setprecision(2) << c.amount << " " << c.currency
        << ", rate " << c.rate << "% per year";
    return out;
}

int main()
{
    ifstream fin("input.txt");   // Входной файл
    ofstream fout("output.txt"); // Выходной файл
    if (!fin) // Ошибка файл не открыт
    {
        cerr << "Error, input.txt not found" << endl;
        return 1;
    }
    int n; // Число кредитов
    fin >> n;
    fin.ignore(256, '\n'); // Пропускаем символы перехода на новую строку
    deque<Credit> credits; // Исходный контейнер deque
    for (int i = 0; i < n; i++) // Читаем кредиты из файла
    {
        string name, currency;
        double amount, rate;
        getline(fin, name); // Название - строка, может содержать пробелы
        if (!name.empty() && name.back() == '\r') name.pop_back(); // Файл с Windows переводами строк
        fin >> amount >> currency >> rate; // Остальные поля в одной строке
        fin.ignore(256, '\n');
        credits.push_back(Credit(name, amount, currency, rate));
    }

    // Копируем исходный контейнер deque в list алгоритмом copy (до сортировки)
    list<Credit> copy_credits(credits.size()); // Нужный размер списка задаем заранее
    copy(credits.begin(), credits.end(), copy_credits.begin());

    fout << "Source container (deque):" << endl;
    for (const Credit & c : credits) fout << c << endl; // Используем перегруженную операцию <<

    // Сортировка deque алгоритмом sort с двумя параметрами (по сумме кредита)
    sort(credits.begin(), credits.end());
    fout << endl << "Container after sorting (deque, std::sort by amount):" << endl;
    for (const Credit & c : credits) fout << c << endl;

    fout << endl << "Copy of the source container (list, algorithm copy):" << endl;
    for (const Credit & c : copy_credits) fout << c << endl;

    if (n > 0) // Демонстрация копирования и перемещения объекта (методы, созданные компилятором)
    {
        Credit first = credits.front(); // Конструктор копирования
        Credit other;
        other = first; // Присваивание с копированием
        fout << endl << "Copy constructor:      " << first << endl;
        fout << "Copy assignment:       " << other << endl;
        Credit moved(std::move(first)); // Конструктор перемещения
        fout << "Move constructor:      " << moved << endl;
        Credit moved2;
        moved2 = std::move(other); // Присваивание с перемещением
        fout << "Move assignment:       " << moved2 << endl;
    }
    return 0;
}
