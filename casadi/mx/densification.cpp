/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "densification.hpp"
#include "mx_tools.hpp"
#include <vector>
#include <sstream>

using namespace std;

namespace CasADi{

Densification::Densification(const MX& x){
  setDependencies(x);
  setSparsity(CRSSparsity(x.size1(),x.size2(),true));
}

Densification* Densification::clone() const{
  return new Densification(*this);
}

void Densification::print(std::ostream &stream, const std::vector<std::string>& args) const{
  stream << "dense(" << args.at(0) << ")";
}

void Densification::evaluate(const DMatrixPtrV& input, DMatrixPtrV& output, const DMatrixPtrVV& fwdSeed, DMatrixPtrVV& fwdSens, const DMatrixPtrVV& adjSeed, DMatrixPtrVV& adjSens){
  int nfwd = fwdSens.size();
  int nadj = adjSeed.size();

  // Propate values
  input[0]->get(output[0]->data(),DENSE);
  
  // Propagate forward seeds
  for(int d=0; d<nfwd; ++d){
    fwdSeed[d][0]->get(fwdSens[d][0]->data(),DENSE);
  }

  // Propagate adjoint seeds
  for(int d=0; d<nadj; ++d){
    adjSens[d][0]->set(adjSeed[d][0]->data(),DENSE);
  }
}

void Densification::evaluateSX(const SXMatrixPtrV& input, SXMatrixPtrV& output, const SXMatrixPtrVV& fwdSeed, SXMatrixPtrVV& fwdSens, const SXMatrixPtrVV& adjSeed, SXMatrixPtrVV& adjSens){
  input[0]->get(output[0]->data(),DENSE);
}

void Densification::evaluateMX(const MXPtrV& input, MXPtrV& output, const MXPtrVV& fwdSeed, MXPtrVV& fwdSens, const MXPtrVV& adjSeed, MXPtrVV& adjSens, bool output_given){
  // Evaluate function
  if(!output_given){
    *output[0] = *input[0];
    makeDense(*output[0]);
  }
  
  // Propagate forward seeds
  int nfwd = fwdSens.size();
  for(int d=0; d<nfwd; ++d){
    *fwdSens[d][0] = *fwdSeed[d][0];
  }

  // Propagate adjoint seeds
  int nadj = adjSeed.size();
  for(int d=0; d<nadj; ++d){
    *adjSens[d][0] += *adjSeed[d][0];
  }
}


} // namespace CasADi

