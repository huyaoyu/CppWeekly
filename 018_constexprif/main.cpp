#include <iostream>
#include <limits>
#include <type_traits>

#include "TypeName.hpp"

template< typename T >
constexpr bool valid_int() { 
    if constexpr( std::is_integral<T>::value && !std::is_same<bool, T>::value ) {
        if constexpr( std::numeric_limits<T>::max() > 1000 ) {
            return true;
        }
    }

    return false;
}

template < typename T >
auto add( const T& a ) {
    if constexpr( valid_int<T>() ) {
        return a + 1;
    } else if constexpr( std::is_floating_point<T>::value ) {
        return a + static_cast<T>(0.1);
    } else {
        return a;
    }
}

int main() {
    std::cout << "Hello, ConstexprIf! \n";

    auto a = add(1);
    auto b = add(1.0);
    auto c = add(1.0f);
    auto d = add("OK");
    auto e = add(static_cast<std::uint8_t>(65));

    std::cout << "Type of a is " << TYPE_NAME(a) << ", value is " << a << '\n';
    std::cout << "Type of b is " << TYPE_NAME(b) << ", value is " << b << '\n';
    std::cout << "Type of c is " << TYPE_NAME(c) << ", value is " << c << '\n';
    std::cout << "Type of d is " << TYPE_NAME(d) << ", value is " << d << '\n';
    std::cout << "Type of e is " << TYPE_NAME(e) << ", value is " << e << '\n';

    return 0;
}