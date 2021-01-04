#include <iostream>
#include <future>

static long int add_sequence(int start, int end) {
    long int res = 0;

    for ( int j = 0; j < 2; j++ ) {
        for ( int i = start; i < end; i++ ) {
            res += static_cast<int>(i * 1.0);
        }
    }

    return res;
}

static void serial() {
    auto res0 = add_sequence(0, 1000000000);
    auto res1 = add_sequence(1000000000, 2000000000 );
    std::cout << "res0 = " << res0 << '\n';
    std::cout << "res1 = " << res1 << '\n';
}

static void async() {
    auto f0 = std::async( std::launch::async, add_sequence, 0, 1000000000 );
    auto f1 = std::async( std::launch::async, add_sequence, 1000000000, 2000000000 );

    std::cout << "f0.get() = " << f0.get() << '\n';
    std::cout << "f1.get() = " << f1.get() << '\n';
}

static void throws() {
    std::runtime_error err("This is an exception.");
    throw err;
}

static void async_exception() {
    auto f = std::async( std::launch::async, throws );
    try {
        f.get();
    } catch ( const std::exception& ex ) {
        std::cout << ex.what() << '\n';
    }
}

int main( int argc, char** argv ) {
    std::cout << "Hello, Future! \n";

    // serial();
    async();

    // async_exception();

    return 0;
}