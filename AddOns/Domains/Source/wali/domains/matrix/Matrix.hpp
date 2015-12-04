#ifndef WALI_DOMAINS_MATRIX_MATRIX_HPP
#define WALI_DOMAINS_MATRIX_MATRIX_HPP

#include "wali/domains/matrix/Matrix_template.hpp"
#include "wali/domains/matrix/MinPlus.hpp"
#include "wali/domains/matrix/SemElemWrapper.hpp"

namespace wali {
  namespace domains {

    typedef Matrix<bool> BoolMatrix;
    typedef Matrix<details::MinPlus<int> > MinPlusIntMatrix;
    typedef Matrix<details::SemElemWrapper> SemElemMatrix;

  }
}

// Yo, Emacs!
// Local Variables:
//   c-file-style: "ellemtel"
//   c-basic-offset: 2
// End:

#endif /* WALI_DOMAINS_MATRIX_HPP */
