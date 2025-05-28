#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "HardwareComponent.h"

#define COUNT 50

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    HardwareComponent components[COUNT];
    int num = 0;
    int choice;
    char searchName[100];
    int searchCode;
    HardwareComponent temp;

    do {
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
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                FILE *in = fopen("components.txt", "r");
                if (!in) {
                    printf("Error opening file!\n");
                    break;
                }
                num = COUNT;
                readComponents(components, num, in);
                fclose(in);
                printf("Data loaded from file.\n");
                break;
            }
            case 2:
                printf("How many records to enter (max %d): ", COUNT);
                scanf("%d", &num);
                if (num > 0 && num <= COUNT)
                    readComponentsFromKeyboard(components, num);
                else
                    printf("Invalid number.\n");
                break;
            case 3:
                printComponents(components, num, stdout);
                break;
            case 4: {
                FILE *out = fopen("components.bin", "wb");
                if (!out) {
                    printf("Error creating file.\n");
                    break;
                }
                fwrite(components, sizeof(HardwareComponent), num, out);
                fclose(out);
                printf("Data written to binary file.\n");
                break;
            }
            case 5: {
                int index;
                printf("Enter index (starting from 0): ");
                scanf("%d", &index);
                readFromBinaryFile(&temp, "components.bin", index);
                printComponent(&temp, stdout);
                break;
            }
            case 6:
                printf("Enter name to search: ");
                scanf("%s", searchName);
                int idxName = findByName(components, num, searchName);
                if (idxName != -1)
                    printComponent(&components[idxName], stdout);
                else
                    printf("Not found.\n");
                break;
            case 7:
                printf("Enter code to search: ");
                scanf("%d", &searchCode);
                int idxCode = findByCode(components, num, searchCode);
                if (idxCode != -1)
                    printComponent(&components[idxCode], stdout);
                else
                    printf("Not found.\n");
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
