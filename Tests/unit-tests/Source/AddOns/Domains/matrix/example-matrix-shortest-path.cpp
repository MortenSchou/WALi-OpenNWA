#include "gtest/gtest.h"

#include "wali/wpds/WPDS.hpp"
#include "wali/wfa/WFA.hpp"
#include "wali/witness/Witness.hpp"
#include "wali/witness/WitnessWrapper.hpp"
#include "wali/domains/matrix/Matrix.hpp"

#include "matrix-equal.hpp"

namespace wali {
namespace domains {

namespace {

const int inf = std::numeric_limits<MinPlusIntMatrix::value_type::value_type>::max();

struct Weights
{
    MinPlusIntMatrix::BackingMatrix
        bm_id,
        bm_initial,
        bm_loop,
        bm_step,
        bm_expected;

    ref_ptr<MinPlusIntMatrix>
        zero,
        id,
        initial,
        loop,
        step,
        expected;

    Weights()
        : bm_id(2,2)
        , bm_initial(2,2)
        , bm_loop(2,2)
        , bm_step(2,2)
        , bm_expected(2,2)
    {
        int m_id[2][2] = {
            {   0, inf},
            { inf,   0},
        };

        int m_initial[2][2] = {
            {   1, inf},
            { inf, inf},
        };

        int m_loop[2][2] = {
            {   1,   1},
            { inf,   1},
        };

        int m_step[2][2] = {
            {   1, inf},
            { inf,   1},
        };

        int m_expected[2][2] = {
            {   2,   3},
            { inf, inf},
        };

        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 2; ++j) {
                bm_id(i, j).set_value(m_id[i][j]);
                bm_initial(i, j).set_value(m_initial[i][j]);
                bm_loop(i, j).set_value(m_loop[i][j]);
                bm_step(i, j).set_value(m_step[i][j]);
                bm_expected(i, j).set_value(m_expected[i][j]);
            }
        }

        id       = new MinPlusIntMatrix(bm_id);
        initial  = new MinPlusIntMatrix(bm_initial);
        loop     = new MinPlusIntMatrix(bm_loop);
        step     = new MinPlusIntMatrix(bm_step);
        expected = new MinPlusIntMatrix(bm_expected);

        zero = dynamic_cast<MinPlusIntMatrix*>(id->zero().get_ptr());
    }
};

struct Keys
{
    Key start, loop, finish, p, acc;

    Keys()
        : start(getKey("start"))
        , loop(getKey("loop"))
        , finish(getKey("finish"))
        , p(getKey("p"))
        , acc(getKey("acc"))
    {}
};

struct WpdsWfa
{
    wpds::WPDS wpds;
    wfa::WFA wfa;

    Weights weights;
    Keys keys;

    WpdsWfa(ref_ptr<wpds::Wrapper> wrapper)
        : wpds(wrapper)
    {
        // WPDS for the following CFG:
        //
        //                     ___
        //                    /   \ <loop>
        //                    \   /
        // (start) --------> (loop) --------> (finish)
        //         <inital>         <step>
        //
        // <...> indicate the weight

        wpds.add_rule(keys.p, keys.start, keys.p, keys.loop,   weights.initial);
        wpds.add_rule(keys.p, keys.loop,  keys.p, keys.loop,   weights.loop);
        wpds.add_rule(keys.p, keys.loop,  keys.p, keys.finish, weights.step);

        // And the automaton for poststar:
        //
        //          (start) <id>
        //  (p) ----------------------> (acc)

        wfa.addState(keys.p,   weights.zero);
        wfa.addState(keys.acc, weights.zero);

        wfa.setInitialState(keys.p);
        wfa.addFinalState(keys.acc);

        wfa.addTrans(keys.p, keys.start, keys.acc, weights.id);
    }

    sem_elem_t
    poststar_finish_weight()
    {
        wfa::WFA ps_wfa = wpds.poststar(wfa);

        wfa::TransSet ts = ps_wfa.match(keys.p, keys.finish);

        if (ts.size() != 1) {
            return NULL;
        }
        else {
            return (*ts.begin())->weight();
        }
    }

    ref_ptr<MinPlusIntMatrix>
    poststar_finish_matrix()
    {
        return dynamic_cast<MinPlusIntMatrix*>(
            poststar_finish_weight().get_ptr());
    }
};

}


TEST(example$matrix$shortest$path, no$witness$gets$right$matrix)
{
    WpdsWfa f(NULL);
    ref_ptr<MinPlusIntMatrix> m = f.poststar_finish_matrix();

    ASSERT_TRUE(m.is_valid());

    EXPECT_EQ(m->matrix(), f.weights.bm_expected);
}


}
}

