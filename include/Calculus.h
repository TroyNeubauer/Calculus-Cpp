/*

CALCULUS.H: PRIMARY HEADER FOR CALCULUS-CPP

Include this file in your application to leverage scientifc functional
manipulations.  This file contains declarations for all user types
intended to be used directly in user code.  It includes all relevant
headers to support the calculus-cpp framework.

A large number of overrides for <math.h> are supplied within this header 
to bridge the gap between more traditional code and that which leverages 
calculus-cpp.


* calculus-cpp: Scientific "Functional" Library
* http://calculus-cpp.sourceforge.net/
* 
* This software was developed at McGill University (Montreal, 2002) by
* Olivier Giroux in the course of his studies in Mechanical Engineering.
* It was presented, along with an accompanying paper, for credit in the fall
* of 2002.
*
* Calculus-cpp was not designed to prove a point or to serve as a formal
* framework within which exact solutions can be derived.  Instead it was
* created to fill the need for run-time functional constructions and to
* accomplish very real and tangible goals.  It remains your responsibility
* to use it properly - as much more sophisticated <math.h>, which allows
* functions to be treated as first-class objects.
*
* You are welcome to make any additions you feel are necessary.

COPYRIGHT AND PERMISSION NOTICE

Copyright (c) 2002, Olivier Giroux, <oliver@canada.com>.

All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without any restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, and/or sell copies of the
Software, and to permit persons to whom the Software is furnished to do so,
provided that the copyright notice(s) and this permission notice appear
in all copies of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN
NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE
LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY
DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Except as contained in this notice, the name of a copyright holder shall not
be used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization of the copyright holder.

THIS SOFTWARE INCLUDES THE NIST'S TNT PACKAGE (FOR USE WITH THE EXAMPLES FURNISHED)
AND THE "LEMON" LALR(1) PARSER GENERATOR.

THE FOLLOWING NOTICE APPLIES SOLELY TO THE TNT-->
* Template Numerical Toolkit (TNT): Linear Algebra Module
*
* Mathematical and Computational Sciences Division
* National Institute of Technology,
* Gaithersburg, MD USA
*
*
* This software was developed at the National Institute of Standards and
* Technology (NIST) by employees of the Federal Government in the course
* of their official duties. Pursuant to title 17 Section 105 of the
* United States Code, this software is not subject to copyright protection
* and is in the public domain. NIST assumes no responsibility whatsoever for
* its use by other parties, and makes no guarantees, expressed or implied,
* about its quality, reliability, or any other characteristic.
<--END NOTICE

THE FOLLOWING NOTICE APPLIES SOLELY TO LEMON-->
** Copyright (c) 1991, 1994, 1997, 1998 D. Richard Hipp
**
** This file contains all sources (including headers) to the LEMON
** LALR(1) parser generator.  The sources have been combined into a
** single file to make it easy to include LEMON as part of another
** program.
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public
** License as published by the Free Software Foundation; either
** version 2 of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** General Public License for more details.
** 
** You should have received a copy of the GNU General Public
** License along with this library; if not, write to the
** Free Software Foundation, Inc., 59 Temple Place - Suite 330,
** Boston, MA  02111-1307, USA.
**
** Author contact information:
**   drh@acm.org
**   http://www.hwaci.com/drh/
<--END NOTICE

*/
#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <iostream>
#include <Calculus_cpp.h>

class user_algebraic_operator
{
protected:
	calculus::algebraic_operator* m_pP;
public:    
    user_algebraic_operator() :  m_pP(NULL) { 
    }

