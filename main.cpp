#include <any>
#include <iostream>

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
        return 123.4f;
    }

    double getHeight() {
        return 234.5;
    }

    bool getSex() {
        return true;
    }

    virtual short getAge() {
        return 32;
    }

    User1() {
        cout << "==== init User1 ====" << endl;
    }

    ~User1() {
        cout << "==== destroy User1 ====" << endl;
    }
};

class User2 : public User1 {
public:
    User2() {
        cout << "==== init User2 ====" << endl;
    }

    ~User2() {
        cout << "==== destroy User2 ====" << endl;
    }

    short getAge() override {
        return 33;
    }
};

struct User3 {
    string account, pwd;
};

union Data {
    int a;
    double b;
};

int add(int a, int b);

int mul(int a, int b);

int mulTable();

// 函数指针
int methodPtr1(int (addPtr1)(int, int), int a, int b);

string methodPtr2(string (User1::*namePtr)(string), User1 *user1, string name);

string methodPtr3(string (User1::*namePtr)(string), User1 &user1, string name);

int main(int argc, char *argv[]) { {
        cout << "Please input:" << endl;
        string name;
        getline(cin, name);
        User1 user1;
        User3 user3;
        user3.account = "admin";
        user3.pwd = "123";
        cout << format("id:{},name:{},fn:{},width:{},height:{},sex:{},age:{},account:{},pwd:{}", user1.getId(),
                       user1.getName(name),
                       user1.getFirstName(),
                       user1.getWidth(), user1.getHeight(), user1.getSex(), user1.getAge(), user3.account,
                       user3.pwd) << endl;
        Data data;
        data.a = numeric_limits<int>::min();
        data.b = numeric_limits<long>::max();
        cout << format("size:{}", sizeof(data)) << endl;
    }
    // 运算符、类型转换
    {
        cout << format("add:{},mul:{}", add(1, 2), mul(2, 3)) << endl;
        mulTable();
        cout << format("int size:{},int min:{},int max:{}", sizeof(int), numeric_limits<int>::min(),
                       numeric_limits<int>::max()) << endl;
        cout << format("short size:{},short min:{},short max:{}", sizeof(short), numeric_limits<short>::min(),
                       numeric_limits<short>::max()) << endl;
        cout << format("long size:{},long min:{},long max:{}", sizeof(long), numeric_limits<long>::min(),
                       numeric_limits<long>::max()) << endl;
        cout << format("long long size:{},int min:{},int max:{}", sizeof(long long), numeric_limits<long long>::min(),
                       numeric_limits<long long>::max()) << endl;
        cout << format("float size:{},float min:{},float max:{}", sizeof(float), numeric_limits<float>::min(),
                       numeric_limits<float>::max()) << endl;
        cout << format("double size:{},double min:{},double max:{}", sizeof(double), numeric_limits<double>::min(),
                       numeric_limits<double>::max()) << endl;
        cout << format("1<<1:{},2>>1:{}", 1 << 1, 2 >> 1) << endl;

        int a = 10;
        long b = 100;
        cout << format("long2int:{}", (static_cast<int>(b))) << endl;
        User1 *user2 = new User2;
        User2 *u2 = dynamic_cast<User2 *>(user2);
        cout << format("age:{}", u2->getAge()) << endl;
        delete u2;
    }
    // 流程控制语句
    {
        cout << "Please input:" << endl;
        int input;
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
        for (int i = input; i < 10; i++) {
            if ((i & 1) == 0) {
                count++;
            }
        }
        cout << format("count:{}", count) << endl;

        while (input < 20) {
            if ((input++ & 1) == 1) {
                count++;
            }
        }
        cout << format("count:{}", count) << endl;

        do {
            cout << format("input:{}", input++) << endl;
        } while (input < 30);
    }
    // lambda
    {
        int a = 10;
        int b = 20;
        auto rlt = [&a,b](int c) {
            a = 20;
            return a + b + c;
        };
        cout << format("a:{},b:{},rlt:{}", a, b, rlt(10)) << endl;

        auto rlt2 = [&]() {
            a = 1;
            b = 1;
            return (a + b) << 1;
        };
        cout << format("a:{},b:{},rlt2:{}", a, b, rlt2()) << endl;
    }
    // 数组
    {
        int arr1[5] = {1, 2, 3, 4, 5};
        int size = sizeof(arr1) / sizeof(arr1[0]);
        int *arr2 = new int[5];
        for (int i = 0; i < size; i++) {
            arr2[i] = arr1[i];
            cout << format("add2[{}]:{}", i, arr2[i]) << endl;
        }

        array<int, 5> arr3 = {1, 2, 3, 4, 5};
        vector<int> arr4(5);
        for (int i = 0; i < arr3.size(); i++) {
            arr4.push_back(arr3[i]);
        }
        cout << format("arr4 size==10:{},arr4[0]==0:{}", arr4.size() == 10, arr4[0] == 0) << endl;
    }
    // 动态类型
    {
        int a = 10;
        void *b = &a;
        b = new int(20);
        cout << format("void2int:{}", *(static_cast<int *>(b))) << endl;

        any c = a;
        if (c.type() == typeid(int)) {
            cout << format("any2int:{}", any_cast<int>(c)) << endl;
        }
    }
    // 指针
    {
        // 普通指针
        {
            int a = 10;
            int *b = &a;
            *b = 30;
            cout << format("a:{},b:{},a==b:{}", a, *b, &a == b) << endl;
        }
        // 函数指针
        {
            cout << format("methodPtr1:{}", methodPtr1(add, 1, 2)) << endl;
            cout << format("methodPtr2:{}", methodPtr2(&User1::getName, new User1, "admin1")) << endl;
            User1 user1;
            cout << format("methodPtr3:{}", methodPtr3(&User1::getName, user1, "admin2")) << endl;
        }
        // 唯一指针
        {
            unique_ptr<User1> user1 = make_unique<User1>();
            // 转让所有权
            unique_ptr<User1> user1_ = move(user1);
            cout << format("user1==null:{}", user1 == nullptr) << endl;
        }
        // 共享指针
        {
            shared_ptr<User1> user1 = make_shared<User1>();
            shared_ptr<User1> user2 = user1;
            shared_ptr<User1> user3 = user1;
            cout << format("ref size:{}", user3.use_count()) << endl;
        }
        // 若指针
        {
            shared_ptr<User1> user1 = make_shared<User1>();
            weak_ptr<User1> w1 = user1;
            weak_ptr<User1> w2 = user1;
            cout << format("ref size==1:{}", user1.use_count() == 1) << endl;
            if (auto u2 = w2.lock()) {
                cout << format("ref size==2:{}", user1.use_count() == 2) << endl;
            }
            cout << format("ref size==1:{}", user1.use_count() == 1) << endl;
        }
    }

    return 0;
}

int add(int a, int b) {
    return a + b;
}

int mul(int a, int b) {
    return a * b;
}

int mulTable() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            cout << format("{}*{}={}\t", j, i, j * i);
        }
        cout << endl;
    }
}

int methodPtr1(int (*addPtr1)(int, int), int a, int b) {
    return addPtr1(a, b);
}

string methodPtr2(string (User1::*namePtr)(string), User1 *user1, string name) {
    return (user1->*namePtr)(name);
}

string methodPtr3(string (User1::*namePtr)(string), User1 &user1, string name) {
    return (user1.*namePtr)(name);
}
