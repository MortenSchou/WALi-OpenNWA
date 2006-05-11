#ifndef wali_wfa_TRANSSET_GUARD
#define wali_wfa_TRANSSET_GUARD 1

/*!
 * @author Nick Kidd
 */

#include "wali/Common.hpp"
#include "wali/Printable.hpp"
#include "wali/wfa/Trans.hpp"

#define IMPL_LIST 0

#if IMPL_LIST
#   include <list>
#else
#   include <set>
#endif


namespace wali
{
    namespace wfa
    {
        class TransFunctor;
        class ConstTransFunctor;

        /*!
         * @class TransSet
         *
         * This class basically wraps the std::set implementation
         * to provide a "wali::Key friendly" interface.
         */
        class TransSet : public Printable
        {
            public:
#if IMPL_LIST
                typedef std::list< Trans* > impl_t;
#else
                typedef std::set< Trans*,TransLT > impl_t;
#endif
                typedef impl_t::iterator iterator;
                typedef impl_t::const_iterator const_iterator;

            public:
                TransSet() {}

                ~TransSet() {}

            public:
                Trans* erase( Trans* t );

                Trans* erase( Key from, Key stack, Key to );

                iterator find( Key from, Key stack, Key to );

                iterator find( Trans* t );

                const_iterator find( Key from, Key stack, Key to ) const;

                const_iterator find( Trans* t ) const;

                void each( TransFunctor& tf );

                void each( ConstTransFunctor& tf ) const;

                bool insert( Trans* t );

                std::ostream& print( std::ostream& o ) const;

                void erase( iterator it ) {
                    impl.erase( it );
                }

                void clear() {
                    impl.clear();
                }

                bool empty() const {
                    return impl.empty();
                }

                void clearAndReleaseResources() {
                    impl_t tmp;
                    tmp.swap(impl);
                }

                iterator begin() {
                    return impl.begin();
                }

                iterator end() {
                    return impl.end();
                }

                const_iterator begin() const {
                    return impl.begin();
                }

                const_iterator end() const {
                    return impl.end();
                }

            protected:
                impl_t impl;

        }; // class TransSet

    } // namespace wfa

} // namespace wali

#endif  // wali_wfa_TRANSSET_GUARD

/* Yo, Emacs!
   ;;; Local Variables: ***
   ;;; tab-width: 4 ***
   ;;; End: ***
*/

