#pragma once

#include <necktar/data.hpp>


namespace necktar
{

    // semitone seq {0,3,5,8,11} -> tone vector {1,0,0,1,0,1,0,1,..}
    inline tone_vec_t vectorize(semitone_seq_t const& s)
    {
        tone_vec_t t(12, 0);
        for (auto v : s) {
            v %= 12;
            if (v < 0)
                v += 12;
            t[v] = 1;
        }
        return t;
    }


    // {"1","b3","5","b7"} -> tone vector {1,0,0,1,0,1,0,1,..}
    inline tone_vec_t vectorize(interval_char_seq_t const& s)
    {
        tone_vec_t t(12, 0);
        for (auto v : s)
            t[semitone(v)%12] = 1;
        return t;
    }


    // {1, 3_b, 5 , 7_b} -> semitone seq {0,3,7,10}
    inline semitone_seq_t normalize(interval_seq_t const& s)
    {
        // already normalized items are +0xff+-12
        semitone_seq_t t;
        t.reserve(s.size());
        for (auto const& v : s) {
            t.push_back( v > detail::INTVDELTA-12
                         ? v - detail::INTVDELTA
                         : detail::interval[v]%12 );
        }
        return t;
    }


    // {"1","b3","5","b7"} -> semitone seq {0,3,7,10}
    inline semitone_seq_t normalize(interval_char_seq_t const& s)
    {
        semitone_seq_t t;
        t.reserve(s.size());
        for (auto const& v : s) {
            t.push_back(semitone(v));
        }
        return t;
    }


}
