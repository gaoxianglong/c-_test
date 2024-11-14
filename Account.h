//
// Created by JohnGao on 2024/11/13.
//

// ifndef后面的标识符为自定义宏名称，也是头文件的唯一标识符
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

namespace c_test {
    // 定义在头文件中的结构体
    struct User3VO {
        int id;
        string name;
    };

    class Account {
    public:
        // 类静态变量，只能在外部定义初始化,头文件中的类静态变量，必须在源文件中定义初始化
        static int id;
        string account, pwd;

        Account(string account, string pwd);

        ~Account();

        string getAccount();

        string getPwd();
    };
}


#endif //ACCOUNT_H
