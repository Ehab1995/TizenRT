/******************************************************************
 *
 * Copyright 2019 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

/*
 * tie.h -- compile-time HAL definitions dependent on CORE & TIE configuration
 *
 *  NOTE:  This header file is not meant to be included directly.
 */

/* This header file describes this specific Xtensa processor's TIE extensions
   that extend basic Xtensa core functionality.  It is customized to this
   Xtensa processor configuration.

   Customer ID=11657; Build=0x5fe96; Copyright (c) 1999-2016 Cadence Design Systems Inc.

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#ifndef _XTENSA_CORE_TIE_H
#define _XTENSA_CORE_TIE_H

#define XCHAL_CP_NUM			1	/* number of coprocessors */
#define XCHAL_CP_MAX			1	/* max CP ID + 1 (0 if none) */
#define XCHAL_CP_MASK			0x01	/* bitmask of all CPs by ID */
#define XCHAL_CP_PORT_MASK		0x00	/* bitmask of only port CPs */

/*  Basic parameters of each coprocessor:  */
#define XCHAL_CP0_NAME			"FPU"
#define XCHAL_CP0_IDENT			FPU
#define XCHAL_CP0_SA_SIZE		72	/* size of state save area */
#define XCHAL_CP0_SA_ALIGN		4	/* min alignment of save area */
#define XCHAL_CP_ID_FPU             	0	/* coprocessor ID (0..7) */

/*  Filler info for unassigned coprocessors, to simplify arrays etc:  */
#define XCHAL_CP1_SA_SIZE		0
#define XCHAL_CP1_SA_ALIGN		1
#define XCHAL_CP2_SA_SIZE		0
#define XCHAL_CP2_SA_ALIGN		1
#define XCHAL_CP3_SA_SIZE		0
#define XCHAL_CP3_SA_ALIGN		1
#define XCHAL_CP4_SA_SIZE		0
#define XCHAL_CP4_SA_ALIGN		1
#define XCHAL_CP5_SA_SIZE		0
#define XCHAL_CP5_SA_ALIGN		1
#define XCHAL_CP6_SA_SIZE		0
#define XCHAL_CP6_SA_ALIGN		1
#define XCHAL_CP7_SA_SIZE		0
#define XCHAL_CP7_SA_ALIGN		1

/*  Save area for non-coprocessor optional and custom (TIE) state:  */
#define XCHAL_NCP_SA_SIZE		48
#define XCHAL_NCP_SA_ALIGN		4

/*  Total save area for optional and custom state (NCP + CPn):  */
#define XCHAL_TOTAL_SA_SIZE		128	/* with 16-byte align padding */
#define XCHAL_TOTAL_SA_ALIGN		4	/* actual minimum alignment */

/*
 * Detailed contents of save areas.
 * NOTE:  caller must define the XCHAL_SA_REG macro (not defined here)
 * before expanding the XCHAL_xxx_SA_LIST() macros.
 *
 * XCHAL_SA_REG(s,ccused,abikind,kind,opt,name,galign,align,asize,
 *		dbnum,base,regnum,bitsz,gapsz,reset,x...)
 *
 *	s = passed from XCHAL_*_LIST(s), eg. to select how to expand
 *	ccused = set if used by compiler without special options or code
 *	abikind = 0 (caller-saved), 1 (callee-saved), or 2 (thread-global)
 *	kind = 0 (special reg), 1 (TIE user reg), or 2 (TIE regfile reg)
 *	opt = 0 (custom TIE extension or coprocessor), or 1 (optional reg)
 *	name = lowercase reg name (no quotes)
 *	galign = group byte alignment (power of 2) (galign >= align)
 *	align = register byte alignment (power of 2)
 *	asize = allocated size in bytes (asize*8 == bitsz + gapsz + padsz)
 *	  (not including any pad bytes required to galign this or next reg)
 *	dbnum = unique target number f/debug (see <xtensa-libdb-macros.h>)
 *	base = reg shortname w/o index (or sr=special, ur=TIE user reg)
 *	regnum = reg index in regfile, or special/TIE-user reg number
 *	bitsz = number of significant bits (regfile width, or ur/sr mask bits)
 *	gapsz = intervening bits, if bitsz bits not stored contiguously
 *	(padsz = pad bits at end [TIE regfile] or at msbits [ur,sr] of asize)
 *	reset = register reset value (or 0 if undefined at reset)
 *	x = reserved for future use (0 until then)
 *
 *  To filter out certain registers, e.g. to expand only the non-global
 *  registers used by the compiler, you can do something like this:
 *
 *  #define XCHAL_SA_REG(s,ccused,p...)	SELCC##ccused(p)
 *  #define SELCC0(p...)
 *  #define SELCC1(abikind,p...)	SELAK##abikind(p)
 *  #define SELAK0(p...)		REG(p)
 *  #define SELAK1(p...)		REG(p)
 *  #define SELAK2(p...)
 *  #define REG(kind,tie,name,galn,aln,asz,csz,dbnum,base,rnum,bsz,rst,x...) \
 *		...what you want to expand...
 */

