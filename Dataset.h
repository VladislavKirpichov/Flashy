#pragma once
#include <vector>


class Dataset {

    //Схожесть заметок (по словам)
    double* mFilesTfidf;
    //Сложность теста (у данного пользователя)
    double* mDifficulty;
    //Общая сложность теста (по всем пользователям)
    double* mGeneralDifficulty;
    //Схожесть текста самого теста (по словам)
    double* mTestTfidf;

public:

    const std::vector<double*> getData();
};