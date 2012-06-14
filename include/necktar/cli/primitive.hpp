#pragma once

#include <rlutil/rlutil.h>


namespace necktar { namespace cli
{

    template<typename T>
    inline void draw_hline(T& os, pos_t x, pos_t y, pos_t len, char const* c = "─")
    {
        auto s = x + len;
        for (pos_t i = x; i < s; ++i)
        {
            rlutil::locate(i, y);
            os << c;
        }
    }


    template<typename T>
    inline void draw_vline(T& os, pos_t x, pos_t y, pos_t len, char const* c = "│")
    {
        auto s = y + len;
        for (pos_t i = y; i < s; ++i)
        {
            rlutil::locate(x, i);
            os << c;
        }
    }


    template<typename T>
    inline void draw_vline_b(T& os, pos_t x, pos_t y, pos_t len, char const* c = "┃")
    {
        draw_vline(os, x, y, len, c);
    }


    ///
    typedef rlutil::CursorHider cursor_hider;

    inline void cls()
    {
        rlutil::cls();
    }

    inline void anykey()
    {
        rlutil::anykey();
    }


    ///
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
