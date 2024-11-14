//
// Created by JohnGao on 2024/11/13.
//

#include "Account.h"

#include <iostream>
using namespace std;

namespace c_test {
    int Account::id = 123;

    Account::Account(string account, string pwd) {
        this->account = account;
        this->pwd = pwd;
        cout << "Account init..." << endl;
    }

    Account::~Account() {
        cout << "Account destroy..." << endl;
    }

    string Account::getAccount() {
        return account;
    }

    string Account::getPwd() {
        return pwd;
    }
}
