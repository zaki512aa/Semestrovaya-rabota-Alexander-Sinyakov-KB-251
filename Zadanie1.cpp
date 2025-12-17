#include <iostream>
#include <string>

using namespace std;

// описание структуры согласно варианту телефон
struct Phone { // объявляем структуру телефона
    string model; // строковое поле для названия модели
    int storage; // целочисленное поле для памяти
    double price; // дробное число для цены
    bool has5G; // логическое поле (true/false) для 5g
}; // конец описания структуры

// --- прототипы функций (объявления до использования) ---

// функция ввода данных, меняет оригинал через ссылку &
void inputPhoneData(Phone& p);

// функция вывода, только читает данные (const) и не копирует их (&)
void printPhoneData(const Phone& p);

// функция-оболочка для выполнения задания (тест)
void runTest();

// --- главная функция ---
int main() { // точка входа в программу
    runTest(); // вызываем функцию тестирования, как требует задание

    return 0; // программа завершилась успешно
} // конец main

// --- реализация функций ---

// реализация функции ввода данных
void inputPhoneData(Phone& p) { // принимаем структуру по ссылке
    cout << "Vvedite model telefona: "; // просим ввести имя
    getline(cin, p.model); // считываем строку целиком (с пробелами)

    cout << "Vvedite pamyat (GB): "; // просим ввести память
    cin >> p.storage; // считываем целое число

    cout << "Vvedite cenu: "; // просим ввести цену
    cin >> p.price; // считываем дробное число

    cout << "Est li 5G? (1 - da, 0 - net): "; // просим ввести 1 или 0
    cin >> p.has5G; // считываем да/нет значение

    // очищаем поток ввода, чтобы следующий getline не считал "энтер"
    cin.ignore();
} // конец функции ввода

// реализация функции вывода данных
void printPhoneData(const Phone& p) { // принимаем константную ссылку
    cout << endl; // выводим пустую строку для красоты
    cout << "=== Dannye o telefone ===" << endl; // заголовок
    cout << "Model: " << p.model << endl; // выводим модель из структуры
    cout << "Pamyat: " << p.storage << " GB" << endl; // выводим память
    cout << "Cena: " << p.price << " rub." << endl; // выводим цену

    if (p.has5G) { // проверяем, есть ли 5g
        cout << "Set: 5G podderzhivaetsya" << endl; // если true (1)
    } else { // если нет 5g
        cout << "Set: tolko 4G/LTE" << endl; // если false (0)
    } // конец условия
} // конец функции вывода

// реализация функции тестирования
void runTest() { // функция, скрывающая логику от main
    Phone myPhone; // создаем переменную типа Phone

    inputPhoneData(myPhone); // передаем ее для заполнения данными
    printPhoneData(myPhone); // передаем ее для вывода на экран
}