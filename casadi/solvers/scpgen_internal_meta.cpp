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


      #include "scpgen_internal.hpp"
      #include <string>

      const std::string casadi::SCPgenInternal::meta_doc=
      "\n"
"A structure-exploiting sequential quadratic programming (to be come\n"
"sequential convex programming) method for nonlinear programming.\n"
"\n"
"\n"
">List of available options\n"
"\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"|       Id        |      Type       |     Default     |   Description   |\n"
"+=================+=================+=================+=================+\n"
"| beta            | OT_REAL         | 0.800           | Line-search     |\n"
"|                 |                 |                 | parameter,      |\n"
"|                 |                 |                 | restoration     |\n"
"|                 |                 |                 | factor of       |\n"
"|                 |                 |                 | stepsize        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| c1              | OT_REAL         | 0.000           | Armijo          |\n"
"|                 |                 |                 | condition,      |\n"
"|                 |                 |                 | coefficient of  |\n"
"|                 |                 |                 | decrease in     |\n"
"|                 |                 |                 | merit           |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| codegen         | OT_BOOLEAN      | false           | C-code          |\n"
"|                 |                 |                 | generation      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| compiler        | OT_STRING       | \"gcc -fPIC -O2\" | Compiler        |\n"
"|                 |                 |                 | command to be   |\n"
"|                 |                 |                 | used for        |\n"
"|                 |                 |                 | compiling       |\n"
"|                 |                 |                 | generated code  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| hessian_approxi | OT_STRING       | \"exact\"         | gauss-          |\n"
"| mation          |                 |                 | newton|exact    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| lbfgs_memory    | OT_INTEGER      | 10              | Size of L-BFGS  |\n"
"|                 |                 |                 | memory.         |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_iter        | OT_INTEGER      | 50              | Maximum number  |\n"
"|                 |                 |                 | of SQP          |\n"
"|                 |                 |                 | iterations      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_iter_ls     | OT_INTEGER      | 1               | Maximum number  |\n"
"|                 |                 |                 | of linesearch   |\n"
"|                 |                 |                 | iterations      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| merit_memsize   | OT_INTEGER      | 4               | Size of memory  |\n"
"|                 |                 |                 | to store        |\n"
"|                 |                 |                 | history of      |\n"
"|                 |                 |                 | merit function  |\n"
"|                 |                 |                 | values          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| merit_start     | OT_REAL         | 0.000           | Lower bound for |\n"
"|                 |                 |                 | the merit       |\n"
"|                 |                 |                 | function        |\n"
"|                 |                 |                 | parameter       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| name_x          | OT_STRINGVECTOR | GenericType()   | Names of the    |\n"
"|                 |                 |                 | variables.      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| print_header    | OT_BOOLEAN      | true            | Print the       |\n"
"|                 |                 |                 | header with     |\n"
"|                 |                 |                 | problem         |\n"
"|                 |                 |                 | statistics      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| print_time      | OT_BOOLEAN      | true            | Print           |\n"
"|                 |                 |                 | information     |\n"
"|                 |                 |                 | about execution |\n"
"|                 |                 |                 | time            |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| print_x         | OT_INTEGERVECTO | GenericType()   | Which variables |\n"
"|                 | R               |                 | to print.       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| qp_solver       | OT_STRING       | GenericType()   | The QP solver   |\n"
"|                 |                 |                 | to be used by   |\n"
"|                 |                 |                 | the SQP method  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| qp_solver_optio | OT_DICTIONARY   | GenericType()   | Options to be   |\n"
"| ns              |                 |                 | passed to the   |\n"
"|                 |                 |                 | QP solver       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| reg_threshold   | OT_REAL         | 0.000           | Threshold for   |\n"
"|                 |                 |                 | the             |\n"
"|                 |                 |                 | regularization. |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| regularize      | OT_BOOLEAN      | false           | Automatic       |\n"
"|                 |                 |                 | regularization  |\n"
"|                 |                 |                 | of Lagrange     |\n"
"|                 |                 |                 | Hessian.        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tol_du          | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion for   |\n"
"|                 |                 |                 | dual            |\n"
"|                 |                 |                 | infeasability   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tol_pr          | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion for   |\n"
"|                 |                 |                 | primal          |\n"
"|                 |                 |                 | infeasibility   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tol_pr_step     | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion for   |\n"
"|                 |                 |                 | the step size   |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| tol_reg         | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion for   |\n"
"|                 |                 |                 | regularization  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"\n"
"\n"
">List of available monitors\n"
"\n"
"+-------------+\n"
"|     Id      |\n"
"+=============+\n"
"| dx          |\n"
"+-------------+\n"
"| eval_f      |\n"
"+-------------+\n"
"| eval_g      |\n"
"+-------------+\n"
"| eval_grad_f |\n"
"+-------------+\n"
"| eval_h      |\n"
"+-------------+\n"
"| eval_jac_g  |\n"
"+-------------+\n"
"| qp          |\n"
"+-------------+\n"
"\n"
"\n"
">List of available stats\n"
"\n"
"+------------+\n"
"|     Id     |\n"
"+============+\n"
"| iter_count |\n"
"+------------+\n"
"\n"
"\n"
"\n"
"\n"
;