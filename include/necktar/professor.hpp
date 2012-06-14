#pragma once

#include <necktar/fretboard.hpp>
#include <necktar/layer.hpp>

namespace necktar
{


    inline pos_seq_seq_t distribute(fretboard const& board, note n)
    {
        pos_seq_seq_t s;

        if (n == note::NAFN)
            return s;

        s.reserve(board.string_count());
        for (size_t i = 0; i < board.string_count(); ++i)
        {
            note t = board.tuning()[i];
            pos_seq_t l;
            for (size_t j = 0; j <= board.fret_count(); ++j)
            {
                if ((t+j)%12 == (size_t)n)
                    l.push_back(j);
            }
            s.push_back(l);
        }
        return s;
    }


    inline pos_seq_seq_t distribute(fretboard const& board, layer const& layer)
    {
        pos_seq_seq_t s;

        note root = layer.tonality();

        if (root == note::NAFN)
            return s;

        s.reserve(board.string_count());
        for (size_t i = 0; i < board.string_count(); ++i)
        {
            note t = board.tuning()[i];
            pos_seq_t l;
            note_base_t d = t - root;
            if (d < 0)
                d += 12;
            for (size_t j = 0; j <= board.fret_count(); ++j)
            {
                pos_t k = (j+d)%12;
                if (layer.scale_vec()[k] == 1)
                    l.push_back(j);
            }
            s.push_back(l);
        }
        return s;
    }


    inline pack_seq_seq_t pack_distribute(fretboard const& board, layer const& layer)
    {
        pack_seq_seq_t s;

        note root = layer.tonality();

        if (root == note::NAFN)
            return s;

        s.reserve(board.string_count());
        for (size_t i = 0; i < board.string_count(); ++i)
        {
            note t = board.tuning()[i];
            pack_seq_t l;
            note_base_t d = t - root;
            if (d < 0)
                d += 12;
            for (size_t j = 0; j <= board.fret_count(); ++j)
            {
                pos_t k = (j+d)%12;
                if (layer.scale_vec()[k] == 1) {
                    l.push_back(std::make_tuple(j, (note)k, (signed)k));
                }
            }
            s.push_back(l);
        }
        return s;
    }


    ///
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
