#include <any>
#include <iostream>
using namespace std;

class User2;

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

    virtual string getAccount() {
        return "account-1";
    }

    User1() {
        cout << "==== init-user1 ====" << endl;
    }

    ~User1() {
        cout << "==== destroy-user1 ====" << endl;
    }
};

class User2 : public User1 {
public:
    string getAccount() override {
        return "account-2";
    }

    User2() {
        cout << "==== init-user2 ====" << endl;
    }

    ~User2() {
        cout << "==== destroy-user2 ====" << endl;
    }
};

// 函数原型
int add(int a, int b);

int mul(int a, int b);

void mulTable();

// 函数指针
string methodPtr1(string (User1::*namPtr)(string), User1 *user1, string name);

int methodPtr2(int (*addPtr)(int, int), int a, int b);

int main(int argc, char *argv[]) { {
        cout << "Please input:" << endl;
        string name;
        getline(cin, name);
        User1 *u1 = new User2;
        cout << format("id:{},name:{},fn:{},width:{},height:{},sex:{}", u1->getId(), u1->getName(name),
                       u1->getFirstName(), u1->getWidth(), u1->getHeight(), u1->getSex()) << endl;
    }

    // sizeof、运算符、类型转换
    {
        cout << format("add:{},mul:{}", add(1, 2), mul(2, 3)) << endl;
        mulTable();
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

        long a = 10;
        int b = 20;
        b = static_cast<int>(a);

        // 强制类型转换
        User1 *u1 = new User2;
        User2 *u2 = dynamic_cast<User2 *>(u1);
        cout << format("account:{}", u2->getAccount()) << endl;
        delete u2;
        u1 = nullptr;
    }

    // 流程控制
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
                cout << "1" << endl;
                break;
            case 2:
                cout << "2" << endl;
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
            cout << format("do-while:{}", input++) << endl;
        } while (input < 30);
    }

    // lambda
    {
        int a = 10;
        int b = 20;
        auto rlt1 = [&a,b](int c) {
            return a + b + c;
        };
        cout << format("a:{},b:{},rlt1:{}", a, b, rlt1(10)) << endl;

        auto rlt2 = [&]() {
            a = 1;
            b = 1;
            return (a * b) << 1;
        };
        cout << format("a:{},b:{},rlt2:{}", a, b, rlt2()) << endl;
    }

    // 数组
    {
        int arr1[5] = {1, 2, 3, 4, 5};
        int size = sizeof(arr1) / sizeof(arr1[0]);
        int *arr2 = new int[5];
        for (int i = 0; i < size; i++) {
            arr2[i] = arr1[i] << 1;
            cout << format("arr2[{}]:{}", i, arr2[i]) << endl;
        }
        delete[] arr2;

        array<int, 5> arr3 = {1, 2, 3, 4, 5};
        vector<int> arr4(5);
        for (auto a: arr3) {
            arr4.push_back(a);
        }
        cout << format("arr4 size==10:{},arr4[0]==0:{}", arr4.size() == 10, arr4[0] == 0) << endl;
    }

    // 动态类型
    {
        void *a = new int(10);
        int *b = static_cast<int *>(a);
        cout << format("b:{}", *b) << endl;
        delete b;

        int *c = new int(10);
        any d = c;
        if (d.type() == typeid(int *)) {
            cout << format("c:{}", *(any_cast<int *>(d))) << endl;
        }
    }
    // 指针
    {
        // 普通指针
        int a = 10;
        int *b = &a;
        a = 20;
        cout << format("a:{},b:{},a==b:{}", a, *b, &a == b) << endl;

        // 函数指针
        User1 *u1 = new User1;
        cout << format("methodPtr1:{}", methodPtr1(&User1::getName, u1, "admin")) << endl;

        cout << format("methodPtr2:{}", methodPtr2(add, 10, 20)) << endl;
        delete u1;

        // 唯一指针
        {
            unique_ptr<User1> u1 = make_unique<User1>();
            // 转让所有权
            unique_ptr<User1> u2 = move(u1);
            cout << format("u1==null:{}", (u1 == nullptr)) << endl;
            cout << "&u2:" << &u2 << endl;
        }

        // 共享指针
        {
            shared_ptr<User1> u1 = make_shared<User1>();
            shared_ptr<User1> u2 = u1;
            shared_ptr<User1> u3 = u2;
            cout << format("ref count:{}", u1.use_count()) << endl;
        }

        // 弱指针
        {
            shared_ptr<User1> u1 = make_shared<User1>();
            weak_ptr<User1> w1 = u1;
            weak_ptr<User1> w2 = u1;
            cout << format("ref count==1:{}", u1.use_count() == 1) << endl;

            if (auto u2 = w2.lock()) {
                cout << format("ref count==2:{}", u1.use_count() == 2) << endl;
                cout << format("name:{},fn:{}", u2->getName("admin"), u2->getFirstName()) << endl;
            } else {
                cout << "u2 is null" << endl;
            }

            cout << format("ref count==1:{}", u1.use_count() == 1) << endl;
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

void mulTable() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            cout << format("{}*{}={}\t", j, i, j * i);
        }
        cout << endl;
    }
}

string methodPtr1(string (User1::*namPtr)(string), User1 *user1, string name) {
    return (user1->getName)(name);
}


int methodPtr2(int (*addPtr)(int, int), int a, int b) {
    return addPtr(a, b);
}
