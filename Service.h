#pragma once
#include "Model.h"
#include "Preprocessor.h"
#include "ServiceInterface.h"

class Service: public ServiceInterface {
    //Для предобработки данных
    Preprocessor* mPreprocessor;
    //Сама модель
    Model* mModel;
public:
    const std::vector<int> getAnswer();
    Service(): mPreprocessor(nullptr), mModel(nullptr){};
    int sendData(std::vector<double*>);
};