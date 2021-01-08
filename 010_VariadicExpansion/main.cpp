
#include <iostream>
#include <sstream>
#include <vector>

template< typename ... T >
std::vector<std::string> convert_2_str( const T& ... args ) {
    std::stringstream ss;
    std::vector<std::string> vs;
    (void)std::initializer_list<int>{ 
        ( ss.str(""), 
          ss << args, 
          vs.push_back(ss.str()), 
          0 )... };
    return vs;
}

template < typename... T >
std::vector<std::string> convert_2_str_fold( const T&... args ) {
    std::stringstream ss;
    return { ( ss.str(""), ss << args, ss.str() )... };
}

int main( int argc, char** argv ) {
    std::cout << "Hello, VariadicExpansion! \n";
    
    auto vs = convert_2_str( "Hello", "world", 1, 2.2f, 3.3 );

    for ( const auto& s : vs ) {
        std::cout << s << '\n';
    }

    auto vsf = convert_2_str_fold( "Hello", "world", 1, 2.2f, 3.3 );
    for ( const auto& s: vs ) {
        std::cout << s << '\n';
    }

    std::cout << "Done! \n";

    return 0;
}
