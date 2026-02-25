#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack* stack_create() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (!s) {
        fprintf(stderr, "Ошибка выделения памяти для стека\n");
        exit(1);
    }
    s->top = NULL;
    s->count = 0;
    return s;
}

void stack_destroy(Stack* s) {
    if (!s) return;
    while (!stack_isEmpty(s)) {
        stack_pop(s);
    }
    free(s);
}

int stack_isEmpty(const Stack* s) {
    return s->top == NULL;
}

int stack_size(const Stack* s) {
    return s->count;
}

void stack_push(Stack* s, const BudgetItem* item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Ошибка выделения памяти для узла\n");
        exit(1);
    }
    newNode->data = *item;
    newNode->next = s->top;
    newNode->prev = NULL;
    if (s->top) s->top->prev = newNode;
    s->top = newNode;
    s->count++;
}

BudgetItem stack_pop(Stack* s) {
    if (stack_isEmpty(s)) {
        fprintf(stderr, "Ошибка: стек пуст!\n");
        exit(1);
    }
    Node* temp = s->top;
    BudgetItem item = temp->data;
    s->top = s->top->next;
    if (s->top) s->top->prev = NULL;
    free(temp);
    s->count--;
    return item;
}

BudgetItem stack_peek(const Stack* s) {
    if (stack_isEmpty(s)) {
        fprintf(stderr, "Ошибка: стек пуст!\n");
        exit(1);
    }
    return s->top->data;
}

void stack_print(const Stack* s) {
    if (stack_isEmpty(s)) {
        printf("Стек пуст.\n");
        return;
    }
    printf("\nСодержимое стека\n");
    printf("%-30s %10s %-8s %10s %12s\n",
        "Наименование", "Цена", "Ед.изм", "Кол-во", "Итого");
    printf("-----------------------------------------------------------------------\n");

    Node* current = s->top;
    while (current) {
        budgetItem_print(&current->data);
        current = current->next;
    }
    printf("-----------------------------------------------------------------------\n");
    printf("Всего: %d позиций\n", s->count);
}

BudgetItem stack_findMaxByTotalCost(const Stack* s) {
    if (stack_isEmpty(s)) {
        fprintf(stderr, "Ошибка: стек пуст!\n");
        exit(1);
    }
    Node* current = s->top;
    BudgetItem maxItem = current->data;
    while (current) {
        if (budgetItem_getTotalCost(&current->data) >
            budgetItem_getTotalCost(&maxItem)) {
            maxItem = current->data;
        }
        current = current->next;
    }
    return maxItem;
}