    user_algebraic_operator(calculus::algebraic_operator * pP) : m_pP(pP) {
	    if (m_pP != NULL)
		    m_pP->addref();
    }
    user_algebraic_operator(const user_algebraic_operator &alg) : m_pP(alg.m_pP) {
	    if (m_pP != NULL)
		    m_pP->addref();
    }
    user_algebraic_operator(char* pscFunction) : m_pP(calculus::algebra_parser::get_service()->parse_to_algebra(pscFunction)) {
	    if (m_pP != NULL)
		    m_pP->addref();
    }
    user_algebraic_operator(double d) : m_pP(calculus::_cst(d)) {
	    if (m_pP != NULL)
		    m_pP->addref();
    }
    user_algebraic_operator::~user_algebraic_operator() {
	    if (m_pP != NULL)
		    m_pP->release();
    }

    calculus::algebraic_operator* operator->() const {
	    return m_pP;
    }
    bool operator==(const calculus::algebraic_operator* pP) const {
	    return (m_pP == pP);
    }

    bool operator!=(const calculus::algebraic_operator* pP) const {
	    return (m_pP != pP);
    }

    bool operator!() const {
	    return !m_pP ;
    }

    operator calculus::algebraic_operator*() const {
        return m_pP;
    }

    operator FUNCTION() const {
        return m_pP->compile();
    }

    double operator()(double * pxs) const {
        return m_pP->eval(pxs);
    }

    double operator()(double x,...) const {
	    double val = 0;
	    unsigned int uiNumberOfvariables = this->m_pP->get_number_of_variables();
	    va_list marker;
	    va_start(marker,x);
	    if (uiNumberOfvariables) {
		    double *pVars = new double[uiNumberOfvariables];
		    pVars[0] = x;
		    for(unsigned int i = 1;i < uiNumberOfvariables;i++)
			    pVars[i] = va_arg(marker,double);
		    va_end(marker);
            val = m_pP->eval(pVars);
		    delete [] pVars;
	    }
        else val = m_pP->eval(NULL);
	    return val;
    }
    inline std::ostream& operator<<(std::ostream &s) {
        if (!m_pP)
            return s;
        char * pBuffer = new char[m_pP->to_string(NULL)+1];
        m_pP->to_string(pBuffer);
        s << pBuffer;
        delete [] pBuffer;
        return s;
    }
    calculus::algebraic_operator * get_partial_derivative(calculus::variable* pvar)
    {
        return m_pP->get_partial_derivative(pvar);
    }
    user_algebraic_operator& operator=(const user_algebraic_operator& func) {
	    if (m_pP != NULL)
		    m_pP->release();
	    m_pP = func.m_pP;
	    if (m_pP != NULL)
		    m_pP->addref();
	    return *this;
    }
    user_algebraic_operator& operator=(calculus::algebraic_operator* func) {
	    if (m_pP != NULL)
		    m_pP->release();
	    m_pP = func;
	    if (m_pP != NULL)
		    m_pP->addref();
	    return *this;
    }	
};
typedef user_algebraic_operator Function;

class user_variable : public user_algebraic_operator
{
public:
    user_variable() : user_algebraic_operator() {	
    }

    user_variable(calculus::variable* pV) : 
        user_algebraic_operator(pV) {
    }

    user_variable(const char* scVarName) : 
        user_algebraic_operator(calculus::_var(scVarName)) {
    }

    user_variable(const user_variable& rSP) : 
        user_algebraic_operator(rSP) {
    }

    operator calculus::variable*() const {
	    return static_cast<calculus::variable*>(m_pP);
    }

    user_variable& operator=(const user_variable& var) {
	    if (m_pP != NULL)
		    m_pP->release();
	    m_pP = var.m_pP;
	    if (m_pP != NULL)
		    m_pP->addref();
	    return *this;
    }
};
typedef user_variable Variable;

inline user_algebraic_operator cst(double x) {
	return calculus::_cst(x);
}

inline user_variable var(char * scVarName) {
	return calculus::_var(scVarName);
}

inline user_algebraic_operator _y0(const user_algebraic_operator & arg) { 
	return calculus::unary_operators::bessel_operators::__y0(arg);
}

