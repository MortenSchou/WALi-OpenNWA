#ifndef wali_witness_WITNESS_MERGE_FN_GUARD
#define wali_witness_WITNESS_MERGE_FN_GUARD 1

/*!
 * @author Nick Kidd
 */

#include "wali/Common.hpp"
#include "wali/SemElem.hpp"

#include "wali/wpds/ewpds/MergeFunction.hpp"

namespace wali {

    namespace witness {

        class WitnessMergeFn;

        typedef ref_ptr<WitnessMergeFn> witness_merge_fn_t;

        class WitnessMergeFn : public wpds::ewpds::MergeFn {
            public:
                typedef wpds::ewpds::merge_fn_t merge_fn_t;

            public:
                WitnessMergeFn( merge_fn_t user_merge );

                virtual ~WitnessMergeFn();

                virtual sem_elem_t apply_f( sem_elem_t w1, sem_elem_t w2);

                virtual std::ostream& print( std::ostream& o ) const;

            protected:
                sem_elem_t priv_do_apply( sem_elem_t w1,sem_elem_t w2 );

            protected:
                merge_fn_t user_merge;

        }; // class WitnessMergeFn

    } // namespace witness

} // namespace wali

#endif  // wali_witness_WITNESS_MERGE_FN_GUARD

/* Yo, Emacs!
   ;;; Local Variables: ***
   ;;; tab-width: 4 ***
   ;;; End: ***
*/

