// ==== HardwareComponent.c ====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HardwareComponent.h"

// Припускаємо, що розмір масивів для рядків — 50 символів.
// Тому обмежуємо довжину рядка у scanf до 49 символів (%49s), щоб уникнути переповнення.

// Зчитування одного компонента з файлу
void inputComponent(HardwareComponent *hc, FILE *f) {
    if (!hc || !f) return;  // Перевірка вказівників на NULL

    // Спроба прочитати всі поля, перевірка коректності введення
    int res = fscanf(f, "%49s %d %49s %f %49s %d",
           hc->name, &hc->code, hc->type,
           &hc->price, hc->manufacturer, &hc->warranty);

    if (res != 6) {
        // Якщо не всі поля прочитано — ініціалізуємо структуру нулями
        memset(hc, 0, sizeof(HardwareComponent));
    }
}

// Зчитування одного компонента з клавіатури
void inputComponentFromKeyboard(HardwareComponent *hc) {
    if (!hc) return;

    char buffer[50];  // Тимчасовий буфер для безпечного зчитування рядків

    printf("(Type 'exit' to return to menu at any time)\n");

    // Введення назви компонента
    printf("Name: ");
    if (scanf("%49s", buffer) != 1) return;
    if (strcmp(buffer, "exit") == 0) {
        hc->name[0] = '\0';  // Позначаємо команду виходу
        return;
    }
    strcpy(hc->name, buffer);

    // Введення коду компонента
    printf("Code: ");
    if (scanf("%d", &hc->code) != 1) return;

    // Введення типу компонента
    printf("Type: ");
    if (scanf("%49s", buffer) != 1) return;
    if (strcmp(buffer, "exit") == 0) {
        hc->name[0] = '\0';  // Вихід
        return;
    }
    strcpy(hc->type, buffer);

    // Введення ціни компонента
    printf("Price: ");
    if (scanf("%f", &hc->price) != 1) return;

    // Введення виробника
    printf("Manufacturer: ");
    if (scanf("%49s", buffer) != 1) return;
    if (strcmp(buffer, "exit") == 0) {
        hc->name[0] = '\0';  // Вихід
        return;
    }
    strcpy(hc->manufacturer, buffer);

    // Введення гарантійного терміну
    printf("Warranty (months): ");
    if (scanf("%d", &hc->warranty) != 1) return;

    // Очищення буфера stdin від залишкових символів
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Виведення одного компонента у файл або на екран
void printComponent(HardwareComponent *hc, FILE *f) {
    if (!hc || !f) return;
    fprintf(f, "%s\t%d\t%s\t%.2f\t%s\t%d\n",
            hc->name, hc->code, hc->type,
            hc->price, hc->manufacturer, hc->warranty);
}

// Зчитування кількох компонентів з файлу
int readComponents(HardwareComponent *arr, int n, FILE *f) {
    if (!arr || !f || n <= 0) return 0;

    int count = 0;
    for (int i = 0; i < n; i++) {
        inputComponent(&arr[i], f);

        // Якщо назва порожня — кінець файлу або помилка
        if (arr[i].name[0] == '\0') break;

        count++;
    }
    return count; // Повертаємо кількість успішно зчитаних записів
}

// Зчитування кількох компонентів з клавіатури
void readComponentsFromKeyboard(HardwareComponent *arr, int n) {
    if (!arr || n <= 0) return;

    for (int i = 0; i < n; i++) {
        printf("\nEntering record #%d:\n", i + 1);
        inputComponentFromKeyboard(&arr[i]);

        // Якщо користувач ввів "exit" (назва порожня) — вихід з циклу
        if (arr[i].name[0] == '\0') {
            printf("Returning to menu...\n");
            break;
        }
    }
}

// Виведення кількох компонентів у файл або на екран
void printComponents(HardwareComponent *arr, int n, FILE *f) {
    if (!arr || !f || n <= 0) return;

    for (int i = 0; i < n; i++) {
        printComponent(&arr[i], f);
    }
}

// Пошук компонента за назвою
int findByName(HardwareComponent *arr, int n, const char *name) {
    if (!arr || !name || n <= 0) return -1;

    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].name, name) == 0)
            return i;
    }
    return -1; // Не знайдено
}

// Пошук компонента за кодом
int findByCode(HardwareComponent *arr, int n, int code) {
    if (!arr || n <= 0) return -1;

    for (int i = 0; i < n; i++) {
        if (arr[i].code == code)
            return i;
    }
    return -1; // Не знайдено
}

// Читання одного запису за індексом з бінарного файлу
void readFromBinaryFile(HardwareComponent *hc, const char *filename, int index) {
    if (!hc || !filename || index < 0) return;

    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Could not open binary file!\n");
        return;
    }

    // Перевірка розміру файлу для захисту від виходу за межі
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    long pos = sizeof(HardwareComponent) * index;
    if (pos >= filesize) {
        printf("Index is out of file bounds!\n");
        fclose(f);
        return;
    }

    // Переміщення курсора на позицію запису
    fseek(f, pos, SEEK_SET);

    // Читання одного запису
    size_t read_count = fread(hc, sizeof(HardwareComponent), 1, f);
    if (read_count != 1) {
        printf("Failed to read record at index %d\n", index);
        memset(hc, 0, sizeof(HardwareComponent));
    }

    fclose(f);
}
