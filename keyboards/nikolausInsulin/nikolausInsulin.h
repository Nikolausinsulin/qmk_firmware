/* Copyright 2020 foostan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

 #define LAYOUT( \
 	L000, L001, L002, L003, L004, L005, 							R000, R001, R002, R003, R004, R005, \
 	L100, L101, L102, L103, L104, L105, 							R100, R101, R102, R103, R104, R105, \
 	L200, L201, L202, L203, L204, L205, 							R200, R201, R202, R203, R204, R205, \
								L300, L301, L302, 			R300, R301, R302\
 ) \
 { \
 	{ L000,  L001,  L002,  L003,  L004,  L005,  L302}, \
 	{ L100,  L101,  L102,  L103,  L104,  L105,  L301}, \
 	{ L200,  L201,  L202,  L203,  L204,  L205,  L300}, \
	{ R302,  R000,  R001,  R002,  R003,  R004,  R005}, \
 	{ R301,  R100,  R101,  R102,  R103,  R104,  R105}, \
 	{ R300,  R200,  R201,  R202,  R203,  R204,  R205} \
 }

/*
#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311 \
) \
{ \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311 } \
}
*/
