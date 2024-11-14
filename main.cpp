#include <any>
#include <iostream>
#include "Account.h"
// 加了#idndef包含保护,多次定义会被忽略
#include "Account.h"

using namespace c_test;
using namespace std;


class User1 {
public:
    string name;

    int getId() {
        return 1;
    }

    string getName(string name) {
        this->name = name;
        return name;
    }

    char getFirstName() {
        return name[0];
    }

    float getWidth() {
        return 123.45f;
    }

    double getHeight() {
        return 234.5;
    }

    bool getSex() {
        return true;
    }

    virtual void exe() {
        cout << "User1 exe..." << endl;
    }

    User1() {
        cout << "User1 init..." << endl;
    }

    ~User1() {
        cout << "User1 destroy..." << endl;
    }
};

class User2 : public User1 {
public:
    void exe() override {
        cout << "User2 exe..." << endl;
    }

    User2() {
        cout << "User2 init..." << endl;
    }

    ~User2() {
        cout << "User2 destroy..." << endl;
    }
};

struct User3 {
public:
    string account, pwd;
};

union Data {
    int a;
    long b;
};

int add(int a, int b);

int mul(int a, int b);

void mulTable();

int methodPtr(int (*addPtr)(int, int), int a, int b);

string methodPtr2(string (User1::*namePtr)(string), User1 *user1, string name);

string methodPtr3(string (User1::*namePtr)(string), User1 &user1, string name);

// 局部静态变量
void requestCount() {
    // 全局只会初始化一次
    static long count = 0;
    cout << format("count:{}", ++count) << endl;
}

// 全局静态变量
static int id = 0;

// 结构体
struct UserVO {
    int id;
    string account;

    UserVO() {
        cout << format("UserVO init...") << endl;
    }

    ~UserVO() {
        cout << format("UserVO destroy...") << endl;
    }

    virtual void exe() {
        cout << "UserVO exe" << endl;
    }
};

struct User2VO : public UserVO {
    User2VO() {
        cout << format("User2VO init...") << endl;
    }

    ~User2VO() {
        cout << format("User2VO destroy...") << endl;
    }

    void exe() override {
        cout << "User2VO exe" << endl;
    }
};

