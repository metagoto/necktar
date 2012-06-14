#pragma once

#include <tuple>
#include <vector>
#include <unordered_map>


namespace necktar
{

    typedef int note_base_t;
    typedef int semitone_t; // 0..11
    typedef unsigned int interval_t; // 1..7
    typedef char const* interval_char_t; // "1".."7"

    typedef std::vector<semitone_t> semitone_seq_t;
    typedef std::vector<interval_t> interval_seq_t;
    typedef std::vector<interval_char_t> interval_char_seq_t;

    typedef semitone_seq_t tone_vec_t;

    typedef unsigned int size_t;
    typedef unsigned int pos_t;
    typedef std::vector<pos_t> pos_seq_t;
    typedef std::vector<pos_seq_t> pos_seq_seq_t;

    enum note : note_base_t;
    typedef std::vector<note> note_seq_t;

    typedef std::tuple<pos_t, note, semitone_t> pack_t;
    typedef std::vector<pack_t> pack_seq_t;
    typedef std::vector<pack_seq_t> pack_seq_seq_t;

    enum note : note_base_t
    {
        C  = 0
       ,Cs = 1
       ,Db = 1
       ,D  = 2
       ,Ds = 3
       ,Eb = 3
       ,E  = 4
       ,F  = 5
       ,Fs = 6
       ,Gb = 6
       ,G  = 7
       ,Gs = 8
       ,Ab = 8
       ,A  = 9
       ,As = 10
       ,Bb = 10
       ,B  = 11
       ,NAFN = -1 // Not A Fucking Note
    };


    inline semitone_t semitone(char const* s)
    {
        static std::unordered_map<char const*, semitone_t> m
        {
             {"root",0}
            ,{"r",   0}
            ,{"R",   0}
            ,{"T",   0}
            ,{"1",   0}

            ,{"d2", 0}
            ,{"bb2",0}
            ,{"b2", 1}
            ,{"m2", 1}
            ,{"2",  2}
            ,{"M2", 2}
            ,{"A2", 3}
            ,{"#2", 3}

            ,{"d3", 2}
            ,{"bb3",2}
            ,{"b3", 3}
            ,{"m3", 3}
            ,{"3",  4}
            ,{"M3", 4}
            ,{"A3", 5}
            ,{"#3", 5}

            ,{"bb4",3}
            ,{"d4", 4}
            ,{"b4", 4}
            ,{"m4", 4}
            ,{"4",  5}
            ,{"P4", 5}
            ,{"M4", 5}
            ,{"A4", 6}
            ,{"#4", 6}

            ,{"bb5",5}
            ,{"d5", 6}
            ,{"b5", 6}
            ,{"m5", 6}
            ,{"5",  7}
            ,{"P5", 7}
            ,{"M5", 7}
            ,{"A5", 8}
            ,{"#5", 8}

            ,{"d6", 7}
            ,{"bb6",7}
            ,{"b6", 8}
            ,{"m6", 8}
            ,{"6",  9}
            ,{"M6", 9}
            ,{"A6", 10}
            ,{"#6", 10}

            ,{"d7", 9}
            ,{"bb7",9}
            ,{"b7", 10}
            ,{"m7", 10}
            ,{"7",  11}
            ,{"M7", 11}
            ,{"A7", 0}
            ,{"#7", 0}
        };

        return m.at(s); // may throw...
    }


    inline char const* note_str(note n, bool sharp = false)
    {
        static char const* NAFN = "";
        static char const* m[] =
        {
            "C"
           ,"Db"
           ,"D"
           ,"Eb"
           ,"E"
           ,"F"
           ,"Gb"
           ,"G"
           ,"Ab"
           ,"A"
           ,"Bb"
           ,"B"
        };

        // sharp...

        if (n == note::NAFN)
            return NAFN;
        return m[n];
    }


    inline char const* interval_str(semitone_t n/*, bool sharp = false*/)
    {
        static char const* NAFN = "";
        static char const* m[] =
        {
            "1"
           ,"b2"
           ,"2"
           ,"b3"
           ,"3"
           ,"4"
           ,"b5"
           ,"5"
           ,"b6"
           ,"6"
           ,"b7"
           ,"7"
        };

        // more intervals...

        if (n <0 || n > 11)
            return NAFN;
        return m[n];
    }


    namespace detail
    {
        constexpr int INTVDELTA = 0xff;

        constexpr semitone_t interval[] =
        //x  1  2  3  4  5  6  7
        { 0, 0, 2, 4, 5, 7, 9, 11};
    }

}
