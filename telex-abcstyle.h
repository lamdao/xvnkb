/*----------------------------------------------------------------------------*/
/*  telex-abcstyle.h -- ABC liked Telex keystroke                             */
/*----------------------------------------------------------------------------*/
/*  copyright         : (C) 2002 by Dao Hai Lam                               */
/*                      VISC Software & Security Consultant Company           */
/*                      Hall 3, Quang Trung Software City                     */
/*                      Tan Chanh Hiep Ward, District 12,                     */
/*                      Ho Chi Minh city, VIETNAM                             */
/*  website           : http://www.visc-network.com                           */
/*  email             : lam@visc-network.com                                  */
/*  last modify       : Thu, 18 Apr 2002 22:00:33 +0700                       */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*   This program is free software; you can redistribute it and/or modify     */
/*   it under the terms of the GNU General Public License as published by     */
/*   the Free Software Foundation; either version 2 of the License, or        */
/*   (at your option) any later version.                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#ifndef __VK_ABC_TELEX
#define __VK_ABC_TELEX
/*----------------------------------------------------------------------------*/
static vietcode_t code_A[] =
{
	{ utf_A,	utf_A6 },				//	A => A^
	{ utf_A1,	utf_A61 },				//	A => A^'
	{ utf_A2,	utf_A62 },				//	A => A^`
	{ utf_A3,	utf_A63 },				//	A => A^?
	{ utf_A4,	utf_A64 },				//	A => A^~
	{ utf_A5,	utf_A65 },				//	A => A^.
	{ utf_A6,	utf_A, utf_A },			//	A^ => AA
	{ utf_A61,	utf_A1, utf_A },		//	A^' => A'A
	{ utf_A62,	utf_A2, utf_A },		//	A^` => A`A
	{ utf_A63,	utf_A3, utf_A },		//	A^? => A?A
	{ utf_A64,	utf_A4, utf_A },		//	A^~ => A~A
	{ utf_A65,	utf_A5, utf_A },		//	A^. => A.A
	{ utf_A8,	utf_A6 },				//	A( => A^
	{ utf_A81,	utf_A61 },				//	A(' => A^'
	{ utf_A82,	utf_A62 },				//	A(` => A^`
	{ utf_A83,	utf_A63 },				//	A(? => A^?
	{ utf_A84,	utf_A64 },				//	A(~ => A^~
	{ utf_A85,	utf_A65 },				//	A(. => A^.
	{ utf_a,	utf_A6 },				//	a => A^
	{ utf_a1,	utf_A61 },				//	a' => a^'
	{ utf_a2,	utf_A62 },				//	a` => a^`
	{ utf_a3,	utf_A63 },				//	a? => a^?
	{ utf_a4,	utf_A64 },				//	a~ => a^~
	{ utf_a5,	utf_A65 },				//	a. => a^.
	{ utf_a6,	utf_A, utf_A },			//	a^ => AA
	{ utf_a61,	utf_A1, utf_A },		//	a^' => A'A
	{ utf_a62,	utf_A2, utf_A },		//	a^` => A`A
	{ utf_a63,	utf_A3, utf_A },		//	a^? => A?A
	{ utf_a64,	utf_A4, utf_A },		//	a^~ => A~A
	{ utf_a65,	utf_A5, utf_A },		//	a^. => A.A
	{ utf_a8,	utf_A6 },				//	a( => A^
	{ utf_a81,	utf_A61 },				//	a(' => A^'
	{ utf_a82,	utf_A62 },				//	a(` => A^`
	{ utf_a83,	utf_A63 },				//	a(? => A^?
	{ utf_a84,	utf_A64 },				//	a(~ => A^~
	{ utf_a85,	utf_A65 },				//	a(. => A^.
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_a[] =
{
	{ utf_A,	utf_a6 },				//	A => a^
	{ utf_A1,	utf_a61 },				//	A' => a^'
	{ utf_A2,	utf_a62 },				//	A` => a^`
	{ utf_A3,	utf_a63 },				//	A? => a^?
	{ utf_A4,	utf_a64 },				//	A~ => a^~
	{ utf_A5,	utf_a65 },				//	A. => a^.
	{ utf_A6,	utf_a, utf_a },			//	A^ => aa
	{ utf_A61,	utf_a1, utf_a },		//	A^' => a'a
	{ utf_A62,	utf_a2, utf_a },		//	A^` => a`a
	{ utf_A63,	utf_a3, utf_a },		//	A^? => a?a
	{ utf_A64,	utf_a4, utf_a },		//	A^~ => a~a
	{ utf_A65,	utf_a5, utf_a },		//	A^. => a.a
	{ utf_A8,	utf_a6 },				//	A( => a^
	{ utf_A81,	utf_a61 },				//	A(' => a^'
	{ utf_A82,	utf_a62 },				//	A(` => a^`
	{ utf_A83,	utf_a63 },				//	A(? => a^?
	{ utf_A84,	utf_a64 },				//	A(~ => a^~
	{ utf_A85,	utf_a65 },				//	A(. => a^.
	{ utf_a,	utf_a6 },				//	a => a^
	{ utf_a1,	utf_a61 },				//	a' => a^'
	{ utf_a2,	utf_a62 },				//	a` => a^`
	{ utf_a3,	utf_a63 },				//	a? => a^?
	{ utf_a4,	utf_a64 },				//	a~ => a^~
	{ utf_a5,	utf_a65 },				//	a. => a^.
	{ utf_a6,	utf_a, utf_a },			//	a^ => aa
	{ utf_a61,	utf_a1, utf_a },		//	a^' => a'a
	{ utf_a62,	utf_a2, utf_a },		//	a^` => a`a
	{ utf_a63,	utf_a3, utf_a },		//	a^? => a?a
	{ utf_a64,	utf_a4, utf_a },		//	a^~ => a~a
	{ utf_a65,	utf_a5, utf_a },		//	a^. => a.a
	{ utf_a8,	utf_a6 },				//	a( => a^
	{ utf_a81,	utf_a61 },				//	a(' => a^'
	{ utf_a82,	utf_a62 },				//	a(` => a^`
	{ utf_a83,	utf_a63 },				//	a(? => a^?
	{ utf_a84,	utf_a64 },				//	a(~ => a^~
	{ utf_a85,	utf_a65 },				//	a(. => a^.
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_E[] =
{
	{ utf_E,	utf_E6 },				//	E => E^
	{ utf_E1,	utf_E61 },				//	E' => E^'
	{ utf_E2,	utf_E62 },				//	E` => E^`
	{ utf_E3,	utf_E63 },				//	E? => E^?
	{ utf_E4,	utf_E64 },				//	E~ => E^~
	{ utf_E5,	utf_E65 },				//	E. => E^.
	{ utf_E6,	utf_E, utf_E },			//	E^ => EE
	{ utf_E61,	utf_E1, utf_E },		//	E^' => E'E
	{ utf_E62,	utf_E2, utf_E },		//	E^` => E`E
	{ utf_E63,	utf_E3, utf_E },		//	E^? => E?E
	{ utf_E64,	utf_E4, utf_E },		//	E^~ => E~E
	{ utf_E65,	utf_E5, utf_E },		//	E^. => E.E
	{ utf_e,	utf_E6 },				//	e => E^
	{ utf_e1,	utf_E61 },				//	e' => E^'
	{ utf_e2,	utf_E62 },				//	e` => E^`
	{ utf_e3,	utf_E63 },				//	e? => E^?
	{ utf_e4,	utf_E64 },				//	e~ => E^~
	{ utf_e5,	utf_E65 },				//	e. => E^.
	{ utf_e6,	utf_E, utf_E },			//	e^ => EE
	{ utf_e61,	utf_E1, utf_E },		//	e^' => E'E
	{ utf_e62,	utf_E2, utf_E },		//	e^` => E`E
	{ utf_e63,	utf_E3, utf_E },		//	e^? => E?E
	{ utf_e64,	utf_E4, utf_E },		//	e^~ => E~E
	{ utf_e65,	utf_E5, utf_E },		//	e^. => E.E
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_e[] =
{
	{ utf_E,	utf_e6 },				//	E => e^
	{ utf_E1,	utf_e61 },				//	E' => e^'
	{ utf_E2,	utf_e62 },				//	E` => e^`
	{ utf_E3,	utf_e63 },				//	E? => e^?
	{ utf_E4,	utf_e64 },				//	E~ => e^~
	{ utf_E5,	utf_e65 },				//	E. => e^.
	{ utf_E6,	utf_e, utf_e },			//	E^ => ee
	{ utf_E61,	utf_e1, utf_e },		//	E^' => e'e
	{ utf_E62,	utf_e2, utf_e },		//	E^` => e`e
	{ utf_E63,	utf_e3, utf_e },		//	E^? => e?e
	{ utf_E64,	utf_e4, utf_e },		//	E^~ => e~e
	{ utf_E65,	utf_e5, utf_e },		//	E^. => e.e
	{ utf_e,	utf_e6 },				//	e => e^
	{ utf_e1,	utf_e61 },				//	e' => e^'
	{ utf_e2,	utf_e62 },				//	e` => e^`
	{ utf_e3,	utf_e63 },				//	e? => e^?
	{ utf_e4,	utf_e64 },				//	e~ => e^~
	{ utf_e5,	utf_e65 },				//	e. => e^.
	{ utf_e6,	utf_e, utf_e },			//	e^ => ee
	{ utf_e61,	utf_e1, utf_e },		//	e^' => e'e
	{ utf_e62,	utf_e2, utf_e },		//	e^` => e`e
	{ utf_e63,	utf_e3, utf_e },		//	e^? => e?e
	{ utf_e64,	utf_e4, utf_e },		//	e^~ => e~e
	{ utf_e65,	utf_e5, utf_e },		//	e^. => e.e
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_O[] =
{
	{ utf_O,	utf_O6 },				//	O => O^
	{ utf_O1,	utf_O61 },				//	O' => O^'
	{ utf_O2,	utf_O62 },				//	O` => O^`
	{ utf_O3,	utf_O63 },				//	O? => O^?
	{ utf_O4,	utf_O64 },				//	O~ => O^~
	{ utf_O5,	utf_O65 },				//	O. => O^.
	{ utf_O6,	utf_O, utf_O },			//	O^ => OO
	{ utf_O61,	utf_O1, utf_O },		//	O^' => O'O
	{ utf_O62,	utf_O2, utf_O },		//	O^` => O`O
	{ utf_O63,	utf_O3, utf_O },		//	O^? => O?O
	{ utf_O64,	utf_O4, utf_O },		//	O^~ => O~O
	{ utf_O65,	utf_O5, utf_O },		//	O^. => O.O
	{ utf_O7,	utf_O6 },				//	O+ => O^
	{ utf_O71,	utf_O61 },				//	O+' => O^'
	{ utf_O72,	utf_O62 },				//	O+` => O^`
	{ utf_O73,	utf_O63 },				//	O+? => O^?
	{ utf_O74,	utf_O64 },				//	O+~ => O^~
	{ utf_O75,	utf_O65 },				//	O+. => O^.
	{ utf_o,	utf_O6 },				//	o => O^
	{ utf_o1,	utf_O61 },				//	o' => O^'
	{ utf_o2,	utf_O62 },				//	o` => O^`
	{ utf_o3,	utf_O63 },				//	o? => O^?
	{ utf_o4,	utf_O64 },				//	o~ => O^~
	{ utf_o5,	utf_O65 },				//	o. => O^.
	{ utf_o6,	utf_O, utf_O },			//	o^ => OO
	{ utf_o61,	utf_O1, utf_O },		//	o^' => O'O
	{ utf_o62,	utf_O2, utf_O },		//	o^` => O`O
	{ utf_o63,	utf_O3, utf_O },		//	o^? => O?O
	{ utf_o64,	utf_O4, utf_O },		//	o^~ => O~O
	{ utf_o65,	utf_O5, utf_O },		//	o^. => O.O
	{ utf_o7,	utf_O6 },				//	o+ => O^
	{ utf_o71,	utf_O61 },				//	o+' => O^'
	{ utf_o72,	utf_O62 },				//	o+` => O^`
	{ utf_o73,	utf_O63 },				//	o+? => O^?
	{ utf_o74,	utf_O64 },				//	o+~ => O^~
	{ utf_o75,	utf_O65 },				//	o+. => O^.
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_o[] =
{
	{ utf_O,	utf_o6 },				//	O => o^
	{ utf_O1,	utf_o61 },				//	O' => O^'
	{ utf_O2,	utf_o62 },				//	O` => O^`
	{ utf_O3,	utf_o63 },				//	O? => O^?
	{ utf_O4,	utf_o64 },				//	O~ => O^~
	{ utf_O5,	utf_o65 },				//	O. => O^.
	{ utf_O6,	utf_o, utf_o },			//	O^ => Oo
	{ utf_O61,	utf_o1, utf_o },		//	O^' => O'o
	{ utf_O62,	utf_o2, utf_o },		//	O^` => O`o
	{ utf_O63,	utf_o3, utf_o },		//	O^? => O?o
	{ utf_O64,	utf_o4, utf_o },		//	O^~ => O~o
	{ utf_O65,	utf_o5, utf_o },		//	O^. => O.o
	{ utf_O7,	utf_o6 },				//	O+ => O^
	{ utf_O71,	utf_o61 },				//	O+' => O^'
	{ utf_O72,	utf_o62 },				//	O+` => O^`
	{ utf_O73,	utf_o63 },				//	O+? => O^?
	{ utf_O74,	utf_o64 },				//	O+~ => O^~
	{ utf_O75,	utf_o65 },				//	O+. => O^.
	{ utf_o,	utf_o6 },				//	o => o^
	{ utf_o1,	utf_o61 },				//	o' => o^'
	{ utf_o2,	utf_o62 },				//	o` => o^`
	{ utf_o3,	utf_o63 },				//	o? => o^?
	{ utf_o4,	utf_o64 },				//	o~ => o^~
	{ utf_o5,	utf_o65 },				//	o. => o^.
	{ utf_o6,	utf_o, utf_o },			//	o^ => oo
	{ utf_o61,	utf_o1, utf_o },		//	o^' => o'o
	{ utf_o62,	utf_o2, utf_o },		//	o^` => o`o
	{ utf_o63,	utf_o3, utf_o },		//	o^? => o?o
	{ utf_o64,	utf_o4, utf_o },		//	o^~ => o~o
	{ utf_o65,	utf_o5, utf_o },		//	o^. => o.o
	{ utf_o7,	utf_o6 },				//	o+ => o^
	{ utf_o71,	utf_o61 },				//	o+' => o^'
	{ utf_o72,	utf_o62 },				//	o+` => o^`
	{ utf_o73,	utf_o63 },				//	o+? => o^?
	{ utf_o74,	utf_o64 },				//	o+~ => o^~
	{ utf_o75,	utf_o65 },				//	o+. => o^.
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_D[] =
{
	{ utf_D,	utf_D9 },				//	D => -D
	{ utf_D9,	utf_D, utf_D },			//	-D => DD
	{ utf_d,	utf_D9 },				//	d => -D
	{ utf_d9,	utf_D, utf_D },			//	-d => DD
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_d[] =
{
	{ utf_D,	utf_d9 },				//	D => -d
	{ utf_D9,	utf_d, utf_d },			//	-D => dd
	{ utf_d,	utf_d9 },				//	d => -d
	{ utf_d9,	utf_d, utf_d },			//	-d => dd
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_W[] =
{
	{ utf_A,	utf_A8 },				//	A => A(
	{ utf_A1,	utf_A81 },				//	A' => A('
	{ utf_A2,	utf_A82 },				//	A` => A(`
	{ utf_A3,	utf_A83 },				//	A? => A(?
	{ utf_A4,	utf_A84 },				//	A~ => A(~
	{ utf_A5,	utf_A85 },				//	A. => A(.
	{ utf_A6,	utf_A8 },				//	A^ => A(
	{ utf_A61,	utf_A81 },				//	A^' => A('
	{ utf_A62,	utf_A82 },				//	A^` => A(`
	{ utf_A63,	utf_A83 },				//	A^? => A(?
	{ utf_A64,	utf_A84 },				//	A^~ => A(~
	{ utf_A65,	utf_A85 },				//	A^. => A(.
	{ utf_A8,	utf_A, utf_W },			//	A( => AW
	{ utf_A81,	utf_A1, utf_W },		//	A(' => A'W
	{ utf_A82,	utf_A2, utf_W },		//	A(` => A`W
	{ utf_A83,	utf_A3, utf_W },		//	A(? => A?W
	{ utf_A84,	utf_A4, utf_W },		//	A(~ => A~W
	{ utf_A85,	utf_A5, utf_W },		//	A(. => A.W
	{ utf_a,	utf_A8 },				//	a => A(
	{ utf_a1,	utf_A81 },				//	a' => A('
	{ utf_a2,	utf_A82 },				//	a` => A(`
	{ utf_a3,	utf_A83 },				//	a? => A(?
	{ utf_a4,	utf_A84 },				//	a~ => A(~
	{ utf_a5,	utf_A85 },				//	a. => A(.
	{ utf_a6,	utf_A8 },				//	a^ => A(
	{ utf_a61,	utf_A81 },				//	a^' => A('
	{ utf_a62,	utf_A82 },				//	a^` => A(`
	{ utf_a63,	utf_A83 },				//	a^? => A(?
	{ utf_a64,	utf_A84 },				//	a^~ => A(~
	{ utf_a65,	utf_A85 },				//	a^. => A(.
	{ utf_a8,	utf_A, utf_W },			//	a( => AW
	{ utf_a81,	utf_A1, utf_W },		//	a(' => A'W
	{ utf_a82,	utf_A2, utf_W },		//	a(` => A`W
	{ utf_a83,	utf_A3, utf_W },		//	a(? => A?W
	{ utf_a84,	utf_A4, utf_W },		//	a(~ => A~W
	{ utf_a85,	utf_A5, utf_W },		//	a(. => A.W
	{ utf_O,	utf_O7 },				//	O => O+
	{ utf_O1,	utf_O71 },				//	O' => O+'
	{ utf_O2,	utf_O72 },				//	O` => O+`
	{ utf_O3,	utf_O73 },				//	O? => O+?
	{ utf_O4,	utf_O74 },				//	O~ => O+~
	{ utf_O5,	utf_O75 },				//	O. => O+.
	{ utf_O6,	utf_O7 },				//	O^ => O+
	{ utf_O61,	utf_O71 },				//	O^' => O+'
	{ utf_O62,	utf_O72 },				//	O^` => O+`
	{ utf_O63,	utf_O73 },				//	O^? => O+?
	{ utf_O64,	utf_O74 },				//	O^~ => O+~
	{ utf_O65,	utf_O75 },				//	O^. => O+.
	{ utf_O7,	utf_O, utf_W },			//	O+ => OW
	{ utf_O71,	utf_O1, utf_W },		//	O+' => O'W
	{ utf_O72,	utf_O2, utf_W },		//	O+` => O`W
	{ utf_O73,	utf_O3, utf_W },		//	O+? => O?W
	{ utf_O74,	utf_O4, utf_W },		//	O+~ => O~W
	{ utf_O75,	utf_O5, utf_W },		//	O+. => O.W
	{ utf_o,	utf_O7 },				//	o => O+
	{ utf_o1,	utf_O71 },				//	o' => O+'
	{ utf_o2,	utf_O72 },				//	o` => O+`
	{ utf_o3,	utf_O73 },				//	o? => O+?
	{ utf_o4,	utf_O74 },				//	o~ => O+~
	{ utf_o5,	utf_O75 },				//	o. => O+.
	{ utf_o6,	utf_O7 },				//	o^ => O+
	{ utf_o61,	utf_O71 },				//	o^' => O+'
	{ utf_o62,	utf_O72 },				//	o^` => O+`
	{ utf_o63,	utf_O73 },				//	o^? => O+?
	{ utf_o64,	utf_O74 },				//	o^~ => O+~
	{ utf_o65,	utf_O75 },				//	o^. => O+.
	{ utf_o7,	utf_O, utf_W },			//	o+ => OW
	{ utf_o71,	utf_O1, utf_W },		//	o+' => O'W
	{ utf_o72,	utf_O2, utf_W },		//	o+` => O`W
	{ utf_o73,	utf_O3, utf_W },		//	o+? => O?W
	{ utf_o74,	utf_O4, utf_W },		//	o+~ => O~W
	{ utf_o75,	utf_O5, utf_W },		//	o+. => O.W
	{ utf_U,	utf_U7 },				//	U => U+
	{ utf_U1,	utf_U71 },				//	U' => U+'
	{ utf_U2,	utf_U72 },				//	U` => U+`
	{ utf_U3,	utf_U73 },				//	U? => U+?
	{ utf_U4,	utf_U74 },				//	U~ => U+~
	{ utf_U5,	utf_U75 },				//	U. => U+.
	{ utf_U7,	utf_U, utf_W },			//	U+ => UW
	{ utf_U71,	utf_U1, utf_W },		//	U+' => U'W
	{ utf_U72,	utf_U2, utf_W },		//	U+` => U`W
	{ utf_U73,	utf_U3, utf_W },		//	U+? => U?W
	{ utf_U74,	utf_U4, utf_W },		//	U+~ => U~W
	{ utf_U75,	utf_U5, utf_W },		//	U+. => U.W
	{ utf_u,	utf_U7 },				//	u => U+
	{ utf_u1,	utf_U71 },				//	u' => U+'
	{ utf_u2,	utf_U72 },				//	u` => U+`
	{ utf_u3,	utf_U73 },				//	u? => U+?
	{ utf_u4,	utf_U74 },				//	u~ => U+~
	{ utf_u5,	utf_U75 },				//	u. => U+.
	{ utf_u7,	utf_U, utf_W },			//	u+ => UW
	{ utf_u71,	utf_U1, utf_W },		//	u+' => U'W
	{ utf_u72,	utf_U2, utf_W },		//	u+` => U`W
	{ utf_u73,	utf_U3, utf_W },		//	u+? => U?W
	{ utf_u74,	utf_U4, utf_W },		//	u+~ => U~W
	{ utf_u75,	utf_U5, utf_W },		//	u+. => U.W
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_w[] =
{
	{ utf_A,	utf_a8 },				//	A => a(
	{ utf_A1,	utf_a81 },				//	A' => a('
	{ utf_A2,	utf_a82 },				//	A` => a(`
	{ utf_A3,	utf_a83 },				//	A? => a(?
	{ utf_A4,	utf_a84 },				//	A~ => a(~
	{ utf_A5,	utf_a85 },				//	A. => a(.
	{ utf_A6,	utf_a8 },				//	A^ => a(
	{ utf_A61,	utf_a81 },				//	A^' => a('
	{ utf_A62,	utf_a82 },				//	A^` => a(`
	{ utf_A63,	utf_a83 },				//	A^? => a(?
	{ utf_A64,	utf_a84 },				//	A^~ => a(~
	{ utf_A65,	utf_a85 },				//	A^. => a(.
	{ utf_A8,	utf_a, utf_w },			//	A( => aw
	{ utf_A81,	utf_a1, utf_w },		//	A(' => a'w
	{ utf_A82,	utf_a2, utf_w },		//	A(` => a`w
	{ utf_A83,	utf_a3, utf_w },		//	A(? => a?w
	{ utf_A84,	utf_a4, utf_w },		//	A(~ => a~w
	{ utf_A85,	utf_a5, utf_w },		//	A(. => a.w
	{ utf_a,	utf_a8 },				//	a => a(
	{ utf_a1,	utf_a81 },				//	a' => a('
	{ utf_a2,	utf_a82 },				//	a` => a(`
	{ utf_a3,	utf_a83 },				//	a? => a(?
	{ utf_a4,	utf_a84 },				//	a~ => a(~
	{ utf_a5,	utf_a85 },				//	a. => a(.
	{ utf_a6,	utf_a8 },				//	a^ => a(
	{ utf_a61,	utf_a81 },				//	a^' => a('
	{ utf_a62,	utf_a82 },				//	a^` => a(`
	{ utf_a63,	utf_a83 },				//	a^? => a(?
	{ utf_a64,	utf_a84 },				//	a^~ => a(~
	{ utf_a65,	utf_a85 },				//	a^. => a(.
	{ utf_a8,	utf_a, utf_w },			//	a( => aw
	{ utf_a81,	utf_a1, utf_w },		//	a(' => a'w
	{ utf_a82,	utf_a2, utf_w },		//	a(` => a`w
	{ utf_a83,	utf_a3, utf_w },		//	a(? => a?w
	{ utf_a84,	utf_a4, utf_w },		//	a(~ => a~w
	{ utf_a85,	utf_a5, utf_w },		//	a(. => a.w
	{ utf_O,	utf_o7 },				//	O => o+
	{ utf_O1,	utf_o71 },				//	O' => o+'
	{ utf_O2,	utf_o72 },				//	O` => o+`
	{ utf_O3,	utf_o73 },				//	O? => o+?
	{ utf_O4,	utf_o74 },				//	O~ => o+~
	{ utf_O5,	utf_o75 },				//	O. => o+.
	{ utf_O6,	utf_o7 },				//	O^ => o+
	{ utf_O61,	utf_o71 },				//	O^' => o+'
	{ utf_O62,	utf_o72 },				//	O^` => o+`
	{ utf_O63,	utf_o73 },				//	O^? => o+?
	{ utf_O64,	utf_o74 },				//	O^~ => o+~
	{ utf_O65,	utf_o75 },				//	O^. => o+.
	{ utf_O7,	utf_o, utf_w },			//	O+ => ow
	{ utf_O71,	utf_o1, utf_w },		//	O+' => o'w
	{ utf_O72,	utf_o2, utf_w },		//	O+` => o`w
	{ utf_O73,	utf_o3, utf_w },		//	O+? => o?w
	{ utf_O74,	utf_o4, utf_w },		//	O+~ => o~w
	{ utf_O75,	utf_o5, utf_w },		//	O+. => o.w
	{ utf_o,	utf_o7 },				//	o => o+
	{ utf_o1,	utf_o71 },				//	o' => o+'
	{ utf_o2,	utf_o72 },				//	o` => o+`
	{ utf_o3,	utf_o73 },				//	o? => o+?
	{ utf_o4,	utf_o74 },				//	o~ => o+~
	{ utf_o5,	utf_o75 },				//	o. => o+.
	{ utf_o6,	utf_o7 },				//	o^ => o+
	{ utf_o61,	utf_o71 },				//	o^' => o+'
	{ utf_o62,	utf_o72 },				//	o^` => o+`
	{ utf_o63,	utf_o73 },				//	o^? => o+?
	{ utf_o64,	utf_o74 },				//	o^~ => o+~
	{ utf_o65,	utf_o75 },				//	o^. => o+.
	{ utf_o7,	utf_o, utf_w },			//	o+ => ow
	{ utf_o71,	utf_o1, utf_w },		//	o+' => o'w
	{ utf_o72,	utf_o2, utf_w },		//	o+` => o`w
	{ utf_o73,	utf_o3, utf_w },		//	o+? => o?w
	{ utf_o74,	utf_o4, utf_w },		//	o+~ => o~w
	{ utf_o75,	utf_o5, utf_w },		//	o+. => o.w
	{ utf_U,	utf_u7 },				//	U => u+
	{ utf_U1,	utf_u71 },				//	U' => u+'
	{ utf_U2,	utf_u72 },				//	U` => u+`
	{ utf_U3,	utf_u73 },				//	U? => u+?
	{ utf_U4,	utf_u74 },				//	U~ => u+~
	{ utf_U5,	utf_u75 },				//	U. => u+.
	{ utf_U7,	utf_u, utf_w },			//	U+ => uw
	{ utf_U71,	utf_u1, utf_w },		//	U+' => u'w
	{ utf_U72,	utf_u2, utf_w },		//	U+` => u`w
	{ utf_U73,	utf_u3, utf_w },		//	U+? => u?w
	{ utf_U74,	utf_u4, utf_w },		//	U+~ => u~w
	{ utf_U75,	utf_u5, utf_w },		//	U+. => u.w
	{ utf_u,	utf_u7 },				//	u => u+
	{ utf_u1,	utf_u71 },				//	u' => u+'
	{ utf_u2,	utf_u72 },				//	u` => u+`
	{ utf_u3,	utf_u73 },				//	u? => u+?
	{ utf_u4,	utf_u74 },				//	u~ => u+~
	{ utf_u5,	utf_u75 },				//	u. => u+.
	{ utf_u7,	utf_u, utf_w },			//	u+ => uw
	{ utf_u71,	utf_u1, utf_w },		//	u+' => u'w
	{ utf_u72,	utf_u2, utf_w },		//	u+` => u`w
	{ utf_u73,	utf_u3, utf_w },		//	u+? => u?w
	{ utf_u74,	utf_u4, utf_w },		//	u+~ => u~w
	{ utf_u75,	utf_u5, utf_w },		//	u+. => u.w
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_S[] =
{
	{ utf_A,	utf_A1 },				//	A => A'
	{ utf_A1,	utf_A, utf_S },			//	A' => AS
	{ utf_A2,	utf_A1 },				//	A` => A'
	{ utf_A3,	utf_A1 },				//	A? => A'
	{ utf_A4,	utf_A1 },				//	A~ => A'
	{ utf_A5,	utf_A1 },				//	A. => A'
	{ utf_a,	utf_A1 },				//	a => A'
	{ utf_a1,	utf_A, utf_S },			//	a' => AS
	{ utf_a2,	utf_A1 },				//	a` => A'
	{ utf_a3,	utf_A1 },				//	a? => A'
	{ utf_a4,	utf_A1 },				//	a~ => A'
	{ utf_a5,	utf_A1 },				//	a. => A'

	{ utf_A6,	utf_A61 },				//	A^ => A^'
	{ utf_A61,	utf_A6, utf_S },		//	A^' => A^S
	{ utf_A62,	utf_A61 },				//	A^` => A^'
	{ utf_A63,	utf_A61 },				//	A^? => A^'
	{ utf_A64,	utf_A61 },				//	A^~ => A^'
	{ utf_A65,	utf_A61 },				//	A^. => A^'
	{ utf_a6,	utf_A61 },				//	a^ => A^'
	{ utf_a61,	utf_A6, utf_S },		//	a^' => A^S
	{ utf_a62,	utf_A61 },				//	a^` => A^'
	{ utf_a63,	utf_A61 },				//	a^? => A^'
	{ utf_a64,	utf_A61 },				//	a^~ => A^'
	{ utf_a65,	utf_A61 },				//	a^. => A^'

	{ utf_A8,	utf_A81 },				//	A( => A('
	{ utf_A81,	utf_A8, utf_S },		//	A(' => A(S
	{ utf_A82,	utf_A81 },				//	A(` => A('
	{ utf_A83,	utf_A81 },				//	A(? => A('
	{ utf_A84,	utf_A81 },				//	A(~ => A('
	{ utf_A85,	utf_A81 },				//	A(. => A('
	{ utf_a8,	utf_A81 },				//	a( => A('
	{ utf_a81,	utf_A8, utf_S },		//	a(' => A(S
	{ utf_a82,	utf_A81 },				//	a(` => A('
	{ utf_a83,	utf_A81 },				//	a(? => A('
	{ utf_a84,	utf_A81 },				//	a(~ => A('
	{ utf_a85,	utf_A81 },				//	a(. => A('

	{ utf_E,	utf_E1 },				//	E => E'
	{ utf_E1,	utf_E, utf_S },			//	E' => ES
	{ utf_E2,	utf_E1 },				//	E` => E'
	{ utf_E3,	utf_E1 },				//	E? => E'
	{ utf_E4,	utf_E1 },				//	E~ => E'
	{ utf_E5,	utf_E1 },				//	E. => E'
	{ utf_e,	utf_E1 },				//	e => E'
	{ utf_e1,	utf_E, utf_S },			//	e' => ES
	{ utf_e2,	utf_E1 },				//	e` => E'
	{ utf_e3,	utf_E1 },				//	e? => E'
	{ utf_e4,	utf_E1 },				//	e~ => E'
	{ utf_e5,	utf_E1 },				//	e. => E'

	{ utf_E6,	utf_E61 },				//	E^ => E^'
	{ utf_E61,	utf_E6, utf_S },		//	E^' => E^S
	{ utf_E62,	utf_E61 },				//	E^` => E^'
	{ utf_E63,	utf_E61 },				//	E^? => E^'
	{ utf_E64,	utf_E61 },				//	E^~ => E^'
	{ utf_E65,	utf_E61 },				//	E^. => E^'
	{ utf_e6,	utf_E61 },				//	e^ => E^'
	{ utf_e61,	utf_E6, utf_S },		//	e^' => E^S
	{ utf_e62,	utf_E61 },				//	e^` => E^'
	{ utf_e63,	utf_E61 },				//	e^? => E^'
	{ utf_e64,	utf_E61 },				//	e^~ => E^'
	{ utf_e65,	utf_E61 },				//	e^. => E^'

	{ utf_O,	utf_O1 },				//	O => O'
	{ utf_O1,	utf_O, utf_S },			//	O' => OS
	{ utf_O2,	utf_O1 },				//	O` => O'
	{ utf_O3,	utf_O1 },				//	O? => O'
	{ utf_O4,	utf_O1 },				//	O~ => O'
	{ utf_O5,	utf_O1 },				//	O. => O'
	{ utf_o,	utf_O1 },				//	o => O'
	{ utf_o1,	utf_O, utf_S },			//	o' => OS
	{ utf_o2,	utf_O1 },				//	o` => O'
	{ utf_o3,	utf_O1 },				//	o? => O'
	{ utf_o4,	utf_O1 },				//	o~ => O'
	{ utf_o5,	utf_O1 },				//	o. => O'

	{ utf_O6,	utf_O61 },				//	O^ => O^'
	{ utf_O61,	utf_O6, utf_S },		//	O^' => O^S
	{ utf_O62,	utf_O61 },				//	O^` => O^'
	{ utf_O63,	utf_O61 },				//	O^? => O^'
	{ utf_O64,	utf_O61 },				//	O^~ => O^'
	{ utf_O65,	utf_O61 },				//	O^. => O^'
	{ utf_o6,	utf_O61 },				//	o^ => O^'
	{ utf_o61,	utf_O6, utf_S },		//	o^' => O^S
	{ utf_o62,	utf_O61 },				//	o^` => O^'
	{ utf_o63,	utf_O61 },				//	o^? => O^'
	{ utf_o64,	utf_O61 },				//	o^~ => O^'
	{ utf_o65,	utf_O61 },				//	o^. => O^'

	{ utf_O7,	utf_O71 },				//	O+ => O+'
	{ utf_O71,	utf_O7, utf_S },		//	O+' => O+S
	{ utf_O72,	utf_O71 },				//	O+` => O+'
	{ utf_O73,	utf_O71 },				//	O+? => O+'
	{ utf_O74,	utf_O71 },				//	O+~ => O+'
	{ utf_O75,	utf_O71 },				//	O+. => O+'
	{ utf_o7,	utf_O71 },				//	o+ => O+'
	{ utf_o71,	utf_O7, utf_S },		//	o+' => O+S
	{ utf_o72,	utf_O71 },				//	o+` => O+'
	{ utf_o73,	utf_O71 },				//	o+? => O+'
	{ utf_o74,	utf_O71 },				//	o+~ => O+'
	{ utf_o75,	utf_O71 },				//	o+. => O+'

	{ utf_U,	utf_U1 },				//	U => U'
	{ utf_U1,	utf_U, utf_S },			//	U' => US
	{ utf_U2,	utf_U1 },				//	U` => U'
	{ utf_U3,	utf_U1 },				//	U? => U'
	{ utf_U4,	utf_U1 },				//	U~ => U'
	{ utf_U5,	utf_U1 },				//	U. => U'
	{ utf_u,	utf_U1 },				//	u => U'
	{ utf_u1,	utf_U, utf_S },			//	u' => US
	{ utf_u2,	utf_U1 },				//	u` => U'
	{ utf_u3,	utf_U1 },				//	u? => U'
	{ utf_u4,	utf_U1 },				//	u~ => U'
	{ utf_u5,	utf_U1 },				//	u. => U'

	{ utf_U7,	utf_U71 },				//	U+ => U+'
	{ utf_U71,	utf_U7, utf_S },		//	U+' => U+S
	{ utf_U72,	utf_U71 },				//	U+` => U+'
	{ utf_U73,	utf_U71 },				//	U+? => U+'
	{ utf_U74,	utf_U71 },				//	U+~ => U+'
	{ utf_U75,	utf_U71 },				//	U+. => U+'
	{ utf_u7,	utf_U71 },				//	u+ => U+'
	{ utf_u71,	utf_U7, utf_S },		//	u+' => U+S
	{ utf_u72,	utf_U71 },				//	u+` => U+'
	{ utf_u73,	utf_U71 },				//	u+? => U+'
	{ utf_u74,	utf_U71 },				//	u+~ => U+'
	{ utf_u75,	utf_U71 },				//	u+. => U+'

	{ utf_I,	utf_I1 },				//	I => I'
	{ utf_I1,	utf_I, utf_S },			//	I' => IS
	{ utf_I2,	utf_I1 },				//	I` => I'
	{ utf_I3,	utf_I1 },				//	I? => I'
	{ utf_I4,	utf_I1 },				//	I~ => I'
	{ utf_I5,	utf_I1 },				//	I. => I'
	{ utf_i,	utf_I1 },				//	i => I'
	{ utf_i1,	utf_I, utf_S },			//	i' => IS
	{ utf_i2,	utf_I1 },				//	i` => I'
	{ utf_i3,	utf_I1 },				//	i? => I'
	{ utf_i4,	utf_I1 },				//	i~ => I'
	{ utf_i5,	utf_I1 },				//	i. => I'

	{ utf_Y,	utf_Y1 },				//	Y => Y'
	{ utf_Y1,	utf_Y, utf_S },			//	Y' => YS
	{ utf_Y2,	utf_Y1 },				//	Y` => Y'
	{ utf_Y3,	utf_Y1 },				//	Y? => Y'
	{ utf_Y4,	utf_Y1 },				//	Y~ => Y'
	{ utf_Y5,	utf_Y1 },				//	Y. => Y'
	{ utf_y,	utf_Y1 },				//	y => Y'
	{ utf_y1,	utf_Y, utf_S },			//	y' => YS
	{ utf_y2,	utf_Y1 },				//	y` => Y'
	{ utf_y3,	utf_Y1 },				//	y? => Y'
	{ utf_y4,	utf_Y1 },				//	y~ => Y'
	{ utf_y5,	utf_Y1 },				//	y. => Y'
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_s[] =
{
	{ utf_A,	utf_a1 },				//	A => a'
	{ utf_A1,	utf_a, utf_s },			//	A' => as
	{ utf_A2,	utf_a1 },				//	A` => a'
	{ utf_A3,	utf_a1 },				//	A? => a'
	{ utf_A4,	utf_a1 },				//	A~ => a'
	{ utf_A5,	utf_a1 },				//	A. => a'
	{ utf_a,	utf_a1 },				//	a => a'
	{ utf_a1,	utf_a, utf_s },			//	a' => as
	{ utf_a2,	utf_a1 },				//	a` => a'
	{ utf_a3,	utf_a1 },				//	a? => a'
	{ utf_a4,	utf_a1 },				//	a~ => a'
	{ utf_a5,	utf_a1 },				//	a. => a'

	{ utf_A6,	utf_a61 },				//	A^ => a^'
	{ utf_A61,	utf_a6, utf_s },		//	A^' => a^s
	{ utf_A62,	utf_a61 },				//	A^` => a^'
	{ utf_A63,	utf_a61 },				//	A^? => a^'
	{ utf_A64,	utf_a61 },				//	A^~ => a^'
	{ utf_A65,	utf_a61 },				//	A^. => a^'
	{ utf_a6,	utf_a61 },				//	a^ => a^'
	{ utf_a61,	utf_a6, utf_s },		//	a^' => a^s
	{ utf_a62,	utf_a61 },				//	a^` => a^'
	{ utf_a63,	utf_a61 },				//	a^? => a^'
	{ utf_a64,	utf_a61 },				//	a^~ => a^'
	{ utf_a65,	utf_a61 },				//	a^. => a^'

	{ utf_A8,	utf_a81 },				//	A( => a('
	{ utf_A81,	utf_a8, utf_s },		//	A(' => a(s
	{ utf_A82,	utf_a81 },				//	A(` => a('
	{ utf_A83,	utf_a81 },				//	A(? => a('
	{ utf_A84,	utf_a81 },				//	A(~ => a('
	{ utf_A85,	utf_a81 },				//	A(. => a('
	{ utf_a8,	utf_a81 },				//	a( => a('
	{ utf_a81,	utf_a8, utf_s },		//	a(' => a(s
	{ utf_a82,	utf_a81 },				//	a(` => a('
	{ utf_a83,	utf_a81 },				//	a(? => a('
	{ utf_a84,	utf_a81 },				//	a(~ => a('
	{ utf_a85,	utf_a81 },				//	a(. => a('

	{ utf_E,	utf_e1 },				//	E => e'
	{ utf_E1,	utf_e, utf_s },			//	E' => es
	{ utf_E2,	utf_e1 },				//	E` => e'
	{ utf_E3,	utf_e1 },				//	E? => e'
	{ utf_E4,	utf_e1 },				//	E~ => e'
	{ utf_E5,	utf_e1 },				//	E. => e'
	{ utf_e,	utf_e1 },				//	e => e'
	{ utf_e1,	utf_e, utf_s },			//	e' => es
	{ utf_e2,	utf_e1 },				//	e` => e'
	{ utf_e3,	utf_e1 },				//	e? => e'
	{ utf_e4,	utf_e1 },				//	e~ => e'
	{ utf_e5,	utf_e1 },				//	e. => e'

	{ utf_E6,	utf_e61 },				//	E^ => e^'
	{ utf_E61,	utf_e6, utf_s },		//	E^' => e^s
	{ utf_E62,	utf_e61 },				//	E^` => e^'
	{ utf_E63,	utf_e61 },				//	E^? => e^'
	{ utf_E64,	utf_e61 },				//	E^~ => e^'
	{ utf_E65,	utf_e61 },				//	E^. => e^'
	{ utf_e6,	utf_e61 },				//	e^ => e^'
	{ utf_e61,	utf_e6, utf_s },		//	e^' => e^s
	{ utf_e62,	utf_e61 },				//	e^` => e^'
	{ utf_e63,	utf_e61 },				//	e^? => e^'
	{ utf_e64,	utf_e61 },				//	e^~ => e^'
	{ utf_e65,	utf_e61 },				//	e^. => e^'

	{ utf_O,	utf_o1 },				//	O => o'
	{ utf_O1,	utf_o, utf_s },			//	O' => os
	{ utf_O2,	utf_o1 },				//	O` => o'
	{ utf_O3,	utf_o1 },				//	O? => o'
	{ utf_O4,	utf_o1 },				//	O~ => o'
	{ utf_O5,	utf_o1 },				//	O. => o'
	{ utf_o,	utf_o1 },				//	o => o'
	{ utf_o1,	utf_o, utf_s },			//	o' => os
	{ utf_o2,	utf_o1 },				//	o` => o'
	{ utf_o3,	utf_o1 },				//	o? => o'
	{ utf_o4,	utf_o1 },				//	o~ => o'
	{ utf_o5,	utf_o1 },				//	o. => o'

	{ utf_O6,	utf_o61 },				//	O^ => o^'
	{ utf_O61,	utf_o6, utf_s },		//	O^' => o^s
	{ utf_O62,	utf_o61 },				//	O^` => o^'
	{ utf_O63,	utf_o61 },				//	O^? => o^'
	{ utf_O64,	utf_o61 },				//	O^~ => o^'
	{ utf_O65,	utf_o61 },				//	O^. => o^'
	{ utf_o6,	utf_o61 },				//	o^ => o^'
	{ utf_o61,	utf_o6, utf_s },		//	o^' => o^s
	{ utf_o62,	utf_o61 },				//	o^` => o^'
	{ utf_o63,	utf_o61 },				//	o^? => o^'
	{ utf_o64,	utf_o61 },				//	o^~ => o^'
	{ utf_o65,	utf_o61 },				//	o^. => o^'

	{ utf_O7,	utf_o71 },				//	O+ => o+'
	{ utf_O71,	utf_o7, utf_s },		//	O+' => o+s
	{ utf_O72,	utf_o71 },				//	O+` => o+'
	{ utf_O73,	utf_o71 },				//	O+? => o+'
	{ utf_O74,	utf_o71 },				//	O+~ => o+'
	{ utf_O75,	utf_o71 },				//	O+. => o+'
	{ utf_o7,	utf_o71 },				//	o+ => o+'
	{ utf_o71,	utf_o7, utf_s },		//	o+' => o+s
	{ utf_o72,	utf_o71 },				//	o+` => o+'
	{ utf_o73,	utf_o71 },				//	o+? => o+'
	{ utf_o74,	utf_o71 },				//	o+~ => o+'
	{ utf_o75,	utf_o71 },				//	o+. => o+'

	{ utf_U,	utf_u1 },				//	U => u'
	{ utf_U1,	utf_u, utf_s },			//	U' => us
	{ utf_U2,	utf_u1 },				//	U` => u'
	{ utf_U3,	utf_u1 },				//	U? => u'
	{ utf_U4,	utf_u1 },				//	U~ => u'
	{ utf_U5,	utf_u1 },				//	U. => u'
	{ utf_u,	utf_u1 },				//	u => u'
	{ utf_u1,	utf_u, utf_s },			//	u' => us
	{ utf_u2,	utf_u1 },				//	u` => u'
	{ utf_u3,	utf_u1 },				//	u? => u'
	{ utf_u4,	utf_u1 },				//	u~ => u'
	{ utf_u5,	utf_u1 },				//	u. => u'

	{ utf_U7,	utf_u71 },				//	U+ => u+'
	{ utf_U71,	utf_u7, utf_s },		//	U+' => u+s
	{ utf_U72,	utf_u71 },				//	U+` => u+'
	{ utf_U73,	utf_u71 },				//	U+? => u+'
	{ utf_U74,	utf_u71 },				//	U+~ => u+'
	{ utf_U75,	utf_u71 },				//	U+. => u+'
	{ utf_u7,	utf_u71 },				//	u+ => u+'
	{ utf_u71,	utf_u7, utf_s },		//	u+' => u+s
	{ utf_u72,	utf_u71 },				//	u+` => u+'
	{ utf_u73,	utf_u71 },				//	u+? => u+'
	{ utf_u74,	utf_u71 },				//	u+~ => u+'
	{ utf_u75,	utf_u71 },				//	u+. => u+'

	{ utf_I,	utf_i1 },				//	I => i'
	{ utf_I1,	utf_i, utf_s },			//	I' => is
	{ utf_I2,	utf_i1 },				//	I` => i'
	{ utf_I3,	utf_i1 },				//	I? => i'
	{ utf_I4,	utf_i1 },				//	I~ => i'
	{ utf_I5,	utf_i1 },				//	I. => i'
	{ utf_i,	utf_i1 },				//	i => i'
	{ utf_i1,	utf_i, utf_s },			//	i' => is
	{ utf_i2,	utf_i1 },				//	i` => i'
	{ utf_i3,	utf_i1 },				//	i? => i'
	{ utf_i4,	utf_i1 },				//	i~ => i'
	{ utf_i5,	utf_i1 },				//	i. => i'

	{ utf_Y,	utf_y1 },				//	Y => Y'
	{ utf_Y1,	utf_y, utf_s },			//	Y' => ys
	{ utf_Y2,	utf_y1 },				//	Y` => y'
	{ utf_Y3,	utf_y1 },				//	Y? => y'
	{ utf_Y4,	utf_y1 },				//	Y~ => y'
	{ utf_Y5,	utf_y1 },				//	Y. => y'
	{ utf_y,	utf_y1 },				//	y => Y'
	{ utf_y1,	utf_y, utf_s },			//	y' => ys
	{ utf_y2,	utf_y1 },				//	y` => y'
	{ utf_y3,	utf_y1 },				//	y? => y'
	{ utf_y4,	utf_y1 },				//	y~ => y'
	{ utf_y5,	utf_y1 },				//	y. => y'
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_F[] =
{
	{ utf_A,	utf_A2 },				//	A => A`
	{ utf_A1,	utf_A2 },				//	A' => A`
	{ utf_A2,	utf_A, utf_F },			//	A` => AF
	{ utf_A3,	utf_A2 },				//	A? => A`
	{ utf_A4,	utf_A2 },				//	A~ => A`
	{ utf_A5,	utf_A2 },				//	A. => A`
	{ utf_a,	utf_A2 },				//	a => A`
	{ utf_a1,	utf_A2 },				//	a' => A`
	{ utf_a2,	utf_A, utf_F },			//	a` => AF
	{ utf_a3,	utf_A2 },				//	a? => A`
	{ utf_a4,	utf_A2 },				//	a~ => A`
	{ utf_a5,	utf_A2 },				//	a. => A`

	{ utf_A6,	utf_A62 },				//	A^ => A^`
	{ utf_A61,	utf_A62 },				//	A^' => A^`
	{ utf_A62,	utf_A6, utf_F },		//	A^` => A^F
	{ utf_A63,	utf_A62 },				//	A^? => A^`
	{ utf_A64,	utf_A62 },				//	A^~ => A^`
	{ utf_A65,	utf_A62 },				//	A^. => A^`
	{ utf_a6,	utf_A62 },				//	a^ => A^`
	{ utf_a61,	utf_A62 },				//	a^' => A^`
	{ utf_a62,	utf_A6, utf_F },		//	a^` => A^F
	{ utf_a63,	utf_A62 },				//	a^? => A^`
	{ utf_a64,	utf_A62 },				//	a^~ => A^`
	{ utf_a65,	utf_A62 },				//	a^. => A^`

	{ utf_A8,	utf_A82 },				//	A( => A(`
	{ utf_A81,	utf_A82 },				//	A(' => A(`
	{ utf_A82,	utf_A8, utf_F },		//	A(` => A(F
	{ utf_A83,	utf_A82 },				//	A(? => A(`
	{ utf_A84,	utf_A82 },				//	A(~ => A(`
	{ utf_A85,	utf_A82 },				//	A(. => A(`
	{ utf_a8,	utf_A82 },				//	a( => A(`
	{ utf_a81,	utf_A82 },				//	a(' => A(`
	{ utf_a82,	utf_A8, utf_F },		//	a(` => A(F
	{ utf_a83,	utf_A82 },				//	a(? => A(`
	{ utf_a84,	utf_A82 },				//	a(~ => A(`
	{ utf_a85,	utf_A82 },				//	a(. => A(`

	{ utf_E,	utf_E2 },				//	E => E`
	{ utf_E1,	utf_E2 },				//	E' => E`
	{ utf_E2,	utf_E, utf_F },			//	E` => EF
	{ utf_E3,	utf_E2 },				//	E? => E`
	{ utf_E4,	utf_E2 },				//	E~ => E`
	{ utf_E5,	utf_E2 },				//	E. => E`
	{ utf_e,	utf_E2 },				//	e => E`
	{ utf_e1,	utf_E2 },				//	e' => E`
	{ utf_e2,	utf_E, utf_F },			//	e` => EF
	{ utf_e3,	utf_E2 },				//	e? => E`
	{ utf_e4,	utf_E2 },				//	e~ => E`
	{ utf_e5,	utf_E2 },				//	e. => E`

	{ utf_E6,	utf_E62 },				//	E^ => E^`
	{ utf_E61,	utf_E62 },				//	E^' => E^`
	{ utf_E62,	utf_E6, utf_F },		//	E^` => E^F
	{ utf_E63,	utf_E62 },				//	E^? => E^`
	{ utf_E64,	utf_E62 },				//	E^~ => E^`
	{ utf_E65,	utf_E62 },				//	E^. => E^`
	{ utf_e6,	utf_E62 },				//	e^ => E^`
	{ utf_e61,	utf_E62 },				//	e^' => E^`
	{ utf_e62,	utf_E6, utf_F },		//	e^` => E^F
	{ utf_e63,	utf_E62 },				//	e^? => E^`
	{ utf_e64,	utf_E62 },				//	e^~ => E^`
	{ utf_e65,	utf_E62 },				//	e^. => E^`

	{ utf_O,	utf_O2 },				//	O => O`
	{ utf_O1,	utf_O2 },				//	O' => O`
	{ utf_O2,	utf_O, utf_F },			//	O` => OF
	{ utf_O3,	utf_O2 },				//	O? => O`
	{ utf_O4,	utf_O2 },				//	O~ => O`
	{ utf_O5,	utf_O2 },				//	O. => O`
	{ utf_o,	utf_O2 },				//	o => O`
	{ utf_o1,	utf_O2 },				//	o' => O`
	{ utf_o2,	utf_O, utf_F },			//	o` => OF
	{ utf_o3,	utf_O2 },				//	o? => O`
	{ utf_o4,	utf_O2 },				//	o~ => O`
	{ utf_o5,	utf_O2 },				//	o. => O`

	{ utf_O6,	utf_O62 },				//	O^ => O^`
	{ utf_O61,	utf_O62 },				//	O^' => O^`
	{ utf_O62,	utf_O6, utf_F },		//	O^` => O^F
	{ utf_O63,	utf_O62 },				//	O^? => O^`
	{ utf_O64,	utf_O62 },				//	O^~ => O^`
	{ utf_O65,	utf_O62 },				//	O^. => O^`
	{ utf_o6,	utf_O62 },				//	o^ => O^`
	{ utf_o61,	utf_O62 },				//	o^' => O^`
	{ utf_o62,	utf_O6, utf_F },		//	o^` => O^F
	{ utf_o63,	utf_O62 },				//	o^? => O^`
	{ utf_o64,	utf_O62 },				//	o^~ => O^`
	{ utf_o65,	utf_O62 },				//	o^. => O^`

	{ utf_O7,	utf_O72 },				//	O+ => O+`
	{ utf_O71,	utf_O72 },				//	O+' => O+`
	{ utf_O72,	utf_O7, utf_F },		//	O+` => O+F
	{ utf_O73,	utf_O72 },				//	O+? => O+`
	{ utf_O74,	utf_O72 },				//	O+~ => O+`
	{ utf_O75,	utf_O72 },				//	O+. => O+`
	{ utf_o7,	utf_O72 },				//	o+ => O+`
	{ utf_o71,	utf_O72 },				//	o+' => O+`
	{ utf_o72,	utf_O7, utf_F },		//	o+` => O+F
	{ utf_o73,	utf_O72 },				//	o+? => O+`
	{ utf_o74,	utf_O72 },				//	o+~ => O+`
	{ utf_o75,	utf_O72 },				//	o+. => O+`

	{ utf_U,	utf_U2 },				//	U => U`
	{ utf_U1,	utf_U2 },				//	U' => U`
	{ utf_U2,	utf_U, utf_F },			//	U` => UF
	{ utf_U3,	utf_U2 },				//	U? => U`
	{ utf_U4,	utf_U2 },				//	U~ => U`
	{ utf_U5,	utf_U2 },				//	U. => U`
	{ utf_u,	utf_U2 },				//	u => U`
	{ utf_u1,	utf_U2 },				//	u' => U`
	{ utf_u2,	utf_U, utf_F },			//	u` => UF
	{ utf_u3,	utf_U2 },				//	u? => U`
	{ utf_u4,	utf_U2 },				//	u~ => U`
	{ utf_u5,	utf_U2 },				//	u. => U`

	{ utf_U7,	utf_U72 },				//	U+ => U+`
	{ utf_U71,	utf_U72 },				//	U+' => U+`
	{ utf_U72,	utf_U7, utf_F },		//	U+` => U+F
	{ utf_U73,	utf_U72 },				//	U+? => U+`
	{ utf_U74,	utf_U72 },				//	U+~ => U+`
	{ utf_U75,	utf_U72 },				//	U+. => U+`
	{ utf_u7,	utf_U72 },				//	u+ => U+`
	{ utf_u71,	utf_U72 },				//	u+' => U+`
	{ utf_u72,	utf_U7, utf_F },		//	u+` => U+F
	{ utf_u73,	utf_U72 },				//	u+? => U+`
	{ utf_u74,	utf_U72 },				//	u+~ => U+`
	{ utf_u75,	utf_U72 },				//	u+. => U+`

	{ utf_I,	utf_I2 },				//	I => I`
	{ utf_I1,	utf_I2 },				//	I' => I`
	{ utf_I2,	utf_I, utf_F },			//	I` => IF
	{ utf_I3,	utf_I2 },				//	I? => I`
	{ utf_I4,	utf_I2 },				//	I~ => I`
	{ utf_I5,	utf_I2 },				//	I. => I`
	{ utf_i,	utf_I2 },				//	i => I`
	{ utf_i1,	utf_I2 },				//	i' => I`
	{ utf_i2,	utf_I, utf_F },			//	i` => IF
	{ utf_i3,	utf_I2 },				//	i? => I`
	{ utf_i4,	utf_I2 },				//	i~ => I`
	{ utf_i5,	utf_I2 },				//	i. => I`

	{ utf_Y,	utf_Y2 },				//	Y => Y`
	{ utf_Y1,	utf_Y2 },				//	Y' => Y`
	{ utf_Y2,	utf_Y, utf_F },			//	Y` => YF
	{ utf_Y3,	utf_Y2 },				//	Y? => Y`
	{ utf_Y4,	utf_Y2 },				//	Y~ => Y`
	{ utf_Y5,	utf_Y2 },				//	Y. => Y`
	{ utf_y,	utf_Y2 },				//	y => Y`
	{ utf_y1,	utf_Y2 },				//	y' => Y`
	{ utf_y2,	utf_Y, utf_F },			//	y` => YF
	{ utf_y3,	utf_Y2 },				//	y? => Y`
	{ utf_y4,	utf_Y2 },				//	y~ => Y`
	{ utf_y5,	utf_Y2 },				//	y. => Y`
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_f[] =
{
	{ utf_A,	utf_a2 },				//	A => a`
	{ utf_A1,	utf_a2 },				//	A' => a`
	{ utf_A2,	utf_a, utf_f },			//	A` => af
	{ utf_A3,	utf_a2 },				//	A? => a`
	{ utf_A4,	utf_a2 },				//	A~ => a`
	{ utf_A5,	utf_a2 },				//	A. => a`
	{ utf_a,	utf_a2 },				//	a => a`
	{ utf_a1,	utf_a2 },				//	a' => a`
	{ utf_a2,	utf_a, utf_f },			//	a` => af
	{ utf_a3,	utf_a2 },				//	a? => a`
	{ utf_a4,	utf_a2 },				//	a~ => a`
	{ utf_a5,	utf_a2 },				//	a. => a`

	{ utf_A6,	utf_a62 },				//	A^ => a^`
	{ utf_A61,	utf_a62 },				//	A^' => a^`
	{ utf_A62,	utf_a6, utf_f },		//	A^` => a^f
	{ utf_A63,	utf_a62 },				//	A^? => a^`
	{ utf_A64,	utf_a62 },				//	A^~ => a^`
	{ utf_A65,	utf_a62 },				//	A^. => a^`
	{ utf_a6,	utf_a62 },				//	a^ => a^`
	{ utf_a61,	utf_a62 },				//	a^' => a^`
	{ utf_a62,	utf_a6, utf_f },		//	a^` => a^f
	{ utf_a63,	utf_a62 },				//	a^? => a^`
	{ utf_a64,	utf_a62 },				//	a^~ => a^`
	{ utf_a65,	utf_a62 },				//	a^. => a^`

	{ utf_A8,	utf_a82 },				//	A( => a(`
	{ utf_A81,	utf_a82 },				//	A(' => a(`
	{ utf_A82,	utf_a8, utf_f },		//	A(` => a(f
	{ utf_A83,	utf_a82 },				//	A(? => a(`
	{ utf_A84,	utf_a82 },				//	A(~ => a(`
	{ utf_A85,	utf_a82 },				//	A(. => a(`
	{ utf_a8,	utf_a82 },				//	a( => a(`
	{ utf_a81,	utf_a82 },				//	a(' => a(`
	{ utf_a82,	utf_a8, utf_f },		//	a(` => a(f
	{ utf_a83,	utf_a82 },				//	a(? => a(`
	{ utf_a84,	utf_a82 },				//	a(~ => a(`
	{ utf_a85,	utf_a82 },				//	a(. => a(`

	{ utf_E,	utf_e2 },				//	E => e`
	{ utf_E1,	utf_e2 },				//	E' => e`
	{ utf_E2,	utf_e, utf_f },			//	E` => ef
	{ utf_E3,	utf_e2 },				//	E? => e`
	{ utf_E4,	utf_e2 },				//	E~ => e`
	{ utf_E5,	utf_e2 },				//	E. => e`
	{ utf_e,	utf_e2 },				//	e => e`
	{ utf_e1,	utf_e2 },				//	e' => e`
	{ utf_e2,	utf_e, utf_f },			//	e` => ef
	{ utf_e3,	utf_e2 },				//	e? => e`
	{ utf_e4,	utf_e2 },				//	e~ => e`
	{ utf_e5,	utf_e2 },				//	e. => e`

	{ utf_E6,	utf_e62 },				//	E^ => e^`
	{ utf_E61,	utf_e62 },				//	E^' => e^`
	{ utf_E62,	utf_e6, utf_f },		//	E^` => e^f
	{ utf_E63,	utf_e62 },				//	E^? => e^`
	{ utf_E64,	utf_e62 },				//	E^~ => e^`
	{ utf_E65,	utf_e62 },				//	E^. => e^`
	{ utf_e6,	utf_e62 },				//	e^ => e^`
	{ utf_e61,	utf_e62 },				//	e^' => e^`
	{ utf_e62,	utf_e6, utf_f },		//	e^` => e^f
	{ utf_e63,	utf_e62 },				//	e^? => e^`
	{ utf_e64,	utf_e62 },				//	e^~ => e^`
	{ utf_e65,	utf_e62 },				//	e^. => e^`

	{ utf_O,	utf_o2 },				//	O => o`
	{ utf_O1,	utf_o2 },				//	O' => o`
	{ utf_O2,	utf_o, utf_f },			//	O` => of
	{ utf_O3,	utf_o2 },				//	O? => o`
	{ utf_O4,	utf_o2 },				//	O~ => o`
	{ utf_O5,	utf_o2 },				//	O. => o`
	{ utf_o,	utf_o2 },				//	o => o`
	{ utf_o1,	utf_o2 },				//	o' => o`
	{ utf_o2,	utf_o, utf_f },			//	o` => of
	{ utf_o3,	utf_o2 },				//	o? => o`
	{ utf_o4,	utf_o2 },				//	o~ => o`
	{ utf_o5,	utf_o2 },				//	o. => o`

	{ utf_O6,	utf_o62 },				//	O^ => o^`
	{ utf_O61,	utf_o62 },				//	O^' => o^`
	{ utf_O62,	utf_o6, utf_f },		//	O^` => o^f
	{ utf_O63,	utf_o62 },				//	O^? => o^`
	{ utf_O64,	utf_o62 },				//	O^~ => o^`
	{ utf_O65,	utf_o62 },				//	O^. => o^`
	{ utf_o6,	utf_o62 },				//	o^ => o^`
	{ utf_o61,	utf_o62 },				//	o^' => o^`
	{ utf_o62,	utf_o6, utf_f },		//	o^` => o^f
	{ utf_o63,	utf_o62 },				//	o^? => o^`
	{ utf_o64,	utf_o62 },				//	o^~ => o^`
	{ utf_o65,	utf_o62 },				//	o^. => o^`

	{ utf_O7,	utf_o72 },				//	O+ => o+`
	{ utf_O71,	utf_o72 },				//	O+' => o+`
	{ utf_O72,	utf_o7, utf_f },		//	O+` => o+f
	{ utf_O73,	utf_o72 },				//	O+? => o+`
	{ utf_O74,	utf_o72 },				//	O+~ => o+`
	{ utf_O75,	utf_o72 },				//	O+. => o+`
	{ utf_o7,	utf_o72 },				//	o+ => o+`
	{ utf_o71,	utf_o72 },				//	o+' => o+`
	{ utf_o72,	utf_o7, utf_f },		//	o+` => o+f
	{ utf_o73,	utf_o72 },				//	o+? => o+`
	{ utf_o74,	utf_o72 },				//	o+~ => o+`
	{ utf_o75,	utf_o72 },				//	o+. => o+`

	{ utf_U,	utf_u2 },				//	U => u`
	{ utf_U1,	utf_u2 },				//	U' => u`
	{ utf_U2,	utf_u, utf_f },			//	U` => uf
	{ utf_U3,	utf_u2 },				//	U? => u`
	{ utf_U4,	utf_u2 },				//	U~ => u`
	{ utf_U5,	utf_u2 },				//	U. => u`
	{ utf_u,	utf_u2 },				//	u => u`
	{ utf_u1,	utf_u2 },				//	u' => u`
	{ utf_u2,	utf_u, utf_f },			//	u` => uf
	{ utf_u3,	utf_u2 },				//	u? => u`
	{ utf_u4,	utf_u2 },				//	u~ => u`
	{ utf_u5,	utf_u2 },				//	u. => u`

	{ utf_U7,	utf_u72 },				//	U+ => u+`
	{ utf_U71,	utf_u72 },				//	U+' => u+`
	{ utf_U72,	utf_u7, utf_f },		//	U+` => u+f
	{ utf_U73,	utf_u72 },				//	U+? => u+`
	{ utf_U74,	utf_u72 },				//	U+~ => u+`
	{ utf_U75,	utf_u72 },				//	U+. => u+`
	{ utf_u7,	utf_u72 },				//	u+ => u+`
	{ utf_u71,	utf_u72 },				//	u+' => u+`
	{ utf_u72,	utf_u7, utf_f },		//	u+` => u+f
	{ utf_u73,	utf_u72 },				//	u+? => u+`
	{ utf_u74,	utf_u72 },				//	u+~ => u+`
	{ utf_u75,	utf_u72 },				//	u+. => u+`

	{ utf_I,	utf_i2 },				//	I => i`
	{ utf_I1,	utf_i2 },				//	I' => i`
	{ utf_I2,	utf_i, utf_f },			//	I` => if
	{ utf_I3,	utf_i2 },				//	I? => i`
	{ utf_I4,	utf_i2 },				//	I~ => i`
	{ utf_I5,	utf_i2 },				//	I. => i`
	{ utf_i,	utf_i2 },				//	i => i`
	{ utf_i1,	utf_i2 },				//	i' => i`
	{ utf_i2,	utf_i, utf_f },			//	i` => if
	{ utf_i3,	utf_i2 },				//	i? => i`
	{ utf_i4,	utf_i2 },				//	i~ => i`
	{ utf_i5,	utf_i2 },				//	i. => i`

	{ utf_Y,	utf_y2 },				//	Y => Y`
	{ utf_Y1,	utf_y2 },				//	Y' => y`
	{ utf_Y2,	utf_y, utf_f },			//	Y` => yf
	{ utf_Y3,	utf_y2 },				//	Y? => y`
	{ utf_Y4,	utf_y2 },				//	Y~ => y`
	{ utf_Y5,	utf_y2 },				//	Y. => y`
	{ utf_y,	utf_y2 },				//	y => Y`
	{ utf_y1,	utf_y2 },				//	y' => y`
	{ utf_y2,	utf_y, utf_f },			//	y` => yf
	{ utf_y3,	utf_y2 },				//	y? => y`
	{ utf_y4,	utf_y2 },				//	y~ => y`
	{ utf_y5,	utf_y2 },				//	y. => y`
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_R[] =
{
	{ utf_A,	utf_A3 },				//	A => A?
	{ utf_A1,	utf_A3 },				//	A' => A?
	{ utf_A2,	utf_A3 },				//	A` => A?
	{ utf_A3,	utf_A, utf_R },			//	A? => AR
	{ utf_A4,	utf_A3 },				//	A~ => A?
	{ utf_A5,	utf_A3 },				//	A. => A?
	{ utf_a,	utf_A3 },				//	a => A?
	{ utf_a1,	utf_A3 },				//	a' => A?
	{ utf_a2,	utf_A3 },				//	a` => A?
	{ utf_a3,	utf_A, utf_R },			//	a? => AR
	{ utf_a4,	utf_A3 },				//	a~ => A?
	{ utf_a5,	utf_A3 },				//	a. => A?

	{ utf_A6,	utf_A63 },				//	A^ => A^?
	{ utf_A61,	utf_A63 },				//	A^' => A^?
	{ utf_A62,	utf_A63 },				//	A^` => A^?
	{ utf_A63,	utf_A6, utf_R },		//	A^? => A^R
	{ utf_A64,	utf_A63 },				//	A^~ => A^?
	{ utf_A65,	utf_A63 },				//	A^. => A^?
	{ utf_a6,	utf_A63 },				//	a^ => A^?
	{ utf_a61,	utf_A63 },				//	a^' => A^?
	{ utf_a62,	utf_A63 },				//	a^` => A^?
	{ utf_a63,	utf_A6, utf_R },		//	a^? => A^R
	{ utf_a64,	utf_A63 },				//	a^~ => A^?
	{ utf_a65,	utf_A63 },				//	a^. => A^?

	{ utf_A8,	utf_A83 },				//	A( => A(?
	{ utf_A81,	utf_A83 },				//	A(' => A(?
	{ utf_A82,	utf_A83 },				//	A(` => A(?
	{ utf_A83,	utf_A8, utf_R },		//	A(? => A(R
	{ utf_A84,	utf_A83 },				//	A(~ => A(?
	{ utf_A85,	utf_A83 },				//	A(. => A(?
	{ utf_a8,	utf_A83 },				//	a( => A(?
	{ utf_a81,	utf_A83 },				//	a(' => A(?
	{ utf_a82,	utf_A83 },				//	a(` => A(?
	{ utf_a83,	utf_A8, utf_R },		//	a(? => A(R
	{ utf_a84,	utf_A83 },				//	a(~ => A(?
	{ utf_a85,	utf_A83 },				//	a(. => A(?

	{ utf_E,	utf_E3 },				//	E => E?
	{ utf_E1,	utf_E3 },				//	E' => E?
	{ utf_E2,	utf_E3 },				//	E` => E?
	{ utf_E3,	utf_E, utf_R },			//	E? => ER
	{ utf_E4,	utf_E3 },				//	E~ => E?
	{ utf_E5,	utf_E3 },				//	E. => E?
	{ utf_e,	utf_E3 },				//	e => E?
	{ utf_e1,	utf_E3 },				//	e' => E?
	{ utf_e2,	utf_E3 },				//	e` => E?
	{ utf_e3,	utf_E, utf_R },			//	e? => ER
	{ utf_e4,	utf_E3 },				//	e~ => E?
	{ utf_e5,	utf_E3 },				//	e. => E?

	{ utf_E6,	utf_E63 },				//	E^ => E^?
	{ utf_E61,	utf_E63 },				//	E^' => E^?
	{ utf_E62,	utf_E63 },				//	E^` => E^?
	{ utf_E63,	utf_E6, utf_R },		//	E^? => E^R
	{ utf_E64,	utf_E63 },				//	E^~ => E^?
	{ utf_E65,	utf_E63 },				//	E^. => E^?
	{ utf_e6,	utf_E63 },				//	e^ => E^?
	{ utf_e61,	utf_E63 },				//	e^' => E^?
	{ utf_e62,	utf_E63 },				//	e^` => E^?
	{ utf_e63,	utf_E6, utf_R },		//	e^? => E^R
	{ utf_e64,	utf_E63 },				//	e^~ => E^?
	{ utf_e65,	utf_E63 },				//	e^. => E^?

	{ utf_O,	utf_O3 },				//	O => O?
	{ utf_O1,	utf_O3 },				//	O' => O?
	{ utf_O2,	utf_O3 },				//	O` => O?
	{ utf_O3,	utf_O, utf_R },			//	O? => OR
	{ utf_O4,	utf_O3 },				//	O~ => O?
	{ utf_O5,	utf_O3 },				//	O. => O?
	{ utf_o,	utf_O3 },				//	o => O?
	{ utf_o1,	utf_O3 },				//	o' => O?
	{ utf_o2,	utf_O3 },				//	o` => O?
	{ utf_o3,	utf_O, utf_R },			//	o? => OR
	{ utf_o4,	utf_O3 },				//	o~ => O?
	{ utf_o5,	utf_O3 },				//	o. => O?

	{ utf_O6,	utf_O63 },				//	O^ => O^?
	{ utf_O61,	utf_O63 },				//	O^' => O^?
	{ utf_O62,	utf_O63 },				//	O^` => O^?
	{ utf_O63,	utf_O6, utf_R },		//	O^? => O^R
	{ utf_O64,	utf_O63 },				//	O^~ => O^?
	{ utf_O65,	utf_O63 },				//	O^. => O^?
	{ utf_o6,	utf_O63 },				//	o^ => O^?
	{ utf_o61,	utf_O63 },				//	o^' => O^?
	{ utf_o62,	utf_O63 },				//	o^` => O^?
	{ utf_o63,	utf_O6, utf_R },		//	o^? => O^R
	{ utf_o64,	utf_O63 },				//	o^~ => O^?
	{ utf_o65,	utf_O63 },				//	o^. => O^?

	{ utf_O7,	utf_O73 },				//	O+ => O+?
	{ utf_O71,	utf_O73 },				//	O+' => O+?
	{ utf_O72,	utf_O73 },				//	O+` => O+?
	{ utf_O73,	utf_O7, utf_R },		//	O+? => O+R
	{ utf_O74,	utf_O73 },				//	O+~ => O+?
	{ utf_O75,	utf_O73 },				//	O+. => O+?
	{ utf_o7,	utf_O73 },				//	o+ => O+?
	{ utf_o71,	utf_O73 },				//	o+' => O+?
	{ utf_o72,	utf_O73 },				//	o+` => O+?
	{ utf_o73,	utf_O7, utf_R },		//	o+? => O+R
	{ utf_o74,	utf_O73 },				//	o+~ => O+?
	{ utf_o75,	utf_O73 },				//	o+. => O+?

	{ utf_U,	utf_U3 },				//	U => U?
	{ utf_U1,	utf_U3 },				//	U' => U?
	{ utf_U2,	utf_U3 },				//	U` => U?
	{ utf_U3,	utf_U, utf_R },			//	U? => UR
	{ utf_U4,	utf_U3 },				//	U~ => U?
	{ utf_U5,	utf_U3 },				//	U. => U?
	{ utf_u,	utf_U3 },				//	u => U?
	{ utf_u1,	utf_U3 },				//	u' => U?
	{ utf_u2,	utf_U3 },				//	u` => U?
	{ utf_u3,	utf_U, utf_R },			//	u? => UR
	{ utf_u4,	utf_U3 },				//	u~ => U?
	{ utf_u5,	utf_U3 },				//	u. => U?

	{ utf_U7,	utf_U73 },				//	U+ => U+?
	{ utf_U71,	utf_U73 },				//	U+' => U+?
	{ utf_U72,	utf_U73 },				//	U+` => U+?
	{ utf_U73,	utf_U7, utf_R },		//	U+? => U+R
	{ utf_U74,	utf_U73 },				//	U+~ => U+?
	{ utf_U75,	utf_U73 },				//	U+. => U+?
	{ utf_u7,	utf_U73 },				//	u+ => U+?
	{ utf_u71,	utf_U73 },				//	u+' => U+?
	{ utf_u72,	utf_U73 },				//	u+` => U+?
	{ utf_u73,	utf_U7, utf_R },		//	u+? => U+R
	{ utf_u74,	utf_U73 },				//	u+~ => U+?
	{ utf_u75,	utf_U73 },				//	u+. => U+?

	{ utf_I,	utf_I3 },				//	I => I?
	{ utf_I1,	utf_I3 },				//	I' => I?
	{ utf_I2,	utf_I3 },				//	I` => I?
	{ utf_I3,	utf_I, utf_R },			//	I? => IR
	{ utf_I4,	utf_I3 },				//	I~ => I?
	{ utf_I5,	utf_I3 },				//	I. => I?
	{ utf_i,	utf_I3 },				//	i => I?
	{ utf_i1,	utf_I3 },				//	i' => I?
	{ utf_i2,	utf_I3 },				//	i` => I?
	{ utf_i3,	utf_I, utf_R },			//	i? => IR
	{ utf_i4,	utf_I3 },				//	i~ => I?
	{ utf_i5,	utf_I3 },				//	i. => I?

	{ utf_Y,	utf_Y3 },				//	Y => Y?
	{ utf_Y1,	utf_Y3 },				//	Y' => Y?
	{ utf_Y2,	utf_Y3 },				//	Y` => Y?
	{ utf_Y3,	utf_Y, utf_R },			//	Y? => YR
	{ utf_Y4,	utf_Y3 },				//	Y~ => Y?
	{ utf_Y5,	utf_Y3 },				//	Y. => Y?
	{ utf_y,	utf_Y3 },				//	y => Y?
	{ utf_y1,	utf_Y3 },				//	y' => Y?
	{ utf_y2,	utf_Y3 },				//	y` => Y?
	{ utf_y3,	utf_Y, utf_R },			//	y? => YR
	{ utf_y4,	utf_Y3 },				//	y~ => Y?
	{ utf_y5,	utf_Y3 },				//	y. => Y?
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_r[] =
{
	{ utf_A,	utf_a3 },				//	A => a?
	{ utf_A1,	utf_a3 },				//	A' => a?
	{ utf_A2,	utf_a3 },				//	A` => a?
	{ utf_A3,	utf_a, utf_r },			//	A? => ar
	{ utf_A4,	utf_a3 },				//	A~ => a?
	{ utf_A5,	utf_a3 },				//	A. => a?
	{ utf_a,	utf_a3 },				//	a => a?
	{ utf_a1,	utf_a3 },				//	a' => a?
	{ utf_a2,	utf_a3 },				//	a` => a?
	{ utf_a3,	utf_a, utf_r },			//	a? => ar
	{ utf_a4,	utf_a3 },				//	a~ => a?
	{ utf_a5,	utf_a3 },				//	a. => a?

	{ utf_A6,	utf_a63 },				//	A^ => a^?
	{ utf_A61,	utf_a63 },				//	A^' => a^?
	{ utf_A62,	utf_a63 },				//	A^` => a^?
	{ utf_A63,	utf_a6, utf_r },		//	A^? => a^r
	{ utf_A64,	utf_a63 },				//	A^~ => a^?
	{ utf_A65,	utf_a63 },				//	A^. => a^?
	{ utf_a6,	utf_a63 },				//	a^ => a^?
	{ utf_a61,	utf_a63 },				//	a^' => a^?
	{ utf_a62,	utf_a63 },				//	a^` => a^?
	{ utf_a63,	utf_a6, utf_r },		//	a^? => a^r
	{ utf_a64,	utf_a63 },				//	a^~ => a^?
	{ utf_a65,	utf_a63 },				//	a^. => a^?

	{ utf_A8,	utf_a83 },				//	A( => a(?
	{ utf_A81,	utf_a83 },				//	A(' => a(?
	{ utf_A82,	utf_a83 },				//	A(` => a(?
	{ utf_A83,	utf_a8, utf_r },		//	A(? => a(r
	{ utf_A84,	utf_a83 },				//	A(~ => a(?
	{ utf_A85,	utf_a83 },				//	A(. => a(?
	{ utf_a8,	utf_a83 },				//	a( => a(?
	{ utf_a81,	utf_a83 },				//	a(' => a(?
	{ utf_a82,	utf_a83 },				//	a(` => a(?
	{ utf_a83,	utf_a8, utf_r },		//	a(? => a(r
	{ utf_a84,	utf_a83 },				//	a(~ => a(?
	{ utf_a85,	utf_a83 },				//	a(. => a(?

	{ utf_E,	utf_e3 },				//	E => e?
	{ utf_E1,	utf_e3 },				//	E' => e?
	{ utf_E2,	utf_e3 },				//	E` => e?
	{ utf_E3,	utf_e, utf_r },			//	E? => er
	{ utf_E4,	utf_e3 },				//	E~ => e?
	{ utf_E5,	utf_e3 },				//	E. => e?
	{ utf_e,	utf_e3 },				//	e => e?
	{ utf_e1,	utf_e3 },				//	e' => e?
	{ utf_e2,	utf_e3 },				//	e` => e?
	{ utf_e3,	utf_e, utf_r },			//	e? => er
	{ utf_e4,	utf_e3 },				//	e~ => e?
	{ utf_e5,	utf_e3 },				//	e. => e?

	{ utf_E6,	utf_e63 },				//	E^ => e^?
	{ utf_E61,	utf_e63 },				//	E^' => e^?
	{ utf_E62,	utf_e63 },				//	E^` => e^?
	{ utf_E63,	utf_e6, utf_r },		//	E^? => e^r
	{ utf_E64,	utf_e63 },				//	E^~ => e^?
	{ utf_E65,	utf_e63 },				//	E^. => e^?
	{ utf_e6,	utf_e63 },				//	e^ => e^?
	{ utf_e61,	utf_e63 },				//	e^' => e^?
	{ utf_e62,	utf_e63 },				//	e^` => e^?
	{ utf_e63,	utf_e6, utf_r },		//	e^? => e^r
	{ utf_e64,	utf_e63 },				//	e^~ => e^?
	{ utf_e65,	utf_e63 },				//	e^. => e^?

	{ utf_O,	utf_o3 },				//	O => o?
	{ utf_O1,	utf_o3 },				//	O' => o?
	{ utf_O2,	utf_o3 },				//	O` => o?
	{ utf_O3,	utf_o, utf_r },			//	O? => or
	{ utf_O4,	utf_o3 },				//	O~ => o?
	{ utf_O5,	utf_o3 },				//	O. => o?
	{ utf_o,	utf_o3 },				//	o => o?
	{ utf_o1,	utf_o3 },				//	o' => o?
	{ utf_o2,	utf_o3 },				//	o` => o?
	{ utf_o3,	utf_o, utf_r },			//	o? => or
	{ utf_o4,	utf_o3 },				//	o~ => o?
	{ utf_o5,	utf_o3 },				//	o. => o?

	{ utf_O6,	utf_o63 },				//	O^ => o^?
	{ utf_O61,	utf_o63 },				//	O^' => o^?
	{ utf_O62,	utf_o63 },				//	O^` => o^?
	{ utf_O63,	utf_o6, utf_r },		//	O^? => o^r
	{ utf_O64,	utf_o63 },				//	O^~ => o^?
	{ utf_O65,	utf_o63 },				//	O^. => o^?
	{ utf_o6,	utf_o63 },				//	o^ => o^?
	{ utf_o61,	utf_o63 },				//	o^' => o^?
	{ utf_o62,	utf_o63 },				//	o^` => o^?
	{ utf_o63,	utf_o6, utf_r },		//	o^? => o^r
	{ utf_o64,	utf_o63 },				//	o^~ => o^?
	{ utf_o65,	utf_o63 },				//	o^. => o^?

	{ utf_O7,	utf_o73 },				//	O+ => o+?
	{ utf_O71,	utf_o73 },				//	O+' => o+?
	{ utf_O72,	utf_o73 },				//	O+` => o+?
	{ utf_O73,	utf_o7, utf_r },		//	O+? => o+r
	{ utf_O74,	utf_o73 },				//	O+~ => o+?
	{ utf_O75,	utf_o73 },				//	O+. => o+?
	{ utf_o7,	utf_o73 },				//	o+ => o+?
	{ utf_o71,	utf_o73 },				//	o+' => o+?
	{ utf_o72,	utf_o73 },				//	o+` => o+?
	{ utf_o73,	utf_o7, utf_r },		//	o+? => o+r
	{ utf_o74,	utf_o73 },				//	o+~ => o+?
	{ utf_o75,	utf_o73 },				//	o+. => o+?

	{ utf_U,	utf_u3 },				//	U => u?
	{ utf_U1,	utf_u3 },				//	U' => u?
	{ utf_U2,	utf_u3 },				//	U` => u?
	{ utf_U3,	utf_u, utf_r },			//	U? => ur
	{ utf_U4,	utf_u3 },				//	U~ => u?
	{ utf_U5,	utf_u3 },				//	U. => u?
	{ utf_u,	utf_u3 },				//	u => u?
	{ utf_u1,	utf_u3 },				//	u' => u?
	{ utf_u2,	utf_u3 },				//	u` => u?
	{ utf_u3,	utf_u, utf_r },			//	u? => ur
	{ utf_u4,	utf_u3 },				//	u~ => u?
	{ utf_u5,	utf_u3 },				//	u. => u?

	{ utf_U7,	utf_u73 },				//	U+ => u+?
	{ utf_U71,	utf_u73 },				//	U+' => u+?
	{ utf_U72,	utf_u73 },				//	U+` => u+?
	{ utf_U73,	utf_u7, utf_r },		//	U+? => u+r
	{ utf_U74,	utf_u73 },				//	U+~ => u+?
	{ utf_U75,	utf_u73 },				//	U+. => u+?
	{ utf_u7,	utf_u73 },				//	u+ => u+?
	{ utf_u71,	utf_u73 },				//	u+' => u+?
	{ utf_u72,	utf_u73 },				//	u+` => u+?
	{ utf_u73,	utf_u7, utf_r },		//	u+? => u+r
	{ utf_u74,	utf_u73 },				//	u+~ => u+?
	{ utf_u75,	utf_u73 },				//	u+. => u+?

	{ utf_I,	utf_i3 },				//	I => i?
	{ utf_I1,	utf_i3 },				//	I' => i?
	{ utf_I2,	utf_i3 },				//	I` => i?
	{ utf_I3,	utf_i, utf_r },			//	I? => ir
	{ utf_I4,	utf_i3 },				//	I~ => i?
	{ utf_I5,	utf_i3 },				//	I. => i?
	{ utf_i,	utf_i3 },				//	i => i?
	{ utf_i1,	utf_i3 },				//	i' => i?
	{ utf_i2,	utf_i3 },				//	i` => i?
	{ utf_i3,	utf_i, utf_r },			//	i? => ir
	{ utf_i4,	utf_i3 },				//	i~ => i?
	{ utf_i5,	utf_i3 },				//	i. => i?

	{ utf_Y,	utf_y3 },				//	Y => Y?
	{ utf_Y1,	utf_y3 },				//	Y' => y?
	{ utf_Y2,	utf_y3 },				//	Y` => y?
	{ utf_Y3,	utf_y, utf_r },			//	Y? => yr
	{ utf_Y4,	utf_y3 },				//	Y~ => y?
	{ utf_Y5,	utf_y3 },				//	Y. => y?
	{ utf_y,	utf_y3 },				//	y => Y?
	{ utf_y1,	utf_y3 },				//	y' => y?
	{ utf_y2,	utf_y3 },				//	y` => y?
	{ utf_y3,	utf_y, utf_r },			//	y? => yr
	{ utf_y4,	utf_y3 },				//	y~ => y?
	{ utf_y5,	utf_y3 },				//	y. => y?
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_X[] =
{
	{ utf_A,	utf_A4 },				//	A => A~
	{ utf_A1,	utf_A4 },				//	A' => A~
	{ utf_A2,	utf_A4 },				//	A` => A~
	{ utf_A3,	utf_A4 },				//	A? => A~
	{ utf_A4,	utf_A, utf_X },			//	A~ => AX
	{ utf_A5,	utf_A4 },				//	A. => A~
	{ utf_a,	utf_A4 },				//	a => A~
	{ utf_a1,	utf_A4 },				//	a' => A~
	{ utf_a2,	utf_A4 },				//	a` => A~
	{ utf_a3,	utf_A4 },				//	a? => A~
	{ utf_a4,	utf_A, utf_X },			//	a~ => AX
	{ utf_a5,	utf_A4 },				//	a. => A~

	{ utf_A6,	utf_A64 },				//	A^ => A^~
	{ utf_A61,	utf_A64 },				//	A^' => A^~
	{ utf_A62,	utf_A64 },				//	A^` => A^~
	{ utf_A63,	utf_A64 },				//	A^? => A^~
	{ utf_A64,	utf_A6, utf_X },		//	A^~ => A^X
	{ utf_A65,	utf_A64 },				//	A^. => A^~
	{ utf_a6,	utf_A64 },				//	a^ => A^~
	{ utf_a61,	utf_A64 },				//	a^' => A^~
	{ utf_a62,	utf_A64 },				//	a^` => A^~
	{ utf_a63,	utf_A64 },				//	a^? => A^~
	{ utf_a64,	utf_A6, utf_X },		//	a^~ => A^X
	{ utf_a65,	utf_A64 },				//	a^. => A^~

	{ utf_A8,	utf_A84 },				//	A( => A(~
	{ utf_A81,	utf_A84 },				//	A(' => A(~
	{ utf_A82,	utf_A84 },				//	A(` => A(~
	{ utf_A83,	utf_A84 },				//	A(? => A(~
	{ utf_A84,	utf_A8, utf_X },		//	A(~ => A(X
	{ utf_A85,	utf_A84 },				//	A(. => A(~
	{ utf_a8,	utf_A84 },				//	a( => A(~
	{ utf_a81,	utf_A84 },				//	a(' => A(~
	{ utf_a82,	utf_A84 },				//	a(` => A(~
	{ utf_a83,	utf_A84 },				//	a(? => A(~
	{ utf_a84,	utf_A8, utf_X },		//	a(~ => A(X
	{ utf_a85,	utf_A84 },				//	a(. => A(~

	{ utf_E,	utf_E4 },				//	E => E~
	{ utf_E1,	utf_E4 },				//	E' => E~
	{ utf_E2,	utf_E4 },				//	E` => E~
	{ utf_E3,	utf_E4 },				//	E? => E~
	{ utf_E4,	utf_E, utf_X },			//	E~ => EX
	{ utf_E5,	utf_E4 },				//	E. => E~
	{ utf_e,	utf_E4 },				//	e => E~
	{ utf_e1,	utf_E4 },				//	e' => E~
	{ utf_e2,	utf_E4 },				//	e` => E~
	{ utf_e3,	utf_E4 },				//	e? => E~
	{ utf_e4,	utf_E, utf_X },			//	e~ => EX
	{ utf_e5,	utf_E4 },				//	e. => E~

	{ utf_E6,	utf_E64 },				//	E^ => E^~
	{ utf_E61,	utf_E64 },				//	E^' => E^~
	{ utf_E62,	utf_E64 },				//	E^` => E^~
	{ utf_E63,	utf_E64 },				//	E^? => E^~
	{ utf_E64,	utf_E6, utf_X },		//	E^~ => E^X
	{ utf_E65,	utf_E64 },				//	E^. => E^~
	{ utf_e6,	utf_E64 },				//	e^ => E^~
	{ utf_e61,	utf_E64 },				//	e^' => E^~
	{ utf_e62,	utf_E64 },				//	e^` => E^~
	{ utf_e63,	utf_E64 },				//	e^? => E^~
	{ utf_e64,	utf_E6, utf_X },		//	e^~ => E^X
	{ utf_e65,	utf_E64 },				//	e^. => E^~

	{ utf_O,	utf_O4 },				//	O => O~
	{ utf_O1,	utf_O4 },				//	O' => O~
	{ utf_O2,	utf_O4 },				//	O` => O~
	{ utf_O3,	utf_O4 },				//	O? => O~
	{ utf_O4,	utf_O, utf_X },			//	O~ => OX
	{ utf_O5,	utf_O4 },				//	O. => O~
	{ utf_o,	utf_O4 },				//	o => O~
	{ utf_o1,	utf_O4 },				//	o' => O~
	{ utf_o2,	utf_O4 },				//	o` => O~
	{ utf_o3,	utf_O4 },				//	o? => O~
	{ utf_o4,	utf_O, utf_X },			//	o~ => OX
	{ utf_o5,	utf_O4 },				//	o. => O~

	{ utf_O6,	utf_O64 },				//	O^ => O^~
	{ utf_O61,	utf_O64 },				//	O^' => O^~
	{ utf_O62,	utf_O64 },				//	O^` => O^~
	{ utf_O63,	utf_O64 },				//	O^? => O^~
	{ utf_O64,	utf_O6, utf_X },		//	O^~ => O^X
	{ utf_O65,	utf_O64 },				//	O^. => O^~
	{ utf_o6,	utf_O64 },				//	o^ => O^~
	{ utf_o61,	utf_O64 },				//	o^' => O^~
	{ utf_o62,	utf_O64 },				//	o^` => O^~
	{ utf_o63,	utf_O64 },				//	o^? => O^~
	{ utf_o64,	utf_O6, utf_X },		//	o^~ => O^X
	{ utf_o65,	utf_O64 },				//	o^. => O^~

	{ utf_O7,	utf_O74 },				//	O+ => O+~
	{ utf_O71,	utf_O74 },				//	O+' => O+~
	{ utf_O72,	utf_O74 },				//	O+` => O+~
	{ utf_O73,	utf_O74 },				//	O+? => O+~
	{ utf_O74,	utf_O7, utf_X },		//	O+~ => O+X
	{ utf_O75,	utf_O74 },				//	O+. => O+~
	{ utf_o7,	utf_O74 },				//	o+ => O+~
	{ utf_o71,	utf_O74 },				//	o+' => O+~
	{ utf_o72,	utf_O74 },				//	o+` => O+~
	{ utf_o73,	utf_O74 },				//	o+? => O+~
	{ utf_o74,	utf_O7, utf_X },		//	o+~ => O+X
	{ utf_o75,	utf_O74 },				//	o+. => O+~

	{ utf_U,	utf_U4 },				//	U => U~
	{ utf_U1,	utf_U4 },				//	U' => U~
	{ utf_U2,	utf_U4 },				//	U` => U~
	{ utf_U3,	utf_U4 },				//	U? => U~
	{ utf_U4,	utf_U, utf_X },			//	U~ => UX
	{ utf_U5,	utf_U4 },				//	U. => U~
	{ utf_u,	utf_U4 },				//	u => U~
	{ utf_u1,	utf_U4 },				//	u' => U~
	{ utf_u2,	utf_U4 },				//	u` => U~
	{ utf_u3,	utf_U4 },				//	u? => U~
	{ utf_u4,	utf_U, utf_X },			//	u~ => UX
	{ utf_u5,	utf_U4 },				//	u. => U~

	{ utf_U7,	utf_U74 },				//	U+ => U+~
	{ utf_U71,	utf_U74 },				//	U+' => U+~
	{ utf_U72,	utf_U74 },				//	U+` => U+~
	{ utf_U73,	utf_U74 },				//	U+? => U+~
	{ utf_U74,	utf_U7, utf_X },		//	U+~ => U+X
	{ utf_U75,	utf_U74 },				//	U+. => U+~
	{ utf_u7,	utf_U74 },				//	u+ => U+~
	{ utf_u71,	utf_U74 },				//	u+' => U+~
	{ utf_u72,	utf_U74 },				//	u+` => U+~
	{ utf_u73,	utf_U74 },				//	u+? => U+~
	{ utf_u74,	utf_U7, utf_X },		//	u+~ => U+X
	{ utf_u75,	utf_U74 },				//	u+. => U+~

	{ utf_I,	utf_I4 },				//	I => I~
	{ utf_I1,	utf_I4 },				//	I' => I~
	{ utf_I2,	utf_I4 },				//	I` => I~
	{ utf_I3,	utf_I4 },				//	I? => I~
	{ utf_I4,	utf_I, utf_X },			//	I~ => IX
	{ utf_I5,	utf_I4 },				//	I. => I~
	{ utf_i,	utf_I4 },				//	i => I~
	{ utf_i1,	utf_I4 },				//	i' => I~
	{ utf_i2,	utf_I4 },				//	i` => I~
	{ utf_i3,	utf_I4 },				//	i? => I~
	{ utf_i4,	utf_I, utf_X },			//	i~ => IX
	{ utf_i5,	utf_I4 },				//	i. => I~

	{ utf_Y,	utf_Y4 },				//	Y => Y~
	{ utf_Y1,	utf_Y4 },				//	Y' => Y~
	{ utf_Y2,	utf_Y4 },				//	Y` => Y~
	{ utf_Y3,	utf_Y4 },				//	Y? => Y~
	{ utf_Y4,	utf_Y, utf_X },			//	Y~ => YX
	{ utf_Y5,	utf_Y4 },				//	Y. => Y~
	{ utf_y,	utf_Y4 },				//	y => Y~
	{ utf_y1,	utf_Y4 },				//	y' => Y~
	{ utf_y2,	utf_Y4 },				//	y` => Y~
	{ utf_y3,	utf_Y4 },				//	y? => Y~
	{ utf_y4,	utf_Y, utf_X },			//	y~ => YX
	{ utf_y5,	utf_Y4 },				//	y. => Y~
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_x[] =
{
	{ utf_A,	utf_a4 },				//	A => a~
	{ utf_A1,	utf_a4 },				//	A' => a~
	{ utf_A2,	utf_a4 },				//	A` => a~
	{ utf_A3,	utf_a4 },				//	A? => a~
	{ utf_A4,	utf_a, utf_x },			//	A~ => ax
	{ utf_A5,	utf_a4 },				//	A. => a~
	{ utf_a,	utf_a4 },				//	a => a~
	{ utf_a1,	utf_a4 },				//	a' => a~
	{ utf_a2,	utf_a4 },				//	a` => a~
	{ utf_a3,	utf_a4 },				//	a? => a~
	{ utf_a4,	utf_a, utf_x },			//	a~ => ax
	{ utf_a5,	utf_a4 },				//	a. => a~

	{ utf_A6,	utf_a64 },				//	A^ => a^~
	{ utf_A61,	utf_a64 },				//	A^' => a^~
	{ utf_A62,	utf_a64 },				//	A^` => a^~
	{ utf_A63,	utf_a64 },				//	A^? => a^~
	{ utf_A64,	utf_a6, utf_x },		//	A^~ => a^x
	{ utf_A65,	utf_a64 },				//	A^. => a^~
	{ utf_a6,	utf_a64 },				//	a^ => a^~
	{ utf_a61,	utf_a64 },				//	a^' => a^~
	{ utf_a62,	utf_a64 },				//	a^` => a^~
	{ utf_a63,	utf_a64 },				//	a^? => a^~
	{ utf_a64,	utf_a6, utf_x },		//	a^~ => a^x
	{ utf_a65,	utf_a64 },				//	a^. => a^~

	{ utf_A8,	utf_a84 },				//	A( => a(~
	{ utf_A81,	utf_a84 },				//	A(' => a(~
	{ utf_A82,	utf_a84 },				//	A(` => a(~
	{ utf_A83,	utf_a84 },				//	A(? => a(~
	{ utf_A84,	utf_a8, utf_x },		//	A(~ => a(x
	{ utf_A85,	utf_a84 },				//	A(. => a(~
	{ utf_a8,	utf_a84 },				//	a( => a(~
	{ utf_a81,	utf_a84 },				//	a(' => a(~
	{ utf_a82,	utf_a84 },				//	a(` => a(~
	{ utf_a83,	utf_a84 },				//	a(? => a(~
	{ utf_a84,	utf_a8, utf_x },		//	a(~ => a(x
	{ utf_a85,	utf_a84 },				//	a(. => a(~

	{ utf_E,	utf_e4 },				//	E => e~
	{ utf_E1,	utf_e4 },				//	E' => e~
	{ utf_E2,	utf_e4 },				//	E` => e~
	{ utf_E3,	utf_e4 },				//	E? => e~
	{ utf_E4,	utf_e, utf_x },			//	E~ => ex
	{ utf_E5,	utf_e4 },				//	E. => e~
	{ utf_e,	utf_e4 },				//	e => e~
	{ utf_e1,	utf_e4 },				//	e' => e~
	{ utf_e2,	utf_e4 },				//	e` => e~
	{ utf_e3,	utf_e4 },				//	e? => e~
	{ utf_e4,	utf_e, utf_x },			//	e~ => ex
	{ utf_e5,	utf_e4 },				//	e. => e~

	{ utf_E6,	utf_e64 },				//	E^ => e^~
	{ utf_E61,	utf_e64 },				//	E^' => e^~
	{ utf_E62,	utf_e64 },				//	E^` => e^~
	{ utf_E63,	utf_e64 },				//	E^? => e^~
	{ utf_E64,	utf_e6, utf_x },		//	E^~ => e^x
	{ utf_E65,	utf_e64 },				//	E^. => e^~
	{ utf_e6,	utf_e64 },				//	e^ => e^~
	{ utf_e61,	utf_e64 },				//	e^' => e^~
	{ utf_e62,	utf_e64 },				//	e^` => e^~
	{ utf_e63,	utf_e64 },				//	e^? => e^~
	{ utf_e64,	utf_e6, utf_x },		//	e^~ => e^x
	{ utf_e65,	utf_e64 },				//	e^. => e^~

	{ utf_O,	utf_o4 },				//	O => o~
	{ utf_O1,	utf_o4 },				//	O' => o~
	{ utf_O2,	utf_o4 },				//	O` => o~
	{ utf_O3,	utf_o4 },				//	O? => o~
	{ utf_O4,	utf_o, utf_x },			//	O~ => ox
	{ utf_O5,	utf_o4 },				//	O. => o~
	{ utf_o,	utf_o4 },				//	o => o~
	{ utf_o1,	utf_o4 },				//	o' => o~
	{ utf_o2,	utf_o4 },				//	o` => o~
	{ utf_o3,	utf_o4 },				//	o? => o~
	{ utf_o4,	utf_o, utf_x },			//	o~ => ox
	{ utf_o5,	utf_o4 },				//	o. => o~

	{ utf_O6,	utf_o64 },				//	O^ => o^~
	{ utf_O61,	utf_o64 },				//	O^' => o^~
	{ utf_O62,	utf_o64 },				//	O^` => o^~
	{ utf_O63,	utf_o64 },				//	O^? => o^~
	{ utf_O64,	utf_o6, utf_x },		//	O^~ => o^x
	{ utf_O65,	utf_o64 },				//	O^. => o^~
	{ utf_o6,	utf_o64 },				//	o^ => o^~
	{ utf_o61,	utf_o64 },				//	o^' => o^~
	{ utf_o62,	utf_o64 },				//	o^` => o^~
	{ utf_o63,	utf_o64 },				//	o^? => o^~
	{ utf_o64,	utf_o6, utf_x },		//	o^~ => o^x
	{ utf_o65,	utf_o64 },				//	o^. => o^~

	{ utf_O7,	utf_o74 },				//	O+ => o+~
	{ utf_O71,	utf_o74 },				//	O+' => o+~
	{ utf_O72,	utf_o74 },				//	O+` => o+~
	{ utf_O73,	utf_o74 },				//	O+? => o+~
	{ utf_O74,	utf_o7, utf_x },		//	O+~ => o+x
	{ utf_O75,	utf_o74 },				//	O+. => o+~
	{ utf_o7,	utf_o74 },				//	o+ => o+~
	{ utf_o71,	utf_o74 },				//	o+' => o+~
	{ utf_o72,	utf_o74 },				//	o+` => o+~
	{ utf_o73,	utf_o74 },				//	o+? => o+~
	{ utf_o74,	utf_o7, utf_x },		//	o+~ => o+x
	{ utf_o75,	utf_o74 },				//	o+. => o+~

	{ utf_U,	utf_u4 },				//	U => u~
	{ utf_U1,	utf_u4 },				//	U' => u~
	{ utf_U2,	utf_u4 },				//	U` => u~
	{ utf_U3,	utf_u4 },				//	U? => u~
	{ utf_U4,	utf_u, utf_x },			//	U~ => ux
	{ utf_U5,	utf_u4 },				//	U. => u~
	{ utf_u,	utf_u4 },				//	u => u~
	{ utf_u1,	utf_u4 },				//	u' => u~
	{ utf_u2,	utf_u4 },				//	u` => u~
	{ utf_u3,	utf_u4 },				//	u? => u~
	{ utf_u4,	utf_u, utf_x },			//	u~ => ux
	{ utf_u5,	utf_u4 },				//	u. => u~

	{ utf_U7,	utf_u74 },				//	U+ => u+~
	{ utf_U71,	utf_u74 },				//	U+' => u+~
	{ utf_U72,	utf_u74 },				//	U+` => u+~
	{ utf_U73,	utf_u74 },				//	U+? => u+~
	{ utf_U74,	utf_u7, utf_x },		//	U+~ => u+x
	{ utf_U75,	utf_u74 },				//	U+. => u+~
	{ utf_u7,	utf_u74 },				//	u+ => u+~
	{ utf_u71,	utf_u74 },				//	u+' => u+~
	{ utf_u72,	utf_u74 },				//	u+` => u+~
	{ utf_u73,	utf_u74 },				//	u+? => u+~
	{ utf_u74,	utf_u7, utf_x },		//	u+~ => u+x
	{ utf_u75,	utf_u74 },				//	u+. => u+~

	{ utf_I,	utf_i4 },				//	I => i~
	{ utf_I1,	utf_i4 },				//	I' => i~
	{ utf_I2,	utf_i4 },				//	I` => i~
	{ utf_I3,	utf_i4 },				//	I? => i~
	{ utf_I4,	utf_i, utf_x },			//	I~ => ix
	{ utf_I5,	utf_i4 },				//	I. => i~
	{ utf_i,	utf_i4 },				//	i => i~
	{ utf_i1,	utf_i4 },				//	i' => i~
	{ utf_i2,	utf_i4 },				//	i` => i~
	{ utf_i3,	utf_i4 },				//	i? => i~
	{ utf_i4,	utf_i, utf_x },			//	i~ => ix
	{ utf_i5,	utf_i4 },				//	i. => i~

	{ utf_Y,	utf_y4 },				//	Y => Y~
	{ utf_Y1,	utf_y4 },				//	Y' => y~
	{ utf_Y2,	utf_y4 },				//	Y` => y~
	{ utf_Y3,	utf_y4 },				//	Y? => y~
	{ utf_Y4,	utf_y, utf_x },			//	Y~ => yx
	{ utf_Y5,	utf_y4 },				//	Y. => y~
	{ utf_y,	utf_y4 },				//	y => Y~
	{ utf_y1,	utf_y4 },				//	y' => y~
	{ utf_y2,	utf_y4 },				//	y` => y~
	{ utf_y3,	utf_y4 },				//	y? => y~
	{ utf_y4,	utf_y, utf_x },			//	y~ => yx
	{ utf_y5,	utf_y4 },				//	y. => y~
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_J[] =
{
	{ utf_A,	utf_A5 },				//	A => A.
	{ utf_A1,	utf_A5 },				//	A' => A.
	{ utf_A2,	utf_A5 },				//	A` => A.
	{ utf_A3,	utf_A5 },				//	A? => A.
	{ utf_A4,	utf_A5 },				//	A~ => A.
	{ utf_A5,	utf_A, utf_J },			//	A. => AJ
	{ utf_a,	utf_A5 },				//	a => A.
	{ utf_a1,	utf_A5 },				//	a' => A.
	{ utf_a2,	utf_A5 },				//	a` => A.
	{ utf_a3,	utf_A5 },				//	a? => A.
	{ utf_a4,	utf_A5 },				//	a~ => A.
	{ utf_a5,	utf_A, utf_J },			//	a. => AJ

	{ utf_A6,	utf_A65 },				//	A^ => A^.
	{ utf_A61,	utf_A65 },				//	A^' => A^.
	{ utf_A62,	utf_A65 },				//	A^` => A^.
	{ utf_A63,	utf_A65 },				//	A^? => A^.
	{ utf_A64,	utf_A65 },				//	A^~ => A^.
	{ utf_A65,	utf_A6, utf_J },		//	A^. => A^J
	{ utf_a6,	utf_A65 },				//	a^ => A^.
	{ utf_a61,	utf_A65 },				//	a^' => A^.
	{ utf_a62,	utf_A65 },				//	a^` => A^.
	{ utf_a63,	utf_A65 },				//	a^? => A^.
	{ utf_a64,	utf_A65 },				//	a^~ => A^.
	{ utf_a65,	utf_A6, utf_J },		//	a^. => A^J

	{ utf_A8,	utf_A85 },				//	A( => A(.
	{ utf_A81,	utf_A85 },				//	A(' => A(.
	{ utf_A82,	utf_A85 },				//	A(` => A(.
	{ utf_A83,	utf_A85 },				//	A(? => A(.
	{ utf_A84,	utf_A85 },				//	A(~ => A(.
	{ utf_A85,	utf_A8, utf_J },		//	A(. => A(J
	{ utf_a8,	utf_A85 },				//	a( => A(.
	{ utf_a81,	utf_A85 },				//	a(' => A(.
	{ utf_a82,	utf_A85 },				//	a(` => A(.
	{ utf_a83,	utf_A85 },				//	a(? => A(.
	{ utf_a84,	utf_A85 },				//	a(~ => A(.
	{ utf_a85,	utf_A8, utf_J },		//	a(. => A(J

	{ utf_E,	utf_E5 },				//	E => E.
	{ utf_E1,	utf_E5 },				//	E' => E.
	{ utf_E2,	utf_E5 },				//	E` => E.
	{ utf_E3,	utf_E5 },				//	E? => E.
	{ utf_E4,	utf_E5 },				//	E~ => E.
	{ utf_E5,	utf_E, utf_J },			//	E. => EJ
	{ utf_e,	utf_E5 },				//	e => E.
	{ utf_e1,	utf_E5 },				//	e' => E.
	{ utf_e2,	utf_E5 },				//	e` => E.
	{ utf_e3,	utf_E5 },				//	e? => E.
	{ utf_e4,	utf_E5 },				//	e~ => E.
	{ utf_e5,	utf_E, utf_J },			//	e. => EJ

	{ utf_E6,	utf_E65 },				//	E^ => E^.
	{ utf_E61,	utf_E65 },				//	E^' => E^.
	{ utf_E62,	utf_E65 },				//	E^` => E^.
	{ utf_E63,	utf_E65 },				//	E^? => E^.
	{ utf_E64,	utf_E65 },				//	E^~ => E^.
	{ utf_E65,	utf_E6, utf_J },		//	E^. => E^J
	{ utf_e6,	utf_E65 },				//	e^ => E^.
	{ utf_e61,	utf_E65 },				//	e^' => E^.
	{ utf_e62,	utf_E65 },				//	e^` => E^.
	{ utf_e63,	utf_E65 },				//	e^? => E^.
	{ utf_e64,	utf_E65 },				//	e^~ => E^.
	{ utf_e65,	utf_E6, utf_J },		//	e^. => E^J

	{ utf_O,	utf_O5 },				//	O => O.
	{ utf_O1,	utf_O5 },				//	O' => O.
	{ utf_O2,	utf_O5 },				//	O` => O.
	{ utf_O3,	utf_O5 },				//	O? => O.
	{ utf_O4,	utf_O5 },				//	O~ => O.
	{ utf_O5,	utf_O, utf_J },			//	O. => OJ
	{ utf_o,	utf_O5 },				//	o => O.
	{ utf_o1,	utf_O5 },				//	o' => O.
	{ utf_o2,	utf_O5 },				//	o` => O.
	{ utf_o3,	utf_O5 },				//	o? => O.
	{ utf_o4,	utf_O5 },				//	o~ => O.
	{ utf_o5,	utf_O, utf_J },			//	o. => OJ

	{ utf_O6,	utf_O65 },				//	O^ => O^.
	{ utf_O61,	utf_O65 },				//	O^' => O^.
	{ utf_O62,	utf_O65 },				//	O^` => O^.
	{ utf_O63,	utf_O65 },				//	O^? => O^.
	{ utf_O64,	utf_O65 },				//	O^~ => O^.
	{ utf_O65,	utf_O6, utf_J },		//	O^. => O^J
	{ utf_o6,	utf_O65 },				//	o^ => O^.
	{ utf_o61,	utf_O65 },				//	o^' => O^.
	{ utf_o62,	utf_O65 },				//	o^` => O^.
	{ utf_o63,	utf_O65 },				//	o^? => O^.
	{ utf_o64,	utf_O65 },				//	o^~ => O^.
	{ utf_o65,	utf_O6, utf_J },		//	o^. => O^J

	{ utf_O7,	utf_O75 },				//	O+ => O+.
	{ utf_O71,	utf_O75 },				//	O+' => O+.
	{ utf_O72,	utf_O75 },				//	O+` => O+.
	{ utf_O73,	utf_O75 },				//	O+? => O+.
	{ utf_O74,	utf_O75 },				//	O+~ => O+.
	{ utf_O75,	utf_O7, utf_J },		//	O+. => O+J
	{ utf_o7,	utf_O75 },				//	o+ => O+.
	{ utf_o71,	utf_O75 },				//	o+' => O+.
	{ utf_o72,	utf_O75 },				//	o+` => O+.
	{ utf_o73,	utf_O75 },				//	o+? => O+.
	{ utf_o74,	utf_O75 },				//	o+~ => O+.
	{ utf_o75,	utf_O7, utf_J },		//	o+. => O+J

	{ utf_U,	utf_U5 },				//	U => U.
	{ utf_U1,	utf_U5 },				//	U' => U.
	{ utf_U2,	utf_U5 },				//	U` => U.
	{ utf_U3,	utf_U5 },				//	U? => U.
	{ utf_U4,	utf_U5 },				//	U~ => U.
	{ utf_U5,	utf_U, utf_J },			//	U. => UJ
	{ utf_u,	utf_U5 },				//	u => U.
	{ utf_u1,	utf_U5 },				//	u' => U.
	{ utf_u2,	utf_U5 },				//	u` => U.
	{ utf_u3,	utf_U5 },				//	u? => U.
	{ utf_u4,	utf_U5 },				//	u~ => U.
	{ utf_u5,	utf_U, utf_J },			//	u. => UJ

	{ utf_U7,	utf_U75 },				//	U+ => U+.
	{ utf_U71,	utf_U75 },				//	U+' => U+.
	{ utf_U72,	utf_U75 },				//	U+` => U+.
	{ utf_U73,	utf_U75 },				//	U+? => U+.
	{ utf_U74,	utf_U75 },				//	U+~ => U+.
	{ utf_U75,	utf_U7, utf_J },		//	U+. => U+J
	{ utf_u7,	utf_U75 },				//	u+ => U+.
	{ utf_u71,	utf_U75 },				//	u+' => U+.
	{ utf_u72,	utf_U75 },				//	u+` => U+.
	{ utf_u73,	utf_U75 },				//	u+? => U+.
	{ utf_u74,	utf_U75 },				//	u+~ => U+.
	{ utf_u75,	utf_U7, utf_J },		//	u+. => U+J

	{ utf_I,	utf_I5 },				//	I => I.
	{ utf_I1,	utf_I5 },				//	I' => I.
	{ utf_I2,	utf_I5 },				//	I` => I.
	{ utf_I3,	utf_I5 },				//	I? => I.
	{ utf_I4,	utf_I5 },				//	I~ => I.
	{ utf_I5,	utf_I, utf_J },			//	I. => IJ
	{ utf_i,	utf_I5 },				//	i => I.
	{ utf_i1,	utf_I5 },				//	i' => I.
	{ utf_i2,	utf_I5 },				//	i` => I.
	{ utf_i3,	utf_I5 },				//	i? => I.
	{ utf_i4,	utf_I5 },				//	i~ => I.
	{ utf_i5,	utf_I, utf_J },			//	i. => IJ

	{ utf_Y,	utf_Y5 },				//	Y => Y.
	{ utf_Y1,	utf_Y5 },				//	Y' => Y.
	{ utf_Y2,	utf_Y5 },				//	Y` => Y.
	{ utf_Y3,	utf_Y5 },				//	Y? => Y.
	{ utf_Y4,	utf_Y5 },				//	Y~ => Y.
	{ utf_Y5,	utf_Y, utf_J },			//	Y. => YJ
	{ utf_y,	utf_Y5 },				//	y => Y.
	{ utf_y1,	utf_Y5 },				//	y' => Y.
	{ utf_y2,	utf_Y5 },				//	y` => Y.
	{ utf_y3,	utf_Y5 },				//	y? => Y.
	{ utf_y4,	utf_Y5 },				//	y~ => Y.
	{ utf_y5,	utf_Y, utf_J },			//	y. => YJ
	{ 0 }
};
/*----------------------------------------------------------------------------*/
static vietcode_t code_j[] =
{
	{ utf_A,	utf_a5 },				//	A => a.
	{ utf_A1,	utf_a5 },				//	A' => a.
	{ utf_A2,	utf_a5 },				//	A` => a.
	{ utf_A3,	utf_a5 },				//	A? => a.
	{ utf_A4,	utf_a5 },				//	A~ => a.
	{ utf_A5,	utf_a, utf_j },			//	A. => aj
	{ utf_a,	utf_a5 },				//	a => a.
	{ utf_a1,	utf_a5 },				//	a' => a.
	{ utf_a2,	utf_a5 },				//	a` => a.
	{ utf_a3,	utf_a5 },				//	a? => a.
	{ utf_a4,	utf_a5 },				//	a~ => a.
	{ utf_a5,	utf_a, utf_j },			//	a. => aj

	{ utf_A6,	utf_a65 },				//	A^ => a^.
	{ utf_A61,	utf_a65 },				//	A^' => a^.
	{ utf_A62,	utf_a65 },				//	A^` => a^.
	{ utf_A63,	utf_a65 },				//	A^? => a^.
	{ utf_A64,	utf_a65 },				//	A^~ => a^.
	{ utf_A65,	utf_a6, utf_j },		//	A^. => a^j
	{ utf_a6,	utf_a65 },				//	a^ => a^.
	{ utf_a61,	utf_a65 },				//	a^' => a^.
	{ utf_a62,	utf_a65 },				//	a^` => a^.
	{ utf_a63,	utf_a65 },				//	a^? => a^.
	{ utf_a64,	utf_a65 },				//	a^~ => a^.
	{ utf_a65,	utf_a6, utf_j },		//	a^. => a^j

	{ utf_A8,	utf_a85 },				//	A( => a(.
	{ utf_A81,	utf_a85 },				//	A(' => a(.
	{ utf_A82,	utf_a85 },				//	A(` => a(.
	{ utf_A83,	utf_a85 },				//	A(? => a(.
	{ utf_A84,	utf_a85 },				//	A(~ => a(.
	{ utf_A85,	utf_a8, utf_j },		//	A(. => a(j
	{ utf_a8,	utf_a85 },				//	a( => a(.
	{ utf_a81,	utf_a85 },				//	a(' => a(.
	{ utf_a82,	utf_a85 },				//	a(` => a(.
	{ utf_a83,	utf_a85 },				//	a(? => a(.
	{ utf_a84,	utf_a85 },				//	a(~ => a(.
	{ utf_a85,	utf_a8, utf_j },		//	a(. => a(j

	{ utf_E,	utf_e5 },				//	E => e.
	{ utf_E1,	utf_e5 },				//	E' => e.
	{ utf_E2,	utf_e5 },				//	E` => e.
	{ utf_E3,	utf_e5 },				//	E? => e.
	{ utf_E4,	utf_e5 },				//	E~ => e.
	{ utf_E5,	utf_e, utf_j },			//	E. => ej
	{ utf_e,	utf_e5 },				//	e => e.
	{ utf_e1,	utf_e5 },				//	e' => e.
	{ utf_e2,	utf_e5 },				//	e` => e.
	{ utf_e3,	utf_e5 },				//	e? => e.
	{ utf_e4,	utf_e5 },				//	e~ => e.
	{ utf_e5,	utf_e, utf_j },			//	e. => ej

	{ utf_E6,	utf_e65 },				//	E^ => e^.
	{ utf_E61,	utf_e65 },				//	E^' => e^.
	{ utf_E62,	utf_e65 },				//	E^` => e^.
	{ utf_E63,	utf_e65 },				//	E^? => e^.
	{ utf_E64,	utf_e65 },				//	E^~ => e^.
	{ utf_E65,	utf_e6, utf_j },		//	E^. => e^j
	{ utf_e6,	utf_e65 },				//	e^ => e^.
	{ utf_e61,	utf_e65 },				//	e^' => e^.
	{ utf_e62,	utf_e65 },				//	e^` => e^.
	{ utf_e63,	utf_e65 },				//	e^? => e^.
	{ utf_e64,	utf_e65 },				//	e^~ => e^.
	{ utf_e65,	utf_e6, utf_j },		//	e^. => e^j

	{ utf_O,	utf_o5 },				//	O => o.
	{ utf_O1,	utf_o5 },				//	O' => o.
	{ utf_O2,	utf_o5 },				//	O` => o.
	{ utf_O3,	utf_o5 },				//	O? => o.
	{ utf_O4,	utf_o5 },				//	O~ => o.
	{ utf_O5,	utf_o, utf_j },			//	O. => oj
	{ utf_o,	utf_o5 },				//	o => o.
	{ utf_o1,	utf_o5 },				//	o' => o.
	{ utf_o2,	utf_o5 },				//	o` => o.
	{ utf_o3,	utf_o5 },				//	o? => o.
	{ utf_o4,	utf_o5 },				//	o~ => o.
	{ utf_o5,	utf_o, utf_j },			//	o. => oj

	{ utf_O6,	utf_o65 },				//	O^ => o^.
	{ utf_O61,	utf_o65 },				//	O^' => o^.
	{ utf_O62,	utf_o65 },				//	O^` => o^.
	{ utf_O63,	utf_o65 },				//	O^? => o^.
	{ utf_O64,	utf_o65 },				//	O^~ => o^.
	{ utf_O65,	utf_o6, utf_j },		//	O^. => o^j
	{ utf_o6,	utf_o65 },				//	o^ => o^.
	{ utf_o61,	utf_o65 },				//	o^' => o^.
	{ utf_o62,	utf_o65 },				//	o^` => o^.
	{ utf_o63,	utf_o65 },				//	o^? => o^.
	{ utf_o64,	utf_o65 },				//	o^~ => o^.
	{ utf_o65,	utf_o6, utf_j },		//	o^. => o^j

	{ utf_O7,	utf_o75 },				//	O+ => o+.
	{ utf_O71,	utf_o75 },				//	O+' => o+.
	{ utf_O72,	utf_o75 },				//	O+` => o+.
	{ utf_O73,	utf_o75 },				//	O+? => o+.
	{ utf_O74,	utf_o75 },				//	O+~ => o+.
	{ utf_O75,	utf_o7, utf_j },		//	O+. => o+j
	{ utf_o7,	utf_o75 },				//	o+ => o+.
	{ utf_o71,	utf_o75 },				//	o+' => o+.
	{ utf_o72,	utf_o75 },				//	o+` => o+.
	{ utf_o73,	utf_o75 },				//	o+? => o+.
	{ utf_o74,	utf_o75 },				//	o+~ => o+.
	{ utf_o75,	utf_o7, utf_j },		//	o+. => o+j

	{ utf_U,	utf_u5 },				//	U => u.
	{ utf_U1,	utf_u5 },				//	U' => u.
	{ utf_U2,	utf_u5 },				//	U` => u.
	{ utf_U3,	utf_u5 },				//	U? => u.
	{ utf_U4,	utf_u5 },				//	U~ => u.
	{ utf_U5,	utf_u, utf_j },			//	U. => uj
	{ utf_u,	utf_u5 },				//	u => u.
	{ utf_u1,	utf_u5 },				//	u' => u.
	{ utf_u2,	utf_u5 },				//	u` => u.
	{ utf_u3,	utf_u5 },				//	u? => u.
	{ utf_u4,	utf_u5 },				//	u~ => u.
	{ utf_u5,	utf_u, utf_j },			//	u. => uj

	{ utf_U7,	utf_u75 },				//	U+ => u+.
	{ utf_U71,	utf_u75 },				//	U+' => u+.
	{ utf_U72,	utf_u75 },				//	U+` => u+.
	{ utf_U73,	utf_u75 },				//	U+? => u+.
	{ utf_U74,	utf_u75 },				//	U+~ => u+.
	{ utf_U75,	utf_u7, utf_j },		//	U+. => u+j
	{ utf_u7,	utf_u75 },				//	u+ => u+.
	{ utf_u71,	utf_u75 },				//	u+' => u+.
	{ utf_u72,	utf_u75 },				//	u+` => u+.
	{ utf_u73,	utf_u75 },				//	u+? => u+.
	{ utf_u74,	utf_u75 },				//	u+~ => u+.
	{ utf_u75,	utf_u7, utf_j },		//	u+. => u+j

	{ utf_I,	utf_i5 },				//	I => i.
	{ utf_I1,	utf_i5 },				//	I' => i.
	{ utf_I2,	utf_i5 },				//	I` => i.
	{ utf_I3,	utf_i5 },				//	I? => i.
	{ utf_I4,	utf_i5 },				//	I~ => i.
	{ utf_I5,	utf_i, utf_j },			//	I. => ij
	{ utf_i,	utf_i5 },				//	i => i.
	{ utf_i1,	utf_i5 },				//	i' => i.
	{ utf_i2,	utf_i5 },				//	i` => i.
	{ utf_i3,	utf_i5 },				//	i? => i.
	{ utf_i4,	utf_i5 },				//	i~ => i.
	{ utf_i5,	utf_i, utf_j },			//	i. => ij

	{ utf_Y,	utf_y5 },				//	Y => Y.
	{ utf_Y1,	utf_y5 },				//	Y' => y.
	{ utf_Y2,	utf_y5 },				//	Y` => y.
	{ utf_Y3,	utf_y5 },				//	Y? => y.
	{ utf_Y4,	utf_y5 },				//	Y~ => y.
	{ utf_Y5,	utf_y, utf_j },			//	Y. => yj
	{ utf_y,	utf_y5 },				//	y => Y.
	{ utf_y1,	utf_y5 },				//	y' => y.
	{ utf_y2,	utf_y5 },				//	y` => y.
	{ utf_y3,	utf_y5 },				//	y? => y.
	{ utf_y4,	utf_y5 },				//	y~ => y.
	{ utf_y5,	utf_y, utf_j },			//	y. => yj
	{ 0 }
};
/*----------------------------------------------------------------------------*/
#endif
