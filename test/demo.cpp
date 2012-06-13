#include <gtest/gtest.h>

#include <necktar/necktar.hpp>
#include <necktar/cli_view.hpp>

using namespace necktar;
using necktar::cli::operator<<;
using std::cout;
using std::endl;


TEST(case_1, test_1)
{

    layer l1;

    EXPECT_EQ(l1.tonality(), note::NAFN);
    EXPECT_EQ(l1.scale().size(), 0);
    EXPECT_EQ(l1.scale_vec().size(), 0);

    l1.tonality(note::C);
    EXPECT_EQ(l1.tonality(), note::C);

    l1.scale({"T","2","3","4","5","6","7"});
    EXPECT_EQ(l1.scale().size(), 7);
    EXPECT_EQ(l1.scale_vec().size(), 12);

    l1.scale({1,2,3,4,5,6,7});
    EXPECT_EQ(l1.scale().size(), 7);
    EXPECT_EQ(l1.scale_vec().size(), 12);


    layer l2{note::A, {"T","2","3","4","5","6","7"}};

    EXPECT_EQ(l2.tonality(), note::A);
    EXPECT_EQ(l1.scale(), l2.scale());

    l1.scale({"T","2","b3","#4","5","b6","b7"});
    l2.scale({1,2,3_b,4_s,5,6_b,7_b});
    EXPECT_EQ(l1.scale(), l2.scale());
}


TEST(case_1, test_2)
{
    fretboard b1{{note::E,note::B,note::G,note::D,note::A,note::E}, 24};
    EXPECT_EQ(b1.tuning().size(), 6);
    EXPECT_EQ(b1.fret_count(), 24);

    b1.tuning({note::D,note::B,note::G,note::D,note::G,note::D});

    fretboard b2{{note::D,note::B,note::G,note::D,note::G,note::D}, 21};
    EXPECT_EQ(b1.tuning(), b2.tuning());
    EXPECT_NE(b1.fret_count(), b2.fret_count());
}


TEST(case_1, test_3)
{
    fretboard b1{{note::E,note::B,note::G,note::D,note::A,note::E}, 24};

    layer l1{note::C, {1,2,3,4,5,6,7}};
    layer l2{note::A, {1,2,3_b,4,5,6_b,7_b}}; // 6th tone, l1's relative minor

    EXPECT_EQ(distribute(b1, l1), distribute(b1, l2));

    l1.tonality(note::Cs);
    EXPECT_NE(distribute(b1, l1), distribute(b1, l2));

    l1.tonality(note::C);
    l2.scale({1,2,3,4_s,5,6,7}); // lydian
    l2.tonality(note::F); // 4th tone
    EXPECT_EQ(distribute(b1, l1), distribute(b1, l2));

    b1.tuning({note::G,note::D,note::G,note::D}); // bass in Open G!
    EXPECT_EQ(distribute(b1, l1), distribute(b1, l2));
}


TEST(case_1, test_4)
{
    fretboard b1{{note::E,note::B,note::G,note::D,note::A,note::E}, 24};

    layer l1{note::C, {1,2,3,4,5,6,7}};
    layer l2{note::A, {1,2,3_b,4,5,6_b,7_b}};

    cli::display(b1, distribute(b1, l1));
    cli::display(b1, distribute(b1, l2));

    l1.tonality(note::E);
    cli::display(b1, distribute(b1, l1));

}
