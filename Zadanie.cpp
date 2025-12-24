#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// структура для описания зайца (вариант 11)
struct Zayac { // объявляем структуру
    string name;    // строковое поле для клички
    int age;        // целочисленное поле для возраста
    double weight;  // вещественное поле для веса
    bool isWild;    // логическое поле: (true) или (false)
}; // конец объявления структуры

// ------------------- прототипы функций -------------------
void menu(); // объявление функции меню
void pokazat_spisok(const Zayac* arr, int size); // объявление функции вывода
void dobavit_element(Zayac*& arr, int& size); // объявление функции добавления
void udalit_element(Zayac*& arr, int& size); // объявление функции удаления
void ochistit_spisok(Zayac*& arr, int& size); // объявление функции очистки
void sohranit_v_fail(const Zayac* arr, int size); // объявление функции сохранения
void zagruzit_iz_faila(Zayac*& arr, int& size); // объявление функции загрузки

// ------------------- главная функция -------------------
int main() {
    menu(); // запускаем основное меню
    return 0;
}

// ------------------- реализация функций -------------------

// функция с логикой меню
void menu() { // начало функции меню
    Zayac* arr = nullptr; // создаем указатель на массив, пока он пустой (null)
    int size = 0;         // переменная хранит текущее количество зайцев
    int vibor = 0;        // переменная для хранения выбора пользователя

    while (vibor != 7) { // цикл работает, пока не выберут пункт 7
        cout << "\n--- MENU  ---\n"; // выводим заголовок
        cout << "1. Vivesti spisok zaycev\n"; // пункт 1: вывод списка
        cout << "2. Dobavit novogo zayca\n"; // пункт 2: добавление
        cout << "3. Udalit zayca\n"; // пункт 3: удаление
        cout << "4. Ochistit spisok\n"; // пункт 4: очистка
        cout << "5. Sohranit v fail\n"; // пункт 5: сохранение
        cout << "6. Zagruzit iz faila\n"; // пункт 6: загрузка
        cout << "7. Vihod\n"; // пункт 7: выход
        cout << "Vash vibor: "; // просим ввести номер действия

        if (!(cin >> vibor)) { // если ввели букву вместо цифры
            cout << "Oshibka! Vvedite chislo.\n"; // сообщаем об ошибке транслитом
            cin.clear(); // сбрасываем флаг ошибки потока
            cin.ignore(10000, '\n'); // очищаем буфер ввода от мусора
            continue; // идем на новую итерацию цикла
        } // конец проверки ввода

        switch (vibor) { // проверяем, какую цифру ввели
            case 1: pokazat_spisok(arr, size); break; // показываем список
            case 2: dobavit_element(arr, size); break; // добавляем элемент
            case 3: udalit_element(arr, size); break; // удаляем элемент
            case 4: ochistit_spisok(arr, size); break; // чистим память
            case 5: sohranit_v_fail(arr, size); break; // сохраняем в файл
            case 6: zagruzit_iz_faila(arr, size); break; // загружаем из файла
            case 7: cout << "Vihod iz programmi...\n"; break;
            default: cout << "Neverniy nomer menu.\n"; // если цифра не от 1 до 7
        } // конец switch
    } // конец цикла while

    ochistit_spisok(arr, size); // удаляем массив из памяти перед выходом
} // конец функции меню

// функция вывода списка на экран
void pokazat_spisok(const Zayac* arr, int size) { // принимаем массив и размер
    if (size == 0) { // если размер равен 0
        cout << "Spisok pust.\n"; // пишем, что список пуст
        return; // выходим из функции
    } // конец проверки
    cout << "\n--- SPISOK ZAYCEV ---\n"; // заголовок списка
    for (int i = 0; i < size; i++) { // цикл по всем элементам массива
        cout << i + 1 << ". " // выводим порядковый номер
             << "Klichka: " << arr[i].name // выводим имя
             << " | Vozrast: " << arr[i].age << " let" // выводим возраст
             << " | Ves: " << arr[i].weight << " kg" // выводим вес
             << " | Tip: " << (arr[i].isWild ? "Dikiy" : "Domashniy") << endl; // выводим тип словами
    } // конец цикла
} // конец функции вывода

