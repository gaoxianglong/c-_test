#include <any>
#include <iostream>
#include "Account.h"
#include <format>
#include <memory>
#include <vector>

// 加了#idndef包含保护,多次定义会被忽略
#include "Account.h"

using namespace c_test;
using namespace std;

/**
 * 使用ADL访问
 */
namespace adl::test {
    /**
     * 贫血模型
     */
    struct UserVO {
        int id;
        string name;

        UserVO(int id, string name): id(id), name(name) {
        }
    };

    void exe(UserVO userVO) {
        cout << format("id:{},name:{}", userVO.id, userVO.name) << endl;
    }
}

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

class User4 : public User1 {
public:
    User4() {
        cout << "User4 init..." << endl;
    }

    ~User4() {
        cout << "User4 destroy..." << endl;
    }

    void exe() override {
        cout << "User4 exe..." << endl;
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

auto age = 20;

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

/**
 * 函数重载
 * @param num
 * @return
 */
string getNumber(string num) {
    return num;
}

string getNumber(string num1, string num2) {
    return num1 + num2;
}

string getNumber() {
    return "123";
}

struct MyData {
    int id;
    string name;

    MyData(int id, string name): id(id), name(name) {
    }

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }
};

/**
 * 重载<<运算符
 * @param cout
 * @param user1 
 * @return 
 */
std::ostream &operator<<(std::ostream &cout, const MyData &data) {
    cout << format("id:{},name:{}", data.getId(), data.getName());
    return cout;
}

int main(int argc, char *argv[]) {
    // 查看C++的版本
    std::cout << __cplusplus << std::endl;

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

        // 数组的多种写法
        {
            // 数组的第1种写法
            {
                User1 u1, u2;
                User1 arr[2] = {u1, u2};
            }
            // 数组的第2种写法
            {
                User1 u1, u2;
                User1 arr[] = {u1, u2};
            }
            // 数组的第3种写法
            {
                User1 u1, u2;
                // 静态指针数组
                User1 *arr[2] = {&u1, &u2};
            }
            // 数组的第4种写法
            {
                // 数组元素是指针
                User1 *arr[2] = {new User1, new User2};
                delete arr[0];
                delete arr[1];
            }
            // 动态数组
            // 数组的第5种写法
            {
                User2 u2;
                // 数组元素是对象
                // 非指针数组会导致丧失多态特性
                User1 *arr = new User1[2]{u2, User4()};
                cout << "<<<" << endl;
                arr[0].exe();
                arr[1].exe();
                delete[] arr;
            }
            // 数组的第6种写法(指针数组)
            {
                // 动态指针数组
                User1 **arr3 = new User1 *[]{new User1, new User2};
                // arr3[0] = new User2;
                // arr3[1] = new User4;
                // 单独释放指针元素
                delete arr3[0];
                delete arr3[1];
                delete[] arr3;
            }
        }
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
            unique_ptr<User1> u2 = std::move(u1);
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

    // oop
    {
        User1 *u4[2] = {new User2, new User4};
        for (auto a: u4) {
            a->exe();
            delete a;
        }
    }
    // 035法则
    {
        class User2 {
        public:
            User2() {
                cout << "User2 init..." << endl;
            }

            ~User2() {
                cout << "User2 destroy...";
                cout << this << endl;
            }
        };

        class User1 {
        public:
            int *id;
            string **accounts;
            int size;
            User2 *u2;

            User1(int id, int size): id(new int(id)), accounts(new string *[size]), size(size), u2(new User2) {
                for (int i = 0; i < size; i++) {
                    accounts[i] = new string(format("admin-{}", i));
                }
                cout << "User1 init..." << endl;
            }

            /**
             * 拷贝构造函数
             */
            User1(const User1 &source): id(new int(*source.id)), accounts(new string *[source.size]), size(source.size),
                                        u2(new User2(*source.u2)) {
                for (int i = 0; i < source.size; i++) {
                    if (source.accounts[i] == nullptr) {
                        continue;
                    }
                    accounts[i] = new string(*source.accounts[i]);
                }
            }

            /**
             * 拷贝赋值运算符
             */
            User1 & operator=(const User1 &source) {
                if (&source != this) {
                    delete id;
                    for (int i = 0; i < size; i++) {
                        delete accounts[i];
                    }
                    delete[] accounts;
                    cout << "---" << endl;
                    delete u2;

                    id = new int(*source.id);
                    accounts = new string *[source.size];
                    for (int i = 0; i < source.size; i++) {
                        accounts[i] = new string(*source.accounts[i]);
                    }
                    size = source.size;
                    u2 = new User2(*source.u2);
                    cout << "User1 copy..." << endl;
                }
                return *this;
            }

            /**
             * 移动构造函数
             */
            User1(User1 &&source) noexcept : id(source.id), accounts(source.accounts), size(source.size),
                                             u2(source.u2) {
                source.id = nullptr;
                source.accounts = nullptr;
                source.size = 0;
                source.u2 = nullptr;
                cout << "User1 move..." << endl;
            }

            /**
             * 移动赋值运算符
             */
            User1 & operator =(User1 &&source) noexcept {
                if (this != &source) {
                    delete id;
                    for (int i = 0; i < size; i++) {
                        delete accounts[i];
                    }
                    delete[] accounts;
                    delete u2;

                    id = source.id;
                    accounts = source.accounts;
                    size = source.size;
                    u2 = source.u2;
                    source.id = nullptr;
                    source.accounts = nullptr;
                    source.size = 0;
                    source.u2 = nullptr;
                    cout << "User1 move..." << endl;
                }
                return *this;
            }

            /**
             * 析构函数
             */
            ~User1() {
                delete id;
                for (int i = 0; i < size; i++) {
                    delete accounts[i];
                }
                delete[] accounts;
                delete u2;
                cout << "User1 destroy..." << endl;
            }
        };
        //
        {
            cout << "<<<" << endl;
            User1 u1(1, 2);
            User1 u2 = u1;
        }
        //
        {
            cout << "<<<" << endl;
            User1 u1(1, 2);
            User1 u2(2, 2);
            u1 = u2;
            cout << format("u1.id=2:{},u1.&id:{:p},u2.&id:{}", *u1.id == 2, static_cast<void *>(u1.id),
                           static_cast<void *>(u2.id)) << endl;
        }
        //
        {
            cout << "<<<" << endl;
            User1 u1(1, 2);
            User1 u2 = std::move(u1);
            cout << format("u1.id==null:{},u1,account==null:{}", (u1.id == nullptr), (u1.accounts == nullptr)) << endl;
        }
        //
        {
            cout << "<<<" << endl;
            User1 u1(1, 2);
            User1 u2(2, 2);
            u2 = std::move(u1);
            cout << format("u1.id==null:{},u1,account==null:{}", (u1.id == nullptr), (u1.accounts == nullptr)) << endl;
        }
    }

    // 函数重载
    {
        cout << format("number:{}", getNumber()) << endl;
        cout << format("number:{}", getNumber("123456")) << endl;
        cout << format("number:{}", getNumber("222", "333")) << endl;
    }

    // 多重继承
    {
        class User1 {
        public:
            string getName() {
                return "user1";
            }
        };
        class User2 {
        public:
            string getName() {
                return "user2";
            }
        };
        class User3 : public User2, public User1 {
        public:
            string getName() {
                return User1::getName() + "-" + User2::getName();
            }
        };

        cout << "<<<" << endl;
        User3 user3;
        cout << format("name:{}", user3.getName()) << endl;
    }
    // 虚拟继承
    {
        class UserA {
        public:
            string getName() {
                return "admin";
            }
        };

        class UserB : virtual public UserA {
        };
        class UserC : virtual public UserA {
        };
        class UserD : public UserC, public UserB {
        };

        UserD userD;
        cout << format("name:{}", userD.getName()) << endl;
    }
    // 异常处理
    {
        class MyException1 : public std::exception {
            string msg;

        public:
            MyException1(const string &msg) : msg(msg) {
            }

            MyException1(const string &msg, const std::exception &e) {
                this->msg = format("{}:{}", msg, e.what());
            }

            /**
             * 继承std::exception需要重写what函数
             */
            const char *what() const noexcept override {
                return msg.c_str();
            }
        };
        class MyException2 : public std::logic_error {
        public:
            MyException2(const string &msg) : logic_error(msg) {
            }

            MyException2(const string &msg, const std::exception &e): logic_error(format("{}:{}", msg, e.what())) {
            }
        };

        //
        {
            try {
                //throw 1;
                //throw MyException1("MyException1");
                throw MyException2("MyException2", MyException1("MyException1"));
                //throw "other exception";
            } catch (const int &e) {
                cout << format("int exception:{}", e) << endl;
            }
            catch (const MyException1 &e) {
                cout << format("MyException1:{}", e.what()) << endl;
            } catch (const MyException2 &e) {
                cout << format("MyException2:{}", e.what()) << endl;
            }
            catch (const std::logic_error &e) {
                cout << format("logic_error:{}", e.what()) << endl;
            }
            catch (const std::exception &e) {
                cout << format("std::exception:{}", e.what()) << endl;
            } catch (...) {
                cout << "other exception" << endl;
            }
        }
    }
    // 左值和右值
    {
        // 非const左值引用只能绑定左值
        {
            int a = 10;
            int &b = a;
            // Non-const lvalue reference 'c' to type int cannot bind to rvalue of type int
            //int &c = 10;
            cout << format("a:{},b:{}", a, b) << endl;
        }
        // const左值引用可以绑定左值和右值
        {
            int a = 10;
            const int &b = a;
            const int &c = 10;
            cout << format("a:{},b:{},c:{}", a, b, c) << endl;
        }
        // 右值引用只能绑定右值
        {
            int a = 10;
            int &&b = 123;
            // Rvalue reference 'c' to type int cannot bind to lvalue of type int
            //int &&c = a;
            cout << format("a:{},b:{}", a, b) << endl;
        }
        // 自动类型推断
        {
            class User1 {
            public:
                void exe() {
                    auto arr = {1, 2, 3, 4, 5};
                    for (auto a: arr) {
                        cout << format("a:{}", a) << endl;
                    }
                }

                auto getId(any id) {
                    auto id2 = 10;
                    return any_cast<int>(id) + id2;
                }
            };

            User1 user1;
            user1.exe();
            cout << format("id:{},age:{}", user1.getId(12), age) << endl;
        }
    }
    // 强制类型转换
    {
        // c语法转换
        {
            long a = 100;
            int b = (int) a;
            cout << format("a:{},b:{}", a, b) << endl;
        }
        // 静态转换
        {
            cout << "<<<" << endl;
            long a = 100;
            int b = static_cast<int>(a);
            cout << format("a:{},b:{}", a, b) << endl;

            User1 *u1 = new User1;
            // 没有运行时检查，可能会出现未定义行为导致程序崩溃
            User2 *u2 = static_cast<User2 *>(u1);
            u2->exe();
            delete u1;
        }
        // 动态转换
        {
            // 指针转换
            {
                User1 *u1 = new User2;
                User2 *u2 = dynamic_cast<User2 *>(u1);
                if (u2) {
                    u2->exe();
                } else {
                    cout << format("User1 2 User2类型转换错误") << endl;
                }
                delete u1;
            }
            // 引用转换
            {
                try {
                    User1 u1;
                    User2 &u2 = dynamic_cast<User2 &>(u1);
                    u2.exe();
                } catch (const std::bad_cast &e) {
                    // 动态转换的时候，如果是引用类型转换失败则会抛bad_case异常
                    cout << format("error:{}", e.what()) << endl;
                }
            }
        }
        // reinterpret_cast转换
        {
            User1 *u1 = new User1;
            // 获取指针指向的内存地址
            uintptr_t address = reinterpret_cast<uintptr_t>(u1);
            cout << "u1:" << u1 << "\taddress:" << hex << address << endl;
            // 内存地址转为指针
            User1 *u2 = reinterpret_cast<User1 *>(address);
            u2->exe();
            delete u1;
        }
        // const_case
        {
            const int a = 100;
            int *b = const_cast<int *>(&a);
            *b = 20;
            cout << format("a:{},b:{}", a, *b) << endl;
        }
    }
    // 未定义行为（UB）
    {
        // 访问未初始化变量
        {
            // a的值不会等于0，值是任意的，可能来源于之前内存位遗留的内容
            int aa;
            int b = 2 + aa;
            cout << format("aa:{},b:{}", aa, b) << endl;
        }
        // // 访问空指针
        // {
        //     int *a = nullptr;
        //     int b = *a;
        //     cout << b << endl;
        // }
        // // 数组越界访问
        // {
        //     int arr[5] = {1, 2, 3, 4, 5};
        //     cout << format("arr[5]:{}", arr[5]) << endl;
        // }
        // 悬垂指针
        // {
        //     int *a = new int(1);
        //     cout << format("a:{}", *a) << endl;
        //     int *b = a;
        //     delete a;
        //     cout << format("b:{}", *b) << endl;
        // }
    }
    // ADL
    {
        // 编译器会根据所属命名空间的参数类型查找到指定的目标函数
        exe(adl::test::UserVO(1, "admin123"));

        // 当不想引入整个命名空间时，可以通过using单独引入某个命名空间的成员来降低命名冲突问题
        using adl::test::exe;
        exe(adl::test::UserVO(2, "admin321"));
    }
    // 重载运算符
    {
        MyData data(1, "data...");
        std::cout << data << endl;
    }
    cout << "==== end ====" << endl;
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
