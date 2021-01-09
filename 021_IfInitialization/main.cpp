
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::cout << "Hello, IfInitialization! \n";
    
    // Create the vector.
    std::vector v { 1, 2, 3, 4, 5, 2, 1 };

    std::cout << "First round. \n";
    if ( auto iterR = std::find( v.rbegin(), v.rend(), 5 ); iterR != v.rend() ) {
        *iterR = 50;
    } else if ( const auto iter = std::find( v.begin(), v.end(), 3 ); iter != v.end() ) {
        std::cout << *iter << '\n';
    } else {
        std::cout << "Else branch. \n";
    }

    std::cout << "Second round. \n";
    if ( auto iterR = std::find( v.rbegin(), v.rend(), 5 ); iterR != v.rend() ) {
        *iterR = 50;
    } else if ( const auto iter = std::find( v.begin(), v.end(), 3 ); iter != v.end() ) {
        std::cout << *iter << '\n';
    } else {
        std::cout << "Else branch. \n";
    }

    std::cout << "Third round. \n";
    if ( auto iterR = std::find( v.rbegin(), v.rend(), 5 ); iterR != v.rend() ) {
        *iterR = 50;
    } else if ( const auto iter = std::find( v.begin(), v.end(), 6 ); iter != v.end() ) {
        std::cout << *iter << '\n';
    } else {
        std::cout << "Else branch. \n";
    }

    for ( const auto& a : v ) {
        std::cout << a << '\n';
    }

    return 0;
}
