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

/*
$Author: miho $
$Header: /home/miho/cvsroot/gensolver/src/libgensolver.cpp,v 1.2 2006/03/13 17:42:34 miho Exp $
*/

#include <libgensolver.h>
#include <librand.h>

namespace GenFloat
{

	double ChromosomeClass::randFunction( double minRand, double maxRand )
	{
		return randFloat( int(minRand), int(maxRand) );
	}
}

namespace GenInt
{
	int ChromosomeClass::randFunction( int minRand, int maxRand )
	{
		return randInt( minRand, maxRand );
	}
}
