// ==== HardwareComponent.h ====
#ifndef HARDWARE_COMPONENT_H
#define HARDWARE_COMPONENT_H

#include <stdio.h>

// ���������, �� ����������� ����������� ���������
typedef struct {
    char name[100];         // ����� ����������
    int code;               // ��� ����������
    char type[50];          // ������������ (CPU, HDD, GPU ����)
    float price;            // ֳ�� (USD)
    char manufacturer[100]; // ��������
    int warranty;           // ������� (�����)
} HardwareComponent;

// ����� ��������� � �����
void inputComponent(HardwareComponent *hc, FILE *f);

// ����� ��������� � ���������
void inputComponentFromKeyboard(HardwareComponent *hc);

// �������� ��������� � ���� ��� �� �����
void printComponent(HardwareComponent *hc, FILE *f);

// ����� n ���������� � ����� � �����
int readComponents(HardwareComponent *arr, int n, FILE *f);

// ����� n ���������� � ��������� � �����
void readComponentsFromKeyboard(HardwareComponent *arr, int n);

// �������� n ���������� � ������ � ���� ��� �� �����
void printComponents(HardwareComponent *arr, int n, FILE *f);

// ����� ���������� �� ������
int findByName(HardwareComponent *arr, int n, const char *name);

// ����� ���������� �� �����
int findByCode(HardwareComponent *arr, int n, int code);

// ���� ���� ����� � �������� ����� �� ��������
void readFromBinaryFile(HardwareComponent *hc, const char *filename, int index);

#endif
