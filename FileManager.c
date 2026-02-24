#define _CRT_SECURE_NO_WARNINGS
#include "FileManager.h"
#include <stdio.h>
#include <string.h>

int fileManager_readBudgetItems(const char* filename, BudgetItem items[], int maxSize) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Ошибка открытия файла '%s'\n", filename);
        return 0;
    }

    char line[256];
    fgets(line, sizeof(line), file);  

    int count = 0;
    while (fgets(line, sizeof(line), file) && count < maxSize) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;

        char name[MAX_NAME_LEN], unit[MAX_UNIT_LEN];
        double cost, quantity;
        if (sscanf(line, "%[^;];%lf;%[^;];%lf", name, &cost, unit, &quantity) == 4) {
            items[count++] = budgetItem_create(name, cost, unit, quantity);
        }
    }
    fclose(file);
    return count;
}

void fileManager_printArray(const BudgetItem arr[], int n, const char* title) {
    printf("\n=== %s ===\n", title);
    printf("%-30s %10s %-8s %10s %12s\n",
        "Наименование", "Цена", "Ед.изм", "Кол-во", "Итого");
    printf("-----------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) budgetItem_print(&arr[i]);
    printf("-----------------------------------------------------------------------\n");
    printf("Всего: %d позиций\n", n);
}