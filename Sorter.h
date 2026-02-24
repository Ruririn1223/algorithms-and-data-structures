#pragma once

#ifndef SORTER_H
#define SORTER_H

#include "BudgetItem.h"

void sorter_selectionSort(BudgetItem arr[], int n);
void sorter_mergeSort(BudgetItem arr[], int n);
double sorter_measureTimeSelection(BudgetItem arr[], int n);
double sorter_measureTimeMerge(BudgetItem arr[], int n);

#endif // SORTER_H
