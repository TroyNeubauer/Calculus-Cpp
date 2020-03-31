/*

CALCULUS_CPP.H: INTERNAL HEADER FOR CALCULUS-CPP

Include this file in modules you create that extend the basic functional
framework.  All but one module of the framework include this file directly
instead of <calculus.h>.  This header presents all internal types and functions
but does not present any entry-level types.

A large number of classes and operators are supplied within this header.

* calculus-cpp: Scientific "Functional" Library
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

THIS SOFTWARE INCLUDES THE NIST'S TNT PACKAGE FOR USE WITH THE EXAMPLES FURNISHED.

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

#ifndef _ASSERT
#ifdef _MSC_VER
	#include <Windows.h>
    #define _ASSERT(x) if ((x)==0) { DebugBreak(); }
#else
    #define _ASSERT(x) (x)
#endif
    
#endif //_ASSERT

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) (x);
#endif

#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <malloc.h>
#include <cstddef>
#include <typeinfo>

void *ParseAlloc(void *(*mallocProc)(size_t));

/////////////////////////////////////////////////////////////////////////////////////////////
//
//  CORE CALCULUS TYPE DEFINITIONS AND KEYWORDS
//
typedef double(*FUNCTION)(double,...);
typedef double(*REAL_FUNCTION)(double*);
/////////////////////////////////////////////////////////////////////////////////////////////
//
//  DECLARATIONS FOR THE STRING PARSER
//
#define CLASS_UNARY_NORMAL		0x1u
#define CLASS_UNARY_EXTENDED	0x2u
#define CLASS_BINARY_NORMAL		0x4u

/////////////////////////////////////////////////////////////////////////////////////////////
//
//	Compiler macros
//
typedef unsigned char byte_type;
typedef unsigned short int word_type;
typedef unsigned long int dword_type;
#ifdef _MSC_VER
typedef unsigned __int64 qword_type;
#else
typedef unsigned long long int qword_type;
#endif

#define COMPILABLE_NULL		0
//FLAGS FOR THE BEHAVIOUR OF THE COMPILER
#define COMPILER_DEBUG						0x01u
#define COMPILER_INTERPRET					0x02u
#define COMPILER_ADAPT						0x04u
#define COMPILER_LEAN_AND_MEAN				0x08u
//FUTURE OF THESE LINES IS UNCERTAIN
#define COMPILER_INFO_V(x)					2*sizeof(dword_type)+x*sizeof(double)
//OPCODE DEFINITIONS

#define CPU_ID() X86
#define REG_EAX		((byte_type)0x0u)
#define REG_ECX		((byte_type)0x1u)
#define REG_EDX		((byte_type)0x2u)
#define REG_EBX		((byte_type)0x3u)
#define REG_ESP		((byte_type)0x4u)
#define REG_EBP		((byte_type)0x5u)
#define REG_ESI		((byte_type)0x6u)
#define REG_EDI		((byte_type)0x7u)
#define REG_EXX(x)	((byte_type)x)
#define REG_STX(x)	((byte_type)x)

/////////////////////////////////////////////////////////////////////////////////////////////
//
//  IMMEDIATE DATA DEFINITIONS
//
#define IMM8(op,imm8val)																	\
	byte_type op = imm8val;
#define IMM16(op,imm16val)																	\
	word_type op = (word_type)imm16val;
#define IMM32(op,imm32val)																	\
	dword_type op = (dword_type)imm32val;
#define IMM64(op,imm64val)																	\
	qword_type op = *((qword_type*)&imm64val);
/////////////////////////////////////////////////////////////////////////////////////////////
//
//  X86 GENERAL PURPOSE ALU OPCODES
//
#ifdef __cplusplus
	#define X86_BREAK(op)           \
        byte_type op[] = { 0xCCu };
	#define X86_NOP(op)             \
        byte_type op[] = { 0x90u };
	#define X86_MOV_EXX_IMM32(op,x) \
        byte_type op[] = { 0xB8u | REG_EXX(x) };
	#define X86_MOV_EXX_EYX(op,x,y) \
        byte_type op[] = { 0x8Bu, 0xC0u | (REG_EXX(x)<<3) | REG_EXX(y) };
	#define X86_PUSH_EXX(op,x)      \
        byte_type op[] = { 0x50u|REG_EXX(x) };
	#define X86_PUSH_IMM32(op)      \
        byte_type op[] = { 0x68u };
	#define X86_POP_EXX(op,x)       \
        byte_type op[] = { 0x58u | REG_EXX(x) };
	#define X86_SUB_EXX_IMM32(op,x)	\
        byte_type op[] = { 0x81u , 0xE8u | REG_EXX(x) };
	#define X86_ADD_EXX_IMM32(op,x)	\
        byte_type op[] = { 0x81u , 0xC0u | REG_EXX(x) };
	#define X86_CMP_EXX_EYX(op,x,y) \
        byte_type op[] = { 0x39u , 0xC0u | (REG_EXX(x)<<3) | REG_EXX(y) };
	#define X86_JMP_IMM8(op)	    \
        byte_type op[] = { 0xEBu };
	#define X86_JE_IMM8(op)         \
        byte_type op[] = { 0x74u };
	#define X86_JAE_IMM8(op)		\
        byte_type op[] = { 0x73u };
	#define X86_JBE_IMM8(op)		\
        byte_type op[] = { 0x76u };
	#define X86_CALL_EXX(op,x)		\
        byte_type op[] = { 0xFFu, 0xD0u | REG_EXX(x) };
	#define X86_RET(op)				\
        byte_type op[] = { 0xC3u };
	#define X86_INC_EXX(op,x)		\
        byte_type op[] = { 0x40u | REG_EXX(x) };
	#define X86_INC_dword_typePTREXX(op,x)\
        byte_type op[] = { 0xFFu , x };
/////////////////////////////////////////////////////////////////////////////////////////////
//
//  X87 FPU ESCAPE OPCODE INSTRUCTION SET
//
	#define X86_FCLEX(op)               \
        byte_type op[] = { 0xDBu , 0xE2u };
	#define X86_FDECSTP(op)				\
        byte_type op[] = { 0xD9u , 0xF6u };
	#define X86_FINCSTP(op)				\
        byte_type op[] = { 0xD9u , 0xF7u };
	#define X86_FLD1(op)				\
        byte_type op[] = { 0xD9u , 0xE8u };
	#define X86_FLDZ(op)				\
        byte_type op[] = { 0xD9u , 0xEEu };
	#define X86_FCOMIP_STX(op,x)		\
        byte_type op[] = { 0xDFu , 0xF0u | REG_STX(x) };
	#define X86_FLD_EBPX_IMM8(op)       \
        byte_type op[] = { 0xDDu , 0x45u };
	#define X86_FLD_EBPX_IMM32(op)		\
        byte_type op[] = { 0xDDu , 0x85u };
	#define X86_FLD_IMM32PTR64(op)		\
        byte_type op[] = { 0xDDu , 0x04u, 0x25 };
	#define X86_FLD_IMM32(op)			\
        byte_type op[] = { 0xD9u , 0x04u, 0x25 };
	#define X86_FLD_STX(op,x)			\
        byte_type op[] = { 0xD9u , 0xC0u | REG_STX(x) };
	#define X86_FSTP_EBPX_IMM8(op)		\
        byte_type op[] = { 0xDDu , 0x5Du };
	#define X86_FSTP_EBPX_IMM32(op)		\
        byte_type op[] = { 0xDDu , 0x9Du };
	#define X86_FSTP_STX(op,x)			\
        byte_type op[] = { 0xDDu , 0xD8u | REG_STX(x) };
	#define X86_FSTP_IMM32PTR64(op)		\
        byte_type op[] = { 0xDDu , 0x1Cu, 0x25u };
	#define X86_FXCH_STX(op,x)			\
        byte_type op[] = { 0xD9u , 0xC8u | REG_STX(x) };
	#define X86_FCHS(op)				\
        byte_type op[] = { 0xD9u , 0xE0u };
	#define X86_FADD_STX(op,x)			\
        byte_type op[] = { 0xD8u , 0xC0u | REG_STX(x) };
	#define X86_FADDP_STX(op,x)			\
        byte_type op[] = { 0xDAu , 0xC0u | REG_STX(x)};
	#define X86_FRADD_STX(op,x)			\
        byte_type op[] = { 0xDCu , 0xC0u | REG_STX(x) };
	#define X86_FRADDP_STX(op,x)		\
        byte_type op[] = { 0xDBu , 0xE2u | REG_STX(x) };
	#define X86_FSUB_STX(op,x)			\
        byte_type op[] = { 0xD8u , 0xE0u | REG_STX(x) };
	#define X86_FSUBP_STX(op,x)			\
        byte_type op[] = { 0xDEu , 0xE8u | REG_STX(x) };
	#define X86_FRSUB_STX(op,x)			\
        byte_type op[] = { 0xDCu , 0xE0u | REG_STX(x) };
	#define X86_FRSUBP_STX(op,x)		\
        byte_type op[] = { 0xDEu , 0xE0u | REG_STX(x) };
	#define X86_FMUL_STX(op,x)			\
        byte_type op[] = { 0xD8u , 0xC8u | REG_STX(x) };
	#define X86_FMULP_STX(op,x)			\
        byte_type op[] = { 0xDEu , 0xC8u | REG_STX(x) };
	#define X86_FDIV_STX(op,x)			\
        byte_type op[] = { 0xD8u , 0xF0u | REG_STX(x) };
	#define X86_FDIVP_STX(op,x)			\
        byte_type op[] = { 0xDEu , 0xF8u | REG_STX(x) };
	#define X86_FRDIV_STX(op,x)			\
        byte_type op[] = { 0xDCu , 0xF0u | REG_STX(x) };
	#define X86_FRDIVP_STX(op,x)		\
        byte_type op[] = { 0xDEu , 0xF0u | REG_STX(x) };
	#define X86_FCOS(op)				\
        byte_type op[] = { 0xD9u , 0xFFu };
	#define X86_FSIN(op)				\
        byte_type op[] = { 0xD9u , 0xFEu };
	#define X86_FSQRT(op)				\
        byte_type op[] = { 0xD9u , 0xFAu };
/////////////////////////////////////////////////////////////////////////////////////////////
//
//  PROCESSOR ABSTRACTION MACROS
//
	#define BREAK					X86_BREAK
	#define NOP						X86_NOP
	#define MOV_EXX_IMM32			X86_MOV_EXX_IMM32
	#define MOV_EXX_EYX				X86_MOV_EXX_EYX
	#define PUSH_EXX				X86_PUSH_EXX
	#define PUSH_IMM32				X86_PUSH_IMM32
	#define POP_EXX					X86_POP_EXX
	#define SUB_EXX_IMM32			X86_SUB_EXX_IMM32
	#define ADD_EXX_IMM32			X86_ADD_EXX_IMM32
	#define CMP_EXX_EYX				X86_CMP_EXX_EYX
	#define JMP_IMM8				X86_JMP_IMM8
	#define JE_IMM8					X86_JE_IMM8
	#define JAE_IMM8				X86_JAE_IMM8
	#define JBE_IMM8				X86_JBE_IMM8
	#define CALL_EXX				X86_CALL_EXX
	#define RET						X86_RET
	#define INC_EXX					X86_INC_EXX
	#define INC_dword_typePTREXX			X86_INC_dword_typePTREXX
/////////////////////////////////////////////////////////////////////////////////////////////
//
//  X87 FPU ESCAPE OPCODE INSTRUCTION SET
//
	#define FCLEX					X86_FCLEX
	#define FDECSTP					X86_FDECSTP
	#define FINCSTP					X86_FINCSTP
	#define FLD1					X86_FLD1
	#define FLDZ					X86_FLDZ
	#define FCOMIP_STX				X86_FCOMIP_STX
	#define FLD_EBPX_IMM8			X86_FLD_EBPX_IMM8
	#define FLD_EBPX_IMM32			X86_FLD_EBPX_IMM32
	#define FLD_IMM32PTR64			X86_FLD_IMM32PTR64
	#define FLD_IMM32				X86_FLD_IMM32
	#define FLD_STX					X86_FLD_STX
	#define FSTP_EBPX_IMM8			X86_FSTP_EBPX_IMM8
	#define FSTP_EBPX_IMM32			X86_FSTP_EBPX_IMM32
	#define FSTP_STX				X86_FSTP_STX
	#define FSTP_IMM32PTR64			X86_FSTP_IMM32PTR64
	#define FXCH_STX				X86_FXCH_STX
	#define FCHS					X86_FCHS
	#define FADD_STX				X86_FADD_STX
	#define FADDP_STX				X86_FADDP_STX
	#define FRADD_STX				X86_FRADD_STX
	#define FRADDP_STX				X86_FRADDP_STX
	#define FSUB_STX				X86_FSUB_STX
	#define FSUBP_STX				X86_FSUBP_STX
	#define FRSUB_STX				X86_FRSUB_STX
	#define FRSUBP_STX				X86_FRSUBP_STX
	#define FMUL_STX				X86_FMUL_STX
	#define FMULP_STX				X86_FMULP_STX
	#define FRMUL_STX				X86_FRMUL_STX
	#define FRMULP_STX				X86_FRMULP_STX
	#define FDIV_STX				X86_FDIV_STX
	#define FDIVP_STX				X86_FDIVP_STX
	#define FRDIV_STX				X86_FRDIV_STX
	#define FRDIVP_STX				X86_FRDIVP_STX
	#define FSIN					X86_FSIN
	#define FCOS					X86_FCOS
	#define FSQRT					X86_FSQRT
#endif //__cplusplus
//FLAGS FOR THE PARSING PROCESS
#define COMPILER_FPU_MAX_STACK		0x8u			//I386 FPU STACK SIZE
#define COMPILER_FPU_MAX_STACK_USE	0x7u			//ACCOUNTS FOR VARIABLE LOADING
//FLAGS FOR THE FEATURES REQUESTED DURING PARSING
#define FEAT_NEED_NONE				(dword_type)0x0000u	//RESET FEATURES
#define FEAT_NEED_EAX				(dword_type)0x0001u
#define FEAT_NEED_EBX				(dword_type)0x0002u
#define FEAT_NEED_ECX				(dword_type)0x0004u
#define FEAT_NEED_EDX				(dword_type)0x0008u
#define FEAT_NEED_LOCAL_STORE		(dword_type)0x0010u
#define FEAT_NEED_GLOBAL_STORE		(dword_type)0x0020u
#define FEAT_NEED_AUX_STORE			(dword_type)0x0020u
	#define FEAT_AUX_NEED_MEMCPY	(dword_type)0x0001u
	#define FEAT_AUX_NEED_CHECKESP	(dword_type)0x0002u
	#define FEAT_AUX_NEED_NONE		(dword_type)0x0000u
#define FEAT_NEED_PTR_MAP			(dword_type)0x0040u
//AUXILIARY FEATURE FLAGS
#define AUX_FEATURE_SIZE			(dword_type)0x0u
#define AUX_FEATURE_TABLE_SIZE		(dword_type)0x0u
//FLAGS FOR THE HEADER STRUCTURE
#define COMPILER_FLAG_NOFLAGS					(dword_type)0x0u
#define COMPILER_FLAG_FUNCTION_NOT_REMOTABLE	(dword_type)0x0001u

void initialize_calculus(unsigned int cMode);
int uninitialize_calculus();

double inline INT_POW(int b,double a) {
    if (b == 0)
        return 1;
    return INT_POW((b > 0)?b-1:b+1,a)*a;
}

namespace calculus
{
    class variable;
}

typedef struct PARSE_TIME_INFO {
	size_t  st_size;					//Size of this structure
	size_t  st_instruction_storage_size;//Amount of instruction storage needed
	size_t  st_local_storage_size;		//Amount of Local storage needed
	size_t  st_global_storage_size;		//Amount of global storage needed
	size_t  st_pmap_size;				//Number of entries in the PTR map
	int     i_fpu_stack_offset;		    //Number of stacked entries needed
	int     i_features_needed;			//Flags for features requested
	int     i_aux_features_needed;		//Flags for the AUX features requested
	int     i_operator_count;			//Number of algebraic operators in the function
	int     i_instruction_count;		//An instruction counter
	int     i_clock_count;				//A clock counter
} PT_INFO,*PPT_INFO;

typedef struct COMPILER_HEADER	{
	size_t				st_mem_size;				//Memory reserved for entire segment
	size_t				st_size;					//Size of the COMPILER_HEADER structure
	COMPILER_HEADER*	pSelf;					//Pointer to this structure
	FUNCTION			pInstructions;			//Pointer to the enclosed function
	int				    i_f_flags;				//A set of optional flags
	int				    i_num_vars;				//Total number of variables in the function
	int				    i_call_count;			//A call count
	int				    i_operator_count;		//An operator count
	int				    i_instruction_count;		//An instruction count
	int				    i_clock_count;			//A clock time count
	unsigned char*		psc_name;					//Pointer to a null-terminated ASCII string with the full name of the function
	unsigned char**		ppv_pmap;				//A map of all the scaled pointers in the function's code
	unsigned char*		pv_global_storage;			//A place of global storage
	unsigned char*		pv_local_storage;			//Local storage for the functions
	unsigned char**		ppv_auxiliary_storage_toc;	//Table containing pointers to start addresses of the AUX storage
	unsigned char*		pv_auxiliary_storage;		//First AUX storage entry
}	COMPILER_HEADER,	*PCOMPILER_HEADER;

typedef struct COMPILE_TIME_INFO
{
	PCOMPILER_HEADER    pHeader;			//A pointer to the associated COMPILER_HEADER structure
	unsigned char**     ppv_pmapPos;				//Current position in the PTR_MAP entries
	unsigned char*      pv_global_storage_pos;				//Current position in the global store
	unsigned char*      pv_local_storage_pos;				//Current position in the local store
	unsigned char*      pv_aux_storage_pos;					//Current position in the AUX store
	unsigned char*      pv_instruction_storage_pos;			//Current position in the instruction store
	int                 i_stack_offset;				//Current stack offset from EBP in byte_types
	int                 i_fpu_stack_offset;				//Number of stacked entries needed
    calculus::variable** ppv_vars;
} CT_INFO,*PCT_INFO;

template <class unknown> void addref_and_release(unknown * punknown) {
	punknown->addref();
	punknown->release();
}

template <class unknown> void mass_addref_and_release(unknown ** ppunknown,int n) {
    do {
		addref_and_release<unknown>(ppunknown[--n]);
    } while(n);
}

template <class unknown> void mass_addref(unknown ** ppUnknown,int n) {
    do {
		ppUnknown[--n]->addref();
    } while(n);
}

template <class unknown> void mass_release(unknown ** ppUnknown,int n) {
    do {
		ppUnknown[--n]->release();
    } while(n);
}

template <typename T,unsigned int N>
struct DATA
{
	DATA<T,N>* m_pNext;
	DATA<T,N>* m_pPrevious;
	T m_tDataSet[N];
	DATA<T,1>* m_pMoreData;
};

template <class T,unsigned int N>
inline DATA<T,N>* AllocateInlinedDataSets(unsigned int NumSets)
{
	DATA<T,N>* pSets = (DATA<T,N>*)malloc(NumSets*sizeof(DATA<T,N>));
	for(unsigned int i = 0;i < NumSets-1;i++)
	{
		pSets[i].m_pNext = pSets+i+1;
		pSets[i].m_pPrevious = pSets+i-1;
		pSets[i].m_pMoreData = NULL;
	};
	pSets[0].m_pPrevious = NULL;
	pSets[NumSets-1].m_pNext = NULL;
	return pSets;
};

template <class T,unsigned int N>
void inline FreeInlinedDataSets(DATA<T,N>* pSets)
{
	free(pSets);
};

template <typename OPCODE_BASE>	struct Opcode {	
	OPCODE_BASE bin;
};
template <typename OPCODE> struct MODRMOpcode {	
	OPCODE opcode;
	byte_type modrm;
};
template <typename MODRMOPCODE>	struct SIBMODRMOpcode {	
	MODRMOPCODE modrmopcode;
	byte_type sib;
};

inline void CompilerWriteInstruction(PCT_INFO pInfo,byte_type* pS,unsigned int binsize) {
	for(;binsize;binsize--,pS++,pInfo->pv_instruction_storage_pos++)
		*(pInfo->pv_instruction_storage_pos) = *pS;
}
inline void CompilerWriteLocalInfo(PCT_INFO pInfo,byte_type* pS,unsigned int binsize) {
	for(;binsize;binsize--,pS++,pInfo->pv_local_storage_pos++)
		*(pInfo->pv_local_storage_pos) = *pS;
}
inline void CompilerWriteGlobalInfo(PCT_INFO pInfo,byte_type* pS,unsigned int binsize) {
	for(;binsize;binsize--,pS++,pInfo->pv_global_storage_pos++)
		*(pInfo->pv_global_storage_pos) = *pS;
}
inline void CompilerWritePTR_ENTRY(PCT_INFO pInfo,unsigned char* pS) {
	*pInfo->ppv_pmapPos = pS;
	pInfo->ppv_pmapPos++;
}
inline void CompilerWriteIMM8(PCT_INFO pInfo, byte_type val) {
	IMM8(imm8,val)
	CompilerWriteInstruction(pInfo,(byte_type*)&imm8,sizeof(imm8));
}
inline unsigned int CompilerSizeOfIMM8() {
	return sizeof(byte_type);
}
inline void CompilerWriteIMM32(PCT_INFO pInfo, dword_type val) {
	IMM32(imm32,val)
	CompilerWriteInstruction(pInfo,(byte_type*)&imm32,sizeof(imm32));
}
inline unsigned int CompilerSizeOfIMM32() {
	return sizeof(dword_type);
}
inline void CompilerWriteIMM64(PCT_INFO pInfo, qword_type val) {
	IMM64(imm64,val)
	CompilerWriteInstruction(pInfo,(byte_type*)&imm64,sizeof(imm64));
}
inline unsigned int CompilerSizeOfIMM64() {
	return sizeof(double);
}
inline void CompilerWriteBREAK(PCT_INFO pInfo) {
	BREAK(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfBREAK() {
	BREAK(op);
	return sizeof(op);
}
inline void CompilerWriteNOP(PCT_INFO pInfo) {
	NOP(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfNOP() {
	NOP(op)
	return sizeof(op);
}
inline void CompilerWriteMOV_EXX_IMM32(PCT_INFO pInfo,byte_type x) {
	MOV_EXX_IMM32(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfMOV_EXX_IMM32() {
	MOV_EXX_IMM32(op,0)
	return sizeof(op);
}
inline void CompilerWriteMOV_EXX_EYX(PCT_INFO pInfo,byte_type x,byte_type y) {
	MOV_EXX_EYX(op,x,y)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfMOV_EXX_EYX() {
	MOV_EXX_EYX(op,0,0)
	return sizeof(op);
}

inline void CompilerWritePUSH_EXX(PCT_INFO pInfo,byte_type x) {
	PUSH_EXX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
	pInfo->i_stack_offset += sizeof(dword_type);
}
inline unsigned int CompilerSizeOfPUSH_EXX() {
	PUSH_EXX(op,0)
	return sizeof(op);
}
inline void CompilerWritePUSH_IMM32(PCT_INFO pInfo) {
	PUSH_IMM32(op);
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
	pInfo->i_stack_offset += sizeof(dword_type);
}
inline unsigned int CompilerSizeOfPUSH_IMM32() {
	PUSH_IMM32(op)
	return sizeof(op);
}
inline void CompilerWritePOP_EXX(PCT_INFO pInfo,byte_type x) {
	POP_EXX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
	pInfo->i_stack_offset -= sizeof(dword_type);
}
inline unsigned int CompilerSizeOfPOP_EXX() {
	POP_EXX(op,0)
	return sizeof(op);
}

inline void CompilerWriteSUB_EXX_IMM32(PCT_INFO pInfo,byte_type x) {
	SUB_EXX_IMM32(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfSUB_EXX_IMM32() {
	SUB_EXX_IMM32(op,0)
	return sizeof(op);
}
inline void CompilerWriteADD_EXX_IMM32(PCT_INFO pInfo,byte_type x) {
	ADD_EXX_IMM32(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfADD_EXX_IMM32() {
	ADD_EXX_IMM32(op,0)
	return sizeof(op);
}
inline void CompilerWriteCMP_EXX_EYX(PCT_INFO pInfo,byte_type x,byte_type y) {
	CMP_EXX_EYX(op,x,y)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfCMP_EXX_EYX() {
	CMP_EXX_EYX(op,0,0)
	return sizeof(op);
}
inline void CompilerWriteCALL_EXX(PCT_INFO pInfo,byte_type x) {
	CALL_EXX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfCALL_EXX() {
	CALL_EXX(op,0)
	return sizeof(op);
}
inline void CompilerWriteRET(PCT_INFO pInfo) {
	RET(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfRET() {
	RET(op)
	return sizeof(op);
}

inline void CompilerWriteINC_EXX(PCT_INFO pInfo,byte_type x) {
	INC_EXX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfINC_EXX() {
	INC_EXX(op,0)
	return sizeof(op);
}
inline void CompilerWriteINC_dword_typePTREXX(PCT_INFO pInfo,byte_type x) {
	INC_dword_typePTREXX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfINC_dword_typePTREXX() {
	INC_dword_typePTREXX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFCLEX(PCT_INFO pInfo) {
	FCLEX(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFCLEX() {
	FCLEX(op)
	return sizeof(op);
}
inline void CompilerWriteFDECSTP(PCT_INFO pInfo) {
	FDECSTP(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFDECSTP() {
	FDECSTP(op)
	return sizeof(op);
}
inline void CompilerWriteFINCSTP(PCT_INFO pInfo) {
	FINCSTP(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFINCSTP() {
	FINCSTP(op)
	return sizeof(op);
}
inline void CompilerWriteFLD1(PCT_INFO pInfo) {
	FLD1(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFLD1() {
	FLD1(op)
	return sizeof(op);
}
inline void CompilerWriteFLDZ(PCT_INFO pInfo) {
	FLDZ(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFLDZ() {
	FLDZ(op)
	return sizeof(op);
}
inline void CompilerWriteFLD_EBPX_IMM32(PCT_INFO pInfo) {	
	X86_FLD_EBPX_IMM32(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFLD_EBPX_IMM32() {
	FLD_EBPX_IMM32(op)
	return sizeof(op);
}
inline void CompilerWriteFLD_IMM32PTR64(PCT_INFO pInfo) {
	FLD_IMM32PTR64(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFLD_IMM32PTR64() {
	FLD_IMM32PTR64(op)
	return sizeof(op);
}
inline void CompilerWriteFLD_STX(PCT_INFO pInfo,byte_type b) {	
	FLD_STX(op,b)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFLD_STX() {
	FLD_STX(op,0)
	return sizeof(op);
}
/*
static inline void CompilerWriteFSTP_EBPX_IMM8(PCT_INFO pInfo,unsigned char s)
{	
	FSTP_EBPX_IMM8(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
	IMM8(imm8,s)
	CompilerWriteInstruction(pInfo,(byte_type*)&imm8,sizeof(imm8));
};
static inline unsigned int CompilerSizeOfFSTP_EBPX_IMM8()
{
	FSTP_EBPX_IMM8(op)
	IMM8(imm8,0)
	return sizeof(imm8)+sizeof(op);
};
*/
inline void CompilerWriteFSTP_EBPX_IMM32(PCT_INFO pInfo) {	
	FSTP_EBPX_IMM32(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFSTP_EBPX_IMM32() {
	FSTP_EBPX_IMM32(op)
	return sizeof(op);
}
inline void CompilerWriteFSTP_IMM32PTR64(PCT_INFO pInfo) {
	FSTP_IMM32PTR64(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFSTP_IMM32PTR64() {
	FSTP_IMM32PTR64(op)
	return sizeof(op);
}
inline void CompilerWriteFSTP_STX(PCT_INFO pInfo,byte_type b) {	
	FSTP_STX(op,b)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFSTP_STX() {
	FSTP_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFXCH_STX(PCT_INFO pInfo,byte_type x) {
	FXCH_STX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFXCH_STX() {
	FXCH_STX(op,0)
	return sizeof(op);
}

inline void CompilerWriteFCHS(PCT_INFO pInfo) {
	FCHS(op);
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFCHS() {
	FCHS(op);
	return sizeof(op);
}

inline void CompilerWriteFADD_STX(PCT_INFO pInfo,byte_type x) {
	FADD_STX(op,x);
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompulerSizeOfFADD_STX() {
	FADD_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFADDP_STX(PCT_INFO pInfo,byte_type x) {
	FADDP_STX(op,x);
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFADDP_STX() {
	FADDP_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFRADD_STX(PCT_INFO pInfo,byte_type x) {
	FRADD_STX(op,x);
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFRADD_STX() {
	FRADD_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFRADDP_STX(PCT_INFO pInfo,byte_type x) {
	FRADDP_STX(op,x);
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFRADDP_STX() {
	FRADDP_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFSUB_STX(PCT_INFO pInfo,byte_type x) {
	FSUB_STX(op,x);
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompulerSizeOfFSUB_STX() {
	FSUB_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFSUBP_STX(PCT_INFO pInfo,byte_type x) {
	FSUBP_STX(op,x);
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFSUBP_STX() {
	FSUBP_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFRSUB_STX(PCT_INFO pInfo,byte_type x) {
	FRSUB_STX(op,x);
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFRSUB_STX() {
	FRSUB_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFRSUBP_STX(PCT_INFO pInfo,byte_type x) {
	FRSUBP_STX(op,x);
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFRSUBP_STX() {
	FRSUBP_STX(op,0)
	return sizeof(op);
}

inline void CompilerWriteFMUL_STX(PCT_INFO pInfo,byte_type x) {
	FMUL_STX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFMUL_STX() {
	FMUL_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFMULP_STX(PCT_INFO pInfo,byte_type x) {
	FMULP_STX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFMULP_STX() {
	FMULP_STX(op,0)
	return sizeof(op);
}

inline void CompilerWriteFDIV_STX(PCT_INFO pInfo,byte_type x) {
	FDIV_STX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFDIV_STX() {
	FDIV_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFDIVP_STX(PCT_INFO pInfo,byte_type x) {
	FDIVP_STX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFDIVP_STX() {
	FDIVP_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFRDIV_STX(PCT_INFO pInfo,byte_type x) {
	FRDIV_STX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFRDIV_STX() {
	FRDIV_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFRDIVP_STX(PCT_INFO pInfo,byte_type x) {
	FRDIVP_STX(op,x)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFRDIVP_STX() {
	FRDIVP_STX(op,0)
	return sizeof(op);
}
inline void CompilerWriteFSIN(PCT_INFO pInfo) {
	FSIN(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFSIN() {
	FSIN(op)
	return sizeof(op);
}
inline void CompilerWriteFCOS(PCT_INFO pInfo) {
	FCOS(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFCOS() {
	FCOS(op)
	return sizeof(op);
}
inline void CompilerWriteFSQRT(PCT_INFO pInfo) {
	FSQRT(op)
	CompilerWriteInstruction(pInfo,(byte_type*)&op,sizeof(op));
}
inline unsigned int CompilerSizeOfFSQRT() {
	FSQRT(op)
	return sizeof(op);
}

namespace calculus 
{
	class IA32_binary
	{
        friend class algebraic_operator;
		static IA32_binary* s_pia32b_first;
		static IA32_binary* s_pia32b_last;
		IA32_binary * m_pia32b_next, * m_pia32b_previous;
		unsigned short* m_pus_binary;
    public :
		static inline void free_all_IA32_binaries() {
			while(IA32_binary::s_pia32b_last)
				delete IA32_binary::s_pia32b_last;
		}
		IA32_binary(unsigned short* pus_binary) {
			m_pus_binary = pus_binary;
			if (IA32_binary::s_pia32b_first == NULL) {
				IA32_binary::s_pia32b_last = IA32_binary::s_pia32b_first = this;
				IA32_binary::s_pia32b_first->m_pia32b_previous = NULL;
			}
			else {
				m_pia32b_previous = IA32_binary::s_pia32b_last;
				IA32_binary::s_pia32b_last = (IA32_binary::s_pia32b_last->m_pia32b_next = this);
			}
			IA32_binary::s_pia32b_last->m_pia32b_next = NULL;
		}
		~IA32_binary() {
			PCOMPILER_HEADER pHead = PCOMPILER_HEADER(this->m_pus_binary-sizeof(dword_type));
			free(pHead);
			if ((this != IA32_binary::s_pia32b_last)&&(this != IA32_binary::s_pia32b_first)) {
				m_pia32b_previous->m_pia32b_next = m_pia32b_next;
				m_pia32b_next->m_pia32b_previous = m_pia32b_previous;
			}
			else if (this == IA32_binary::s_pia32b_first) {
				IA32_binary::s_pia32b_first = this->m_pia32b_next;
				if (IA32_binary::s_pia32b_first)
					IA32_binary::s_pia32b_first->m_pia32b_previous = NULL;
			}
            else {
				IA32_binary::s_pia32b_last = this->m_pia32b_previous;
				if (IA32_binary::s_pia32b_last)
					IA32_binary::s_pia32b_last->m_pia32b_next = NULL;
			}
		}
	};

	class algebraic_operator
	{

	protected :
        bool m_b_variables_identified;
		int m_i_number_of_variables;
		variable** m_ppv_variables;
        static unsigned int s_ui_compilation_deferral;
		static unsigned short s_us_compile_flags;
		unsigned int m_ui_call_count;
		unsigned long m_ul_refcount;                             //The reference count
		algebraic_operator** m_ppao_partial_derivatives;					//Link to the derived functions
        IA32_binary * m_pia32_binary;                                 //Link to the IA32_binary version

        algebraic_operator();
        virtual ~algebraic_operator();
		virtual algebraic_operator* partial_derivative(variable * pVar);
		virtual variable** identify_variables();
	public :
		virtual void to_IA32_binary(PCT_INFO pInfo);
		virtual void annotate(PPT_INFO pParseInfo);
		virtual int to_string(char* pBuffer);
		virtual int get_number_of_variables();
		virtual variable** get_variables();
		virtual bool is_function_of(variable* a);
		virtual algebraic_operator * create_copy();
		virtual double eval(double* pVars);

        IA32_binary* to_IA32_binary();
		unsigned int get_call_count();
		FUNCTION compile();
		algebraic_operator* get_partial_derivative(variable * pVar);
		void set_partial_derivative(variable * pVar,algebraic_operator * ppartial_derivative);
		inline void increment_call_count() { this->m_ui_call_count++; };

        virtual unsigned long addref(void) {
			return ++(this->m_ul_refcount);
		}
		virtual unsigned long release(void) {
			unsigned long i = --(this->m_ul_refcount);
			if (!i)
				delete this;
			return i;
		}
	};

	class variable : public algebraic_operator
	{
		static unsigned int uiNextAutoVarName;
#define MAX_VARIABLE_NAME_LENGTH 16
		char m_scVarName[MAX_VARIABLE_NAME_LENGTH];
		variable * pThis;
		variable(const char *pVarName);
		virtual ~variable() {		
			this->m_ppv_variables = NULL;
		}
		static unsigned int nums[27];
		static variable ** ppVars[27];
	public :
		static void FreeRegistry();
		static algebraic_operator * create(const char * psc_name);
		virtual algebraic_operator * create_copy() {
			return new variable(get_variable_name());
		}
	protected :
		virtual void to_IA32_binary(PCT_INFO pInfo);
		virtual void annotate(PPT_INFO pParseInfo);
		virtual algebraic_operator* partial_derivative(variable * pVar);
		virtual double eval(double* pVars);
	public :
		char * get_variable_name() { return this->m_scVarName; };
		virtual int to_string(char* pBuffer);
		virtual variable** identify_variables();
		virtual int get_number_of_variables();
		virtual bool is_function_of(variable* a);
	};
	inline variable * _var(const char * scVarName) {
		return static_cast<calculus::variable*>(calculus::variable::create(scVarName));
	}

	class constant : public algebraic_operator
	{
		double m_tValue;
		constant(double value);
		virtual ~constant() { };
	public :
		static algebraic_operator * create(double val)
		{
			return new constant(val);
		};
		virtual algebraic_operator * create_copy()
		{
			return new constant(GetValue());
		};
	protected :
		virtual void to_IA32_binary(PCT_INFO pInfo);
		virtual void annotate(PPT_INFO pParseInfo);
		virtual algebraic_operator* partial_derivative(variable * pVar);
		virtual double eval(double *pVars);
	public :
		virtual int to_string(char* pBuffer);
		virtual variable** identify_variables();
		virtual int get_number_of_variables();
		virtual bool is_function_of(variable* a);
		double GetValue()
		{
			return m_tValue;
		};
	};
	inline constant * _cst(double value)
	{
		return static_cast<constant*>(calculus::constant::create(value));
	};

	class function_adapter : public algebraic_operator {
		char m_sc_function_adapter_name[16];
		void * m_pv_function_adapter;
		function_adapter(void * pv_function_adapter,char * psc_function_adapter_name,int i_num_vars,variable ** ppv_vars);
	public :
		static calculus::algebraic_operator * create(void * pv_function_adapter,char * psc_function_adapter_name,int i_num_vars,variable ** ppv_vars);
		virtual algebraic_operator * create_copy() {
			return new function_adapter(get_function_adapter(),get_variable_name(),get_number_of_variables(),get_variables());
		}
	protected :
		virtual void to_IA32_binary(PCT_INFO pInfo);
		virtual void annotate(PPT_INFO pParseInfo);
		virtual double eval(double *pVars);
	public :
		virtual int to_string(char* pBuffer);
		virtual variable** identify_variables();
		virtual int get_number_of_variables();
		virtual algebraic_operator* partial_derivative(variable * pVar);
		char * get_variable_name() {
			return m_sc_function_adapter_name;
		}
		void * get_function_adapter() {
			return m_pv_function_adapter;
		}
	};
    inline calculus::function_adapter * _linkf(void * pv_function_adapter,char * psc_function_adapter_name,int i_num_vars,variable ** ppv_vars) {
		return static_cast<calculus::function_adapter*>(calculus::function_adapter::create(pv_function_adapter,psc_function_adapter_name,i_num_vars,ppv_vars));
	}

	class algebra_parser
	{
		static algebra_parser* _running_service;
		
		algebra_parser();
	public :
        ~algebra_parser();
		typedef calculus::algebraic_operator * (* unary_create_function)(calculus::algebraic_operator*);
		unary_create_function * punary_create_functions;
	private :
		char * psc_unary_operator_string;
		int * pi_unary_operator_string_positions;
		int i_num_unary_operators;
	public :
		typedef calculus::algebraic_operator * (* unary_create_extended_function)(int,calculus::algebraic_operator*);
		unary_create_extended_function * punary_create_extended_functions;
	private :
		char * psc_extended_unary_operator_string;
		int * pi_extended_unary_operator_string_positions;
		int i_num_extended_unary_operators;
	public :
		typedef calculus::algebraic_operator * (* binary_create_function)(calculus::algebraic_operator*,calculus::algebraic_operator*);
		binary_create_function * pbinary_create_functions;
	private :
		char * psc_binary_operator_string;
		int *pi_binary_operator_string_positions;
		int i_num_binary_operators;
	public :
		unary_create_function get_unary_create_function(char * pString);
		unary_create_extended_function get_extended_unary_create_function(char * pString);
		binary_create_function get_binary_create_function(char * pString);

		void register_class(dword_type dwOperatorType,dword_type pcreateFunc,char * pOperatorString );

		static algebra_parser*  get_service();

		calculus::algebraic_operator * parse_to_algebra(char * psc_algebraic_string);

		void initialize();
		static void kill_service();
	};
	
	namespace unary_operators
	{

		class unary_operator : public algebraic_operator
		{
			algebraic_operator* m_pao_operand;
			unary_operator() : algebraic_operator(), m_pao_operand(NULL)
			{
			};
		protected :
			unary_operator(algebraic_operator * pP) : m_pao_operand(pP)
			{
				if (m_pao_operand)
					m_pao_operand->addref();
			};
			virtual ~unary_operator()
			{
				if (m_pao_operand)
					m_pao_operand->release();
			};
			virtual double eval_unary(double a)
			{
				UNREFERENCED_PARAMETER(a);
				return 0;
			};
			virtual variable** identify_variables()
			{
                if (m_ppv_variables)
					delete [] m_ppv_variables;
                m_ppv_variables = NULL;
				m_i_number_of_variables = m_pao_operand->get_number_of_variables();
                if (m_i_number_of_variables) {
				    m_ppv_variables = new variable*[m_i_number_of_variables];
				    calculus::variable** ppao_operand_variables = m_pao_operand->get_variables();
				    mass_addref<calculus::variable>(ppao_operand_variables,m_i_number_of_variables);
				    for(int i = 0;i < m_i_number_of_variables;i++)
					    m_ppv_variables[i] = ppao_operand_variables[i];
                }
                m_b_variables_identified = true;
				return m_ppv_variables;
			};
		public :
			virtual algebraic_operator * get_operand() {
				return m_pao_operand;
			}
			virtual double eval(double* pVars) {
                if (m_pao_operand)
                    eval_unary(m_pao_operand->eval(pVars));
                return 0;
			}
		};

		namespace intrinsic_operators
		{

			//DEFINE_UNARY_OPERATOR_DEFAULT(nop,nop);
			class nop : public unary_operator 
			{ 
				nop(algebraic_operator * pAlg) : unary_operator(pAlg)
				{
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new nop(pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new nop(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)nop::create,"nop"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual double eval_unary(double a);
			}; 
			inline nop* _nop(algebraic_operator * pArg) 
			{ 
				return static_cast<nop*>(nop::create(pArg));
			};
		
			class negate : public unary_operator 
			{ 
				negate(algebraic_operator * pAlg) : unary_operator(pAlg)
				{
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new negate(pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new negate(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)negate::create,"neg"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual double eval_unary(double a);
				virtual algebraic_operator* partial_derivative(variable * pVar); 
			}; 
			inline negate* _neg(algebraic_operator * parg) 
			{ 
				return static_cast<negate*>(negate::create(parg));
			};

			class square_root : public unary_operator 
			{ 
				square_root(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new square_root(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new square_root(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)square_root::create,"sqrt"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
				virtual double eval_unary(double a);
			}; 
			inline square_root* _sqrt(algebraic_operator * parg) 
			{ 
				return static_cast<square_root*>(square_root::create(parg));
			};

			class ln : public unary_operator 
			{ 
				ln(algebraic_operator * pAlg) : unary_operator(pAlg)
				{
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new ln(pAlg);
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new ln(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)ln::create,"log"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar);
				virtual double eval_unary(double a); 
			}; 
			inline ln* _log(algebraic_operator * parg) 
			{ 
				return static_cast<ln*>(ln::create(parg)); 
			};
			
			class log : public unary_operator 
			{ 
				log(algebraic_operator * pAlg) : unary_operator(pAlg)
				{
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new log(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new log(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)log::create,"log10"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
				virtual double eval_unary(double a); 
			}; 
			inline log* _log10(algebraic_operator * parg) 
			{ 
				return static_cast<log*>(log::create(parg));
			};

			class exponential : public unary_operator 
			{ 
				exponential(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new exponential(pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new exponential(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService)
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)exponential::create,"exp"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual int to_string(char* pBuffer); 
			public : 
				virtual void annotate(PPT_INFO pParseInfo); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
				virtual double eval_unary(double a); 
			}; 
			inline exponential* _exp(algebraic_operator * parg) 
			{ 
				return static_cast<exponential*>(exponential::create(parg));
			};

			class integer_power : public unary_operator
			{
				int m_iConstant;
				integer_power(algebraic_operator * pAlg,int n) : unary_operator(pAlg), m_iConstant(n)
				{
				};
			public :
				static algebraic_operator * create(int n,algebraic_operator * pAlg)
				{
					return new integer_power(pAlg,n);
				};
				virtual algebraic_operator * create_copy()
				{
					return new integer_power(get_operand(),GetExponent());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x2u,(dword_type)integer_power::create,"INT_POW"); 
				};
			protected :
				virtual void to_IA32_binary(PCT_INFO pInfo);
				virtual void annotate(PPT_INFO pParseInfo);
			public :
				virtual int to_string(char* pBuffer);
				virtual algebraic_operator* partial_derivative(variable * pVar);
				virtual double eval_unary(double a);
				int GetExponent()
				{
					return this->m_iConstant;
				};
			};
			inline algebraic_operator * _INT_POW(int n,algebraic_operator * alg)
			{
				if ((n != 1)&&(n))
					return static_cast<integer_power*>(integer_power::create(n,alg));
				return (n)?alg:_cst(1);
			};
		}

		namespace trigonometric_operators
		{
			//DEFINE_UNARY_OPERATOR_DEFAULT(sine,sin);
			class sine : public unary_operator 
			{ 
				sine(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg)
				{
					return new sine(pAlg);
				};
				virtual algebraic_operator * create_copy()
				{
					return new sine(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)sine::create,"sin"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
				virtual double eval_unary(double a);
			}; 
			inline sine* _sin(algebraic_operator * parg) 
			{ 
				return static_cast<sine*>(sine::create(parg)); 
			};

			//DEFINE_UNARY_OPERATOR_DEFAULT(cosine,cos);
			class cosine : public unary_operator 
			{ 
				cosine(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new cosine(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new cosine(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)cosine::create,"cos");
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
				virtual double eval_unary(double a); 
			};
			inline cosine* _cos(algebraic_operator * parg) 
			{ 
				return static_cast<cosine*>(cosine::create(parg)); 
			};

			//DEFINE_UNARY_OPERATOR_DEFAULT(tangent,tan);
			class tangent : public unary_operator 
			{ 
				tangent(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new tangent(pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new tangent(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)tangent::create,"tan"); 
				};
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
				virtual double eval_unary(double a);
			};
			inline tangent* _tan(algebraic_operator * parg) 
			{ 
				return static_cast<tangent*>(tangent::create(parg)); 
			};

			//DEFINE_UNARY_OPERATOR_DEFAULT(arcsine,asin);
			class arcsine : public unary_operator 
			{ 
				arcsine(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new arcsine(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new arcsine(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)arcsine::create,"asin"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
				virtual double eval_unary(double a);
			}; 
			inline arcsine* _asin(algebraic_operator * parg) 
			{ 
				return static_cast<arcsine*>(arcsine::create(parg)); 
			};

			//DEFINE_UNARY_OPERATOR_DEFAULT(arccosine,acos);
			class arccosine : public unary_operator 
			{ 
				arccosine(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new arccosine(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new arccosine(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service();
					pService->register_class(0x1u,(dword_type)arccosine::create,"acos");
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
				virtual double eval_unary(double a);
			}; 
			inline arccosine* _acos(algebraic_operator * parg) 
			{ 
				return static_cast<arccosine*>(arccosine::create(parg)); 
			};

			//DEFINE_UNARY_OPERATOR_DEFAULT(arctangent,atan);
			class arctangent : public unary_operator 
			{ 
				arctangent(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new arctangent(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new arctangent(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)arctangent::create,"atan");
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
				virtual double eval_unary(double a); 
			}; 
			inline arctangent* _atan(algebraic_operator * parg) 
			{ 
				return static_cast<arctangent*>(arctangent::create(parg)); 
			};
		}
		namespace hyperbolic_operators
		{
			//DEFINE_UNARY_OPERATOR_DEFAULT(sinh,sinh);
			class sinh : public unary_operator 
			{ 
				sinh(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new sinh(pAlg);
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new sinh(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)sinh::create,"sinh");
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual double eval_unary(double a);
				virtual algebraic_operator* partial_derivative(variable * pVar);
			}; 
			inline sinh* _sinh(algebraic_operator * parg) 
			{ 
				return static_cast<sinh*>(sinh::create(parg)); 
			};

			//DEFINE_UNARY_OPERATOR_DEFAULT(cosh,cosh);
			class cosh : public unary_operator 
			{ 
				cosh(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new cosh(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new cosh(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service();
					pService->register_class(0x1u,(dword_type)cosh::create,"cosh"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual double eval_unary(double a);
				virtual algebraic_operator* partial_derivative(variable * pVar);
			}; 
			inline cosh* _cosh(algebraic_operator * parg) 
			{ 
				return static_cast<cosh*>(cosh::create(parg)); 
			};

			//DEFINE_UNARY_OPERATOR_DEFAULT(tanh,tanh);
			class tanh : public unary_operator 
			{ 
				tanh(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new tanh(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new tanh(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)tanh::create,"tanh"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual double eval_unary(double a);
			}; 
			inline tanh* _tanh(algebraic_operator * parg) 
			{ 
				return static_cast<tanh*>(tanh::create(parg)); 
			};
		}
		namespace bessel_operators
		{
			//DEFINE_UNARY_OPERATOR_DEFAULT(bessel_y0,_y0);
			class bessel_y0 : public unary_operator 
			{ 
				bessel_y0(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg)
				{ 
					return new bessel_y0(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new bessel_y0(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)bessel_y0::create,"_y0"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo);
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual double eval_unary(double a);
			}; 
			inline bessel_y0* __y0(algebraic_operator * parg) 
			{ 
				return static_cast<bessel_y0*>(bessel_y0::create(parg)); 
			};

			//DEFINE_UNARY_OPERATOR_DEFAULT(bessel_y1,_y1);
			class bessel_y1 : public unary_operator 
			{ 
				bessel_y1(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new bessel_y1(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new bessel_y1(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)bessel_y1::create,"_y1"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual double eval_unary(double a);
			};
			inline bessel_y1* __y1(algebraic_operator * parg) 
			{ 
				return static_cast<bessel_y1*>(bessel_y1::create(parg));
			};

			class bessel_yn : public unary_operator
			{
				unsigned int m_uiConstant;
				bessel_yn(unsigned int n,algebraic_operator * pAlg) : unary_operator(pAlg), m_uiConstant(n)
				{
				};
			public :
				static algebraic_operator * create(int n,algebraic_operator * pAlg)
				{
					return new bessel_yn(n,pAlg);
				};
				virtual algebraic_operator * create_copy()
				{
					return new bessel_yn(GetBesselIndex(),get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service();
					pService->register_class(0x2u,(dword_type)bessel_yn::create,"_yn"); 
				};
			protected :
				virtual void to_IA32_binary(PCT_INFO pInfo);
				virtual void annotate(PPT_INFO pParseInfo);
			public :
				virtual int to_string(char* pBuffer);
				virtual double eval_unary(double a);
				unsigned int GetBesselIndex()
				{
					return this->m_uiConstant;
				};
			};
			inline bessel_yn * __yn(unsigned int n,algebraic_operator * pAlg)
			{
				return static_cast<bessel_yn*>(bessel_yn::create(n,pAlg));
			};
			
			//DEFINE_UNARY_OPERATOR_DEFAULT(bessel_j0,_j0);
			class bessel_j0 : public unary_operator 
			{
				bessel_j0(algebraic_operator * pAlg) : unary_operator(pAlg)
				{
				};
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new bessel_j0(pAlg); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new bessel_j0(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)bessel_j0::create,"_j0"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual double eval_unary(double a); 
			}; 
			inline bessel_j0* __j0(algebraic_operator * parg) 
			{ 
				return static_cast<bessel_j0*>(bessel_j0::create(parg)); 
			};

			//DEFINE_UNARY_OPERATOR_DEFAULT(bessel_j1,_j1);
			class bessel_j1 : public unary_operator 
			{ 
				bessel_j1(algebraic_operator * pAlg) : unary_operator(pAlg)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * pAlg) 
				{ 
					return new bessel_j1(pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new bessel_j1(get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x1u,(dword_type)bessel_j1::create,"_j1"); 
				}; 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo);
				virtual void annotate(PPT_INFO pParseInfo); 
			public : 
				virtual int to_string(char* pBuffer); 
				virtual double eval_unary(double a); 
			}; 
			inline bessel_j1* __j1(algebraic_operator * parg) 
			{ 
				return static_cast<bessel_j1*>(bessel_j1::create(parg));
			};

			class bessel_jn : public unary_operator
			{
				unsigned int m_uiConstant;
				bessel_jn(unsigned int n,algebraic_operator * pAlg) : unary_operator(pAlg), m_uiConstant(n)
				{
				};
			public :
				static algebraic_operator * create(int n,algebraic_operator * pAlg)
				{
					return new bessel_jn(n,pAlg);
				};
				virtual algebraic_operator * create_copy()
				{
					return new bessel_jn(GetBesselIndex(),get_operand());
				};
				static void Register(algebra_parser * pService)
				{
					if (!pService)
						pService = algebra_parser::get_service();
					pService->register_class(CLASS_UNARY_EXTENDED,(dword_type)bessel_jn::create,"_jn");
				}
			protected :
				virtual void to_IA32_binary(PCT_INFO pInfo);
				virtual void annotate(PPT_INFO pParseInfo);
			public :
				virtual int to_string(char* pBuffer);
				virtual double eval_unary(double a);
				unsigned int GetBesselIndex()
				{
					return this->m_uiConstant;
				};
			};
			inline bessel_jn * __jn(unsigned int n,algebraic_operator * pAlg)
			{
				return static_cast<bessel_jn*>(bessel_jn::create(n,pAlg));
			};
		}
		namespace derivative_operators
		{
			class derivative_operator : public unary_operator
			{
				calculus::variable * m_pv_derivative_var;
				double * m_pi_derivative_coefficients;
				double m_h;
				int m_i_num_coefficients;
#define LMODE_CENTERED	0x1u
#define LMODE_BACKWARD	0x2u
#define LMODE_FORWARD	0x4u
				unsigned int m_lMode;
			protected :
				derivative_operator(unsigned int nCoeff,unsigned int nMode,double * pDCoeffs,variable * pVar,algebraic_operator * pAlg);
				virtual ~derivative_operator();
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			public :
				virtual int to_string(char* pBuffer); 
				virtual double eval(double* pVars);
				variable * get_partial_derivative_variable();
				int get_number_of_coefficients();
			};
			class derivative_3c : public derivative_operator
			{ 
				static double s_pD3PCCoefficients[3];
				derivative_3c(variable * pVar,algebraic_operator * pAlg) : derivative_operator(3,LMODE_CENTERED,s_pD3PCCoefficients,pVar,pAlg)	{	};
			public : 
				static algebraic_operator * create(variable * pVar,algebraic_operator * pAlg) 
				{ 
					return new derivative_3c(pVar,pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new derivative_3c(get_partial_derivative_variable(),get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x2u,(dword_type)derivative_3c::create,"_d3pc"); 
				}; 
			};
			inline derivative_3c* __d3pc(variable * pvar,algebraic_operator * parg) 
			{ 
				return static_cast<derivative_3c*>(derivative_3c::create(pvar,parg)); 
			};

			class derivative_3f : public derivative_operator
			{ 
				static double s_pD3PFCoefficients[3];
				derivative_3f(variable * pVar,algebraic_operator * pAlg) : derivative_operator(3,LMODE_FORWARD,s_pD3PFCoefficients,pVar,pAlg)	{	};
			public : 
				static algebraic_operator * create(variable * pVar,algebraic_operator * pAlg) 
				{ 
					return new derivative_3f(pVar,pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new derivative_3f(get_partial_derivative_variable(),get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x2u,(dword_type)derivative_3f::create,"_d3pf"); 
				}; 
			};
			inline derivative_3f* __d3pf(variable * pvar,algebraic_operator * parg) 
			{ 
				return static_cast<derivative_3f*>(derivative_3f::create(pvar,parg)); 
			};

			class derivative_3b : public derivative_operator
			{ 
				static double s_pD3PBCoefficients[3];
				derivative_3b(variable * pVar,algebraic_operator * pAlg) : derivative_operator(3,LMODE_BACKWARD,s_pD3PBCoefficients,pVar,pAlg)	{	};
			public : 
				static algebraic_operator * create(variable * pVar,algebraic_operator * pAlg) 
				{ 
					return new derivative_3b(pVar,pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new derivative_3b(get_partial_derivative_variable(),get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x2u,(dword_type)derivative_3b::create,"_d3pb"); 
				}; 
			};
			inline derivative_3b* __d3pb(variable * pvar,algebraic_operator * parg) 
			{ 
				return static_cast<derivative_3b*>(derivative_3b::create(pvar,parg)); 
			};

			class derivative_5c : public derivative_operator
			{ 
				static double s_pD5PCCoefficients[5];
				derivative_5c(variable * pVar,algebraic_operator * pAlg) : derivative_operator(5,LMODE_CENTERED,s_pD5PCCoefficients,pVar,pAlg)	{	};
			public : 
				static algebraic_operator * create(variable * pVar,algebraic_operator * pAlg) 
				{ 
					return new derivative_5c(pVar,pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new derivative_5c(get_partial_derivative_variable(),get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x2u,(dword_type)derivative_5c::create,"_d5pc"); 
				}; 
			};
			inline derivative_5c* __d5pc(variable * pvar,algebraic_operator * parg) 
			{ 
				return static_cast<derivative_5c*>(derivative_5c::create(pvar,parg)); 
			};

			class derivative_5f : public derivative_operator
			{ 
				static double s_pD5PFCoefficients[5];
				derivative_5f(variable * pVar,algebraic_operator * pAlg) : derivative_operator(5,LMODE_FORWARD,s_pD5PFCoefficients,pVar,pAlg)	{	};
			public : 
				static algebraic_operator * create(variable * pVar,algebraic_operator * pAlg) 
				{ 
					return new derivative_5f(pVar,pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new derivative_5f(get_partial_derivative_variable(),get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x2u,(dword_type)derivative_5f::create,"_d5pf"); 
				}; 
			};
			inline derivative_5f* __d5pf(variable * pvar,algebraic_operator * parg) 
			{ 
				return static_cast<derivative_5f*>(derivative_5f::create(pvar,parg)); 
			};

			class derivative_5b : public derivative_operator
			{ 
				static double s_pD5PBCoefficients[5];
				derivative_5b(variable * pVar,algebraic_operator * pAlg) : derivative_operator(5,LMODE_BACKWARD,s_pD5PBCoefficients,pVar,pAlg)	{	};
			public :
				static algebraic_operator * create(variable * pVar,algebraic_operator * pAlg) 
				{ 
					return new derivative_5b(pVar,pAlg); 
				};
				virtual algebraic_operator * create_copy()
				{
					return new derivative_5b(get_partial_derivative_variable(),get_operand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x2u,(dword_type)derivative_5b::create,"_d5pb"); 
				}; 
			};
			inline derivative_5b* __d5pb(variable * pvar,algebraic_operator * parg) 
			{ 
				return static_cast<derivative_5b*>(derivative_5b::create(pvar,parg)); 
			};
		}
		namespace polynomials
		{
            enum poly_function_type {
		        Standard = 0x1u,
		        Optimized,
		        Interpolatory
	        };

            class polynomial;
			polynomial * _poly(unsigned int uiOrder,poly_function_type pft,double * pAis,algebraic_operator* pF);
			polynomial * _poly(unsigned int uiOrder,double * pXs,double * pAis,algebraic_operator* pF);
			polynomial * _lagrange_poly(unsigned int uiNumPoints,double * pXs,double * pYs,algebraic_operator* pF);
			polynomial * _lagrange_poly(unsigned int uiOrder,double a,double b,algebraic_operator* pF);
			class polynomial : public unary_operator
			{
				unsigned int m_uiOrder;
				double** m_ppi_coefficients;
				poly_function_type m_epoly_function_type;
			protected :
				polynomial(unsigned int uiOrder,poly_function_type pft,double * pAis,algebraic_operator* pF);
				polynomial(unsigned int uiOrder,double * pXs,double * pAis,algebraic_operator* pF);
				virtual ~polynomial();
				void __load_interpolant(unsigned int uiOrder,double * pIC_1,double * pIC_2);
			public :
				static void get_lagrange_interpolatory_coefficients_from_function(unsigned int uiOrder,double a,double b,algebraic_operator* pF,double ** ppXs,double ** ppAis);
				static void get_lagrange_interpolatory_coefficients_from_points(unsigned int uiNumPoints,double * pXs,double * pYs,double ** ppAis);
				static algebraic_operator * create_lagrange_polynomial(unsigned int uiNumPoints,double * pXs,double * pYs,algebraic_operator* pF)
				{
					double * pAis;
					get_lagrange_interpolatory_coefficients_from_points(uiNumPoints,pXs,pYs,&pAis);
					polynomial * pPF = _poly(uiNumPoints-1,pXs,pAis,pF);
					delete [] pAis;
					return pPF;
				}
				static algebraic_operator * create_lagrange_polynomial(unsigned int uiOrder,double a,double b,algebraic_operator* pF)
				{
					double * pAis, * pXs;
					get_lagrange_interpolatory_coefficients_from_function(uiOrder,a,b,pF,&pXs,&pAis);
					polynomial * pPF = _poly(uiOrder,pXs,pAis,pF);
					delete [] pAis;
					delete [] pXs;
					return pPF;
				}
                static polynomial * create(unsigned int uiOrder,poly_function_type pft,double * pAis,algebraic_operator* pF)
				{
					return new polynomial(uiOrder,pft,pAis,pF);
				};
				static polynomial * create(unsigned int uiOrder,double * pXs,double * pAis,algebraic_operator* pF)
				{
					return new polynomial(uiOrder,pXs,pAis,pF);
				};
				virtual double eval_unary(double a);
				virtual algebraic_operator* partial_derivative(variable * pVar);
				virtual int to_string(char* pBuffer);
			protected :
				virtual void to_IA32_binary(PCT_INFO pInfo);
				virtual void annotate(PPT_INFO pParseInfo);
			};
/*			
			class CHermitePolyFunction : public polynomial
			{
			public :
				static DATA<double,2> *HermiteInterpolatoryCoefficientsFromPoints(unsigned int uiNumPoints,DATA<double,3>* pPoints);
				CHermitePolyFunction(unsigned int uiNumPoints, DATA<double,3>* pPoints);
			};
			
			class CSplineFunction : public polynomial
			{
			public :
				CSplineFunction(CSplineFunction& op) : polynomial(op) { };
				virtual algebraic_operator* Mirror() {
					algebraic_operator * pret = NULL;
					if (this->m_bMirrorCopy)
					{
						pret = new CSplineFunction(*this);
					}
					else
					{
						pret = this;
					}
					pret->addref();
					return pret;
				};
			protected :
				CSplineFunction();
			public :
				static void NaturalSplineCoefficientsFromPoints(unsigned int uiNumPoints,DATA<double,2>* pPoints,DATA<double,4>** pCs);
				static void ClampedSplineCoefficientsFromPoints(unsigned int uiNumPoints,double start_derivative,double end_derivative,double *lpXPoints,double *lpYPoints,double **lplpABuffer,double **lplpBBuffer,double **lplpCBuffer,double **lplpDBuffer);
				static double *PolyCoefficientsFromSplineCoefficients(unsigned int uiSplineIndex,DATA<double,5>* pAi,double *lpBuffer);
				virtual ~CSplineFunction();
			public :
				virtual algebraic_operator* simplify();
				virtual double eval(double point);
				virtual algebraic_operator* partial_derivative();
				virtual algebraic_operator* Integral();
			protected :
				virtual int to_string(char* pBuffer);
				virtual void to_IA32_binary(PCT_INFO pInfo);
				virtual void annotate(PPT_INFO pParseInfo);
			};
		*/
		}
	}
	namespace binary_operators
	{
		class binary_operator : public algebraic_operator
		{
			algebraic_operator* m_pao_left_operand;
			algebraic_operator* m_pao_right_operand;
		protected :
			binary_operator(algebraic_operator * pAlg1,algebraic_operator * pAlg2) : algebraic_operator(), m_pao_left_operand(pAlg1), m_pao_right_operand(pAlg2)
			{
				if (m_pao_left_operand)
					m_pao_left_operand->addref();
				if (m_pao_right_operand)
					m_pao_right_operand->addref();
			};
			virtual ~binary_operator()
			{
				if (m_pao_left_operand)
					m_pao_left_operand->release();
				if (m_pao_right_operand)
					m_pao_right_operand->release();
			};
			virtual double eval_binary(double x,double y)
			{	
				UNREFERENCED_PARAMETER(x);
				UNREFERENCED_PARAMETER(y);
				return 0;
			};
			virtual variable** identify_variables();
		private:
			static bool UseConstantOptimizations;
		public :
			static inline bool IsUsingConstantOptimizations() { return UseConstantOptimizations; };
			static inline bool EnableConstantOptimizations() { bool pstate = IsUsingConstantOptimizations(); UseConstantOptimizations = true; return pstate; };
			static inline bool DisableConstantOptimizations() { bool pstate = IsUsingConstantOptimizations(); UseConstantOptimizations = false; return pstate; };
		private:
			static bool UseFlipOptimizations;
		public :
			static inline bool IsUsingFlipOptimizations() { return UseFlipOptimizations; };
			static inline bool EnableFlipOptimizations() { bool pstate = IsUsingFlipOptimizations(); UseFlipOptimizations= true; return pstate; };
			static inline bool DisableFlipOptimizations() { bool pstate = IsUsingFlipOptimizations(); UseFlipOptimizations = false; return pstate; };
		private:
			static bool UseDisorderedOptimizations;
		public :
			static inline bool IsUsingDisorderedOptimizations() { return UseDisorderedOptimizations; };
			static inline bool EnableDisorderedOptimizations() { bool pstate = IsUsingDisorderedOptimizations(); UseDisorderedOptimizations = true; return pstate; };
			static inline bool DisableDisorderedOptimizations() { bool pstate = IsUsingDisorderedOptimizations(); UseDisorderedOptimizations = false; return pstate; };
			virtual double eval(double* pVars);
			algebraic_operator* GetLeftOperand()
			{
				return m_pao_left_operand;
			};
			algebraic_operator* GetRightOperand()
			{
				return m_pao_right_operand;
			};
		};

		namespace intrinsic_operators
		{
			class addition : public binary_operator 
			{ 
				addition(algebraic_operator * pAlg1,algebraic_operator * pAlg2) : binary_operator(pAlg1,pAlg2)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * Alg1,algebraic_operator * Alg2) 
				{ 
					return new addition(Alg1,Alg2); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new addition(GetLeftOperand(),GetRightOperand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x4u,(dword_type)addition::create,"add"); 
				}; 
				virtual double eval_binary(double x,double y); 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			}; 
			algebraic_operator * _add(algebraic_operator * arg1,algebraic_operator * arg2);

			class subtraction : public binary_operator 
			{ 
				subtraction(algebraic_operator * pAlg1,algebraic_operator * pAlg2) : binary_operator(pAlg1,pAlg2)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * Alg1,algebraic_operator * Alg2) 
				{ 
					return new subtraction(Alg1,Alg2); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new subtraction(GetLeftOperand(),GetRightOperand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x4u,(dword_type)subtraction::create,"subtract"); 
				}; 
				virtual double eval_binary(double x,double y); 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			}; 
			calculus::algebraic_operator * _subtract(calculus::algebraic_operator * arg1,calculus::algebraic_operator * arg2); 

			class multiplication : public binary_operator 
			{ 
				multiplication(algebraic_operator * pAlg1,algebraic_operator * pAlg2) : binary_operator(pAlg1,pAlg2)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * Alg1,algebraic_operator * Alg2) 
				{ 
					return new multiplication(Alg1,Alg2);
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new multiplication(GetLeftOperand(),GetRightOperand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x4u,(dword_type)multiplication::create,"multiply");
				};
				virtual double eval_binary(double x,double y); 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			}; 
			calculus::algebraic_operator * _multiply(calculus::algebraic_operator * arg1,calculus::algebraic_operator * arg2); 

			class division : public binary_operator 
			{ 
				division(algebraic_operator * pAlg1,algebraic_operator * pAlg2) : binary_operator(pAlg1,pAlg2)
				{ 
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * Alg1,algebraic_operator * Alg2) 
				{ 
					return new division(Alg1,Alg2); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new division(GetLeftOperand(),GetRightOperand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x4u,(dword_type)division::create,"divide"); 
				};
				virtual double eval_binary(double x,double y); 
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			}; 
			calculus::algebraic_operator * _divide(calculus::algebraic_operator * arg1,calculus::algebraic_operator * arg2); 

			class exponentiation : public binary_operator 
			{ 
				exponentiation(algebraic_operator * pAlg1,algebraic_operator * pAlg2) : binary_operator(pAlg1,pAlg2)
				{
				}; 
			public : 
				static algebraic_operator * create(algebraic_operator * Alg1,algebraic_operator * Alg2) 
				{
					return new exponentiation(Alg1,Alg2); 
				}; 
				virtual algebraic_operator * create_copy()
				{
					return new exponentiation(GetLeftOperand(),GetRightOperand());
				};
				static void Register(algebra_parser * pService) 
				{ 
					if (!pService) 
						pService = algebra_parser::get_service(); 
					pService->register_class(0x4u,(dword_type)exponentiation::create,"pow"); 
				}; 
				virtual double eval_binary(double x,double y);
				virtual int to_string(char* pBuffer); 
				virtual algebraic_operator* partial_derivative(variable * pVar); 
			protected : 
				virtual void to_IA32_binary(PCT_INFO pInfo); 
				virtual void annotate(PPT_INFO pParseInfo); 
			}; 
			calculus::algebraic_operator * _pow(calculus::algebraic_operator * arg1,calculus::algebraic_operator * arg2);
		}
	}
}