inline user_algebraic_operator _y1(const user_algebraic_operator & arg) { 
	return calculus::unary_operators::bessel_operators::__y1(arg);
}

inline user_algebraic_operator _yn(unsigned int n,const user_algebraic_operator & arg) {
	return calculus::unary_operators::bessel_operators::__yn(n,arg);
}

inline user_algebraic_operator _j0(const user_algebraic_operator & arg) { 
	return calculus::unary_operators::bessel_operators::__j0(arg); 
}

inline user_algebraic_operator _j1(const user_algebraic_operator & arg) { 
	return calculus::unary_operators::bessel_operators::__j1(arg);
}

inline user_algebraic_operator _jn(unsigned int n,const user_algebraic_operator & arg) {
	return calculus::unary_operators::bessel_operators::__jn(n,arg);
}

inline user_algebraic_operator _d3pc(const Variable & arg1,const user_algebraic_operator & arg2) { 
	return calculus::unary_operators::derivative_operators::__d3pc(arg1,arg2);
}

inline user_algebraic_operator _d3pf(const Variable & arg1,const user_algebraic_operator & arg2) { 
	return calculus::unary_operators::derivative_operators::__d3pf(arg1,arg2);
}

inline user_algebraic_operator _d3pb(const Variable & arg1,const user_algebraic_operator & arg2) { 
	return calculus::unary_operators::derivative_operators::__d3pb(arg1,arg2);
}

inline user_algebraic_operator _d5pc(const Variable & arg1,const user_algebraic_operator & arg2) { 
	return calculus::unary_operators::derivative_operators::__d5pc(arg1,arg2);
}

inline user_algebraic_operator _d5pf(const Variable & arg1,const user_algebraic_operator & arg2) { 
	return calculus::unary_operators::derivative_operators::__d5pf(arg1,arg2);
}

inline user_algebraic_operator _d5pb(const Variable & arg1,const user_algebraic_operator & arg2) { 
	return calculus::unary_operators::derivative_operators::__d5pb(arg1,arg2);
}

inline user_algebraic_operator sin(const user_algebraic_operator & arg) {
	return calculus::unary_operators::trigonometric_operators::_sin(arg);
}

inline user_algebraic_operator cos(const user_algebraic_operator & arg) {
	return calculus::unary_operators::trigonometric_operators::_cos(arg);
}

inline user_algebraic_operator tan(const user_algebraic_operator & arg) {
	return calculus::unary_operators::trigonometric_operators::_tan(arg);
}

inline user_algebraic_operator asin(const user_algebraic_operator & arg) {
	return calculus::unary_operators::trigonometric_operators::_asin(arg);
}

inline user_algebraic_operator acos(const user_algebraic_operator & arg) {
	return calculus::unary_operators::trigonometric_operators::_acos(arg);
}

inline user_algebraic_operator atan(const user_algebraic_operator & arg) {
	return calculus::unary_operators::trigonometric_operators::_atan(arg);
}

inline user_algebraic_operator log(const user_algebraic_operator & arg) {
	return calculus::unary_operators::intrinsic_operators::_log(arg);
}

inline user_algebraic_operator log10(const user_algebraic_operator & arg) {
	return calculus::unary_operators::intrinsic_operators::_log10(arg);
}

inline user_algebraic_operator sqrt(const user_algebraic_operator & arg) {
	return calculus::unary_operators::intrinsic_operators::_sqrt(arg);
}

inline user_algebraic_operator nop(const user_algebraic_operator & arg) {
	return calculus::unary_operators::intrinsic_operators::_nop(arg);
}

inline user_algebraic_operator exp(const user_algebraic_operator & arg) {
	return calculus::unary_operators::intrinsic_operators::_exp(arg);
}

inline user_algebraic_operator neg(const user_algebraic_operator & arg) {
	return calculus::unary_operators::intrinsic_operators::_neg(arg);
}

