/*----------------------------------------------------------------------------*/
/*  visckey.c                                                                 */
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
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
/*----------------------------------------------------------------------------*/
#include "debug.h"
/*----------------------------------------------------------------------------*/
#include "visckey.h"
#include "utf.h"
#include "viqr.h"
#include "tcvn.h"
#include "vni.h"
#include "viscii.h"
#include "vps.h"
#include "utf8.h"
/*----------------------------------------------------------------------------*/
#define	chr_A	'A'
#define	chr_a	'a'
#define	chr_U	'U'
#define	chr_u	'u'
#define	chr_G	'G'
#define	chr_g	'g'
#define	chr_Q	'Q'
#define	chr_q	'q'
/*----------------------------------------------------------------------------*/
#ifndef WORDSIZE
#define WORDSIZE	32
#endif
/*----------------------------------------------------------------------------*/
int count;
ushort word[WORDSIZE], *pw;
ushort backup[WORDSIZE];
/*----------------------------------------------------------------------------*/
int vk_using = 0;
int vk_method = VKM_TELEX;
int vk_charset = VKC_UTF8;
int vk_spelling = 1;
/*----------------------------------------------------------------------------*/
int vk_blength, vk_plength;
char vk_buffer[256];
char **vk_charmap = UTF8;
/*----------------------------------------------------------------------------*/
#ifdef VK_CHECK_SPELLING
int vp = -1;
int vpc = 0;
int vps[WORDSIZE];
char lvs[WORDSIZE];
#endif
int tempoff = 0;
/*----------------------------------------------------------------------------*/
char *vowels = "AIUEOYaiueoy";
char *consonants = "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz";
/*----------------------------------------------------------------------------*/
static inline int ui_group(register ushort u)
{
	static ushort UI[] = {
		utf_U,  utf_U1,  utf_U2,  utf_U3,  utf_U4,  utf_U5,
		utf_u,  utf_u1,  utf_u2,  utf_u3,  utf_u4,  utf_u5,
		utf_U7, utf_U71, utf_U72, utf_U73, utf_U74, utf_U75,
		utf_u7, utf_u71, utf_u72, utf_u73, utf_u74, utf_u75,
		utf_I,  utf_I1,  utf_I2,  utf_I3,  utf_I4,  utf_I5,
		utf_i,  utf_i1,  utf_i2,  utf_i3,  utf_i4,  utf_i5, 0
	};
	register ushort *ui = UI;
	while( *ui ) if( u==*ui++ ) return ui-UI;
	return 0;
}
/*----------------------------------------------------------------------------*/
/* Lookup char 'c' in table 't'                                               */
/*----------------------------------------------------------------------------*/
#define	VKLookupChar(t, c) for( ; *t && *t!=c; t++ )
/*----------------------------------------------------------------------------*/
static inline int utf_vn_cmp(register ushort u1, register ushort u2)
{
	static ushort V[] = {
		utf_a, utf_A, utf_a1, utf_A1, utf_a2, utf_A2,
		utf_a3, utf_A3, utf_a4, utf_A4, utf_a5, utf_A5,
		utf_a6, utf_A6, utf_a61, utf_A61, utf_a62, utf_A62,
		utf_a63, utf_A63, utf_a64, utf_A64, utf_a65, utf_A65,
		utf_a8, utf_A8, utf_a81, utf_A81, utf_a82, utf_A82,
		utf_a83, utf_A83, utf_a84, utf_A84, utf_a85, utf_A85,
		utf_e, utf_E, utf_e1, utf_E1, utf_e2, utf_E2,
		utf_e3, utf_E3, utf_e4, utf_E4, utf_e5, utf_E5,
		utf_e6, utf_E6, utf_e61, utf_E61, utf_e62, utf_E62,
		utf_e63, utf_E63, utf_e64, utf_E64, utf_e65, utf_E65,
		utf_o, utf_O, utf_o1, utf_O1, utf_o2, utf_O2,
		utf_o3, utf_O3, utf_o4, utf_O4, utf_o5, utf_O5,
		utf_o6, utf_O6, utf_o61, utf_O61, utf_o62, utf_O62,
		utf_o63, utf_O63, utf_o64, utf_O64, utf_o65, utf_O65,
		utf_o7, utf_O7, utf_o71, utf_O71, utf_o72, utf_O72,
		utf_o73, utf_O73, utf_o74, utf_O74, utf_o75, utf_O75,
		utf_y, utf_Y, utf_y1, utf_Y1, utf_y2, utf_Y2,
		utf_y3, utf_Y3, utf_y4, utf_Y4, utf_y5, utf_Y5,
		utf_u, utf_U, utf_u1, utf_U1, utf_u2, utf_U2,
		utf_u3, utf_U3, utf_u4, utf_U4, utf_u5, utf_U5,
		utf_u7, utf_U7, utf_u71, utf_U71, utf_u72, utf_U72,
		utf_u73, utf_U73, utf_u74, utf_U74, utf_u75, utf_U75,
		utf_i, utf_I, utf_i1, utf_I1, utf_i2, utf_I2,
		utf_i3, utf_I3, utf_i4, utf_I4, utf_i5, utf_I5,
		utf_d9, utf_D9, 0
	};
	register int i = -1, j = -1;
	register ushort *v = V;

	VKLookupChar(v, u1);
	if( *v ) i = v - V;
	v = V;
	VKLookupChar(v, u2);
	if( *v ) j = v - V;

	return i-j;
}
/*----------------------------------------------------------------------------*/
/* TODO: Pre-calculate length in bytes of every character will speedup        */
/*----------------------------------------------------------------------------*/
static inline int VKStrLen(register ushort *w, register int count)
{
	int n = 0;

	if( vk_charset==VKC_UTF8 )
		return count;

	for( ; count>0; count--, w++ )
		if( *w<127 )
			n++;
		else {
			register ushort *u = UTF16;

			VKLookupChar(u, *w);
			if( !*u )
				n++;
			else {
				register char *s = vk_charmap[u-UTF16];
				while( *s ) {
					n++;
					s++;
				}
			}
		}
	return n;
}
/*----------------------------------------------------------------------------*/
static inline char *VKStrCat(register char *s, ushort w)
{
	register ushort *u = UTF16;

	VKLookupChar(u, w);
	if( !*u )
		*s++ = w;
	else {
		register char *ss = vk_charmap[u-UTF16];
		while( *ss ) *s++ = *ss++;
	}
	
	return s;
}
/*----------------------------------------------------------------------------*/
static inline void VKMapToCharset(register ushort *w, int count)
{
	register char *s;
	if( !vk_charmap ) return;
	for( s = vk_buffer, pw = w; count>0; count--, w++ )
		if( *w<127 )
			*s++ = (char)*w;
		else
			s = VKStrCat(s, *w);
	*s = 0;
	vk_blength = s - vk_buffer;
}
/*----------------------------------------------------------------------------*/
static inline void VKShiftBuffer()
{
	tempoff = 0;
	word[0] = word[count-1];
	count = 1;
#ifdef VK_CHECK_SPELLING
	if( !vk_spelling ) return;

	// FIXME: word[0] maybe a vowel with accent
	if( !strchr(vowels, word[0]) ) {
		vp = -1;
		vpc = 0;
	}
	else {
		vpc = 1;
		vps[vp = 0] = -1;
		lvs[0] = word[0];
	}
#endif
}
/*----------------------------------------------------------------------------*/
#ifdef VK_CHECK_SPELLING
static inline void VKAppend(ushort lastkey, char key)
{
	static char *spchk = "AIUEOYaiueoy|BDFJKLQSVWXZbdfjklqsvwxz|'`~?.^*+=";
	static char *vwchk = "|ia|ua|oa|ai|ui|oi|au|iu|eu|ie|ue|oe|ye|ao|uo|eo|ay|uy|uu|ou|io|";

	if( vk_spelling && !tempoff ) {
		char *sp = strchr(spchk, key);
		int kp = sp ? (sp - spchk) : -1;

		if( !count ) {
			if( kp>=0 && kp<12 ) {
				vpc = 1;
				vps[vp = 0] = -1;
				lvs[0] = key;
			}
			else
			if( kp==12 || kp>37 )
				return;
			else {
				vp = -1;
				vpc = 0;
			}
		}
		else
		if( kp==12 || kp>37 ) {
			VKClearBuffer();
			return;
		}
		else
		if( kp>12 ) // b, d, f,...
			tempoff = count;
		else
		if( kp>=0 ) { // vowels
			if( vp<0 ) {
				vps[vpc++] = vp;
				vp = count;
				lvs[0] = key;
			}
			else
			if( count-vp>1 )
				tempoff = count;
			else {
				#define lower(c) ((c) <= 'Z' ? (c) + 'a' - 'A' : c)
				static char w[5] = { '|', 0, 0, '|', 0 };
				w[1] = lower(lvs[vpc-1]);
				w[2] = lower(key);
				if( !strstr(vwchk, w) )
					tempoff = count;
				else {
					lvs[vpc] = key;
					vps[vpc++] = vp;
					vp = count;
				}
				#undef lower
			}
		}
		else
		switch( key ) {
			case 'h':
			case 'H': // [cgknpt]h
				if( lastkey>127 || !strchr("CGKNPTcgknpt", lastkey) )
					tempoff = count;
				break;
			case 'g':
			case 'G': // [n]g
				if( lastkey!='n' && lastkey!='N' )
					tempoff = count;
				break;
			case 'r':
			case 'R': // [t]r
				if( lastkey!='t' && lastkey!='T' )
					tempoff = count;
				break;
			default:
				if( strchr(consonants, lastkey) )
					tempoff = count;
				break;
		}
	}
	word[count++] = (ushort)key;
}
#else
#define VKAppend(lastkey, key)	word[count++] = ((ushort)key)
#endif
/*----------------------------------------------------------------------------*/
#define VKAppendKey( word, count, key )	\
{										\
	VKAppend(c, key);					\
	return -1;							\
}
/*----------------------------------------------------------------------------*/
inline long VKAddKey( char key )
{
	int p = -1;
	int i, j = -1;
	ushort c = 0, cc;
	modifier_t *m = modes[ vk_method-1 ];
	vietcode_t *v = NULL;
	#ifdef VK_USE_EXTSTROKE
	static int wcase = 0;
	#endif

	if( count >= 30 )
		VKShiftBuffer();

	if( !count || tempoff ) {
	#ifdef VK_USE_EXTSTROKE
		if( !count ) {
			i = 0;
			while( m[i].level == 0 ) {
				if( m[i].modifier == key ) break;
				i++;
			}
			if( m[i].level == 0 ) {
			#ifdef VK_CHECK_SPELLING
				vpc = 1;
				vps[vp = 0] = -1;
				lvs[0] = key;
			#endif
				backup[ 0 ] = (ushort)key;
				word[ count++ ] = (ushort)(int)m[i].code;
				wcase = (key == 'w' || key == 'W');
				VKMapToCharset(word, 1);
				return -3;
			}
		}
		wcase = 0;
	#endif
		VKAppendKey( word, count, key );
	}

	c = word[ p = count-1 ];
	for( i = 0; m[i].modifier; i++ )
		if( key == m[i].modifier ) v = m[j = i].code;
	if( !v ) VKAppendKey( word, count, key );

	switch( m[j].level ) {
	#ifdef VK_USE_EXTSTROKE
		case 0:
	__extra_case:
			vk_plength = VKStrLen(&word[p], 1);
			if( c == (ushort)(int)v ) {
				word[ tempoff = p ] = key;
				wcase = 0;
				i = -2;
			}
			else {
				backup[ count ] = (ushort)key;
				word[ count++ ] = (ushort)(int)v;
				wcase = (key == 'w' || key == 'W');
				i = -3;
				p++;
			}
			VKMapToCharset(&word[p], 1);
			return i;
	#endif
		case 1:
	#ifdef VK_USE_EXTSTROKE
			if( (key == 'w' || key == 'W') &&
				(wcase || c == utf_d9 || c == utf_D9 || strchr(consonants, c)) ) {
				for( i = 0; !m[i].level && m[i].modifier != key; i++ );
				v = m[i].code;
				goto __extra_case;
			}
			wcase = 0;
	#endif
			break;
		case 2:
		default:
			i = p;
			while( i >= 0 && word[i] < 0x80 && !strchr(vowels, word[i]) ) i--;
			if( i < 0 ) VKAppendKey(word, count, key);

			while( i-1 >= 0 &&
				(strchr(vowels, word[i-1]) || word[i-1] > 0x80) &&
				utf_vn_cmp( word[i-1], word[i] ) < 0 ) i--;
			if( i == count-1 && i-1 >= 0 &&	(j = ui_group(word[i-1])) > 0 )
			switch( word[i] ) {
				case chr_a:
				case chr_A:
					if( i-2 < 0 ||
						(j < 24 && word[i-2] != chr_q && word[i-2] != chr_Q) ||
						(j > 24 && word[i-2] != chr_g && word[i-2] != chr_G) )
						i = i - 1;
					break;
				case chr_u:
				case chr_U:
					if( i-2 < 0 || (word[i-2] != chr_g && word[i-2] != chr_G) )
						i = i - 1;
					break;
			}
			c = word[p = i];
			break;
	}

	for( i = 0; (cc = v[i].c) != 0 && c != cc; i++ );
	if( !cc ) VKAppendKey( word, count, key );
	vk_plength = VKStrLen(&word[p], count-p);
	if( !v[i].r2 ) {
		word[ p ] = v[i].r1;
		backup[ p ] = c;
	}
	else {
		word[ tempoff = count++ ] = (ushort)key;
		word[ p ] = backup[ p ];
	}

	VKMapToCharset(&word[p], count-p);
	return p;
}
/*----------------------------------------------------------------------------*/
/* Buffer control                                                             */
/*----------------------------------------------------------------------------*/
inline void VKClearBuffer()
{
	tempoff = count = *word = 0;
#ifdef VK_CHECK_SPELLING
	vpc = 0;
	vp = -1;
#endif
}
/*----------------------------------------------------------------------------*/
inline long VKBackspaceDelete()
{
	if( count>0 ) {
		register ushort *u = UTF16;
		register ushort c = word[ --count ];

	#ifdef VK_CHECK_SPELLING
		if( vp==count ) vp = vps[--vpc];
	#endif
		if( tempoff==count ) tempoff = 0;
		if( vk_charset==VKC_UTF8 || !vk_charmap ) return -1;

		VKLookupChar(u, c);
		if( *u ) {
			char *s = vk_charmap[u-UTF16];
			char i = -1;
			while( *s++ ) i++;
			return i;
		}
	}
	return 0;
}
/*----------------------------------------------------------------------------*/
/* Input methods & charset                                                    */
/*----------------------------------------------------------------------------*/
inline void VKSwitchMethod()
{
	vk_method = vk_method==VKM_OFF ? vk_using : VKM_OFF;
	VKClearBuffer();
}
/*----------------------------------------------------------------------------*/
inline void VKChangeCharset(int id)
{
	static char **cmap[] = { TCVN, VNI, VIQR, VISCII, VPS, UTF8 };
	vk_charmap = cmap[vk_charset = (id % 6)];
	VKClearBuffer();
}
/*----------------------------------------------------------------------------*/
/* Check spelling                                                             */
/*----------------------------------------------------------------------------*/
inline void VKSetSpelling(int s)
{
	VKClearBuffer();
	vk_spelling = s;
}
/*----------------------------------------------------------------------------*/
