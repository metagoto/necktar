#pragma once

#include <necktar/fretboard.hpp>
#include <necktar/layer.hpp>

namespace necktar
{

    inline tone_vec_t chord_vectorize(fretboard const& board, string_pos_seq_t const& s)
    {
        tone_vec_t note_vec(12, 0);
        for (auto const& sp : s)
        {
            auto const& sn = std::get<0>(sp);
            auto const& fn = std::get<1>(sp);

            note n = note_at(board, sn, fn);
            if (n == note::NAFN)
                return tone_vec_t();
            note_vec[n] = 1;
        }

        return note_vec;

    }


    inline semitone_seq_seq_t which_chords(fretboard const& board, string_pos_seq_t const& s)
    {
        /*
         for each string_pos_seq
           find note
           construct tone_vec_t N of notes
         for each n in N
           take note n as root
           compute intervals from n
        */

        tone_vec_t const& tv = chord_vectorize(board, s);
        if (!tv.size())
            return semitone_seq_seq_t(); ///

        semitone_seq_t rv;
        for (std::size_t i = 0; i < tv.size(); ++i)
        {
            if (tv[i]) rv.push_back(i);
        }

        semitone_seq_seq_t res;
        auto const rvs = rv.size();
        for (std::size_t i = 0; i < rvs; ++i)
        {
            // take i as root
            semitone_seq_t v;
            v.reserve(rvs);
            v.push_back(0);
            for (std::size_t j = i+1; j < rvs+i; ++j)
            {
                auto a = rv[j%rvs] - rv[i];
                if (a < 0) a += 12;
                v.push_back(a);
            }
            res.push_back(v);
        }
        return res;
    }



}
