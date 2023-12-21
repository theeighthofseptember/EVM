#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

// Функция conclusion выводит результаты среднего времени выполнения команды
void conclusion(float add_P, float add_K, float n) {
    add_P /= n; // Делим суммарное время выполнения без конвейера на количество итераций (n) для получения среднего времени выполнения без конвейера
    add_K /= n; // Делим суммарное время выполнения с конвейером на количество итераций (n) для получения среднего времени выполнения с конвейером
    cout << "average pipeline execution time: " << add_K << " not pipeline: " << add_P << endl; // Выводим результаты: среднее время выполнения с конвейером и без конвейера
}

// Функция getUserChoice запрашивает у пользователя ввод, пока он не введет корректное значение в заданном диапазоне
int getUserChoice(const string& prompt, int minOption, int maxOption) {
    int choice;
    bool isValidInput = false;

    do {
        cout << prompt;

        // Проверяем, что введенное значение является числом и в границах допустимого диапазона
        if (cin >> choice && choice >= minOption && choice <= maxOption) {
            isValidInput = true; // Если условие выполняется, устанавливаем флаг валидного ввода
        }
        else {
            // Очищаем поток ввода от ошибочного ввода и игнорируем его
            cout << "El stupido! U gonna be el deportato! Just choose 1, 2 or 3, porfavor..." << endl;
            cin.clear(); // Очищаем поток ввода от ошибочного ввода
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем оставшиеся символы в потоке до символа новой строки
        }
    } while (!isValidInput);

    return choice;
}

// Функция, запрашивающая вероятность у пользователя
float getProbability(const string& prompt) {
    int choice = getUserChoice(prompt, 1, 3);

    switch (choice) {
    case 1:
        return 0.9;
    case 2:
        return 0.8;
    case 3:
        return 0.6;
    }
}

// Функция, запрашивающая целое значение у пользователя
int getIntValue(const string& prompt, int option1, int option2, int option3) {
    int choice = getUserChoice(prompt, 1, 3);

    switch (choice) {
    case 1:
        return option1;
    case 2:
        return option2;
    case 3:
        return option3;
    }
}

// Функция getRandomValue возвращает случайное число в диапазоне [0, 1)
float Rand() {
    static std::random_device rd; // Создаем объект для генерации неэнтропийных случайных чисел
    static std::mt19937 gen(rd()); // Инициализируем генератор случайных чисел Mersenne Twister с 32-битным состоянием
    std::uniform_real_distribution<float> dis(0.0, 1.0); // Создаем объект для равномерного распределения в заданном диапазоне [0.0, 1.0)
    return dis(gen); // Возвращаем случайное число из указанного диапазона
}

int main() {
    srand(time(NULL));

    char c;
    float P1 = 0, P2 = 0, add_P = 0, add_K = 0, n = 20000;

    // Основной цикл программы
    while (true) {
        cout << "1 - start programm\n2 - quit programm\n";
        cin >> c;
        while (cin.fail() || (c != '1' && c != '2')) {
            cout << "Ay caramba, can u just put 1 or 2?" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> c;
        }
        switch (c) {
        case '1':
            // Запрос вероятности P1 у пользователя и присвоение соответствующего значения
            P1 = getProbability(" P1 = \n1)  0.9\n2)  0.8\n3)  0.6\n");

            // Запрос вероятности P2 у пользователя и присвоение соответствующего значения
            P2 = getProbability(" P2 = \n1)  0.9\n2)  0.7\n3)  0.5\n");

            int N, M;

            // Запрос значения N у пользователя и присвоение соответствующего значения
            N = getIntValue(" N = \n1)  2\n2)  5\n3)  10\n", 2, 5, 10);

            // Запрос значения M у пользователя и присвоение соответствующего значения
            M = getIntValue(" M = \n1)  4\n2)  8\n3)  16\n", 4, 8, 16);

            // Цикл симуляции конвейера процессора
            for (int i = 0; i < n; i++) {
                cout << i;
                // Массив stages представляет собой ступени конвейера
                int level[5] = { 1, 1, 1, 1, 1 };

                // Этап 1: Чтение и декодирование
                level[0] = 1;

                // Этап 2: Извлечение операнда
                level[1] = 1;

                // Этап 3: Извлечение второго операнда с вероятностью P1
                level[2] = Rand() > P1 ? N : 1;

                // Этап 4: Выполнение с вероятностью P2
                level[3] = Rand() > P2 ? M : 1;

                // Этап 5: Запись результата
                level[4] = level[2];  // Предполагаем запись по тому же адресу, что и у второго операнда

                // Вывод текущих ступеней конвейера
                for (int i = 0; i < 5; i++) {
                    add_P += level[i];
                    cout << " " << level[i];
                }
                cout << endl;

                // Вычисление максимума по ступеням конвейера
                int MAX = *max_element(begin(level), end(level));

                // Добавление к общему времени выполнения
                add_K += MAX;
                add_K += level[3];
                add_K += level[4];
            }
            // Вывод результатов среднего времени выполнения
            conclusion(add_P, add_K, n);
            break;

        case '2':
            cout << "Adios, amigo!";
            return 0;
        }
    }
}
