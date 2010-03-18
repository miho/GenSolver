/***************************************************************************
 *   Copyright (C) 2006 by Michael Hoffer                                  *
 *   info@michaelhoffer.de                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/** @file 	librand.cpp
 * @brief 	Random-Functions
 * @author 	Michael Hoffer (www.mihosoft.de)
 * @date 	13.03.06
 */

#include "librand.h"
#include <iostream>
using namespace std;

/**
 * Returns a random number.
 *
 * Returns a random number between 0 and 1
 * @return double value ( 0 < value < 1 )
 */
double randFloat()
{
	return ( rand() ) / ( RAND_MAX + 1.0 );
}

/**
 * Returns a random number.
 *
 * Returns a random number between x and y
 * @param x minimum random value
 * @param y maximum random value
 * @return double value ( x <= value <= y )
 */
double randFloat( int x, int y )
{
	long tmp = rand();
	y -= 1;
	return tmp % ( y - x + 1 ) + x + tmp / ( RAND_MAX + 1.0 );
}

/**
 * Returns a random number.
 *
 * Returns a random number between x and y
 * @param x minimum random value
 * @param y maximum random value
 * @return integer value ( x <= value <= y )
 */
int randInt( int x, int y )
{
	return rand() % ( y - x + 1 ) + x;
}
