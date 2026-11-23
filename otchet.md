## Московский государственный технический университет имени Н.Э. Баумана

# Отчёт по лабораторной работе № 4

**Тема:** Использование объектов своих классов в последовательных контейнерах библиотеки STL

**Выполнила:** Смирнова Полина Игоревна  
**Проверил:** Барыкин Дмиртий Ваильевич  
**Группа:** ИУ8-14  
**Вариант:** 22

**Москва, 2026**

---
## 1. Цель работы

Научиться использовать объекты собственных классов в последовательных контейнерах STL (`deque`, `list`), применять алгоритмы `std::copy` и `std::sort`, метод `list::sort`, перегружать операции для пользовательского класса и обосновывать необходимость специальных методов класса.

## 2. Задание (вариант 22)

| Параметр | Значение |
|---|---|
| Объект | банковский кредит |
| Поля | название, сумма кредита, тип валюты, ставка в % годовых |
| Исходный контейнер | `std::deque` |
| Контейнер, в который копируем | `std::list` |
| Сортировка | по сумме кредита |

Требования:

- элементы контейнеров — **объекты класса, а не указатели**;
- класс содержит необходимые конструкторы, перегруженную операцию вставки в поток `<<`; наличие или отсутствие конструктора копирования, конструктора перемещения и операций присваивания (с копированием и перемещением) обосновано;
- копирование исходного контейнера в другой выполняется алгоритмом `std::copy`;
- исходный контейнер сортируется алгоритмом `std::sort` с двумя параметрами (итератор на начало и итератор на конец), так как `deque` имеет итераторы произвольного доступа;
- данные читаются из `input.txt`, в `output.txt` выводятся исходный контейнер, контейнер после сортировки и контейнер-копия (через перегруженную операцию `<<`).

## 3. Описание программы

### 3.1. Класс `Credit`

| Поле | Тип | Назначение |
|---|---|---|
| `name` | `string` | название кредита |
| `amount` | `double` | сумма кредита |
| `currency` | `string` | тип валюты (RUB, USD, EUR) |
| `rate` | `double` | ставка в % годовых |

Методы класса:

- **конструктор без параметров** — необходим, т. к. контейнер `list<Credit> copy_credits(credits.size())` создаётся заранее нужного размера и заполняет элементы значениями по умолчанию;
- **конструктор с параметрами** — инициализирует все поля при чтении данных из файла;
- **`operator <`** — сравнивает кредиты по сумме (`amount`); используется алгоритмом `std::sort`;
- **дружественная `operator <<`** — вставка объекта в поток вывода (`ostream`), принимает ссылку на поток и константную ссылку на объект, возвращает ссылку на поток, что позволяет строить цепочки вывода.

### 3.2. Обоснование отсутствия конструктора копирования, конструктора перемещения и операций присваивания

В классе `Credit` нет указателей и динамически выделяемой памяти, которой управлял бы сам класс. Поля `string` и `double` корректно копируются и перемещаются стандартными средствами. Конструкторы копирования и перемещения и операции присваивания, которые автоматически создаёт компилятор, выполняют именно то, что требуется (поэлементное копирование и перемещение полей), поэтому писать их вручную не нужно (правило нуля). Явное определение лишь дублировало бы работу компилятора и добавило бы риск ошибок. Работа этих методов продемонстрирована в конце программы.

### 3.3. Ход работы программы

1. Открываются файлы `input.txt` и `output.txt`; при отсутствии входного файла выводится сообщение об ошибке.
2. Считывается количество кредитов `n`, затем `n` записей: название (строка целиком, может содержать пробелы) и в следующей строке сумма, валюта и ставка. Кредиты заносятся в `deque<Credit>`.
3. Исходный контейнер копируется в `list<Credit>` алгоритмом `std::copy` (до сортировки).
4. В `output.txt` выводится исходный контейнер.
5. Контейнер `deque` сортируется `sort(credits.begin(), credits.end())` по возрастанию суммы кредита; результат выводится в файл.
6. Выводится контейнер-копия (`list`) — он сохранил исходный порядок.
7. Демонстрируются конструктор копирования, присваивание с копированием, конструктор перемещения и присваивание с перемещением.

### 3.4. Формат входного файла

