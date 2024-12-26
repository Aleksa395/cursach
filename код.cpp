#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

void findIntersection(int** arrays, int* sizes, int numArrays) {
    int* intersection = (int*)malloc(sizeof(int) * sizes[0]);
    int intersectionSize = 0;

    // Поиск пересечения
    for (int i = 0; i < sizes[0]; i++) {
        int isCommon = 1;

        for (int j = 1; j < numArrays; j++) {
            int found = 0;
            for (int k = 0; k < sizes[j]; k++) {
                if (arrays[0][i] == arrays[j][k]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                isCommon = 0;
                break;
            }
        }

        if (isCommon) {
            intersection[intersectionSize++] = arrays[0][i];
        }
    }

    printf("Пересечение: ");
    for (int i = 0; i < intersectionSize; i++) {
        printf("%d ", intersection[i]);
    }
    printf("\n");

    // Вывод изначальных массивов
    for (int i = 0; i < numArrays; i++) {
        printf("Массив %d: ", i + 1);
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d ", arrays[i][j]);
        }
        printf("\n");
    }

    free(intersection);
}

void menu() {
    setlocale(LC_ALL, "Rus");
    int choice = 0;
    int numArrays;
    int** arrays = NULL;
    int* sizes = NULL;
    int fillChoice;

    do {
        printf("\nМеню:\n");
        printf("1. Введите кол-во множеств\n");
        printf("2. Создать множества\n");
        printf("3. Найти пересечение множеств\n");
        printf("4. Выйти\n");
        printf("Ваш выбор: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("Введите количество массивов: ");
            scanf("%d", &numArrays);
            // Динамическое выделение памяти
            arrays = (int**)malloc(numArrays * sizeof(int*));
            sizes = (int*)malloc(numArrays * sizeof(int));
            break;
        case 2:
            printf("Выберите способ заполнения массивов:\n");
            printf("1. Ручное заполнение\n");
            printf("2. Автоматическое заполнение\n");
            printf("Ваш выбор: ");
            scanf("%d", &fillChoice);

            for (int i = 0; i < numArrays; i++) {
                printf("Введите размер массива %d: ", i + 1);
                scanf("%d", &sizes[i]);
                arrays[i] = (int*)malloc(sizes[i] * sizeof(int));

                if (fillChoice == 1) {
                    // Ручное заполнение
                    printf("Введите элементы массива %d:\n", i + 1);
                    for (int j = 0; j < sizes[i]; j++) {
                        scanf("%d", &arrays[i][j]);
                    }
                }
                else if (fillChoice == 2) {
                    // Автоматическое заполнение
                    printf("Автоматически заполняем массив %d:\n", i + 1);
                    for (int j = 0; j < sizes[i]; j++) {
                        arrays[i][j] = rand() % 10; // случайные числа от 0 до 1
                    }
                }
            }
            break;
        case 3:
            findIntersection(arrays, sizes, numArrays);
            break;
        case 4:
            printf("Выход из программы.\n");
            // Освобождение памяти
            for (int i = 0; i < numArrays; i++) {
                free(arrays[i]);
            }
            free(arrays);
            free(sizes);
            break;
        default:
            printf("Неверный выбор, попробуйте снова.\n");
        }
        system("pause");
        system("cls");
    } while (choice != 4);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    menu();

    return 0;
}