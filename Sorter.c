#define _CRT_SECURE_NO_WARNINGS
#include "Sorter.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

void sorter_selectionSort(BudgetItem arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (budgetItem_getTotalCost(&arr[j]) <
                budgetItem_getTotalCost(&arr[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            BudgetItem temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

static void merge(BudgetItem arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    BudgetItem* L = malloc(n1 * sizeof(BudgetItem));
    BudgetItem* R = malloc(n2 * sizeof(BudgetItem));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (budgetItem_getTotalCost(&L[i]) <= budgetItem_getTotalCost(&R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L); free(R);
}

static void mergeSortRecursive(BudgetItem arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(arr, left, mid);
        mergeSortRecursive(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void sorter_mergeSort(BudgetItem arr[], int n) {
    if (n > 0) mergeSortRecursive(arr, 0, n - 1);
}

#define MEASURE_ITERATIONS 10000

double sorter_measureTimeSelection(BudgetItem arr[], int n) {
    if (n <= 0) return 0.0;

    BudgetItem* template = (BudgetItem*)malloc(n * sizeof(BudgetItem));
    BudgetItem* workArray = (BudgetItem*)malloc(n * sizeof(BudgetItem));
    memcpy(template, arr, n * sizeof(BudgetItem));

    clock_t start = clock();
    for (int i = 0; i < MEASURE_ITERATIONS; i++) {
        memcpy(workArray, template, n * sizeof(BudgetItem));
        sorter_selectionSort(workArray, n);
    }
    clock_t end = clock();

    double totalTimeMs = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    double avgTimeMs = totalTimeMs / MEASURE_ITERATIONS;

    free(template);
    free(workArray);
    return avgTimeMs;
}

double sorter_measureTimeMerge(BudgetItem arr[], int n) {
    if (n <= 0) return 0.0;

    BudgetItem* template = (BudgetItem*)malloc(n * sizeof(BudgetItem));
    BudgetItem* workArray = (BudgetItem*)malloc(n * sizeof(BudgetItem));
    memcpy(template, arr, n * sizeof(BudgetItem));

    clock_t start = clock();
    for (int i = 0; i < MEASURE_ITERATIONS; i++) {
        memcpy(workArray, template, n * sizeof(BudgetItem));
        sorter_mergeSort(workArray, n);
    }
    clock_t end = clock();

    double totalTimeMs = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    double avgTimeMs = totalTimeMs / MEASURE_ITERATIONS;

    free(template);
    free(workArray);
    return avgTimeMs;
}