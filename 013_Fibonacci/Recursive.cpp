#include <iostream>

static int fib( int i ) {
    if ( 0 == i ) return 0;
    if ( 1 == i ) return 1;

    return fib( i - 2 ) + fib( i - 1 );
}

int main() {
    std::cout << "Hello, Fibonacci! \n";

    const int i = 46;

    std::cout << "The " << i << "th Fibonacci number is " << fib(i) << '\n';

    return 0;
}