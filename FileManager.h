#pragma once

#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "BudgetItem.h"

int fileManager_readBudgetItems(const char* filename, BudgetItem items[], int maxSize);
void fileManager_printArray(const BudgetItem arr[], int n, const char* title);

#endif // FILE_MANAGER_H
