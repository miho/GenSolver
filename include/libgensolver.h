/***************************************************************************
*   Copyright (C) 2006 by Michael Hoffer                                  *
*   info@michaelhoffer.de                                                 *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

/*
$Author: miho $
$Header: /home/miho/cvsroot/gensolver/src/libgensolver.h,v 1.2 2006/03/13 17:42:38 miho Exp $
*/

#ifndef LIBGENSOLVER_H
#define LIBGENSOLVER_H

#include <fstream>
#include <string>
#include <vector>

#include "librand.h"
#include "libgensolver.ipp"
using namespace std;

/** @file 	libgensolver.h
 * @brief 	template classes for genetic algorithms
 * @author 	Michael Hoffer (www.mihosoft.de)
 * @date 	14.03.06
 */

/*-----------------------------------------------------------------------------
	Namespace:	GenFloat
	Description:	This is a set of genetic Classes to handle double
			values ( chromosomes consist of double values).
 
			For further explanations have a look at the
			file "libgensolvertpl.h". All methods are
			explained there in detail.
-----------------------------------------------------------------------------*/ 
/**
 * The classes in this namespace handle double values.
 *
 * This is a set of genetic Classes to handle double
 * values ( chromosomes consist of double values).
 */
namespace GenFloat
{
	class ChromosomeClass : public GenBase::ChromosomeClass<double>
	{

		public:
			double randFunction( double minRand, double maxRand );

	};

	class GenerationClass : public GenBase::GenerationClass<double,ChromosomeClass>
	{
		public: GenerationClass( int numberOfChromosomes ) :
			GenBase::GenerationClass<double,ChromosomeClass>( numberOfChromosomes ) {};
	};

	class PopulationClass : public GenBase::PopulationClass<double,GenerationClass, ChromosomeClass>
		{}
	;

	class GenSolver : public GenBase::GenSolver<PopulationClass>
		{}
	;
}

/**
 * The classes in this namespace handle integer values.
 *
 * This is a set of genetic Classes to handle integer
 * values ( chromosomes consist of integer values).
 */
namespace GenInt
{
	class ChromosomeClass : public GenBase::ChromosomeClass<int>
	{
		public:
			int randFunction( int minRand, int maxRand );
	};

	class GenerationClass : public GenBase::GenerationClass<int,ChromosomeClass>
	{
		public: GenerationClass( int numberOfChromosomes ) :
			GenBase::GenerationClass<int,ChromosomeClass>( numberOfChromosomes ) {};
	};

	class PopulationClass : public GenBase::PopulationClass<double,GenerationClass, ChromosomeClass>
		{}
	;

	class GenSolver : public GenBase::GenSolver<PopulationClass>
		{}
	;
}

#endif /*LIBGENSOLVER_H*/
