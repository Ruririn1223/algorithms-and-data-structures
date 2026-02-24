#define _CRT_SECURE_NO_WARNINGS
#include "BudgetItem.h"
#include <stdio.h>
#include <string.h>

BudgetItem budgetItem_create(const char* name, double cost,
    const char* unit, double quantity) {
    BudgetItem item;
    strncpy(item.workName, name, MAX_NAME_LEN - 1);
    item.workName[MAX_NAME_LEN - 1] = '\0';
    item.cost = cost;
    strncpy(item.unit, unit, MAX_UNIT_LEN - 1);
    item.unit[MAX_UNIT_LEN - 1] = '\0';
    item.quantity = quantity;
    return item;
}

double budgetItem_getTotalCost(const BudgetItem* item) {
    return item->cost * item->quantity;
}

void budgetItem_print(const BudgetItem* item) {
    printf("%-30s %10.2f %-8s %10.1f %12.2f\n",
        item->workName, item->cost, item->unit,
        item->quantity, budgetItem_getTotalCost(item));
}