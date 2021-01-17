
#include <cstdint>
#include <limits>

constexpr auto seed() { 
    std::uint64_t shifted = 0;

    for ( const auto c : __TIME__ ) {
        shifted <<= 8;
        shifted |= c;
    }

    return shifted;
}

struct PCG {
    struct pcg_32_random_t { 
        std::uint64_t state = 0;
        std::uint64_t inc = seed();
    };

    pcg_32_random_t rng;

    typedef std::uint32_t ResultType_T;

    constexpr ResultType_T operator()() { 
        return pcg_32_random_r();
    }

    static ResultType_T constexpr min() { 
        return std::numeric_limits<ResultType_T>::min();
    }

    static ResultType_T constexpr max() {
        return std::numeric_limits<ResultType_T>::max();
    }

private:
    constexpr ResultType_T pcg_32_random_r() {
        std::uint64_t oldState = rng.state;
        rng.state = oldState * 6364136223846793005ULL + ( rng.inc|1 );
        std::uint32_t xorshifted = ((oldState >> 18u) ^ oldState) >> 27u;
        std::uint32_t rot = oldState >> 59u;
        return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
    }
};

constexpr auto get_random(int x) {
    PCG pcg;
    while ( x > 0 ) {
        pcg();
        --x;
    }

    return pcg();
}

int main() {
    constexpr auto r = get_random(10);
    return r;
}