В первой строке — число кредитов. Далее для каждого кредита две строки: название; сумма, тип валюты и ставка через пробел.

## 4. Входные данные (`input.txt`)

```text
6
Mortgage Standard
4500000.00 RUB 11.5
Auto Loan Fast
1200000.50 RUB 14.9
Student Credit
350000 RUB 5.5
Business Start
25000.75 USD 9.2
Consumer Credit
80000 EUR 12
Home Repair
150000.00 RUB 10.8
```

## 5. Результаты работы (`output.txt`)

```text
Source container (deque):
Mortgage Standard, amount 4500000.00 RUB, rate 11.50% per year
Auto Loan Fast, amount 1200000.50 RUB, rate 14.90% per year
Student Credit, amount 350000.00 RUB, rate 5.50% per year
Business Start, amount 25000.75 USD, rate 9.20% per year
Consumer Credit, amount 80000.00 EUR, rate 12.00% per year
Home Repair, amount 150000.00 RUB, rate 10.80% per year

Container after sorting (deque, std::sort by amount):
Business Start, amount 25000.75 USD, rate 9.20% per year
Consumer Credit, amount 80000.00 EUR, rate 12.00% per year
Home Repair, amount 150000.00 RUB, rate 10.80% per year
Student Credit, amount 350000.00 RUB, rate 5.50% per year
Auto Loan Fast, amount 1200000.50 RUB, rate 14.90% per year
Mortgage Standard, amount 4500000.00 RUB, rate 11.50% per year

Copy of the source container (list, algorithm copy):
Mortgage Standard, amount 4500000.00 RUB, rate 11.50% per year
Auto Loan Fast, amount 1200000.50 RUB, rate 14.90% per year
Student Credit, amount 350000.00 RUB, rate 5.50% per year
Business Start, amount 25000.75 USD, rate 9.20% per year
Consumer Credit, amount 80000.00 EUR, rate 12.00% per year
Home Repair, amount 150000.00 RUB, rate 10.80% per year

Copy constructor:      Business Start, amount 25000.75 USD, rate 9.20% per year
Copy assignment:       Business Start, amount 25000.75 USD, rate 9.20% per year
Move constructor:      Business Start, amount 25000.75 USD, rate 9.20% per year
Move assignment:       Business Start, amount 25000.75 USD, rate 9.20% per year
```

Контейнер `deque` после сортировки упорядочен по возрастанию суммы кредита, контейнер `list` содержит копию исходных данных в исходном порядке, что подтверждает корректность работы `std::copy` и `std::sort`.

## 6. Листинг программы (`main.cpp`)

```cpp
// Лабораторная работа №4. Вариант 22.
// Объект - банковский кредит (поля: название, сумма кредита, тип валюты, ставка в % годовых).
// Исходный контейнер deque, копируем в list. Сортировка по сумме кредита.
// Элементы контейнеров - объекты класса, а не указатели.
// Исходные данные читаются из input.txt, результаты выводятся в output.txt.
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
    // Конструктор копирования, конструктор перемещения и операции присваивания (с копированием и
    // с перемещением) писать не нужно: в классе нет указателей и динамической памяти, которой
    // владел бы сам класс. Поля string, double копируются и перемещаются корректно стандартными
    // средствами, поэтому подходят методы, которые автоматически создает компилятор.
    // Явное определение только дублировало бы их работу (правило нуля).
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
```

## 7. Вывод

В ходе лабораторной работы создан класс `Credit` для хранения информации о банковском кредите и организованы контейнеры `deque` и `list`, элементами которых являются объекты класса, а не указатели. Для класса перегружена операция вставки в поток `<<`, что упростило вывод объектов в файл, и операция `<` для сравнения по сумме кредита. Показано, что для класса без динамической памяти конструкторы копирования и перемещения и операции присваивания не требуется определять вручную: компилятор создаёт их корректно, что продемонстрировано в программе. Содержимое `deque` скопировано в `list` алгоритмом `std::copy`, а сортировка `deque` выполнена алгоритмом `std::sort` с двумя параметрами, так как `deque` поддерживает итераторы произвольного доступа. Для `list` такая сортировка недоступна (итераторы двунаправленные), для него применяется метод `list::sort`.
