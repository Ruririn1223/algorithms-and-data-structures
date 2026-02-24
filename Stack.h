#pragma once
#ifndef STACK_H
#define STACK_H

#include "BudgetItem.h"

typedef struct Node {
    BudgetItem data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int count;
} Stack;

 
Stack* stack_create();
void stack_destroy(Stack* s);

 
int stack_isEmpty(const Stack* s);
int stack_size(const Stack* s);
void stack_push(Stack* s, const BudgetItem* item);
BudgetItem stack_pop(Stack* s);
BudgetItem stack_peek(const Stack* s);
 

void stack_print(const Stack* s);
BudgetItem stack_findMaxByTotalCost(const Stack* s);

#endif // STACK_H
