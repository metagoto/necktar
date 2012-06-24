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
            if (d < 0) d += 12;
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
            if (d < 0) d += 12;
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


    inline note note_at(fretboard const& board, pos_t string_num, pos_t fret_num)
    {
        if (string_num > board.string_count() || fret_num > board.fret_count())
            return note::NAFN;

        note n = board.tuning()[string_num];
        return static_cast<note>((n+fret_num)%12);
    }


}
