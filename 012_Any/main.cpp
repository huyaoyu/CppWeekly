#include <any>
#include <functional>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <vector>

using namespace std::string_literals;

// Build a map for handling simple numerics.
template< typename T, typename F >
inline std::pair< const std::type_index, std::function<void(std::any& a)> > 
to_any_visitor(F const& f) {
    return { 
        std::type_index( typeid(T) ), 
        [ g = f ] ( std::any& a ) {
            if constexpr ( std::is_void_v<T> ) {
                g();
            } else {
                g( std::any_cast<T>(&a) );
            }
        }
    };
}

static std::unordered_map< 
    std::type_index, std::function<void(std::any&)> >
    any_visitor {
        to_any_visitor<void>([]{ std::cout << "{}"; }),
        to_any_visitor<int>([](int* a){ *a += 1; std::cout << "int visitor\n"; }),
        to_any_visitor<float>([](float* a){ *a += 1.f; std::cout << "float visitor\n"; }),
        to_any_visitor<double>([](double* a){ *a += 1.0; std::cout << "double visitor\n"; })
    };

inline void process( std::any& a ) {
    if ( const auto it = any_visitor.find( std::type_index(a.type()) ); 
         it != any_visitor.end() ) {
             it->second(a);
    } else {
        std::cout << "Unregistered type: " << std::quoted( a.type().name() ) << '\n';
    }
}

int main( int argc, char** argv ) {
    std::cout << "Hello, Any! \n";

    std::vector<std::any> v { "Hello"s, 1, 2.2f, 3.3 };

    for ( const auto& a : v ) {
        std::cout << "a.type().name() = " << a.type().name() << '\n';
    }

    for ( auto& a : v ) {
        process(a);
    }

    std::cout << "std::any_cast<double>(v[3]) = " << std::any_cast<double>(v[3]) << '\n';

    return 0;
}
