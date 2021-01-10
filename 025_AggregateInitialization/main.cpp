
class A {
public:
    int a = 0;
};

struct SA {
    int a = 0;
    void f() {}
};

class B : public A {
public:
    int b = 0;
};

class C {
public:
    int a = 0;
    int b = 0;
};

class D {
public:
    int a = 0;
private:
    int b = 0;
};

struct SD {
    int a = 0;
private:
    int b = 0;
};

int main() {
    A a {1};
    // A af {1.1}; // This is an error.
    SA sa {1};
    B b { {1}, 2 };
    C c { 1, 2 };
    C cc {1};
    // The followings will cause errors.
    // D d { 1, 2 }; 
    // SD sd { 1, 2 };
    // D d {1};
    // SD sd {1};

    return 0;
}