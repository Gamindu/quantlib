
/*
 * Copyright (C) 2000-2001 QuantLib Group
 *
 * This file is part of QuantLib.
 * QuantLib is a C++ open source library for financial quantitative
 * analysts and developers --- http://quantlib.sourceforge.net/
 *
 * QuantLib is free software and you are allowed to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of it under the conditions stated
 * in the QuantLib License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You should have received a copy of the license along with this file;
 * if not, contact ferdinando@ametrano.net
 * The license is also available at http://quantlib.sourceforge.net/LICENSE.TXT
 *
 * The members of the QuantLib Group are listed in the Authors.txt file, also
 * available at http://quantlib.sourceforge.net/Authors.txt
*/

/*! \file symmetricschurdecomposition.hpp
    \brief Eigenvalues / eigenvectors of a real symmetric matrix

    $Id$
*/

// $Source$
// $Log$
// Revision 1.7  2001/07/13 14:29:08  sigmud
// removed a few gcc compile warnings
//
// Revision 1.6  2001/06/22 16:38:15  lballabio
// Improved documentation
//
// Revision 1.5  2001/06/05 09:35:13  lballabio
// Updated docs to use Doxygen 1.2.8
//
// Revision 1.4  2001/05/24 15:38:08  nando
// smoothing #include xx.hpp and cutting old Log messages
//

#ifndef quantlib_math_jacobi_decomposition_h
#define quantlib_math_jacobi_decomposition_h

#include "ql/Math/matrix.hpp"

namespace QuantLib {

    namespace Math {

        //! symmetric threshold Jacobi algorithm.
        /*! Given a real symmetric matrix S, the Schur decomposition
            finds the eigenvalues and eigenvectors of S. If D is the
            diagonal matrix formed by the eigenvalues and U the
            unitarian matrix of th eigenvector we can write the
            Schur decomposition as
            \f[ S = U \cdot D \cdot U^T \, ,\f]
            where \f$ \cdot \f$ is the standard matrix product
            and  \f$ ^T  \f$ is the transpose operator.
            This class implements the Schur decomposition using the
            symmetric threshold Jacobi algorithm. For details on the
            different Jacobi transfomations you can start from the great book
            on matrix computations by Golub and Van Loan: Matrix computation,
            second edition The Johns Hopkins University Press
        */
        class SymmetricSchurDecomposition {
          public:
            /* \pre s must be symmetric */
            SymmetricSchurDecomposition(Matrix &s);
            Array eigenvalues() const;
            Matrix eigenvectors() const;
          private:
            Matrix s_;
            int size_;
            mutable Array diagonal_;
            mutable Matrix eigenVectors_;
            mutable bool hasBeenComputed_;
            int maxIterations_;
            double epsPrec_;
            void compute() const;
            void jacobiRotate(Matrix & m, double rot, double dil,
                int j1, int k1, int j2, int k2) const;
        };


        // inline definitions
        
        inline Array SymmetricSchurDecomposition::eigenvalues() const{
            if(!hasBeenComputed_)
                compute();
            return diagonal_;
        }

        inline Matrix SymmetricSchurDecomposition::eigenvectors() const{
            if(!hasBeenComputed_)
                compute();
            return eigenVectors_;
        }

        //! This routines implements the Jacobi, a.k.a. Givens, rotation
        inline void SymmetricSchurDecomposition::jacobiRotate(Matrix &m,
              double rot, double dil, int j1, int k1, int j2, int k2) const{

            double x1, x2;
            x1 = m[j1][k1];
            x2 = m[j2][k2];
            m[j1][k1] = x1 - dil*(x2 + x1*rot);
            m[j2][k2] = x2 + dil*(x1 - x2*rot);
        }

    }

}

#endif


