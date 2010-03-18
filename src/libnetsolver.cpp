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


#include <iostream>
#include "libnetsolver.h"
#include <genutil.h>

//using namespace std;

NetSolver::NetSolver()
{
	actualEntity = NULL;
	actualEntityID = 0;
}

NetSolver::NetSolver( string fileName)
{
	actualEntity = NULL;
	actualEntityID = 0;
	
	if ( !net.loadNet(fileName) )
	{
		// File not found!
		exit(1);
	}
}

void NetSolver::parseChromosomes()
{
	// PREPROCESSING
	// not implemented yet
	
	for (unsigned int k = 0; k < newGeneration->size(); k++)
	{
		
		// set wights
		vector <double> weights;
		for ( unsigned int j = 0; j < newGeneration->sizeOfChromosome( k ); j++ )
		{
			weights.push_back( ( *( *newGeneration ) ( k ) ) ( j ) );
		}
		
		net.setWeights( weights );
		net.reset();
		
		actualEntity = ( *newGeneration ) ( k );
		actualEntityID = k;
		
		// call virtual fitness funciton
		fitnessFunction();
		
		if (_solution)
		{
			break;
		}
	}
	
	// POSTPROCESSING
	// not implemented yet
}

void NetSolver::initialize( unsigned int generationSize, int minRand, int maxRand )
{
	PopulationClass::initialize(generationSize, net.numberOfConnections(), net.numberOfConnections(),1, 1, minRand, maxRand );
}
