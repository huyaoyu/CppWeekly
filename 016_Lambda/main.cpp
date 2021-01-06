
#include <functional>
#include <iostream>
#include <string>
#include <string_view>

/**
 * Found at 
 * https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c/56766138#56766138
 */
template <typename T>
constexpr auto type_name() noexcept {
  std::string_view name = "Error: unsupported compiler", prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void) noexcept";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

static void process(int a) {
    std::cout << "Do nothing. " << '\n';
}

template < typename T >
static auto process( const std::string& s, int a, const T& b ) {
    const auto res = a + b;
    std::cout << s << ": " << res << '\n';
    return res;
}

template < typename T >
static auto process( int a, const std::string& s, T& b ) {
    const auto res = a + b;
    b = res;
    std::cout << s << ": " << res << '\n';
    return res;
}

struct A {
    explicit A(int a) 
    :val{a} {}

    A(const A& other) = default;

    double add(double r) const {
        const auto res = static_cast<double>( val + r );
        std::cout << "res = " << res << '\n';
        return res;
    }

    A operator + ( double r ) const {
        A res(*this);
        res.val += r;
        return res;
    }

    int val;
};

template < typename T >
struct B {
    explicit B(const T& a)
    : val{a} {}

    template< typename R >
    R add(const R& r) const { 
        std::cout << "Type of r is " << type_name<decltype(r)>() << '\n';
        const auto res = static_cast<R>( val + r );
        std::cout << "res = " << res << '\n';
        return res;
    }

    template< typename R >
    R add_ref(R& r) const { 
        std::cout << "Type of r is " << type_name<decltype(r)>() << '\n';
        const auto res = static_cast<R>( val + r );
        std::cout << "res = " << res << '\n';
        r = res;
        return res;
    }

    double add_d(double r) const { 
        const auto res = static_cast<double>( val + r );
        std::cout << "res = " << res << '\n';
        return res;
    }

    T val;
};

template < typename R, typename C, typename ...A >
R call_fn( const std::function<R(const C&, A...)>& fn, const C& c, A&... args ) {
    return fn(c, args...);
}

int main() {
    std::cout << "Hello, Lambda! \n";
    
    process("1 + 2.2", 1, 2.2);

    const auto L = []( const auto& b, int a, const std::string& s, auto... args ) {
        return process( s, a, b );
    };

    std::cout << "Type of L is " << type_name<decltype(L)>() << '\n';

    std::cout << "L(3.3, 1, \"3.3 + 1\")" << '\n';
    L(3.3, 1, "3.3 + 1");

    auto F = std::function<double(const double&, int, const std::string&)>(L);
    F(4.4, 1, "4.4 + 1");

    auto G = std::function<float(const double&, int, const std::string&)>(L);
    auto resG = G(5.5, 1, "5.5 + 1");
    std::cout << "The of resG is " << type_name<decltype(resG)>() << '\n';
    G(5.5f, 1, "5.5f + 1");

    auto H = std::function<float(const float&, int, const std::string&)>(L);
    auto resH = H(6.6, 1, "6.6 + 1");

    const auto LR = []( auto& b, int a, const std::string& s, auto... args ) {
        // Use the overload function. 
        return process( a, s, b );
    };

    std::cout << '\n';

    std::cout << "LR(3.3, 1, \"3.3 + 1\")" << '\n';
    double a = 3.3;
    LR(a, 1, "3.3 + 1");
    std::cout << "a = " << a << '\n';

    a = 3.3;
    auto FR = std::function<double(double&, int, const std::string&)>(LR);
    FR(a, 1, "3.3 + 1");
    std::cout << "a = " << a << '\n';

    a = 3.3;
    auto GR = std::function<float(double&, int, const std::string&)>(LR);
    GR(a, 1, "3.3 + 1");
    std::cout << "a = " << a << '\n';

    float b = 3.3f;
    auto HR = std::function<float(float&, int, const std::string&)>(LR);
    HR(b, 1, "3.3f + 1");
    std::cout << "b = " << b << '\n';

    std::cout << '\n';

    std::cout << "Class A" << '\n';
    auto I = std::function< double(const A&, double) >( &A::add );
    A objA(1);
    objA.add(2.2f);
    I(objA, 2.2f);

    // This seems impossible.
    // auto IP = std::function< double(const A&, double) > (&A::+);

    std::cout << "Class B<int>" << '\n';
    B<int> objB(1);
    objB.add( 2.2 );
    // We can use non-reference type for the add<>() function since all the arguments of add<>() are const reference type.
    auto J = std::function<double(const B<int>&, double)>(&B<int>::add<double>);
    // Automatic argument type promotion. 
    J(objB, 2.2f);
    J(objB, 2);

    auto K = std::function<int(const B<int>&, int)>(&B<int>::add<int>);
    // Automatic convert 2.2f to 2.
    K(objB, 2.2f);

    // Reference argument.
    auto M = std::function<int(const B<int>&, int&)>(&B<int>::add_ref<int>);
    auto c = 2;
    M(objB, c);
    std::cout << "c = " << c << '\n';

    // This seems impossible.
    // auto N = std::function<void(int)>(process);

    std::cout << '\n';

    std::cout << "call_fn" << '\n';
    call_fn( K, objB, c );
    // call_fn( M, objB, c ); // This is error. Cannot deduct type int&.

    return 0;
}
