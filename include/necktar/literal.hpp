#pragma once

#include <necktar/utility.hpp>


namespace necktar
{

    // flat
    constexpr semitone_t operator "" _f(unsigned long long i)
    {
        return detail::INTVDELTA
            + (i > 0 && i < 8 ? (detail::interval[i]-1)%12 : 0); // 0 ??
    }

    // bemol (= flat)
    constexpr semitone_t operator "" _b(unsigned long long i)
    {
        return operator "" _f(i);
    }

    // bemol bemol
    constexpr semitone_t operator "" _bb(unsigned long long i)
    {
        return detail::INTVDELTA
            + (i > 0 && i < 8 ? (detail::interval[i]-2)%12 : 0); // 0 ??
    }

    // sharp
    constexpr semitone_t operator "" _s(unsigned long long i)
    {
        return detail::INTVDELTA
            + (i > 0 && i < 8 ? (detail::interval[i]+1)%12 : 0); // 0 ??
    }

    // diminished, augmented etc
    // ..

}
