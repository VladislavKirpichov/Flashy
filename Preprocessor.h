#pragma once

#include "Dataset.h"
#include "Stemmer.h"

//Предобработка данных
class Preprocessor {
    Stemmer mStemmer;
    Dataset* mDataset;

    int calculateTextFeatures();
    int stemming();
    int calculateDifficulty();

public:
    Preprocessor(): mStemmer(Stemmer()), mDataset(nullptr){};
    int calculateAll();
};
