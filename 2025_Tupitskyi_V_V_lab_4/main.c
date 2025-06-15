// ==== main.c ====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "HardwareComponent.h"

#define COUNT 50

// ������� ��� �������� ������� � ����� stdin ���� scanf
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    // ������������ ��������� ������ �� UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    HardwareComponent components[COUNT]; // ����� ����������
    int num = 0;                         // ʳ������ �������� ���������� � �����
    int choice;
    char searchName[100];
    int searchCode;
    HardwareComponent temp;              // ��������� ����� ��� ������� � �������� �����

    do {
        // ���� ����
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

        // �������� ���������� ����� choice
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Try again.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer(); // ������� ����� ���� ����� �����

        switch (choice) {
            case 1: {
                // ³������� ���������� ����� ��� �������
                FILE *in = fopen("components.txt", "r");
                if (!in) {
                    printf("Error opening file!\n");
                    break;
                }

                // ������� �������� COUNT ������
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
                // �������� ������� ������ ��� ����� � ���������
                printf("How many records to enter (max %d): ", COUNT);
                if (scanf("%d", &num) != 1 || num <= 0 || num > COUNT) {
                    printf("Invalid number.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();
                // ���������� ������ � ���������
                readComponentsFromKeyboard(components, num);
                break;
            }
            case 3: {
                // ���� ������ ���������� �� �����
                if (num <= 0) {
                    printf("No data to display.\n");
                    break;
                }
                printComponents(components, num, stdout);
                break;
            }
            case 4: {
                // ����� ������ � ������� ����
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
                // ������� ������ ������ � �������� ����� �� ��������
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
                // ����� �� ������
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
                // ����� �� �����
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
