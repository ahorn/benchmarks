/* Simplified */

/*--------------------------------------------------------------------*/
/*--- Header included by every tool C file.      pub_tool_basics.h ---*/
/*--------------------------------------------------------------------*/

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2000-2013 Julian Seward 
      jseward@acm.org

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

#ifndef __PUB_TOOL_BASICS_H
#define __PUB_TOOL_BASICS_H

//--------------------------------------------------------------------
// PURPOSE: This header should be imported by every single C file in
// tools.  It contains the basic types and other things needed everywhere.
// There is no corresponding C file because this isn't a module
// containing executable code, it's all just declarations.
//--------------------------------------------------------------------

/* ---------------------------------------------------------------------
   Other headers to include
   ------------------------------------------------------------------ */

typedef signed char Char;
typedef unsigned char UChar;
typedef signed short Short;
typedef unsigned short UShort;
typedef signed int Int;
typedef unsigned int UInt;
typedef signed long Long;
typedef unsigned int ULong;
typedef int Bool;
typedef char HChar;

#define False 0
#define True 1

/* ---------------------------------------------------------------------
   symbol prefixing
   ------------------------------------------------------------------ */
 
// All symbols externally visible from Valgrind are prefixed
// as specified here to avoid namespace conflict problems.
//
// VG_ is for symbols exported from modules.  ML_ (module-local) is
// for symbols which are not intended to be visible outside modules,
// but which cannot be declared as C 'static's since they need to be
// visible across C files within a given module.  It is a mistake for
// a ML_ name to appear in a pub_core_*.h or pub_tool_*.h file.
// Likewise it is a mistake for a VG_ name to appear in a priv_*.h
// file. 

#define VGAPPEND(str1,str2) str1##str2

#define VG_(str)    VGAPPEND(vgPlain_,          str)
#define ML_(str)    VGAPPEND(vgModuleLocal_,    str)


/* ---------------------------------------------------------------------
   builtin types
   ------------------------------------------------------------------ */

// By choosing the right types, we can get these right for 32-bit and 64-bit
// platforms without having to do any conditional compilation or anything.
// POSIX references:
// - http://www.opengroup.org/onlinepubs/009695399/basedefs/sys/types.h.html
// - http://www.opengroup.org/onlinepubs/009695399/basedefs/stddef.h.html
// 
// Size in bits on:                          32-bit archs   64-bit archs
//                                           ------------   ------------
typedef unsigned long          UWord;     // 32             64
typedef   signed long           Word;     // 32             64

// Addr is for holding an address.  AddrH was intended to be "Addr on the
// host", for the notional case where host word size != guest word size.
// But since the assumption that host arch == guest arch has become so
// deeply wired in, it's a pretty pointless distinction now.
typedef UWord                  Addr;      // 32             64
typedef UWord                  AddrH;     // 32             64

// Our equivalents of POSIX 'size_t' and 'ssize_t':
// - size_t is an "unsigned integer type of the result of the sizeof operator".
// - ssize_t is "used for a count of bytes or an error indication".
typedef UWord                  SizeT;     // 32             64
typedef  Word                 SSizeT;     // 32             64

// Our equivalent of POSIX 'ptrdiff_t':
// - ptrdiff_t is a "signed integer type of the result of subtracting two
//   pointers".
// We use it for memory offsets, eg. the offset into a memory block.
typedef  Word                 PtrdiffT;   // 32             64

#if !defined(NULL)
#  define NULL ((void*)0)
#endif

/* This is just too useful to not have around the place somewhere. */
typedef  struct { UWord uw1; UWord uw2; }  UWordPair;


/* ---------------------------------------------------------------------
   non-builtin types
   ------------------------------------------------------------------ */

// These probably shouldn't be here, but moving them to their logical
// modules results in a lot more #includes...

/* ThreadIds are simply indices into the VG_(threads)[] array. */
typedef UInt ThreadId;

#endif /* __PUB_TOOL_BASICS_H */

/*--------------------------------------------------------------------*/
/*--- end                                                          ---*/
/*--------------------------------------------------------------------*/