#define XCHAL_NCP_SA_NUM	12
#define XCHAL_NCP_SA_LIST(s)	\
 XCHAL_SA_REG(s,1,2,1,1,      threadptr, 4, 4, 4,0x03E7,  ur,231, 32,0,0,0) \
 XCHAL_SA_REG(s,1,0,0,1,          acclo, 4, 4, 4,0x0210,  sr,16 , 32,0,0,0) \
 XCHAL_SA_REG(s,1,0,0,1,          acchi, 4, 4, 4,0x0211,  sr,17 ,  8,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,             br, 4, 4, 4,0x0204,  sr,4  , 16,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,      scompare1, 4, 4, 4,0x020C,  sr,12 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,             m0, 4, 4, 4,0x0220,  sr,32 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,             m1, 4, 4, 4,0x0221,  sr,33 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,             m2, 4, 4, 4,0x0222,  sr,34 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,0,1,             m3, 4, 4, 4,0x0223,  sr,35 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,        f64r_lo, 4, 4, 4,0x03EA,  ur,234, 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,        f64r_hi, 4, 4, 4,0x03EB,  ur,235, 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,           f64s, 4, 4, 4,0x03EC,  ur,236, 32,0,0,0)

#define XCHAL_CP0_SA_NUM	18
#define XCHAL_CP0_SA_LIST(s)	\
 XCHAL_SA_REG(s,0,0,1,0,            fcr, 4, 4, 4,0x03E8,  ur,232, 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,1,0,            fsr, 4, 4, 4,0x03E9,  ur,233, 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             f0, 4, 4, 4,0x0030,   f,0  , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             f1, 4, 4, 4,0x0031,   f,1  , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             f2, 4, 4, 4,0x0032,   f,2  , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             f3, 4, 4, 4,0x0033,   f,3  , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             f4, 4, 4, 4,0x0034,   f,4  , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             f5, 4, 4, 4,0x0035,   f,5  , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             f6, 4, 4, 4,0x0036,   f,6  , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             f7, 4, 4, 4,0x0037,   f,7  , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             f8, 4, 4, 4,0x0038,   f,8  , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,             f9, 4, 4, 4,0x0039,   f,9  , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,            f10, 4, 4, 4,0x003A,   f,10 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,            f11, 4, 4, 4,0x003B,   f,11 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,            f12, 4, 4, 4,0x003C,   f,12 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,            f13, 4, 4, 4,0x003D,   f,13 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,            f14, 4, 4, 4,0x003E,   f,14 , 32,0,0,0) \
 XCHAL_SA_REG(s,0,0,2,0,            f15, 4, 4, 4,0x003F,   f,15 , 32,0,0,0)

#define XCHAL_CP1_SA_NUM	0
#define XCHAL_CP1_SA_LIST(s)	/* empty */

#define XCHAL_CP2_SA_NUM	0
#define XCHAL_CP2_SA_LIST(s)	/* empty */

#define XCHAL_CP3_SA_NUM	0
#define XCHAL_CP3_SA_LIST(s)	/* empty */

#define XCHAL_CP4_SA_NUM	0
#define XCHAL_CP4_SA_LIST(s)	/* empty */

#define XCHAL_CP5_SA_NUM	0
#define XCHAL_CP5_SA_LIST(s)	/* empty */

#define XCHAL_CP6_SA_NUM	0
#define XCHAL_CP6_SA_LIST(s)	/* empty */

#define XCHAL_CP7_SA_NUM	0
#define XCHAL_CP7_SA_LIST(s)	/* empty */

/* Byte length of instruction from its first nibble (op0 field), per FLIX.  */
#define XCHAL_OP0_FORMAT_LENGTHS	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3
/* Byte length of instruction from its first byte, per FLIX.  */
#define XCHAL_BYTE0_FORMAT_LENGTHS	\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3,\
	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3, 3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3

#endif /*_XTENSA_CORE_TIE_H*/
