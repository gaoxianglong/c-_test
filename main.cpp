#include <iostream>

using namespace std;

namespace adl::test {
    struct UserVO {
        int id;
        string name;

        UserVO(int id, string name): id(id), name(name) {
        }
    };

    void exe(UserVO user_vo) {
        cout << format("====id:{},name:{}", user_vo.id, user_vo.name) << endl;
    }

    /**
     * 重写<<运算符
     */
    ostream &operator<<(ostream &os, const UserVO &user_vo) {
        cout << format("id:{},name:{}", user_vo.id, user_vo.name);
        return os;
    }
}

int main(int argc, char *argv[]) {
    // 035法则
    {
        class User2 {
        public:
            User2() {
                cout << "User2 init..." << endl;
            }

            ~User2() {
                cout << "User2 destroy..." << endl;
            }
        };

        class User1 {
        public:
            int *id;
            string **account;
            int size;
            User2 *u2;

            User1(int id, int size): id(new int(id)), size(size), account(new string *[size]), u2(new User2) {
                for (auto i = 0; i < size; i++) {
                    account[i] = new string(format("admin-{}", i));
                }
                cout << "User1 init..." << endl;
            }

            /**
             * 拷贝构造函数
             */
            User1(User1 &source): id(new int(*source.id)), size(source.size), account(new string *[source.size]),
                                  u2(new User2(*source.u2)) {
                for (auto i = 0; i < size; i++) {
                    if (source.account[i] != nullptr) {
                        account[i] = new string(*source.account[i]);
                    }
                }
            }

            /**
             * 拷贝赋值运算符
             */
            User1 & operator=(User1 &source) {
                if (&source != this) {
                    delete id;
                    for (auto i = 0; i < size; i++) {
                        delete account[i];
                    }
                    delete[] account;
                    delete u2;
                    size = 0;

                    id = new int(*source.id);
                    size = source.size;
                    account = new string *[size];
                    for (auto i = 0; i < size; i++) {
                        if (source.account[i] != nullptr) {
                            account[i] = new string(*source.account[i]);
                        }
                    }
                    u2 = new User2(*source.u2);
                }
                return *this;
            }

            /**
             * 移动构造函数
             */
            User1(User1 &&source): id(source.id), size(source.size), account(source.account), u2(source.u2) {
                source.id = nullptr;
                source.size = 0;
                source.account = nullptr;
                source.u2 = nullptr;
            }

            /**
             * 移动赋值运算符
             */
            User1 & operator =(User1 &&source) {
                if (&source != this) {
                    delete id;
                    for (auto i = 0; i < size; i++) {
                        delete account[i];
                    }
                    delete[] account;
                    delete u2;
                    size = 0;

                    id = source.id;
                    size = source.size;
                    account = source.account;
                    u2 = source.u2;
                    source.id = nullptr;
                    source.size = 0;
                    source.account = nullptr;
                    source.u2 = nullptr;
                }
                return *this;
            }

            /**
             * 析构函数
             */
            ~User1() {
                delete id;
                for (auto i = 0; i < size; i++) {
                    delete account[i];
                }
                delete[] account;
                delete u2;
                cout << "User1 destroy..." << endl;
            }
        };
        //
        {
            User1 u1(100, 2);
            User1 u2 = u1;
            cout << format("u1.id:{},u2.id:{},u1.&id:{:p},u2.&id:{:p}", *u1.id, *u2.id, static_cast<void *>(u1.id),
                           static_cast<void *>(u2.id)) << endl;
        }

        //
        {
            cout << "<<<" << endl;
            User1 u1(100, 2);
            User1 u2(200, 2);
            u1 = u2;
            cout << format("u1.id:{},u2.id:{},u1.&id:{:p},u2.&id:{:p}", *u1.id, *u2.id, static_cast<void *>(u1.id),
                           static_cast<void *>(u2.id)) << endl;
        }

        //
        {
            cout << "<<<" << endl;
            User1 u1(11, 2);
            User1 u2 = std::move(u1);
            cout << format("u2.id:{},u1.id=null:{}", *u2.id, u1.id == nullptr) << endl;
        }

        //
        {
            cout << "<<<" << endl;
            User1 u1(11, 2);
            User1 u2(22, 2);
            u2 = std::move(u1);
            cout << format("u2.id:{},u1.id==null:{}", *u2.id, u1.id == nullptr) << endl;
        }
    }

    //
    {
        class Base1 {
        public:
            int getId() {
                return 1;
            }
        };
        class Base2 {
        public:
            string getName() {
                return "admin";
            }
        };
        class Sub : public Base1, public Base2 {
        public:
            void exe() {
                cout << format("id:{},name:{}", getId(), getName()) << endl;
            }
        };
        Sub().exe();
    }
    //
    {
        class Base {
        public:
            virtual string getName() {
                return "admin";
            }
        };
        class Sub1 : virtual public Base {
        };
        class Sub2 : virtual public Base {
        };
        class Sub3 : public Sub1, public Sub2 {
        public:
            void exe() {
                cout << format("name:{}", getName()) << endl;
            }
        };

        Sub3().exe();
    }
    //
    {
        class MyException1 : public std::exception {
            string msg;

        public:
            MyException1(const string &msg): msg(msg) {
            }

            MyException1(const string &msg, const std::exception &e): msg(format("{}:{}", msg, string(e.what()))) {
            }

            const char * what() const noexcept override {
                return msg.c_str();
            }
        };

        class MyException2 : public std::logic_error {
        public:
            MyException2(const string &msg): logic_error(msg) {
            }

            MyException2(const string &msg, const std::exception &e): logic_error(
                format("{}:{}", msg, string(e.what()))) {
            }
        };

        try {
            //throw 123;
            throw MyException1("MyException1", MyException2("MyException2"));
        } catch (const int &e) {
            cout << format("int:{}", e) << endl;
        }
        catch (const MyException1 &e) {
            cout << format("MyException1:{}", e.what()) << endl;
        }
        catch (const MyException2 &e) {
            cout << format("MyException2:{}", e.what()) << endl;
        }
        catch (const logic_error &e) {
            cout << format("logic_error:{}", e.what()) << endl;
        }
        catch (const std::exception &e) {
            cout << format("std::exception:{}", e.what()) << endl;
        }
        catch (...) {
            cout << "other exception" << endl;
        }
    }
    //
    {
        // 非const左值引用只能绑定左值
        {
            int a = 10;
            int &b = a;
            cout << format("a:{},b:{}", a, b) << endl;
        }
        // const左值引用可以绑定左右值
        {
            int a = 10;
            const int &b = a;
            const int &c = 20;
            cout << format("a:{},b:{},c:{}", a, b, c) << endl;
        }
        // 右值引用只能够绑定右值
        {
            int a = 10;
            //int &&b = a;
            int &&c = 20;
            cout << format("a:{},c:{}", a, c) << endl;
        }
    }
    // 强制类型转换
    {
        // c风格
        {
            long a = 1024;
            int b = (int) a;
            cout << format("a:{},b:{}", a, b) << endl;
        }

        class User1 {
        public:
            virtual void exe() {
                cout << format("User1 exe...") << endl;
            }
        };

        class User2 : public User1 {
        public:
            void exe() override {
                cout << format("User2 exe...") << endl;
            }
        };

        // 静态转换
        {
            long a = 100;
            int b = static_cast<int>(a);
            cout << format("a:{},b:{}", a, b) << endl;

            User1 *u1 = new User1;
            // 这里可能会引起未定义行为
            User2 *u2 = static_cast<User2 *>(u1);
            u1->exe();
        }
        // 动态转换
        {
            User1 *u1 = new User1;
            User2 *u2 = dynamic_cast<User2 *>(u1);
            // 动态转换，会进行运行时检查，查看u1的虚表指向的对象类型不对就返回null
            if (u2 == nullptr) {
                cout << "指针类型类型转换错误" << endl;
            } {
                try {
                    User1 u1;
                    User2 u2 = dynamic_cast<User2 &>(u1);
                    u2.exe();
                } catch (const std::bad_cast &e) {
                    cout << "引用类型类型转换错误" << endl;
                }
            }
        }
        //
        {
            User1 *u1 = new User1;
            uintptr_t address = reinterpret_cast<uintptr_t>(u1);
            cout << "address:0x" << hex << address << "\t&u1:" << u1 << endl;
            User1 *u2 = reinterpret_cast<User1 *>(address);
            u2->exe();
        }
        //
        {
            const int a = 10;
            int *b = const_cast<int *>(&a);
            *b = 20;
            cout << format("a:{}", a) << endl;
        }
    }
    //
    {
        cout << "<<<" << endl;
        adl::test::UserVO user_vo(123, "admin");
        exe(user_vo);

        cout << user_vo << endl;
    }
    cout << "==== end ====" << endl;
    return 0;
}
