// @HEADER
// ***********************************************************************
//
//                    Teuchos: Common Tools Package
//                 Copyright (2004) Sandia Corporation
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
// Questions? Contact Michael A. Heroux (maherou@sandia.gov)
//
// ***********************************************************************
// @HEADER

#ifndef TEUCHOS_STANDARD_CATCH_MACROS_HPP
#define TEUCHOS_STANDARD_CATCH_MACROS_HPP

#include "Teuchos_GlobalMPISession.hpp"
#include "Teuchos_FancyOStream.hpp"
#include "Teuchos_TypeNameTraits.hpp"
#include "Teuchos_stacktrace.hpp"
#include "Teuchos_Assert.hpp"


#ifdef HAVE_TEUCHOS_STACKTRACE
#  define TEUCHOS_GET_STORED_STACKTRACE() \
  (Teuchos::TestForException_getEnableStacktrace() \
    ? Teuchos::get_stored_stacktrace() + "\n" \
    : std::string() )
#else
#  define TEUCHOS_GET_STORED_STACKTRACE() ""
#endif


/** \brief Implementation of TEUCHOS_STANDARD_CATCH_STATEMENTS(...) that
 * allows toggle of showing stack trace.
 */
#define TEUCHOS_STANDARD_CATCH_STATEMENTS_IMPL(VERBOSE, ERR_STREAM, \
  SHOW_STACK_TRACE, SUCCESS_FLAG \
  ) \
  catch (const std::exception &excpt) { \
    if((VERBOSE)) { \
      std::ostringstream oss; \
      oss \
        << "\np="<<::Teuchos::GlobalMPISession::getRank() \
        <<": *** Caught standard std::exception of type \'" \
        <<Teuchos::concreteTypeName(excpt)<<"\' :\n\n"; \
      Teuchos::OSTab scsi_tab(oss); \
      if (SHOW_STACK_TRACE) { \
        scsi_tab.o() << TEUCHOS_GET_STORED_STACKTRACE(); \
      } \
      scsi_tab.o() << excpt.what() << std::endl; \
      (ERR_STREAM) << std::flush; \
      (ERR_STREAM) << oss.str(); \
      (SUCCESS_FLAG) = false; \
    } \
  } \
  catch (const int &excpt_code) { \
    if((VERBOSE)) { \
      std::ostringstream oss; \
      oss \
        << "\np="<<::Teuchos::GlobalMPISession::getRank() \
        << ": *** Caught an integer exception with value = " \
        << excpt_code << std::endl; \
      (ERR_STREAM) << std::flush; \
      (ERR_STREAM) << oss.str(); \
      (SUCCESS_FLAG) = false; \
    } \
  } \
  catch ( ... ) { \
    if ((VERBOSE)) { \
      std::ostringstream oss; \
      oss << "\np="<<::Teuchos::GlobalMPISession::getRank() \
          <<": *** Caught an unknown exception\n"; \
      (ERR_STREAM) << std::flush; \
      (ERR_STREAM) << oss.str(); \
      (SUCCESS_FLAG) = false; \
    } \
  }



/** \brief Simple macro that catches and reports standard exceptions and other
 * exceptions.
 *
 * \ingroup teuchos_language_support_grp
 *
 * This macro should be used to write simple <tt>main()</tt> program functions
 * wrapped in a try statement as:

 \code

 int main(...)
 {
   bool verbose = true;
   bool success = true;
   try {
     ...
   }
   TEUCHOS_STANDARD_CATCH_STATEMENTS(verbose, std::cerr, success);
   return ( success ? EXIT_SUCCESS : EXIT_FAILURE );
 }
 \endcode
 *
 * NOTE: This macro will print out stacktraces generated by exceptions thrown
 * with the TEUCHOS_TEST_FOR_EXCEPTION() family of macros (see the main doc
 * page for details).
 */
#define TEUCHOS_STANDARD_CATCH_STATEMENTS(VERBOSE, ERR_STREAM, SUCCESS_FLAG) \
  TEUCHOS_STANDARD_CATCH_STATEMENTS_IMPL(VERBOSE, ERR_STREAM, true, SUCCESS_FLAG)


#endif // TEUCHOS_STANDARD_CATCH_MACROS_HPP
