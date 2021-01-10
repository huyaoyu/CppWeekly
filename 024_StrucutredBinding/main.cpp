
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

struct A {
    int    a = 0;
    float  b = 1.1f;
    double c = 2.2;
    std::string d = "d";
};

class B {
public:
    int a = 0;
    int b = 1.1f;
private:
    int c = 2.2;
};

class C {
public:
    int a = 0;
    int b = 1;
public:
    void f() {}
private:
    void g() {}
public:
    int c = 2;
};

class D {
public:
    int d = 3;
};

class E0 : public C {
public:
    int e = 4;
};

class E1 : public C, D {
public:
    int e = 4;
};

class F {
public:
    static int a;
};

int F::a = 0;

class G : public F {
public:
    static int b;
};

int G::b = 0;

int& add_v( std::map<std::string, int>& v, const std::string& name) {
    if ( auto [ iter, flag ] = v.insert({name, 0}); flag ) {
        return iter->second;
    } else {
        throw std::runtime_error("Add failed. ");
    }
}

int main() {
    std::cout << "Hello, StructuredBinding! \n";

    std::map<std::string, int> m;

    auto& ret = add_v(m, "v0");

    std::cout << "m[\"v0\"] = " << m["v0"] << '\n';

    ret = 1;

    std::cout << "m[\"v0\"] = " << m["v0"] << '\n';

    std::cout << '\n';

    // Test std::tie and std::ignore.
    bool flag = false;
    std::tie( std::ignore, flag ) = m.insert({"v1", 0});

    std::cout << "Test with plain array and std::array. \n";
    {
        int a[] = {0, 1, 2};
        auto [ a0, a1, a2 ] = a;

        std::array b = { 0, 1, 2 };
        auto [ b0, b1, b2 ] = b;
    }

    std::cout << "Test structured binding with structs and classes. \n";
    {
        auto [ a, b, c, d ] = A();

        std::cout << "a = " << a << '\n';
        std::cout << "b = " << b << '\n';
        std::cout << "c = " << c << '\n';
        std::cout << "d = " << d << '\n';

        // Decompose A into 2 elements.
        // auto [ aa, bb ] = A(); // This is an error.
    }

    // Test structured binding with class.
    {
        // Structured binding with privatre data members.
        // auto [ a, b ] = B(); // This is an error.
        auto [ a, b, c ] = C();
        C objC;
        auto [ ca, cb, cc ] = objC;
        ca = -1;
        std::cout << "objC.a = " << objC.a << '\n';

        auto & [ rca, rcb, rcc ] = objC;
        rca = -2;
        std::cout << "objC.a = " << objC.a << '\n';
    }

    // Test structured binding with class hierarchy.
    {
        // auto [ a, b, e ] = E0(); // This is an error.
        // auto [ a, b, d, e ] = E1(); // This is an error.
        // auto [ a, b ] = G(); // This is an error.
    }

    return 0;
}
