#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// структура для описания телефона
struct Phone { // объявляем структуру
    string model; // название модели
    int storage; // объем памяти
    double price; // цена устройства
    bool has5G; // есть ли поддержка 5g
}; // конец объявления структуры

// ------------------- прототипы функций -------------------
void menu(); // функция управления меню
void pokazat_spisok(const Phone* arr, int size); // вывод на экран
void dobavit_element(Phone*& arr, int& size); // добавление
void udalit_element(Phone*& arr, int& size); // удаление
void ochistit_spisok(Phone*& arr, int& size); // полная очистка
void sohranit_v_fail(const Phone* arr, int size); // сохранение
void zagruzit_iz_faila(Phone*& arr, int& size); // загрузка

// ------------------- главная функция -------------------
int main() { // точка входа
    menu(); // просто запускаем меню, вся логика там
    return 0; // завершаем программу
} // конец main

// ------------------- реализация функций -------------------

// функция с главным циклом меню
void menu() { // реализация меню
    Phone* arr = nullptr; // указатель на динамический массив, пока пустой
    int size = 0; // текущий размер массива
    int vibor = 0; // переменная для выбора пользователя

    while (vibor != 7) { // пока не выбрали выход (цифра 7)
        cout << "\n--- MENYU ---\n"; // выводим название меню
        cout << "1. Vivesti spisok\n"; // пункт 1
        cout << "2. Dobavit element\n"; // пункт 2
        cout << "3. Udalit element\n"; // пункт 3
        cout << "4. Ochistit spisok\n"; // пункт 4
        cout << "5. Sohranit v fail\n"; // пункт 5
        cout << "6. Zagruzit iz faila\n"; // пункт 6
        cout << "7. Vihod\n"; // пункт 7
        cout << "Vash vibor: "; // просим ввести выбор

        // --- защита от ввода букв ---
        if (!(cin >> vibor)) { // если ввод не удался (ввели буквы)
            cout << "Oshibka! Nuzhno vvesti cifru.\n"; // сообщение об ошибке
            cin.clear(); // сбрасываем флаг ошибки потока
            cin.ignore(10000, '\n'); // очищаем буфер ввода от мусора
            continue; // идем в начало цикла заново
        } // конец защиты

        switch (vibor) { // проверяем, что выбрали
            case 1: pokazat_spisok(arr, size); break; // показываем список
            case 2: dobavit_element(arr, size); break; // добавляем
            case 3: udalit_element(arr, size); break; // удаляем
            case 4: ochistit_spisok(arr, size); break; // чистим всё
            case 5: sohranit_v_fail(arr, size); break; // сохраняем
            case 6: zagruzit_iz_faila(arr, size); break; // загружаем
            case 7: cout << "Vihod iz programmi...\n"; break; // выход
            default: cout << "Neverniy nomer.\n"; // если цифра не 1-7
        } // конец switch
    } // конец цикла while

    ochistit_spisok(arr, size); // удаляем память перед выходом из программы
} // конец функции меню

// функция вывода списка на экран
void pokazat_spisok(const Phone* arr, int size) { // принимаем массив и размер
    if (size == 0) { // если элементов нет
        cout << "Spisok pust.\n"; // пишем, что пусто
        return; // выходим из функции
    } // конец проверки
    cout << "\n--- VASH SPISOK ---\n"; // заголовок списка
    for (int i = 0; i < size; i++) { // пробегаем по всем элементам
        cout << i + 1 << ". " << arr[i].model // выводим номер и модель
             << " | " << arr[i].storage << "GB | " // память
             << arr[i].price << " rub | 5G: " // цена
             << (arr[i].has5G ? "Da" : "Net") << endl; // наличие 5g текстом
    } // конец цикла
} // конец функции вывода

