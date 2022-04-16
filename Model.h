#pragma once

#include "Dataset.h"
#include <iostream>
#include <vector>
#include <string>

class Model
{
    //Используемый датасет
    Dataset* mDataset;
public:
    Model(): mDataset(nullptr){};
    std::vector<int> showNearNeighbor();
};