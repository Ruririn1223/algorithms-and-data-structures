#pragma once

#ifndef BUDGET_ITEM_H
#define BUDGET_ITEM_H

#define MAX_NAME_LEN 100
#define MAX_UNIT_LEN 20

typedef struct {
    char workName[MAX_NAME_LEN];
    double cost;
    char unit[MAX_UNIT_LEN];
    double quantity;
} BudgetItem;

 
BudgetItem budgetItem_create(const char* name, double cost,
    const char* unit, double quantity);
 

double budgetItem_getTotalCost(const BudgetItem* item);

 
void budgetItem_print(const BudgetItem* item);

#endif // BUDGET_ITEM_H