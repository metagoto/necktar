#pragma once

#include <necktar/fretboard.hpp>
#include <necktar/layer.hpp>

namespace necktar { namespace cli
{

    // pure shit for now
    inline void display(fretboard const& board, pos_seq_seq_t const& s)
    {

        auto& o = std::cout;
        for (size_t i = 0; i < board.string_count(); ++i)
        {
            auto const& t = s[i];
            pos_t k = 0;
            for (size_t j = 0; j <= board.fret_count(); ++j)
            {
                pos_t u = t[k];
                if (u == j) {
                    o << "o";
                    ++k;
                } else {
                    o << " ";
                }

                o << "|";
                if (j == 0)
                    o << "|";
            }
            o << "\n";
        }
        o << std::endl;
    }


    template<typename T>
    std::ostream& operator<<(std::ostream& os, std::vector<T> const& l)
    {
        os << "[";
        for (auto n : l) {
            os << n << ",";
        }
        return os << "]" << std::endl;
    }

} }
