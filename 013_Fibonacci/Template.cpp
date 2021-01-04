#include <array>
#include <iostream>
#include <utility>

template < size_t I >
struct Fib {
    static const int value = Fib<I-2>::value + Fib<I-1>::value;
};

template <>
struct Fib<0> {
    static const int value = 0;
};

template <>
struct Fib<1> {
    static const int value = 1;
};

template < size_t... I >
static const int fib_impl( std::index_sequence<I...>, int i ) {
    constexpr std::array< int, sizeof...(I) > fibs = {
        Fib<I>::value... };

    std::cout << "sizeof...(I) = " << sizeof...(I) << '\n';

    return fibs[i];
}

const int fib(int i) {
    return fib_impl( std::make_index_sequence<47>(), i );
}

int main() {
    std::cout << "Hello, TemplateFibonacci! \n";

    std::cout << fib(46) << '\n';

    return 0;
}