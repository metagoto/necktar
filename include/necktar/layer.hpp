#pragma once

#include <necktar/data.hpp>
#include <necktar/utility.hpp>


namespace necktar
{

    struct layer
    {
        layer()
            : tonality_(note::NAFN)
        {}

        layer(note tonality, interval_seq_t scale)
            : tonality_(tonality)
            , scale_(normalize(scale))
            , scale_vec_(vectorize(scale_))
        {}

        layer(note tonality, interval_char_seq_t scale)
            //: layer(tonality, normalize(scale))
            : tonality_(tonality)
            , scale_(normalize(scale))
            , scale_vec_(vectorize(scale_))
        {}


        note tonality() const
        {
            return tonality_;
        }

        void tonality(note tonality)
        {
            tonality_ = tonality;
        }

        semitone_seq_t const& scale() const
        {
            return scale_;
        }

        void scale(interval_seq_t scale)
        {
            scale_ = normalize(scale);
            scale_vec_ = vectorize(scale_);
        }

        void scale(interval_char_seq_t scale)
        {
            scale_ = normalize(scale);
            scale_vec_ = vectorize(scale_);
        }

        //
        tone_vec_t const& scale_vec() const
        {
            return scale_vec_;
        }

    private:
        note tonality_;
        semitone_seq_t scale_;
        tone_vec_t scale_vec_;
    };


}
