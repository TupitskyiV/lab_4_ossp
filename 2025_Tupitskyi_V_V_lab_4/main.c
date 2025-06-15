// ==== main.c ====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "HardwareComponent.h"

#define COUNT 50

// Функція для очищення залишків у буфері stdin після scanf
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    // Встановлення кодування консолі на UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    HardwareComponent components[COUNT]; // Масив компонентів
    int num = 0;                         // Кількість активних компонентів у масиві
    int choice;
    char searchName[100];
    int searchCode;
    HardwareComponent temp;              // Тимчасова змінна для читання з бінарного файлу

    do {
        // Вивід меню
        printf("\n+===============================+\n");
        printf("|       LAB WORK #4 MENU        |\n");
        printf("+===============================+\n");
        printf("1. Read array from file\n");
        printf("2. Enter array from keyboard\n");
        printf("3. Display array to screen\n");
        printf("4. Save array to binary file\n");
        printf("5. Read element from binary file by index\n");
        printf("6. Search by name\n");
        printf("7. Search by code\n");
        printf("0. Exit\n");
        printf("Your choice: ");

        // Перевірка коректності вводу choice
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Try again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer(); // Очищаємо буфер після вводу числа

        switch (choice) {
            case 1: {
                // Відкриття текстового файлу для читання
                FILE *in = fopen("components.txt", "r");
                if (!in) {
                    printf("Error opening file!\n");
                    break;
                }

                // Зчитуємо максимум COUNT записів
                num = COUNT;
                if (!readComponents(components, num, in)) {
                    printf("Error reading components from file.\n");
                    fclose(in);
                    break;
                }
                fclose(in);
                printf("Data loaded from file.\n");
                break;
            }
            case 2: {
                // Введення кількості записів для вводу з клавіатури
                printf("How many records to enter (max %d): ", COUNT);
                if (scanf("%d", &num) != 1 || num <= 0 || num > COUNT) {
                    printf("Invalid number.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();
                // Зчитування записів з клавіатури
                readComponentsFromKeyboard(components, num);
                break;
            }
            case 3: {
                // Вивід масиву компонентів на екран
                if (num <= 0) {
                    printf("No data to display.\n");
                    break;
                }
                printComponents(components, num, stdout);
                break;
            }
            case 4: {
                // Запис масиву у бінарний файл
                if (num <= 0) {
                    printf("No data to save.\n");
                    break;
                }
                FILE *out = fopen("components.bin", "wb");
                if (!out) {
                    printf("Error creating file.\n");
                    break;
                }
                size_t written = fwrite(components, sizeof(HardwareComponent), num, out);
                fclose(out);
                if (written != (size_t)num) {
                    printf("Error writing to binary file.\n");
                } else {
                    printf("Data written to binary file.\n");
                }
                break;
            }
            case 5: {
                // Читання одного запису з бінарного файлу за індексом
                if (num <= 0) {
                    printf("No data available. Save data first.\n");
                    break;
                }
                int index;
                printf("Enter index (starting from 0): ");
                if (scanf("%d", &index) != 1 || index < 0 || index >= num) {
                    printf("Invalid index.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                readFromBinaryFile(&temp, "components.bin", index);
                printComponent(&temp, stdout);
                break;
            }
            case 6: {
                // Пошук за назвою
                if (num <= 0) {
                    printf("No data to search.\n");
                    break;
                }
                printf("Enter name to search: ");
                if (scanf("%99s", searchName) != 1) {
                    printf("Invalid input.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                int idxName = findByName(components, num, searchName);
                if (idxName != -1)
                    printComponent(&components[idxName], stdout);
                else
                    printf("Not found.\n");
                break;
            }
            case 7: {
                // Пошук за кодом
                if (num <= 0) {
                    printf("No data to search.\n");
                    break;
                }
                printf("Enter code to search: ");
                if (scanf("%d", &searchCode) != 1) {
                    printf("Invalid input.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                int idxCode = findByCode(components, num, searchCode);
                if (idxCode != -1)
                    printComponent(&components[idxCode], stdout);
                else
                    printf("Not found.\n");
                break;
            }
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
