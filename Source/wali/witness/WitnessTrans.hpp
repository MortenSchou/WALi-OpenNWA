#ifndef wali_wfa_TRANS_WITNESS_GUARD
#define wali_wfa_TRANS_WITNESS_GUARD 1

/*!
 * @author Nick Kidd
 */

#include "wali/Common.hpp"
#include "wali/witness/Witness.hpp"
#include "wali/wfa/Trans.hpp"

namespace wali
{
    using wfa::Trans;

    namespace witness
    {

        /*!
         * @class WitnessTrans
         *
         * This class bears witness to the fact that a weight comes from a
         * transition, most likely user supplied as in the input WFA to
         * pre/poststar
         */
        class WitnessTrans : public Witness
        {
            public:
                /*!
                 * @brief constructor
                 *
                 * Creates a WitnessTrans. Copies information from trans_t
                 * excluding the weight, which it passes to its parent class
                 * Witness. This class should be kept in sync with reference
                 * counting of transitions, namely if it is changed that WFA
                 * uses reference counting then the contructor should reflect
                 * that. Local copies of the Trans object are made so that a
                 * cycle is not created b/c cycles render reference counting
                 * useless.
                 *
                 * @see Witness
                 * @see Trans
                 * @see sem_elem_t
                 * @see WFA
                 */
                WitnessTrans( const Trans& t );

                /*!
                 * Destructor does nothing.
                 */
                ~WitnessTrans();

                /*!
                 * Override Witness::accept
                 */
                virtual void accept( Visitor& v );

                /*!
                 * Overrides Witness::prettyPrint
                 */
                virtual std::ostream& prettyPrint( std::ostream& o,size_t depth ) const;

                const Trans& getTrans() const;

            protected:
                Trans t;

        }; // class WitnessTrans

    } // namespace witness

} // namespace wali

#endif  // wali_wfa_TRANS_WITNESS_GUARD

/* Yo, Emacs!
;;; Local Variables: ***
;;; tab-width: 4 ***
;;; End: ***
*/
