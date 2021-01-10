
#include <algorithm>
#include <iostream>

#include "TypeName.hpp"

struct A {
    explicit A(int v)
    : val{v} {}

    A (const A& other) = default;

    friend bool operator < ( const A& first, const A& second ) { 
        return first.val < second.val;
    }

    int val;
};

static void test_auto_without_reference() {
    int b = 10;
    int c = 0;
    int d = 5;

    auto e = std::clamp( b, c, d );

    std::cout << "Type of e is " << TYPE_NAME(e) << ", value is " << e << '\n';

    int& f = d;
    std::cout << "&d = " << &d << '\n';
    std::cout << "&e = " << &e << '\n';
    std::cout << "&f = " << &f << '\n';

    std::cout << '\n';

    int g = 3;
    auto h = std::clamp( g, c, d );

    std::cout << "d = -1 \n";
    d = -1;
    std::cout << "e = " << e << '\n';
    std::cout << "f = " << f << '\n';

    std::cout << '\n';
    std::cout << "g = -1 \n";
    g = -1;
    std::cout << "&g = " << &g << '\n';
    std::cout << "&h = " << &h << '\n';
    std::cout << "h = " << h << '\n';

    A objB(10);
    A objC(0);
    A objD(5);

    auto objE = std::clamp( objB, objC, objD );

    std::cout << "Type of objE is " << TYPE_NAME(objE) << '\n';
    std::cout << "objE.val = " << objE.val << '\n';

    A& objF = objD;
    std::cout << "Type of objF is " << TYPE_NAME(objF) << '\n';
    std::cout << "&objD = " << &objD << '\n';
    std::cout << "&objE = " << &objE << '\n';
    std::cout << "&objF = " << &objF << '\n';

    std::cout << "Assign -1 to objD. \n";
    objD.val = -1;
    std::cout << "objE.val = " << objE.val << '\n';
    std::cout << "objF.val = " << objF.val << '\n';

    std::cout << '\n';

    A objG(3);
    auto objH = std::clamp( objG, objC, objD );
    std::cout << "Type of objH is " << TYPE_NAME(objH) << '\n';
    std::cout << "&objG = " << &objG << '\n';
    std::cout << "&objH = " << &objH << '\n';

    std::cout << "Assign -1 to objG. \n";
    objG.val = -1;
    std::cout << "objH.val = " << objH.val << '\n';
}

static void test_auto_with_reference() {
    int b = 10;
    int c = 0;
    int d = 5;

    auto& e = std::clamp( b, c, d );

    std::cout << "Type of e is " << TYPE_NAME(e) << ", value is " << e << '\n';

    int& f = d;
    std::cout << "&d = " << &d << '\n';
    std::cout << "&e = " << &e << '\n';
    std::cout << "&f = " << &f << '\n';

    std::cout << '\n';

    int g = 3;
    auto& h = std::clamp( g, c, d );

    std::cout << "d = -1 \n";
    d = -1;
    std::cout << "e = " << e << '\n';
    std::cout << "f = " << f << '\n';

    std::cout << '\n';
    std::cout << "g = -1 \n";
    g = -1;
    std::cout << "&g = " << &g << '\n';
    std::cout << "&h = " << &h << '\n';
    std::cout << "h = " << h << '\n';

    A objB(10);
    A objC(0);
    A objD(5);

    auto& objE = std::clamp( objB, objC, objD );

    std::cout << "Type of objE is " << TYPE_NAME(objE) << '\n';
    std::cout << "objE.val = " << objE.val << '\n';

    A& objF = objD;
    std::cout << "Type of objF is " << TYPE_NAME(objF) << '\n';
    std::cout << "&objD = " << &objD << '\n';
    std::cout << "&objE = " << &objE << '\n';
    std::cout << "&objF = " << &objF << '\n';

    std::cout << "Assign -1 to objD. \n";
    objD.val = -1;
    std::cout << "objE.val = " << objE.val << '\n';
    std::cout << "objF.val = " << objF.val << '\n';

    std::cout << '\n';

    A objG(3);
    auto& objH = std::clamp( objG, objC, objD );
    std::cout << "Type of objH is " << TYPE_NAME(objH) << '\n';
    std::cout << "&objG = " << &objG << '\n';
    std::cout << "&objH = " << &objH << '\n';

    std::cout << "Assign -1 to objG. \n";
    objG.val = -1;
    std::cout << "objH.val = " << objH.val << '\n';
}

int main() {
    std::cout << "Hello, Clamp! \n"; 

    // auto a = std::clamp( 1, 0.0, 2.0f ); // This is an error.
    // auto a = std::clamp( 1, 0.0, 2.0 ); // This is also an error.
    auto a = std::clamp( 1.0, 0.0, 2.0 );
    std::cout << "Type of a is " << TYPE_NAME(a) << ", value is " << a << '\n';

    test_auto_without_reference();

    std::cout << "==========\n";

    test_auto_with_reference();

    return 0;
}
