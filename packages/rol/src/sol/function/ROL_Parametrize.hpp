// @HEADER
// ************************************************************************
//
//               Rapid Optimization Library (ROL) Package
//                 Copyright (2014) Sandia Corporation
//
// Under terms of Contract DE-AC04-94AL85000, there is a non-exclusive
// license for use of this work by or on behalf of the U.S. Government.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact lead developers:
//              Drew Kouri   (dpkouri@sandia.gov) and
//              Denis Ridzal (dridzal@sandia.gov)
//
// ************************************************************************
// @HEADER

/** @ingroup stochastic_group
    \class ROL::Parametrize
    \brief Provides the mix-in interface for making objects parametrized.

    ROL::Parametrize is used to make ROL::Objective's and
    ROL::EqualityConstraint's parametrized.  ROL::Parametrize contains a single
    parameter (std::vector) and has methods for setting and getting the
    parameter.  By using a mix-in (multiple inheritence) to define class such as
    ROL::ParametrizedObjective_SimOpt and
    ROL::ParametrizedEqualityConstraint_SimOpt we avoid diamond interitance.
*/

#ifndef ROL_PARAMETRIZE_HPP
#define ROL_PARAMETRIZE_HPP

namespace ROL {

template<class Real>
class Parametrize {
private:
  std::vector<Real> param_;

protected:
  /** \brief Return the parameter.
  */
  const std::vector<Real> getParameter(void) const {
    return param_;
  }

public:
  virtual ~Parametrize(void) {}
  /** \brief Set the parameter.

      @param[in] param is a user-provided parameter

      The internal storage copies the input.
  */
  virtual void setParameter(const std::vector<Real> &param) {
    param_.assign(param.begin(),param.end());
  }
};

}

#endif
