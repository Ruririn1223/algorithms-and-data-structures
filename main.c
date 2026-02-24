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
        fprintf(stderr, "\n!!! КРИТИЧЕСКАЯ ОШИБКА !!!\n");
        fprintf(stderr, "Не удалось прочитать данные из файла 'budget.txt'\n");
        fprintf(stderr, "Возможные причины:\n");
        fprintf(stderr, "  1. Файл 'budget.txt' отсутствует в папке с программой\n");
        fprintf(stderr, "  2. Файл пустой или содержит только заголовок\n");
        fprintf(stderr, "  3. Некорректный формат данных (должно быть: Наименование;Цена;Ед.изм;Количество)\n");
        fprintf(stderr, "  4. Неправильные разделители (должна быть точка с запятой ';')\n\n");
        fprintf(stderr, "Пример корректной строки файла:\n");
        fprintf(stderr, "Штукатурка стен;450.00;м2;35.5\n");
        return 1;
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

    printf("\n=== Сравнение ===\n");
    printf("Выбором: %.6f мс\n", selTime);
    printf("Слиянием: %.6f мс\n", mergeTime);
    if (mergeTime > 0) printf("Ускорение: %.2fx\n", selTime / mergeTime);

    return 0;
}