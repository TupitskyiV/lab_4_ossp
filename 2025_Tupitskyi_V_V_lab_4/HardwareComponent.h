// ==== HardwareComponent.h ====
#ifndef HARDWARE_COMPONENT_H
#define HARDWARE_COMPONENT_H

#include <stdio.h>

// Структура, що представляє комп’ютерний компонент
typedef struct {
    char name[100];         // Назва компонента
    int code;               // Код компонента
    char type[50];          // Класифікація (CPU, HDD, GPU тощо)
    float price;            // Ціна (USD)
    char manufacturer[100]; // Виробник
    int warranty;           // Гарантія (місяці)
} HardwareComponent;

// Зчитує компонент з файлу
void inputComponent(HardwareComponent *hc, FILE *f);

// Зчитує компонент з клавіатури
void inputComponentFromKeyboard(HardwareComponent *hc);

// Виводить компонент у файл або на екран
void printComponent(HardwareComponent *hc, FILE *f);

// Зчитує n компонентів з файлу у масив
int readComponents(HardwareComponent *arr, int n, FILE *f);

// Зчитує n компонентів з клавіатури у масив
void readComponentsFromKeyboard(HardwareComponent *arr, int n);

// Виводить n компонентів з масиву у файл або на екран
void printComponents(HardwareComponent *arr, int n, FILE *f);

// Пошук компонента за назвою
int findByName(HardwareComponent *arr, int n, const char *name);

// Пошук компонента за кодом
int findByCode(HardwareComponent *arr, int n, int code);

// Читає один запис з бінарного файлу за індексом
void readFromBinaryFile(HardwareComponent *hc, const char *filename, int index);

#endif
