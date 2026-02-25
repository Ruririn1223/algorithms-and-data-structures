#define _CRT_SECURE_NO_WARNINGS
#include "BudgetItem.h"
#include "Stack.h"
#include "Sorter.h"
#include "FileManager.h"
#include <stdio.h>
#include <Windows.h>

#define MAX_ITEMS 100

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    BudgetItem items[MAX_ITEMS];
    int itemCount = fileManager_readBudgetItems("budget.txt", items, MAX_ITEMS);

    if (itemCount == 0) {
        printf("Файл не найден. Используем тестовые данные.\n");
        items[0] = budgetItem_create("Штукатурка стен", 450.0, "м2", 35.5);
        items[1] = budgetItem_create("Поклейка обоев", 320.0, "м2", 42.0);
        items[2] = budgetItem_create("Укладка плитки", 890.0, "м2", 18.3);
        items[3] = budgetItem_create("Монтаж проводки", 1200.0, "точка", 15.0);
        items[4] = budgetItem_create("Сантехника", 2500.0, "шт", 8.0);
        itemCount = 5;
    }

    fileManager_printArray(items, itemCount, "Исходная смета");

 
    Stack* stack = stack_create();
    for (int i = 0; i < itemCount; i++) stack_push(stack, &items[i]);
    stack_print(stack);

    BudgetItem maxItem = stack_findMaxByTotalCost(stack);
    printf("\nМаксимальная позиция:\n");
    budgetItem_print(&maxItem);

    stack_destroy(stack);

 
    BudgetItem selSorted[MAX_ITEMS];
    memcpy(selSorted, items, itemCount * sizeof(BudgetItem));
    double selTime = sorter_measureTimeSelection(selSorted, itemCount);
    fileManager_printArray(selSorted, itemCount, "Сортировка выбором");
    printf("Время: %.6f мс\n", selTime);

    BudgetItem mergeSorted[MAX_ITEMS];
    memcpy(mergeSorted, items, itemCount * sizeof(BudgetItem));
    double mergeTime = sorter_measureTimeMerge(mergeSorted, itemCount);
    fileManager_printArray(mergeSorted, itemCount, "Сортировка слиянием");
    printf("Время: %.6f мс\n", mergeTime);

    printf("\nСравнение\n");
    printf("Выбором: %.6f мс\n", selTime);
    printf("Слиянием: %.6f мс\n", mergeTime);
    if (mergeTime > 0) printf("Ускорение: %.2fx\n", selTime / mergeTime);

    return 0;
}