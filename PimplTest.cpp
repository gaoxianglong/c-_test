//
// Created by JohnGao on 2025/1/7.
//

#include "PimplTest.h"
#include <iostream>

class PimplTestImpl {
public:
    void print() {
        std::cout << "PimplTestImpl::print()" << std::endl;
    }
};


PimplTest::PimplTest(): impl(std::make_unique<PimplTestImpl>()) {
}

PimplTest::~PimplTest() = default;

void PimplTest::print() {
    impl->print();
}
