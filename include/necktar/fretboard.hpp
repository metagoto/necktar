#pragma once

#include <necktar/data.hpp>


namespace necktar
{


    struct fretboard
    {

        fretboard(note_seq_t tuning = stdtuning, size_t fret_count = 21)
            : tuning_(std::move(tuning))
            , fret_count_(fret_count)
        { }

        note_seq_t const& tuning() const
        {
            return tuning_;
        }

        void tuning(note_seq_t tuning)
        {
            tuning_ = std::move(tuning);
        }

        size_t string_count() const
        {
            return tuning_.size();
        }

        size_t fret_count() const
        {
            return fret_count_;
        }

    private:

        note_seq_t tuning_;
        size_t fret_count_;
    };


}
