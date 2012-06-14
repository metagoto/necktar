#pragma once

#include <necktar/fretboard.hpp>
#include <necktar/cli/primitive.hpp>


namespace necktar { namespace cli
{

    struct luthier
    {

        luthier(std::basic_ostream<char>& os)
            : os_(os)
        { }


        void draw(fretboard const& board)
        {
            auto sc = board.string_count();
            auto fc = board.fret_count();

            rlutil::setColor(1);
            draw_vline_b(os_, fret_gap_+offset_x_, offset_y_+1, sc*string_gap_-1);
            for (size_t i = 2; i <= fc+1; ++i)
            {
                draw_vline(os_, i*fret_gap_+offset_x_, offset_y_+1, sc*string_gap_-1);
            }

            rlutil::setColor(0);
            for (size_t j = 0; j < sc; ++j)
            {
                draw_hline(os_, offset_x_, j*string_gap_+offset_y_+1, (fc+1)*fret_gap_+1);
            }
        }


        void draw_note(pos_t string, pos_t fret, char const* c = "®", int color = 15)
        {
            pos_t x = (fret+1)*fret_gap_+offset_x_ - fret_gap_/2;
            pos_t y = string*string_gap_+offset_y_+1;

            rlutil::setColor(color);
            rlutil::locate(x, y);
            os_ << c;
        }


        void clear()
        {
            cli::cls();
        }


    private:
        std::basic_ostream<char>& os_;


#define NECKTAR_PROP(type, prop, def) \
    private: type prop##_ = def; \
    public: \
        type prop() const { return prop##_; } \
        void prop(type v) { prop##_ = v; }

        NECKTAR_PROP(pos_t, offset_x, 1)
        NECKTAR_PROP(pos_t, offset_y, 1)
        NECKTAR_PROP(pos_t, fret_gap, 4)
        NECKTAR_PROP(pos_t, string_gap, 2)
#undef NECKTAR_PROP

    };


} }
