#include <necktar/necktar.hpp>
#include <necktar/cli/cli.hpp>

using namespace necktar;

int main()
{
    cli::cursor_hider ch;
    cli::cls();

    // ah the guitar..
    // could be Suhr or Fender.
    // gonna be a terminal for now ;)
    cli::luthier luth{std::cout};

    // i just want the standard 6 strings man!
    // E A D G B E tuning. 21 frets.
    fretboard board{{note::E,note::A,note::D,note::G,note::B,note::E}};

    // hey prof, you gonna use my guitar
    professor<decltype(luth)> prof{luth, board};

    // and show me where you put your fingers
    // for, say, the major scale in the key of C
    // and explain me the intervals please!
    prof.show({note::C, {1,2,3,4,5,6,7}});

    cli::anykey();

    // got it prof! major in key of C i knew it!
    prof.ok_done();

    // what about the natural minor in the key of E
    prof.show({note::E, {1,2,3_b,4,5,6_b,7_b}});

    // hey prof we should stack layers and see
    // the common notes for my solo over that progression.
    // dude.. it's gonna be another time

    cli::anykey();
    cli::cls();
}