// функция добавления элемента
void dobavit_element(Phone*& arr, int& size) { // меняем и массив, и размер
    Phone* temp = new Phone[size + 1]; // создаем новый массив на 1 больше
    for (int i = 0; i < size; i++) { // копируем старые данные
        temp[i] = arr[i]; // переносим элемент
    } // конец копирования

    // очищаем ввод перед использованием getline
    cin.ignore();

    cout << "Vvedite model: "; // запрос модели
    getline(cin, temp[size].model); // ! исправлено: читаем строку с пробелами

    cout << "Vvedite pamyat (GB): "; // запрос памяти
    cin >> temp[size].storage; // запись числа

    cout << "Vvedite cenu: "; // запрос цены
    cin >> temp[size].price; // запись цены

    cout << "Est li 5G (1-da, 0-net): "; // запрос 5g
    cin >> temp[size].has5G; // запись логического значения

    if (arr != nullptr) delete[] arr; // удаляем старый массив, если он был
    arr = temp; // обновляем указатель на новый массив
    size++; // увеличиваем счетчик элементов
    cout << "Element uspeshno dobavlen.\n"; // успех
} // конец функции добавления

// функция удаления элемента по номеру
void udalit_element(Phone*& arr, int& size) { // принимаем по ссылке
    if (size == 0) { // если список пуст
        cout << "Udalyat nechego.\n"; // ошибка
        return; // выход
    }
    int nomer; // переменная для номера
    cout << "Vvedite nomer (1-" << size << "): "; // просим номер
    if (!(cin >> nomer)) { // проверка на ввод букв внутри удаления
        cout << "Oshibka ввода.\n"; // ошибка
        cin.clear(); cin.ignore(10000, '\n'); // чистим ввод
        return; // выходим
    }

    if (nomer < 1 || nomer > size) { // проверка границ
        cout << "Takogo nomera net.\n"; // ошибка
        return; // выход
    }

    Phone* temp = new Phone[size - 1]; // новый массив поменьше
    int index = 0; // индекс для нового массива
    for (int i = 0; i < size; i++) { // проходим по старому массиву
        if (i == nomer - 1) continue; // пропускаем тот, который удаляем
        temp[index] = arr[i]; // копируем остальные
        index++; // двигаем индекс
    }
    delete[] arr; // удаляем старый массив
    arr = temp; // переключаем на новый
    size--; // уменьшаем размер
    cout << "Udaleno.\n"; // успех
} // конец функции удаления

// функция очистки всего списка
void ochistit_spisok(Phone*& arr, int& size) { // принимаем по ссылке
    if (arr != nullptr) { // если память выделена
        delete[] arr; // освобождаем её
        arr = nullptr; // зануляем указатель
    }
    size = 0; // сбрасываем размер
    cout << "Spisok ochishen.\n"; // сообщение
} // конец очистки

// функция сохранения в файл
void sohranit_v_fail(const Phone* arr, int size) { // чтение массива
    ofstream file("phones.txt"); // открываем файл для записи
    if (!file.is_open()) { // если не открылся
        cout << "Ne udalos otkrit fail.\n"; // ошибка
        return;
    }
    file << size << endl; // пишем количество
    for (int i = 0; i < size; i++) { // пишем данные
        // сохраняем все поля через пробел
        file << arr[i].model << endl; // модель на отдельной строке (так безопаснее для пробелов)
        file << arr[i].storage << endl; // память
        file << arr[i].price << endl; // цена
        file << arr[i].has5G << endl; // 5g
    }
    file.close(); // закрываем файл
    cout << "Sohraneno v phones.txt\n"; // успех
} // конец сохранения

// функция загрузки из файла
void zagruzit_iz_faila(Phone*& arr, int& size) { // запись в массив
    ifstream file("phones.txt"); // открываем для чтения
    if (!file.is_open()) { // если нет файла
        cout << "Fail ne naiden.\n"; // ошибка
        return;
    }
    ochistit_spisok(arr, size); // чистим текущий список
    file >> size; // читаем количество
    file.ignore(); // пропускаем перенос строки после числа

    if (size > 0) { // если есть данные
        arr = new Phone[size]; // выделяем память
        for (int i = 0; i < size; i++) { // читаем цикл
            getline(file, arr[i].model); // читаем модель (целую строку)
            file >> arr[i].storage; // читаем память
            file >> arr[i].price; // читаем цену
            file >> arr[i].has5G; // читаем 5g
            file.ignore(); // пропускаем перенос строки перед следующим
        }
    }
    file.close(); // закрываем
    cout << "Zagruzheno.\n"; // успех
} // конец загрузки