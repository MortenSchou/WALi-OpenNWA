/*!
 * @author Nick Kidd
 */

#include "wali/Common.hpp"
#include "wali/SemElemPair.hpp"
#include "wali/wfa/WeightMaker.hpp"

namespace wali
{
    namespace wfa
    {
        sem_elem_t KeepLeft::make_weight( sem_elem_t lhs, sem_elem_t rhs ATTR_UNUSED )
        {
            return lhs;
        }

        sem_elem_t KeepBoth::make_weight( sem_elem_t lhs, sem_elem_t rhs )
        {
            return new SemElemPair(lhs,rhs);
        }

    } // namespace wfa

} // namespace wali

/* Yo, Emacs!
   ;;; Local Variables: ***
   ;;; tab-width: 4 ***
   ;;; End: ***
*/
