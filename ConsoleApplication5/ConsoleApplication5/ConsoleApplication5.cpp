#include <iostream>

using namespace std;

// Функция для добавления столбца в матрицу
void addColumn(int*** matrix, int& rows, int& cols, int* newCol, int position) {
    // Проверка на допустимость позиции
    if (position < 0 || position > cols) {
        cout << "Неверная позиция!" << endl;
        return;
    }

    // Выделяем новую память для матрицы
    int** newMatrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        newMatrix[i] = new int[cols + 1]; // Увеличиваем количество столбцов
    }

    // Копируем данные в новую матрицу, добавляя новый столбец
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols + 1; j++) {
            if (j < position) {
                newMatrix[i][j] = (*matrix)[i][j];
            }
            else if (j == position) {
                newMatrix[i][j] = newCol[i]; // Добавляем новый столбец
            }
            else {
                newMatrix[i][j] = (*matrix)[i][j - 1];
            }
        }
    }

    // Освобождаем память старой матрицы
    for (int i = 0; i < rows; i++) {
        delete[](*matrix)[i];
    }
    delete[] * matrix;

    *matrix = newMatrix; // Указываем на новую матрицу
    cols++; // Увеличиваем количество столбцов
}

// Функция для удаления столбца из матрицы
void removeColumn(int*** matrix, int& rows, int& cols, int position) {
    // Проверка на допустимость позиции
    if (position < 0 || position >= cols) {
        cout << "Неверная позиция!" << endl;
        return;
    }

    // Выделяем новую память для матрицы
    int** newMatrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        newMatrix[i] = new int[cols - 1]; // Уменьшаем количество столбцов
    }

    // Копируем данные в новую матрицу, пропуская удаляемый столбец
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols - 1; j++) {
            newMatrix[i][j] = (j < position) ? (*matrix)[i][j] : (*matrix)[i][j + 1];
        }
    }

    // Освобождаем память старой матрицы
    for (int i = 0; i < rows; i++) {
        delete[](*matrix)[i];
    }
    delete[] * matrix;

    *matrix = newMatrix; // Указываем на новую матрицу
    cols--; // Уменьшаем количество столбцов
}

// Функция для циклического сдвига строк
void shiftRows(int** matrix, int rows, int cols, int shifts) {
    shifts = shifts % rows; // Убедимся, что shifts не превышает количество строк
    if (shifts < 0) shifts += rows;

    int** temp = new int* [rows];
    for (int i = 0; i < rows; i++) {
        temp[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            temp[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = temp[(i - shifts + rows) % rows][j];
        }
    }

    // Освобождаем память временной матрицы
    for (int i = 0; i < rows; i++) {
        delete[] temp[i];
    }
    delete[] temp;
}

// Функция для циклического сдвига столбцов
void shiftColumns(int** matrix, int rows, int cols, int shifts) {
    shifts = shifts % cols; // Убедимся, что shifts не превышает количество столбцов
    if (shifts < 0) shifts += cols;

    int** temp = new int* [rows];
    for (int i = 0; i < rows; i++) {
        temp[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            temp[i][j] = matrix[i][j];
        }
    }

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            matrix[i][j] = temp[i][(j - shifts + cols) % cols];
        }
    }

    // Освобождаем память временной матрицы
    for (int i = 0; i < rows; i++) {
        delete[] temp[i];
    }
    delete[] temp;
}

// Функция для печати матрицы
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Изначальная матрица
    int rows = 3, cols = 3;
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    // Заполнение матрицы значениями
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
        }
    }

    cout << "Исходная матрица:" << endl;
    printMatrix(matrix, rows, cols);

    // Добавление нового столбца
    int newCol[] = { 10, 11, 12 }; // Новый столбец
    int addPosition = 1; // позиция для добавления нового столбца
    addColumn(&matrix, rows, cols, newCol, addPosition);

    cout << "Матрица после добавления столбца:" << endl;
    printMatrix(matrix, rows, cols);

    // Удаление столбца
    int removePosition = 1; // позиция для удаления столбца
    removeColumn(&matrix, rows, cols, removePosition);

    cout << "Матрица после удаления столбца:" << endl;
    printMatrix(matrix, rows, cols);

    // Циклический сдвиг строк и столбцов
    int rowShifts = 1; // количество сдвигов строк
    int colShifts = 1; // количество сдвигов столбцов

    shiftRows(matrix, rows, cols, rowShifts);
    shiftColumns(matrix, rows, cols, colShifts);

    cout << "Матрица после сдвига строк и столбцов:" << endl;
    printMatrix(matrix, rows, cols);

    // Освобождение памяти матрицы
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
