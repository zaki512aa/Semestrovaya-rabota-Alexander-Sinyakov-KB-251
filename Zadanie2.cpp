#include <iostream>
#include <string>

using namespace std;

// структура для хранения товара
struct Tovar { // объявляем структуру
    string nazvanie; // название товара
    double cena; // цена товара
}; // конец структуры

// ------------------- прототипы функций -------------------
// функция добавления товара (принимает указатель на массив и размер по ссылке)
void dobavit_tovar(Tovar*& massiv, int& razmer);
// функция показа списка (принимает массив и копию размера)
void pokazat_spisok(const Tovar* massiv, int razmer);
// функция очистки памяти перед выходом
void ochistit_pamyat(Tovar*& massiv);

int main() { // точка входа в программу
    Tovar* moi_tovari = nullptr; // инициализируем указатель пустотой
    int kolichestvo = 0; // переменная хранит текущее количество товаров
    int vibor = 0; // переменная для хранения выбора меню

    while (vibor != 3) { // цикл работает, пока не выберут выход (3)
        cout << "\n--- MENYU ---\n"; // выводим заголовок меню
        cout << "1. Dobavit tovar\n"; // пункт 1
        cout << "2. Pokazat spisok\n"; // пункт 2
        cout << "3. Vihod\n"; // пункт 3
        cout << "Vash vibor: "; // просим ввести число

        // проверка: удалось ли считать число в переменную
        if (!(cin >> vibor)) { // если ввод сломался (ввели буквы)
            cout << "Oshibka! Nuzhno vvesti cifru.\n"; // пишем ошибку
            cin.clear(); // сбрасываем флаг ошибки у cin, "чиним" его
            cin.ignore(10000, '\n'); // удаляем весь мусор (буквы) из памяти ввода
            continue; // перезапускаем цикл с начала, чтобы спросить снова
        } // конец проверки на ошибки

        switch (vibor) { // проверяем, какую цифру ввели
            case 1: // если ввели 1
                dobavit_tovar(moi_tovari, kolichestvo); // идем в функцию добавления
                break; // выходим из switch
            case 2: // если ввели 2
                pokazat_spisok(moi_tovari, kolichestvo); // идем в функцию просмотра
                break; // выходим из switch
            case 3: // если ввели 3
                cout << "Zavershenie raboti...\n"; // прощаемся
                break; // выходим из switch
            default: // если ввели любую другую цифру
                cout << "Neverniy vvod. Viberite 1, 2 ili 3.\n"; // ругаемся
        }
    }

    ochistit_pamyat(moi_tovari); // чистим память перед выходом
    return 0;
}
// ------------------- реализация функций -------------------

void dobavit_tovar(Tovar*& massiv, int& razmer) { // реализация добавления
    // 1. создаем новый временный массив размером на 1 больше старого
    Tovar* temp = new Tovar[razmer + 1]; // выделяем память

    // 2. копируем старые данные в новый массив
    for (int i = 0; i < razmer; i++) { // пробегаем по старому размеру
        temp[i] = massiv[i]; // переносим данные в новый массив
    } // конец цикла копирования

    // 3. очищаем буфер перед вводом строки
    // это нужно, потому что после ввода числа в меню остался "энтер"
    cin.ignore();

    // 4. спрашиваем данные
    cout << "Vvedite nazvanie: "; // запрос названия
    getline(cin, temp[razmer].nazvanie); // ! ИСПРАВЛЕНО: читаем всю строку с пробелами

    cout << "Vvedite cenu: "; // запрос цены
    cin >> temp[razmer].cena; // записываем цену

    // 5. удаляем старый маленький массив
    if (massiv != nullptr) { // проверяем, был ли он вообще создан
        delete[] massiv; // удаляем старый массив
    } // конец проверки

    // 6. перенаправляем основной указатель
    massiv = temp; // теперь наш массив — это temp
    razmer++; // увеличиваем счетчик товаров на 1
    cout << "Tovar dobavlen.\n"; // сообщаем об успехе
}

void pokazat_spisok(const Tovar* massiv, int razmer) { // реализация просмотра
    if (razmer == 0) { // если товаров 0
        cout << "Spisok pust.\n"; // пишем, что пусто
        return; // выходим из функции
    } // конец проверки

    cout << "\n--- VASHI TOVARI ---\n"; // заголовок
    for (int i = 0; i < razmer; i++) { // цикл от 0 до конца массива
        // выводим: номер. название - цена
        cout << (i + 1) << ". " << massiv[i].nazvanie
             << " - " << massiv[i].cena << " rub.\n";
    }
}

void ochistit_pamyat(Tovar*& massiv) { // реализация очистки
    if (massiv != nullptr) { // если память была выделена
        delete[] massiv; // освобождаем память массива
        massiv = nullptr; // зануляем указатель для безопасности
    }
}