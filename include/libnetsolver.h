/**************************************************************************
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

#ifndef LIBNETSOLVER_H
#define LIBNETSOLVER_H

#include <iostream>
#include <libgensolver.h>
#include <libnnet.h>

using namespace std;


class NetSolver : public GenFloat::GenSolver
{
	public:
		NetSolver();
		NetSolver( string fileName);
		
		NNet net;
		virtual void fitnessFunction() = 0;
		virtual void initialize( unsigned int generationSize, int minRand, int maxRand );

		GenFloat::ChromosomeClass * actualEntity;
	private:
		void parseChromosomes();
		unsigned int actualEntityID;
};

#endif /*LIBNETSOLVER_H*/

