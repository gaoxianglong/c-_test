//
// Created by JohnGao on 2025/1/7.
//

#ifndef PIMPLTEST_H
#define PIMPLTEST_H
#include <memory>

// 向前声明
class PimplTestImpl;

class PimplTest {
public:
    PimplTest();

    ~PimplTest();

    void print();

private:
    std::unique_ptr<PimplTestImpl> impl;
};


#endif //PIMPLTEST_H
