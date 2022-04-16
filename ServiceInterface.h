#pragma once

class ServiceInterface {
public:
    virtual const std::vector<int> getAnswer(){};
    virtual int sendData(const std::vector<double*>&){};
};