inline user_algebraic_operator operator-(user_algebraic_operator & arg) {
	return neg(arg);
}

inline user_algebraic_operator cosh(const user_algebraic_operator & arg) {
	return calculus::unary_operators::hyperbolic_operators::_cosh(arg);
}

inline user_algebraic_operator tanh(const user_algebraic_operator & arg) {
	return calculus::unary_operators::hyperbolic_operators::_tanh(arg);
}

inline user_algebraic_operator sinh(const user_algebraic_operator & arg) {
	return calculus::unary_operators::hyperbolic_operators::_sinh(arg);
}

inline user_algebraic_operator INT_POW(int n,const user_algebraic_operator & arg) {
	return calculus::unary_operators::intrinsic_operators::_INT_POW(n,arg);
}

inline user_algebraic_operator operator^(const user_algebraic_operator & arg,int n) {
	return INT_POW(n,arg);
}

inline user_algebraic_operator add(const user_algebraic_operator & arg1,const user_algebraic_operator & arg2) { 
	return calculus::binary_operators::intrinsic_operators::_add(arg1,arg2);
}

inline user_algebraic_operator operator+(const user_algebraic_operator & arg1,const user_algebraic_operator & arg2) { 
	return add(arg1,arg2); 
}

inline user_algebraic_operator subtract(const user_algebraic_operator & arg1,const user_algebraic_operator & arg2) { 
	return calculus::binary_operators::intrinsic_operators::_subtract(arg1,arg2);
}

inline user_algebraic_operator operator-(const user_algebraic_operator & arg1,const user_algebraic_operator & arg2) {
	return subtract(arg1,arg2);
}

inline user_algebraic_operator multiply(const user_algebraic_operator & arg1,const user_algebraic_operator & arg2) { 
	return calculus::binary_operators::intrinsic_operators::_multiply(arg1,arg2);
}

inline user_algebraic_operator operator*(const user_algebraic_operator & arg1,const user_algebraic_operator & arg2) { 
	return multiply(arg1,arg2); 
}

inline user_algebraic_operator divide(const user_algebraic_operator & arg1,const user_algebraic_operator & arg2) { 
	return calculus::binary_operators::intrinsic_operators::_divide(arg1,arg2);
}

inline user_algebraic_operator operator/(const user_algebraic_operator & arg1,const user_algebraic_operator & arg2) { 
	return divide(arg1,arg2); 
}

inline user_algebraic_operator pow(const user_algebraic_operator & arg1,const user_algebraic_operator & arg2) { 
	return calculus::binary_operators::intrinsic_operators::_pow(arg1,arg2);
}

inline user_algebraic_operator operator^(const user_algebraic_operator & arg1,const user_algebraic_operator & arg2) { 
	return pow(arg1,arg2);
}

inline user_algebraic_operator linkf(void * pFunction,char * pscFunctionName,unsigned int uiNumberOfvariables,calculus::variable ** ppVars) {
	return calculus::_linkf(pFunction,pscFunctionName,uiNumberOfvariables,(uiNumberOfvariables)?ppVars:NULL);
}

inline user_algebraic_operator poly(unsigned int uiOrder,calculus::unary_operators::polynomials::poly_function_type pft,double * pAis,const user_algebraic_operator & F) {
	return calculus::unary_operators::polynomials::_poly(uiOrder,pft,pAis,F);
}

inline user_algebraic_operator poly(unsigned int uiOrder,double * pXs,double * pAis,const user_algebraic_operator & F) {
	return calculus::unary_operators::polynomials::_poly(uiOrder,pXs,pAis,F);
}

inline std::istream& operator>>(std::istream &s, user_algebraic_operator & arg) {
    calculus::algebra_parser * pParser = calculus::algebra_parser::get_service();
    char * pBuffer = new char[65535];
    s >> pBuffer;
    arg = pParser->parse_to_algebra(pBuffer);
    delete pBuffer;
    return s;
}

