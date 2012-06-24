#pragma once

#include <algorithm>
#include <necktar/professor/distribute.hpp>
#include <necktar/professor/chord.hpp>


namespace necktar
{

    template<typename Luthier>
    struct professor
    {

        professor(Luthier& luthier, fretboard& board)
            : luthier_(luthier)
            , board_(board)
        { }


        void show(layer const& layer)
        {
            luthier_.draw(board_);
            auto const& m = pack_distribute(board_, layer);
            for (pos_t i = 0; i < m.size(); ++i)
            {
                for (pos_t j = 0; j < m[i].size(); ++j)
                {
                    auto const& z = m[i][j];
                    luthier_.draw_note(m.size()-i-1, std::get<0>(z)
                                       //,note_str(std::get<1>(z)));
                                       ,interval_str(std::get<2>(z))
                                       ,2+std::get<2>(z));
                }
            }
        }


        void ok_done()
        {
            luthier_.clear();
        }

        Luthier& luthier_;
        fretboard& board_;
    };


}
