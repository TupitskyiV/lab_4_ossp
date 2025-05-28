// ==== HardwareComponent.h ====
#ifndef HARDWARE_COMPONENT_H
#define HARDWARE_COMPONENT_H

#include <stdio.h>

// Structure representing a computer component
typedef struct {
    char name[100];         // Component name
    int code;               // Component code
    char type[50];          // Classification (CPU, HDD, GPU, etc.)
    float price;            // Price (USD)
    char manufacturer[100]; // Manufacturer
    int warranty;           // Warranty (months)
} HardwareComponent;

// Function prototypes
void inputComponent(HardwareComponent *hc, FILE *f);
void inputComponentFromKeyboard(HardwareComponent *hc);
void printComponent(HardwareComponent *hc, FILE *f);
int readComponents(HardwareComponent *arr, int n, FILE *f);
void readComponentsFromKeyboard(HardwareComponent *arr, int n);
void printComponents(HardwareComponent *arr, int n, FILE *f);
int findByName(HardwareComponent *arr, int n, const char *name);
int findByCode(HardwareComponent *arr, int n, int code);
void readFromBinaryFile(HardwareComponent *hc, const char *filename, int index);

#endif
