// @HEADER
//
// ***********************************************************************
//
//        MueLu: A package for multigrid based preconditioning
//                  Copyright 2012 Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
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
// Questions? Contact
//                    Jonathan Hu       (jhu@sandia.gov)
//                    Andrey Prokopenko (aprokop@sandia.gov)
//                    Ray Tuminaro      (rstumin@sandia.gov)
//
// ***********************************************************************
//
// @HEADER
#ifndef PACKAGES_MUELU_SRC_REBALANCING_MUELU_CLONEREPARTITIONINTERFACE_DECL_HPP_
#define PACKAGES_MUELU_SRC_REBALANCING_MUELU_CLONEREPARTITIONINTERFACE_DECL_HPP_


#include <Xpetra_Map.hpp>
#include <Xpetra_Matrix.hpp>
#include <Xpetra_MapFactory_fwd.hpp>
#include <Xpetra_VectorFactory.hpp>
#include <Xpetra_BlockedCrsMatrix.hpp>

#include "MueLu_SingleLevelFactoryBase.hpp"

#include "MueLu_Level_fwd.hpp"
#include "MueLu_FactoryBase_fwd.hpp"
#include "MueLu_Graph_fwd.hpp"
#include "MueLu_AmalgamationFactory_fwd.hpp"
#include "MueLu_AmalgamationInfo_fwd.hpp"
#include "MueLu_Utilities_fwd.hpp"

namespace MueLu {

  /*!
    @class CloneRepartitionInterface
    @brief Helper class which transforms an "Partition" array generated from a block in a blocked operator to a new "Partition" vector for another compatible block in the blocked operator.

    This class is meant to be used with another {Zoltan,Zoltan2,Isorropia,...}Interface class which generates a "Partition" vector for a specific block to be rebalanced.
    This class reuses the rebalancing and creates a compatible "Partition" array for another block.

    @note This class is used for blocked operators only.

    ## Input/output of CloneRepartitionInterface ##

    ### User parameters of CloneRepartitionInterface ###
    Parameter | type | default | master.xml | validated | requested | description
    ----------|------|---------|:----------:|:---------:|:---------:|------------
    | A                                      | Factory | null  |   | * | * | Generating factory of the matrix A used during the prolongator smoothing process (must be of type SubBlockAFactory representing the corresponding diagonal block in the blocked operator) |
    | number of partitions                   | GO      | - |  | * | * | Short-cut parameter set by RepartitionFactory. Avoid repartitioning algorithms if only one partition is necessary (not used in this factory)
    | Partition | null |  | * | * | Factory generating the Partition array (e.g. ZoltanInterface) associated with the sub block in the blocked operator which partitioning information shall to be cloned

    The * in the @c master.xml column denotes that the parameter is defined in the @c master.xml file.<br>
    The * in the @c validated column means that the parameter is declared in the list of valid input parameters (see CloneRepartitionInterface::GetValidParameters).<br>
    The * in the @c requested column states that the data is requested as input with all dependencies (see CloneRepartitionInterface::DeclareInput).

    ### Variables provided by CloneRepartitionInterface ###

    After CloneRepartitionInterface::Build the following data is available (if requested)

    Parameter | generated by | description
    ----------|--------------|------------
    | Partition       | CloneRepartitionInterface   | GOVector based on the Row map of A (DOF-based) containing the process id the DOF should be living in after rebalancing/repartitioning

  */

  template <class Scalar = double, class LocalOrdinal = int, class GlobalOrdinal = LocalOrdinal, class Node = KokkosClassic::DefaultNode::DefaultNodeType>
  class CloneRepartitionInterface : public SingleLevelFactoryBase {

#undef MUELU_CLONEREPARTITIONINTERFACE_SHORT
#include "MueLu_UseShortNames.hpp"

  public:

    //! @name Constructors/Destructors
    //@{

    //! Constructor
    CloneRepartitionInterface() { }

    //! Destructor
    virtual ~CloneRepartitionInterface() { }
    //@}

    RCP<const ParameterList> GetValidParameterList() const;

    //! @name Input
    //@{
    void DeclareInput(Level & level) const;
    //@}

    //! @name Build methods.
    //@{
    void Build(Level &level) const;

    //@}



  private:



  };  //class CloneRepartitionInterface

} //namespace MueLu

#define MUELU_CLONEREPARTITIONINTERFACE_SHORT


#endif /* PACKAGES_MUELU_SRC_REBALANCING_MUELU_CLONEREPARTITIONINTERFACE_DECL_HPP_ */
