
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>

struct Color {
  std::uint8_t num;  
  std::uint8_t r;  
  std::uint8_t g;  
  std::uint8_t b;
  double luma = 0.2126 * r + 0.7152 * g + 0.0722 * b;  
};

template < typename Colors >
constexpr auto nearest_color( 
    const Colors& colors, 
    const std::uint8_t r,
    const std::uint8_t g,
    const std::uint8_t b ) {
        return *std::min_element( 
            begin(colors), end(colors), 
            [r, g, b](const auto& lhs, const auto& rhs){ 
                const auto square = [](const auto& t){ return t*t; };
                return ( square( lhs.r - r ) + square( lhs.g - g ) + square( lhs.b - b ) )
                     < ( square( rhs.r - r ) + square( rhs.g - g ) + square( rhs.b - b ) );
             } );
    }

template < std::size_t N >
constexpr auto sort_by_luma( const std::array< Color, N >& colors ) {
    auto retVal = colors;

    const auto arrayHead = &std::get<0>(retVal);
    const auto end       = arrayHead + colors.size();

    for ( std::size_t i = 0; i < colors.size(); ++i ) {
        const auto begin = arrayHead + i;

        auto minElem = std::min_element( begin, end, 
            [](const auto& lhs, const auto& rhs){ return lhs.luma < rhs.luma; } );

        const auto tmp = *minElem;
        *minElem = *begin;
        *begin = tmp;
    }

    return retVal;
}

int main() {
    constexpr std::array< Color, 16 > colors {{
        Color{0,  0x00, 0x00, 0x00},
        Color{1,  0xFF, 0xFF, 0xFF},
        Color{2,  0x88, 0x39, 0x32},
        Color{3,  0x67, 0xB6, 0xBD},
        Color{4,  0x8B, 0x3F, 0x96},
        Color{5,  0x55, 0xA0, 0x49},
        Color{6,  0x40, 0x31, 0x8D},
        Color{7,  0xBF, 0xCE, 0x72},
        Color{8,  0x8B, 0x54, 0x29},
        Color{9,  0x57, 0x42, 0x00},
        Color{10, 0xB8, 0x69, 0x62},
        Color{11, 0x50, 0x50, 0x50},
        Color{12, 0x78, 0x78, 0x78},
        Color{13, 0x94, 0xE0, 0x89},
        Color{14, 0x78, 0x69, 0xC4},
        Color{15, 0x9F, 0x9F, 0x9F}
    }};

    static_assert( 12 == nearest_color( colors, 128, 128, 128 ).num );
    static_assert( 0  == nearest_color( colors,   0,   0,   0 ).num );

    constexpr auto sorted_colors = sort_by_luma( colors );

    static_assert(sorted_colors[ 0].num ==  0);
    static_assert(sorted_colors[ 7].num == 14);
    static_assert(sorted_colors[ 8].num == 12);
    static_assert(sorted_colors[15].num ==  1);

    for( const auto& c : sorted_colors ) {
        std::cout << static_cast<int>(c.num) << ": " << c.luma << '\n';
    }

    return sorted_colors[15].num;
}

