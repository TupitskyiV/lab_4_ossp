// ==== HardwareComponent.c ====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HardwareComponent.h"

// Read a component from a file
void inputComponent(HardwareComponent *hc, FILE *f) {
    fscanf(f, "%s %d %s %f %s %d",
           hc->name, &hc->code, hc->type,
           &hc->price, hc->manufacturer, &hc->warranty);
}

// Input a component from the keyboard
void inputComponentFromKeyboard(HardwareComponent *hc) {
    printf("(Type 'exit' to return to menu at any time)\n");
    printf("Name: ");
    if (scanf("%s", hc->name) && strcmp(hc->name, "exit") == 0) return;
    printf("Code: ");
    if (scanf("%d", &hc->code) != 1) return;
    printf("Type: ");
    if (scanf("%s", hc->type) && strcmp(hc->type, "exit") == 0) return;
    printf("Price: ");
    if (scanf("%f", &hc->price) != 1) return;
    printf("Manufacturer: ");
    if (scanf("%s", hc->manufacturer) && strcmp(hc->manufacturer, "exit") == 0) return;
    printf("Warranty (months): ");
    if (scanf("%d", &hc->warranty) != 1) return;
}

// Print a component to a file or screen
void printComponent(HardwareComponent *hc, FILE *f) {
    fprintf(f, "%s\t%d\t%s\t%.2f\t%s\t%d\n",
            hc->name, hc->code, hc->type,
            hc->price, hc->manufacturer, hc->warranty);
}

// Read multiple components from a file
int readComponents(HardwareComponent *arr, int n, FILE *f) {
    for (int i = 0; i < n; i++) {
        inputComponent(&arr[i], f);
    }
    return 1;
}

// Read multiple components from keyboard
void readComponentsFromKeyboard(HardwareComponent *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEntering record #%d:\n", i + 1);
        inputComponentFromKeyboard(&arr[i]);
        if (strcmp(arr[i].name, "exit") == 0) {
            printf("Returning to menu...\n");
            break;
        }
    }
}

// Print multiple components to file or screen
void printComponents(HardwareComponent *arr, int n, FILE *f) {
    for (int i = 0; i < n; i++) {
        printComponent(&arr[i], f);
    }
}

// Search by name
int findByName(HardwareComponent *arr, int n, const char *name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].name, name) == 0)
            return i;
    }
    return -1;
}

// Search by code
int findByCode(HardwareComponent *arr, int n, int code) {
    for (int i = 0; i < n; i++) {
        if (arr[i].code == code)
            return i;
    }
    return -1;
}

// Read one record by index from binary file
void readFromBinaryFile(HardwareComponent *hc, const char *filename, int index) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Could not open binary file!\n");
        return;
    }
    fseek(f, sizeof(HardwareComponent) * index, SEEK_SET);
    fread(hc, sizeof(HardwareComponent), 1, f);
    fclose(f);
}
