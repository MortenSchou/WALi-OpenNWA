#ifndef wali_KEY_FACTORY_GUARD
#define wali_KEY_FACTORY_GUARD 1

/**
 * @author Nicholas Kidd
 */

#include "wali/Common.hpp"
#include "wali/HashMap.hpp"
#include "wali/KeySource.hpp"   //! defines hm_hash<wali::KeySource*>
#include <vector>

namespace wali
{
  /**
   * @class KeySpace
   */
  class KeySpace
  {
    public:
      KeySpace() {}

      ~KeySpace();

      /**
       * get_key returns the unique wali::Key associated with the
       * KeySource* ks. If no such key exists, a new wali::Key will be
       * generated.
       *
       * @see KeySource
       * @see wali::Key
       *
       * @param KeySource* ks for which a key is sought
       * @return wali::Key associated with parameter KeySource
       */
      wali::Key getKey( KeySource* ks );

      /**
       * Wrapper method for createing a StringSource and
       * inserting it into the KeySpace
       */
      wali::Key getKey( const std::string& s );

      /**
       * Wrapper method for createing a StringSource and
       * inserting it into the KeySpace
       */
      wali::Key getKey( const char* s );

      /**
       * Wrapper method for createing a IntSource and
       * inserting it into the KeySpace
       */
      wali::Key getKey( int i );

      /**
       * Wrapper method for createing a KeyPairSource and
       * inserting it into the KeySpace
       */
      wali::Key getKey( wali::Key k1, wali::Key k2 );

      /**
       * getKeySource retrieves the KeySource* associated to the
       * wali::Key key. If no such KeySource exists, then a NULL
       * pointer (0) is returned.
       *
       * @see KeySource
       * @see wali::Key
       *
       * @param key whose correpsonding KeySource* is desired
       * @return KeySource* associated with parameter key
       */
      KeySource* getKeySource( wali::Key key );

      /**
       * Reset the KeySpace. Clears all keys and deletes
       * all KeySources
       */
      void clear();

      /**
       * Return the number of allocated keys
       */
      size_t size();

      /**
       * Helper method that looks up the key and calls KeySource::print
       *
       * @see KeySource
       */
      std::ostream& printKey( std::ostream& o, wali::Key key );

      /**
       * Return std::string rep of KeySource. Looks up the key and calls
       * KeySource::to_string(). 
       *
       * @see KeySource
       */
      std::string key2str( wali::Key key );

    protected:
      typedef wali::HashMap< KeySource*, wali::Key > ks_hash_map_t;
      typedef std::vector< KeySource* > ks_vector_t;

      /** 
       * keymap maps KeySource* to wali::Key. The wali::Key is
       * an index into the vector values
       */
      ks_hash_map_t keymap;

      /**
       * wali::Key's are guaranteed to be unique w.r.t. this KeySpace
       * because they are indexes into the vector values. KeySource's
       * are retrieved by a lookup into values
       */
      ks_vector_t values;

  }; // class KeySpace

} // namespace wali

#endif  // wali_KEY_FACTORY_GUARD