int main(int argc, char *argv[]) {
    // 基础
    {
        cout << "Please input:" << endl;
        string input;
        getline(cin, input);
        User1 user1;
        cout << format("id:{},name:{},fn:{},width:{},height:{},sex:{}", user1.getId(), user1.getName(input),
                       user1.getFirstName(), user1.getWidth(), user1.getHeight(), user1.getSex()) << endl;
        user1.exe();
        cout << format("input size:{}", input.size() * sizeof(char)) << endl;

        User3 user3;
        user3.account = "admin";
        user3.pwd = "123";
        cout << format("account:{},pwd:{}", user3.account, user3.pwd) << endl;

        Data data;
        data.b = 1000;
        data.a = 10;
        cout << format("data.a==1:{},dada.size==8:{}", data.a == 10, sizeof(data) == 8) << endl;
    }

    // 运算符
    {
        cout << format("int size:{},int min:{},int max:{}", sizeof(int), numeric_limits<int>::min(),
                       numeric_limits<int>::max()) << endl;
        cout << format("short size:{},short min:{},short max:{}", sizeof(short), numeric_limits<short>::min(),
                       numeric_limits<short>::max()) << endl;
        cout << format("long size:{},long min:{},long max:{}", sizeof(long), numeric_limits<long>::min(),
                       numeric_limits<long>::max()) << endl;
        cout << format("long long size:{},long long min:{},long long max:{}", sizeof(long long),
                       numeric_limits<long long>::min(),
                       numeric_limits<long long>::max()) << endl;
        cout << format("float size:{},float min:{},float max:{}", sizeof(float), numeric_limits<float>::min(),
                       numeric_limits<float>::max()) << endl;
        cout << format("double size:{},double min:{},double max:{}", sizeof(double), numeric_limits<double>::min(),
                       numeric_limits<double>::max()) << endl;

        cout << format("1<<1:{},2>>1:{}", 1 << 1, 2 >> 1) << endl;
        cout << format("add:{},mul:{}", add(1, 2), mul(2, 3)) << endl;
        mulTable();
    }

    // 流程控制
    {
        cout << "Please input:" << endl;
        int input = 0;
        cin >> input;

        if (input <= 5) {
            cout << "input <= 5" << endl;
        } else {
            cout << "input > 5" << endl;
        }

        switch (input) {
            case 1:
                cout << "input == 1" << endl;
                break;
            case 2:
                cout << "input == 2" << endl;
                break;
            default:
                cout << format("other:{}", input) << endl;
        }

        int count = 0;
        for (; input <= 10; input++) {
            if ((input & 1) == 1) {
                count++;
            }
        }
        cout << format("count:{}", count) << endl;

        while (input <= 20) {
            if ((input++ & 1) == 0) {
                count++;
            }
        }
        cout << format("count:{}", count) << endl;

        do {
            cout << format("input:{}", input++) << endl;
        } while (input <= 30);
    }

    // lambda
    {
        int a = 10;
        int b = 20;
        auto rlt1 = [&a,b](int c) {
            a = 20;
            return a + b + c;
        };
        cout << format("a:{},b:{},rlt:{}", a, b, rlt1(10)) << endl;

        auto rlt2 = [&]() {
            a = 1;
            b = 1;
            return (a + b) << 1;
        };
        cout << format("a:{},b:{},rlt:{}", a, b, rlt2()) << endl;
    }

    // 数组
    {
        int arr1[5] = {1, 2, 3, 4, 5};
        int size = sizeof(arr1) / sizeof(int);
        int *arr2 = new int[size];
        for (int i = 0; i < size; i++) {
            arr2[i] = arr1[i] << 1;
            cout << format("arr2[{}]:{}", i, arr2[i]) << endl;
        }
        delete []arr2;

        array<int, 5> arr3 = {1, 2, 3, 4, 5};
        vector<int> arr4(5);
        for (auto a: arr3) {
            arr4.push_back(a);
        }
        cout << format("arr4.length==10:{},arr4[0]==0", arr4.size() == 10, arr4[0] == 0) << endl;
    }

    // 动态类型
    {
        int a = 10;
        void *b = &a;
        cout << format("b:{}", *(static_cast<int *>(b))) << endl;

        any c = a;
        if (c.type() == typeid(int)) {
            cout << format("c:{}", any_cast<int>(c)) << endl;
        }
    }

    // 类型转换
    {
        long a = 20;
        cout << format("long2int:{}", static_cast<int>(a)) << endl;

        User1 *u1 = new User2;
        u1->exe();
        User2 *u2 = dynamic_cast<User2 *>(u1);
        cout << "u2 address:" << u2 << endl;
        delete u2;

        // 悬垂指针
        cout << "u1 address:" << u1 << ",u1!=null:" << boolalpha << (u1 != nullptr) << endl;
        u1 = nullptr;
    }

    // 指针
    {
        // 普通指针
        {
            int a = 10;
            int *b = &a;
            *b = 1;
            cout << format("a:{},b:{}", a, *b) << endl;
        }

        // 函数指针
        {
            cout << format("add:{}", methodPtr(add, 10, 20)) << endl;
            cout << format("name:{}", methodPtr2(&User1::getName, new User1, "admin")) << endl;
            User2 user2;
            cout << format("name:{}", methodPtr3(&User1::getName, user2, "admin2")) << endl;
        }

        // 智能指针
        {
            // 唯一指针
            unique_ptr<User1> u1 = make_unique<User1>();
            // 转让所有权
            unique_ptr<User1> u2 = move(u1);
            cout << format("u1==null:{}", u1 == nullptr) << endl;

            // 共享指针
            shared_ptr<User1> u3 = make_shared<User1>();
            shared_ptr<User1> u4 = u3;
            shared_ptr<User1> u5 = u3;
            cout << format("ref count==3:{}", u3.use_count() == 3) << endl;

            // 弱指针
            shared_ptr<User1> u6 = make_shared<User1>();
            weak_ptr<User1> u7 = u6;
            weak_ptr<User1> u8 = u6;
            cout << format("ref count==1:{}", u6.use_count() == 1) << endl;
            if (auto u9 = u8.lock()) {
                cout << format("ref count==2:{}", u6.use_count() == 2) << endl;
            }
            cout << format("ref count==1:{}", u6.use_count() == 1) << endl;
        }
    }

    // 文件头&定义
    {
        Account account("admin", "123");
        cout << format("account:{},pwd:{}", account.getAccount(), account.getPwd()) << endl;
        cout << format("static value:{}", Account::id) << endl;
        // 修改类静态变量的值
        Account::id = 30;
        cout << format("static value:{}", Account::id) << endl;

        // 访问局部静态变量
        for (int i = 0; i < 10; i++) {
            requestCount();
        }

        // 访问全局静态变量
        id = 10;
        cout << format("global id:{}", id) << endl;
    }

    // 结构体
    {
        UserVO *userVO = new User2VO;
        userVO->id = 1;
        userVO->account = "admin";
        cout << format("id:{},account:{}", userVO->id, userVO->account) << endl;

        // 重写
        userVO->exe();
        delete userVO;

        User3VO user3VO;
        user3VO.id = 123;
        user3VO.name = "admin2";
        cout << format("id:{},account:{}", user3VO.id, user3VO.name) << endl;
    }
    return 0;
}

int add(int a, int b) {
    return a + b;
}

int mul(int a, int b) {
    return a * b;
}

void mulTable() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            cout << format("{}*{}={}\t", j, i, j * i);
        }
        cout << endl;
    }
}

int methodPtr(int (*addPtr)(int, int), int a, int b) {
    return addPtr(a, b);
}

string methodPtr2(string (User1::*namePtr)(string), User1 *user1, string name) {
    return (user1->*namePtr)(name);
}

string methodPtr3(string (User1::*namePtr)(string), User1 &user1, string name) {
    return (user1.*namePtr)(name);
}
