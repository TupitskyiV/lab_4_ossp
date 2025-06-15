// ==== HardwareComponent.c ====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HardwareComponent.h"

// ����������, �� ����� ������ ��� ����� � 50 �������.
// ���� �������� ������� ����� � scanf �� 49 ������� (%49s), ��� �������� ������������.

// ���������� ������ ���������� � �����
void inputComponent(HardwareComponent *hc, FILE *f) {
    if (!hc || !f) return;  // �������� ��������� �� NULL

    // ������ ��������� �� ����, �������� ���������� ��������
    int res = fscanf(f, "%49s %d %49s %f %49s %d",
           hc->name, &hc->code, hc->type,
           &hc->price, hc->manufacturer, &hc->warranty);

    if (res != 6) {
        // ���� �� �� ���� ��������� � ���������� ��������� ������
        memset(hc, 0, sizeof(HardwareComponent));
    }
}

// ���������� ������ ���������� � ���������
void inputComponentFromKeyboard(HardwareComponent *hc) {
    if (!hc) return;

    char buffer[50];  // ���������� ����� ��� ���������� ���������� �����

    printf("(Type 'exit' to return to menu at any time)\n");

    // �������� ����� ����������
    printf("Name: ");
    if (scanf("%49s", buffer) != 1) return;
    if (strcmp(buffer, "exit") == 0) {
        hc->name[0] = '\0';  // ��������� ������� ������
        return;
    }
    strcpy(hc->name, buffer);

    // �������� ���� ����������
    printf("Code: ");
    if (scanf("%d", &hc->code) != 1) return;

    // �������� ���� ����������
    printf("Type: ");
    if (scanf("%49s", buffer) != 1) return;
    if (strcmp(buffer, "exit") == 0) {
        hc->name[0] = '\0';  // �����
        return;
    }
    strcpy(hc->type, buffer);

    // �������� ���� ����������
    printf("Price: ");
    if (scanf("%f", &hc->price) != 1) return;

    // �������� ���������
    printf("Manufacturer: ");
    if (scanf("%49s", buffer) != 1) return;
    if (strcmp(buffer, "exit") == 0) {
        hc->name[0] = '\0';  // �����
        return;
    }
    strcpy(hc->manufacturer, buffer);

    // �������� ����������� ������
    printf("Warranty (months): ");
    if (scanf("%d", &hc->warranty) != 1) return;

    // �������� ������ stdin �� ���������� �������
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ��������� ������ ���������� � ���� ��� �� �����
void printComponent(HardwareComponent *hc, FILE *f) {
    if (!hc || !f) return;
    fprintf(f, "%s\t%d\t%s\t%.2f\t%s\t%d\n",
            hc->name, hc->code, hc->type,
            hc->price, hc->manufacturer, hc->warranty);
}

// ���������� ������ ���������� � �����
int readComponents(HardwareComponent *arr, int n, FILE *f) {
    if (!arr || !f || n <= 0) return 0;

    int count = 0;
    for (int i = 0; i < n; i++) {
        inputComponent(&arr[i], f);

        // ���� ����� ������� � ����� ����� ��� �������
        if (arr[i].name[0] == '\0') break;

        count++;
    }
    return count; // ��������� ������� ������ �������� ������
}

// ���������� ������ ���������� � ���������
void readComponentsFromKeyboard(HardwareComponent *arr, int n) {
    if (!arr || n <= 0) return;

    for (int i = 0; i < n; i++) {
        printf("\nEntering record #%d:\n", i + 1);
        inputComponentFromKeyboard(&arr[i]);

        // ���� ���������� ��� "exit" (����� �������) � ����� � �����
        if (arr[i].name[0] == '\0') {
            printf("Returning to menu...\n");
            break;
        }
    }
}

// ��������� ������ ���������� � ���� ��� �� �����
void printComponents(HardwareComponent *arr, int n, FILE *f) {
    if (!arr || !f || n <= 0) return;

    for (int i = 0; i < n; i++) {
        printComponent(&arr[i], f);
    }
}

// ����� ���������� �� ������
int findByName(HardwareComponent *arr, int n, const char *name) {
    if (!arr || !name || n <= 0) return -1;

    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].name, name) == 0)
            return i;
    }
    return -1; // �� ��������
}

// ����� ���������� �� �����
int findByCode(HardwareComponent *arr, int n, int code) {
    if (!arr || n <= 0) return -1;

    for (int i = 0; i < n; i++) {
        if (arr[i].code == code)
            return i;
    }
    return -1; // �� ��������
}

// ������� ������ ������ �� �������� � �������� �����
void readFromBinaryFile(HardwareComponent *hc, const char *filename, int index) {
    if (!hc || !filename || index < 0) return;

    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Could not open binary file!\n");
        return;
    }

    // �������� ������ ����� ��� ������� �� ������ �� ���
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    long pos = sizeof(HardwareComponent) * index;
    if (pos >= filesize) {
        printf("Index is out of file bounds!\n");
        fclose(f);
        return;
    }

    // ���������� ������� �� ������� ������
    fseek(f, pos, SEEK_SET);

    // ������� ������ ������
    size_t read_count = fread(hc, sizeof(HardwareComponent), 1, f);
    if (read_count != 1) {
        printf("Failed to read record at index %d\n", index);
        memset(hc, 0, sizeof(HardwareComponent));
    }

    fclose(f);
}