// функция добавления элемента в динамический массив
void dobavit_element(Zayac*& arr, int& size) { // принимаем ссылки на указатель и размер
    Zayac* temp = new Zayac[size + 1]; // создаем новый массив на 1 элемент больше

    for (int i = 0; i < size; i++) { // копируем данные из старого массива
        temp[i] = arr[i]; // переносим элемент
    } // конец цикла копирования

    cin.ignore(); // очищаем буфер ввода перед чтением строки
    cout << "Vvedite klichku zayaca: "; // просим ввести имя
    getline(cin, temp[size].name); // читаем строку с пробелами в новый элемент

    cout << "Vvedite vozrast (let): "; // просим ввести возраст
    cin >> temp[size].age; // записываем возраст

    cout << "Vvedite ves (kg): "; // просим ввести вес
    cin >> temp[size].weight; // записываем вес

    cout << "Zayac dikiy? (1 - da, 0 - net): "; // просим указать тип
    cin >> temp[size].isWild; // записываем булево значение

    if (arr != nullptr) delete[] arr; // если старый массив был, удаляем его
    arr = temp; // перенаправляем указатель на новый массив
    size++; // увеличиваем счетчик элементов
    cout << "\nZayac uspeshno dobavlen.\n"; // сообщаем об успехе
} // конец функции добавления

// функция удаления элемента
void udalit_element(Zayac*& arr, int& size) { // принимаем ссылки для изменения
    if (size == 0) { // если элементов нет
        cout << "Spisok pust, udalyat nechego.\n"; // ошибка удаления
        return; // выход
    } // конец проверки

    int nomer; // переменная для номера
    cout << "Vvedite nomer dlya udaleniya (1-" << size << "): "; // просим номер
    if (!(cin >> nomer)) { // если ввели буквы
        cin.clear(); cin.ignore(10000, '\n'); // чистим ввод
        cout << "Oshibka vvoda.\n"; // ошибка
        return; // выход
    } // конец проверки ввода

    if (nomer < 1 || nomer > size) { // проверяем границы номера
        cout << "Takogo nomera net.\n"; // если номер неверен
        return; // выход
    } // конец проверки границ

    Zayac* temp = new Zayac[size - 1]; // новый массив на 1 элемент меньше
    int index = 0; // индекс для заполнения нового массива
    for (int i = 0; i < size; i++) { // пробегаем по старому массиву
        if (i == nomer - 1) continue; // пропускаем тот элемент, который удаляем
        temp[index] = arr[i]; // копируем остальные элементы
        index++; // увеличиваем индекс нового массива
    } // конец цикла

    delete[] arr; // удаляем старый массив
    arr = temp; // обновляем указатель
    size--; // уменьшаем размер
    cout << "Element udalen.\n"; // успех
} // конец функции удаления

// функция очистки памяти
void ochistit_spisok(Zayac*& arr, int& size) { // принимаем ссылки
    if (arr != nullptr) { // если память была выделена
        delete[] arr; // освобождаем её
        arr = nullptr; // зануляем указатель
    } // конец условия
    size = 0; // обнуляем размер
    cout << "Spisok ochishen.\n"; // сообщение
} // конец функции очистки

// функция сохранения в файл
void sohranit_v_fail(const Zayac* arr, int size) { // только чтение данных
    ofstream file("zayacy.txt"); // открываем файл для записи
    if (!file.is_open()) { // если файл не открылся
        cout << "Oshibka otkritiya faila.\n"; // ошибка
        return; // выход
    } // конец проверки
    file << size << endl; // записываем количество элементов
    for (int i = 0; i < size; i++) { // цикл записи данных
        file << arr[i].name << endl; // пишем имя
        file << arr[i].age << endl; // пишем возраст
        file << arr[i].weight << endl; // пишем вес
        file << arr[i].isWild << endl; // пишем статус
    } // конец цикла
    file.close(); // закрываем файл
    cout << "Spisok sohranen v fail zayacy.txt\n"; // успех
} // конец функции сохранения

// функция загрузки из файла
void zagruzit_iz_faila(Zayac*& arr, int& size) { // изменение данных
    ifstream file("zayacy.txt"); // открываем файл для чтения
    if (!file.is_open()) { // если файла нет
        cout << "Fail zayacy.txt ne naiden.\n"; // ошибка
        return; // выход
    } // конец проверки

    ochistit_spisok(arr, size); // удаляем текущие данные

    file >> size; // читаем количество элементов
    file.ignore(); // пропускаем перенос строки

    if (size > 0) { // если список не пуст
        arr = new Zayac[size]; // выделяем новую память
        for (int i = 0; i < size; i++) { // цикл чтения
            getline(file, arr[i].name); // читаем строку имени
            file >> arr[i].age; // читаем возраст
            file >> arr[i].weight; // читаем вес
            file >> arr[i].isWild; // читаем статус
            file.ignore(); // пропускаем перенос строки для следующего getline
        } // конец цикла
    } // конец условия
    file.close(); // закрываем файл
    cout << "Spisok zagruzhen iz faila.\n"; // успех

} // конец функции загрузки
