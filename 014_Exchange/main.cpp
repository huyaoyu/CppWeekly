
#include <iostream>
#include <string>
#include <utility>

struct A {
    A()
    :val{0}, name{""} {}

    ~A() = default;

    A(const A& other) {
        this->val = other.val;
        if ( name.empty() ) {
            std::cout << "Copy construct. " << '\n';
        } else {
            std::cout << name << ": Copy construct" << '\n';
        }
    }

    A( A&& other ) {
        this->val = other.val;
        other.val = -1;
        if ( name.empty() ) {
            std::cout << "Move construct. " << '\n';
        } else {
            std::cout << name << ": Move construct. " << '\n';
        }
    }

    A& operator = ( const A& other ) {
        if ( &other == this ) {
            return *this;
        }

        this->val = other.val;
        if ( name.empty() ) {
            std::cout << "Assignment. " << '\n';
        } else {
            std::cout << name << ": Assignment. " << '\n';
        }
        
        return *this;
    }

    A& operator = ( A&& other ) {
        if ( &other == this ) {
            return *this;
        }

        this->val = other.val;

        if ( name.empty() ) {
            std::cout << "Move assignment. " << '\n';
        } else {
            std::cout << name << ": Move assigment. " << '\n';
        }

        return *this;
    }

    friend std::ostream& operator << ( std::ostream& os, const A& a) {
        os << a.val;
        
        return os;
    }

    int val;
    std::string name;
};

int main() {
    std::cout << "Hello, Exchange! \n";
    
    int a = 1;
    int b = std::exchange( a, 2 );

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';

    A objA;
    objA.val = 1;

    std::cout << "objA = " << objA << '\n';

    A objB(objA);
    std::cout << "objB = " << objB << '\n';

    A objC( std::move(objB) );
    std::cout << "objC = " << objC << '\n';
    std::cout << "objB = " << objB << '\n';

    objC.val = 2;

    std::cout << "objD = objC;" << '\n';
    A objD;
    objD = objC; // Assignment. 
    std::cout << "objD = " << objD << '\n';
    
    std::cout << "A objE = objC;" << '\n';
    A objE = objC; // This invokes the copy constructor, not the assignment operator. 
    std::cout << "objE = " << objE << '\n';

    std::cout << "objF = std::move(objE);" << '\n';
    A objF;
    objF = std::move(objE); // Move assignment. 
    std::cout << "objF = " << objF << '\n';

    std::cout << "A objG = std::move(objF);" << '\n';
    A objG = std::move(objF); // This inokes the move constructor, not the move assigment operator. 
    std::cout << "objG = " << objG << '\n';

    std::cout << '\n';

    objG.name = "objG";
    objF.name = "objF";

    std::cout << "objH = std::exchange(objG, objF);" << '\n';
    A objH;
    objH.name = "objH";
    objH = std::exchange(objG, objF);

    std::cout << "objI = std::exchange(objG, std::move(objF));" << '\n';
    A objI;
    objI.name = "objI";
    objI = std::exchange(objG, std::move(objF));

    std::cout << '\n';

    std::cout << "A objJ = std::exchange( objG, objF );" << '\n';
    A objJ = std::exchange( objG, objF );

    std::cout << "A objJ = std::exchange( objG, std::move(objF) );" << '\n';
    A objK = std::exchange( objG, std::move( objF ) );

    return 0;
}
