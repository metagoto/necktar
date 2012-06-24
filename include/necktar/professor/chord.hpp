#pragma once

#include <necktar/fretboard.hpp>
#include <necktar/layer.hpp>

namespace necktar
{

    namespace
    {
        typedef std::tuple<std::vector<int>, tone_vec_t> chord_vec_info_t;

        inline chord_vec_info_t
        chord_vectorize(fretboard const& board, string_pos_seq_t const& s)
        {
            std::vector<int> string_index(board.string_count(), -1);
            tone_vec_t note_vec(12, 0);
            for (auto const& sp : s)
            {
                auto const& sn = std::get<0>(sp);
                auto const& fn = std::get<1>(sp);

                note n = note_at(board, sn, fn);
                if (n == note::NAFN)
                    return chord_vec_info_t();

                string_index[sn] = n;
                note_vec[n] = 1;
            }
            return std::make_tuple(string_index, note_vec);
        }
    }


    inline semitone_seq_seq_t
    which_chords(fretboard const& board, string_pos_seq_t const& s)
    {
        /*
         for each string_pos_seq
           find note
           construct tone_vec_t N of notes
         for each n in N
           take note n as root
           compute intervals from n
        */

        auto const& cv = chord_vectorize(board, s);

        auto const& iv = std::get<0>(cv);
        auto const& tv = std::get<1>(cv);

        if (!tv.size())
            return semitone_seq_seq_t(); ///

        semitone_seq_t rv;
        for (auto i = 0u; i < tv.size(); ++i)
        {
            if (tv[i]) rv.push_back(i);
        }

        semitone_seq_seq_t res(iv.size());

        auto const rvs = rv.size();
        for (auto k = 0u; k < iv.size(); ++k)
        {
            auto n = iv[k];
            if (n < 0)
                continue;

            auto i = unsigned(std::find(std::begin(rv), std::end(rv), n)
                              -std::begin(rv));
            semitone_seq_t v;
            v.reserve(rvs);
            v.push_back(0);
            for (auto j = i+1; j < rvs+i; ++j)
            {
                auto a = rv[j%rvs] - rv[i];
                if (a < 0) a += 12;
                v.push_back(a);
            }

            res[k] = v;
        }
        return res;
    }

}
