/*!
 * @author Nick Kidd
 */

#include "wali/Common.hpp"
#include "wali/wfa/State.hpp"

namespace wali
{
    namespace wfa
    {

        int State::numStates = 0;

        State::State( wali_key_t key, sem_elem_t W ) :
            Countable(true),name(key),se(W),delta(W)
        {
            assert( W.is_valid() );
            quasi = W->zero();
            {
                // TODO : R
                std::cerr << "State(...) : " << ++numStates << std::endl;;
            }
        }

        State::~State()
        {
            {
                // TODO : R
                std::cerr << "~State()   : " << --numStates << std::endl;;
            }
        }

        std::ostream & State::print( std::ostream & o ) const
        {
            o << "State[ name=\"" << name << "\" W=\"";
            o << se->to_string() << "\" ]";
            return o;
        }

        void State::add_trans( Trans * t )
        {
            // assert( t->from() == this->name );
            trans_ls.push_back( t );
        }

        void State::add_rev_trans( Trans * t )
        {
            rev_trans_ls.push_back(t);
        }

    } // namespace wfa

} // namespace wali

/* Yo, Emacs!
   ;;; Local Variables: ***
   ;;; tab-width: 4 ***
   ;;; End: ***
 */
