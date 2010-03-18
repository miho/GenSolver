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

#include "libnnet.h"
#include <cmath>
#include <genutil.h>

Cell::Cell()
{
	signalSum = 0;
	alreadyConnected = false;
	netIndex = 0;
	// 	weight = 0;
}

void Cell::connect( Cell* c )
{
	connections.push_back( c );
	weights.push_back( 0 );
}

void Cell::connect( Cell* c, double weight )
{
	connections.push_back( c );
	weights.push_back( weight );
}

double Cell::sigmoid( double activation )
{
	// 	std::cout << "activation: "<< activation << std::endl;
	// 	   return activation;
	return 1 / ( 1 + exp( -activation ) );
}

void Cell::firstInput( double value )
{
	signalSum = value;
}

void Cell::input( double value )
{
	signalSum += value;
}

double Cell::output( int i )
{
	double value = sigmoid( signalSum ) * weights[ i ];
	// 	signalSum = 0;
	return value;
}

double Cell::output( )
{
	double value = sigmoid( signalSum );
	//   	signalSum = 0;
	return value;
}

double Cell::finalOutput()
{
	double value = signalSum;
// 	signalSum = 0;
	return value;
}

void Cell::sendSignals()
{
	for ( unsigned int i = 0; i < connections.size(); i++ )
	{
		connections[ i ] ->input( this->output( i ) );
	}
	// 	signalSum = 0;
}



NNet::NNet()
{
	setMemory( false );
}

NNet::NNet( std::string fileName )
{
	setMemory( false );

	this->loadNet( fileName );
}

NNet::NNet( const NNet &net )
{
	std::cout << __PRETTY_FUNCTION__ << " here i am" << std::endl;
}

NNet & NNet::operator=( const NNet & net )
{
	std::cout << __PRETTY_FUNCTION__ << " here i am" << std::endl;

	//for ( int i = 0; i < net.allCells.size();i++)
	//{
	//        Cell *cell = new Cell();
	//        *cell = *net.allCells[i];

	//        allCells.push_back(cell);
	//}

	std::cout << ">> not available yet" << std::endl;
}

NNet::NNet( int numberOfInputs, int numberOfOutputs, std::vector<int> layerSize )
{
	setMemory( false );

	createNet( numberOfInputs, numberOfOutputs, layerSize );
}

bool NNet::createNet( int numberOfInputs, int numberOfOutputs, std::vector<int> layerSize )
{
	int numberOfCells = 0;

	std::vector<int> _layerSize;

	std::vector<int> inputs;
	std::vector<int> outputs;

	_layerSize.push_back( numberOfInputs );

	// adding hidden layers
	for ( int i = 0; i < layerSize.size();i++ )
	{
		_layerSize.push_back( layerSize[i] );
	}

	_layerSize.push_back( numberOfOutputs );

	std::vector<netConnection> connections;

	// find out numberOfCells
	for ( int i = 0; i < _layerSize.size(); i++ )
	{
		numberOfCells += _layerSize[i];
	}

	// create input indices
	for ( int  i = 0; i < numberOfInputs; i++ )
	{
		inputs.push_back( i );
	}

	// create output indices
	for ( int  i = 0; i < numberOfOutputs; i++ )
	{
		outputs.push_back( numberOfCells - numberOfOutputs + i );
	}

	// create connections
	int offset = 0;
	for ( int i = 0; i < _layerSize.size() - 1;i++ )
	{
		int count = 0;
		for ( int j = offset; j < offset + _layerSize[i];j++ )
		{
			int nextOffset = offset + _layerSize[i];
			for ( int k = nextOffset; k < nextOffset + _layerSize[i+1];k++ )
			{
				//std::cout << "S: " << j << " R: " << k << std::endl;
				connections.push_back( netConnection( j, k, 0 ) );
			}
			count++;
		}
		offset += count;
	}


	generateNet( inputs, outputs, connections );
}

void NNet::sendSignals()
{


	// Reset all cells if memory disabled
	if ( !enableMemory )
	{

// 		//Save activation values of all input cells
// 		std::vector <double> tmpActivations;
//
// 		for ( unsigned int i = 0; i < this->inputCells.size();i++ )
// 		{
// 			tmpActivations.push_back( this->inputCells[ i ] ->finalOutput() );
// 		}
//
// 		// Reset activations of all cells
// 		for ( unsigned int i = 0; i < this->allCells.size();i++ )
// 		{
// 			this->allCells[ i ] ->firstInput( 0 );
// 		}
//
// 		//restore Activation of output cells as they are
// 		//resetted if memory disabled
// 		for ( unsigned int i = 0; i < this->inputCells.size();i++ )
// 		{
// 			this->inputCells[ i ] ->firstInput( tmpActivations[ i ] ) ;
// 		}

		reset();
	}


	std::vector <Cell*> tmpCells1;


	tmpCells1 = inputCells;

// 		for ( unsigned int i = 0; i < inputCells.size();i++ )
// 		{
// 			std::cout << "Input (" << i << "):\t" << inputCells[ i ] ->signalSum << std::endl;
// 		}
// 		std::cout << "---------------------------" << std::endl;
// 		for ( unsigned int i = 0; i < outputCells.size();i++ )
// 		{
// 			std::cout << "Output (" << i << "):\t" << outputCells[ i ] ->signalSum << std::endl;
// 		}
// 		std::cout << "---------------------------" << std::endl;


	tmpCells1 = inputCells;

	while ( tmpCells1.size() > 0 )
	{
		std::vector <Cell*> tmpCells2;

		for ( unsigned int i = 0; i < tmpCells1.size(); i++ )
		{
			for ( unsigned int j = 0; j < tmpCells1[ i ] ->connections.size();j++ )
			{
				Cell * connectedCell = tmpCells1[ i ] ->connections[ j ];

				// 				bool alreadyConnected = false;
				// 				for (int k = 0;k < tmpCells2.size();k++)
				// 				{
				// 					if (tmpCells2[k]->netIndex == connectedCell->netIndex ) alreadyConnected = true;
				// 				}
				if ( !connectedCell->alreadyConnected )
				{
					tmpCells2.push_back( connectedCell );
					connectedCell->alreadyConnected = true;
				}
			}
			tmpCells1[ i ] ->sendSignals();
		}
		for ( unsigned int k = 0;k < tmpCells2.size();k++ )
		{
			tmpCells2[ k ] ->alreadyConnected = false;
		}
		tmpCells1 = tmpCells2;

	}

// 				for ( unsigned int i = 0; i < inputCells.size();i++ )
// 				{
// 					std::cout << "Input (" << i << "):\t" << inputCells[ i ] ->signalSum << std::endl;
// 				}
// 				std::cout << "---------------------------" << std::endl;
// 				for ( unsigned int i = 0; i < outputCells.size();i++ )
// 				{
// 					std::cout << "Output (" << i << "):\t" << outputCells[ i ] ->signalSum << std::endl;
// 				}
// 				std::cout << "---------------------------" << std::endl;




// 	//Save activation values of all output cells
// 	std::vector <double> tmpActivations;
//
// 	for ( unsigned int i = 0; i < this->outputCells.size();i++ )
// 	{
// 		tmpActivations.push_back( this->outputCells[ i ] ->finalOutput() );
// 	}


// 	// Reset all cells if memory disabled
// 	if ( !enableMemory )
// 	{
//
// 	for ( unsigned int i = 0; i < this->allCells.size();i++ )
// 	{
// 		this->allCells[ i ] ->firstInput( 0 );
// 	}
//
// 	}


	// restore Activation of output cells as they are
	// resetted if memory disabled
// 	for ( unsigned int i = 0; i < this->outputCells.size();i++ )
// 	{
// 		this->outputCells[ i ] ->firstInput( tmpActivations[ i ] ) ;
// 	}
}

bool NNet::readHeaderSection( std::ifstream  &f, std::vector <std::string> &headerList )
{
	/*-----------------------------------------
		  Read Header Information
	------------------------------------------*/

	while ( !f.eof() )
	{
		std::string tmpStr;
		f >> tmpStr;
		headerList.push_back( tmpStr );
		if ( tmpStr == "</header>" ) break;
	}

	/*-----------------------------------------
	   Error Handling for Header Information
	------------------------------------------*/

	if ( headerList[ 0 ] != "<header>" )
	{
		std::cerr << "Error: Unknown file format!" << std::endl;
		return false;
	}

	if ( headerList[ headerList.size() - 1 ] != "</header>" )
	{
		std::cerr << "Error: Missing </header>!" << std::endl;
		return false;
	}

	if ( headerList[ 1 ] != "#NNet-File" )
	{
		std::cerr << "Error: Unknown file format!" << std::endl;
		return false;
	}

	if ( atof( headerList[ 2 ].c_str() ) == 0 )
	{
		std::cerr << "Error: Can't verify version of file format!" << std::endl;
		return false;
	}
	else
	{
		if ( atof( headerList[ 2 ].c_str() ) > 0.1 )
		{
			std::cerr << "Error: File is made by newer version of this program!" << std::endl;
			return false;
		}
	}
	return true;
}

bool NNet::readInputSection( std::ifstream &f )
{
	std::vector <std::string> inputStrList;
	/*-----------------------------------------
		   Read Input-Cell Indices
	------------------------------------------*/

	while ( !f.eof() )
	{
		std::string tmpStr;
		f >> tmpStr;
		inputStrList.push_back( tmpStr );
		if ( tmpStr == "</inputs>" ) break;
	}


	if ( inputStrList[ 0 ] != "<inputs>" )
	{
		std::cerr << "Error: Input section missing!" << std::endl;
		return false;
	}
	if ( inputStrList[ inputStrList.size() - 1 ] != "</inputs>" )
	{
		std::cerr << "Error: Missing </inputs>!" << std::endl;
		return false;
	}

	for ( unsigned int i = 1;i < inputStrList.size() - 1;i++ )
	{
		int tmpVal = atoi( inputStrList[ i ].c_str() );
		if (( inputStrList[ i ] != "0" ) && ( tmpVal == 0 ) )
		{
			std::cerr << "Error: Entry " << i << " in \"<inputs> </inputs>\" - Section is not a valid integer number!" << std::endl;
			return false;
		}
		inputList.push_back( tmpVal );
	}

	return true;
}

bool NNet::readOutputSection( std::ifstream &f )
{
	std::vector <std::string> outputStrList;

	/*-----------------------------------------
		   Read Output-Cell Indices
	------------------------------------------*/

	while ( !f.eof() )
	{
		std::string tmpStr;
		f >> tmpStr;
		outputStrList.push_back( tmpStr );
		if ( tmpStr == "</outputs>" ) break;
	}


	if ( outputStrList[ 0 ] != "<outputs>" )
	{
		std::cerr << "Error: Output section missing!" << std::endl;
		return false;
	}
	if ( outputStrList[ outputStrList.size() - 1 ] != "</outputs>" )
	{
		std::cerr << "Error: Missing </outputs>!" << std::endl;
		return false;
	}

	for ( unsigned int i = 1;i < outputStrList.size() - 1;i++ )
	{
		int tmpVal = atoi( outputStrList[ i ].c_str() );
		if (( outputStrList[ i ] != "0" ) && ( tmpVal == 0 ) )
		{
			std::cerr << "Error: Entry " << i << " in \"<outputs> </outputs>\" - Section is not a valid integer number!" << std::endl;
			return false;
		}
		outputList.push_back( tmpVal );
	}

	return true;
}

bool NNet::readConnectionSection( std::ifstream &f )
{
	std::vector <std::string> connectionStrList;
	/*-----------------------------------------
		Read Connection Information
	------------------------------------------*/

	while ( !f.eof() )
	{
		std::string tmpStr;
		f >> tmpStr;
		if ( tmpStr[ 0 ] == '#' )
		{
			getline( f, tmpStr );
		}
		else
		{
			connectionStrList.push_back( tmpStr );
		}
		if ( tmpStr == "</connections>" ) break;
	}

	if ( connectionStrList[ 0 ] != "<connections>" )
	{
		std::cerr << "Error: Connections section missing!" << std::endl;
		return false;
	}
	if ( connectionStrList[ connectionStrList.size() - 1 ] != "</connections>" )
	{
		std::cerr << "Error: Missing </connections>!" << std::endl;
		return false;
	}

	/*--------------------------------------------
		Convert connectionList to
		netList

		Start with i = 1 because first
		entry is <connections> tag.

		Stop with < connectionList.size() - 2
		because size is one too much and
		last entry is </conections> tag.

		This concerns also most of the
		following for-loops
	----------------------------------------------*/

	if (( connectionStrList.size() - 2 ) % 3 != 0 )
	{
		std::cerr << "Error: Wrong number of Entries in \"<connections> </connections>\" - Section!" << std::endl;
		return false;
	}

	for ( unsigned int i = 1;i < connectionStrList.size() - 2;i += 3 )
	{
		int tmpVal = atoi( connectionStrList[ i ].c_str() );
		if (( connectionStrList[ i ] != "0" ) && ( tmpVal == 0 ) )
		{
			std::cerr << "Error: Entry " << i << " in \"<connections> </connections>\" - Section is not a valid integer number!" << std::endl;
			return false;

		}
		tmpVal = atoi( connectionStrList[ i + 1 ].c_str() );
		if (( connectionStrList[ i + 1 ] != "0" ) && ( tmpVal == 0 ) )
		{
			std::cerr << "Error: Entry " << i + 1 << " in \"<connections> </connections>\" - Section is not a valid integer number!" << std::endl;
			return false;
		}
		double tmpVal2 = atof( connectionStrList[ i + 2 ].c_str() );
		if (( connectionStrList[ i + 2 ] != "0" ) && ( tmpVal2 == 0 ) )
		{
			std::cerr << "Error: Entry " << i + 2 << " in \"<connections> </connections>\" - Section is not a valid floating point number!" << std::endl;
			return false;
		}

		// 		netConnection tmpConnection;
		// 		tmpConnection(connectionStrList[ i ],connectionStrList[ i + 1 ],connectionStrList[ i + 2 ]);
		connectionList.push_back( netConnection( connectionStrList[ i ], connectionStrList[ i + 1 ], connectionStrList[ i + 2 ] ) );
	}

	return true;
}

const int NNet::getNumberOfCells() const
{
	/*--------------------------------------------
		Get number of cells
	----------------------------------------------*/

	int numberOfCells = 0;

	for ( unsigned int i = 0; i < connectionList.size();i++ )
	{
		if ( numberOfCells < connectionList[ i ].sender )
		{
			numberOfCells = connectionList[ i ].sender;
		}
		if ( numberOfCells < connectionList[ i ].receiver )
		{
			numberOfCells = connectionList[ i ].receiver;
		}
	}

	for ( unsigned int i = 0; i < inputList.size();i++ )
	{
		if ( numberOfCells < inputList[ i ] )
		{
			numberOfCells = inputList[ i ];
		}
	}

	for ( unsigned int i = 0; i < outputList.size();i++ )
	{
		if ( numberOfCells < outputList[ i ] )
		{
			numberOfCells = outputList[ i ];
		}
	}

	return numberOfCells + 1;
}

void NNet::generateCells( unsigned int numberOfCells )
{
	/*--------------------------------------------
		Store cells in NNet::allCells
	----------------------------------------------*/

	//std::vector <Cell*> cellList;

	for ( unsigned int i = 0;i < numberOfCells;i++ )
	{
		Cell *tmpCell = new Cell;
		tmpCell->netIndex = i;
		this->allCells.push_back( tmpCell );
	}
}

void NNet::storeInputCells()
{
	/*--------------------------------------------
		Store input cells
	----------------------------------------------*/

	for ( unsigned int i = 0;i < inputList.size();i++ )
	{
		this->inputCells.push_back( this->allCells[ inputList[ i ] ] );
	}
}

void NNet::storeOutputCells()
{
	/*--------------------------------------------
		Store output cells
	----------------------------------------------*/

	for ( unsigned int i = 0;i < outputList.size();i++ )
	{
		this->outputCells.push_back( this->allCells[ outputList[ i ] ] );
	}
}

void NNet::connectCells()
{
	/*--------------------------------------------
		Connect cells
	----------------------------------------------*/

	for ( unsigned int i = 0; i < connectionList.size();i++ )
	{
		this->allCells[ connectionList[ i ].sender ] ->connect( this->allCells[ connectionList[ i ].receiver ], connectionList[ i ].weight );
//  		std::cout << "Connect: " << connectionList[ i ].sender << " -> " << connectionList[ i ].receiver << std::endl;
	}
}

bool NNet::generateNet( std::vector<int>inputs, std::vector<int>outputs, std::vector<netConnection>connections )
{
	this->inputList = inputs;
	this->outputList = outputs;
	this->connectionList = connections;

	int numberOfCells = this->getNumberOfCells();

	this->generateCells( numberOfCells );

	this->storeInputCells();

	this->storeOutputCells();

	this->connectCells();

	return true;
}



bool NNet::loadNet( std::string fileName )
{
	// List with header informations
	std::vector <std::string> headerList;

	// The file stream
	std:: ifstream f( fileName.c_str() );

	if ( !f )
	{
		std::cerr << "Error: File doesn't exist!" << std::endl;
		return false;
	};

	if ( !this->readHeaderSection( f, headerList ) ) return false;

	if ( !this->readInputSection( f ) ) return false;

	if ( !this->readOutputSection( f ) ) return false;

	if ( !this->readConnectionSection( f ) ) return false;

	f.close();

	generateNet( inputList, outputList, connectionList );

	return true;
}

void NNet::writeHeaderSection( std::ofstream &f, double version ) const
{
	/*-----------------------------------------
		  Write Header-Section
	------------------------------------------*/

	f << "<header>\n";
	f << "#NNet-File " << version;
	f << "\n</header>\n";

}

void NNet::writeInputSection( std::ofstream &f ) const
{
	/*-----------------------------------------
		  Write Input-Section
	------------------------------------------*/

	f << "<inputs>\n";

	for ( unsigned int i = 0;i < this->inputList.size();i++ )
	{
		f << this->inputList[ i ] << " ";
	}

	f << "\n</inputs>\n";

}

void NNet::writeOutputSection( std::ofstream &f ) const
{
	/*-----------------------------------------
		  Write Output-Section
	------------------------------------------*/

	f << "<outputs>\n";

	for ( unsigned int i = 0;i < this->outputList.size();i++ )
	{
		f << this->outputList[ i ] << " ";
	}

	f << "\n</outputs>\n";
}

void NNet::writeConnectionSection( std::ofstream &f ) const
{
	/*-----------------------------------------
		  Write Connection-Section
	------------------------------------------*/

	f << "<connections>\n";

	int weightIndex = 0;
	int senderTmp = 0;

	for ( unsigned int i = 0;i < this->connectionList.size();i++ )
	{
		int sender = this->connectionList[ i ].sender;
		int receiver = this->connectionList[ i ].receiver;

		if ( senderTmp != sender )
		{
			weightIndex = 0;
			senderTmp = sender;
		}

		f << sender << " " << receiver
		<< " " << this->allCells[ sender ] ->weights[ weightIndex ] << std::endl;

// 		std::cout << sender << " " << receiver
// 		<< " " << this->allCells[ sender ] ->weights[ weightIndex ] << std::endl;

		weightIndex++;
	}

	f << "</connections>\n";
}

bool NNet::saveNet( std::string fileName )
{

	// The file stream
	std::ofstream f( fileName.c_str(), std::ios::out );

	this->writeHeaderSection( f, 0.1 );
	this->writeInputSection( f );
	this->writeOutputSection( f );
	this->writeConnectionSection( f );

	f.close();

	return true;
}

Cell * NNet::input( int i )
{
	return this->inputCells[ i ];
}

Cell * NNet::output( int i )
{
	return this->outputCells[ i ];
}

const int NNet::numberOfConnections() const
{
	return connectionList.size();
}

void NNet::setWeights( std::vector<double>newWeights )
{
	int indexOffset = 0;

	for ( unsigned int i = 0; i < this->allCells.size();i++ )
	{
		for ( unsigned int j = 0; j < this->allCells[ i ] ->weights.size(); j++ )
		{
			this->allCells[ i ] ->weights[ j ] = newWeights[ j + indexOffset ];
		}
		indexOffset += this->allCells[ i ] ->weights.size();
	}
}

NNet::~ NNet()
{
	//delete memory of all cells
	for ( unsigned int i = 0; i < this->allCells.size();i++ )
	{
		if ( allCells[i] != NULL )
		{
			delete allCells[ i ];
			allCells[i] = NULL;
		}
	}
}

void NNet::setMemory( bool value )
{
	enableMemory = value;
}

void NNet::reset()
{
	//Save activation values of all input cells
	std::vector <double> tmpActivations;

	for ( unsigned int i = 0; i < this->inputCells.size();i++ )
	{
		tmpActivations.push_back( this->inputCells[ i ] ->finalOutput() );
	}

	// Reset activations of all cells
	for ( unsigned int i = 0; i < this->allCells.size();i++ )
	{
		this->allCells[ i ] ->firstInput( 0 );
	}

	//restore Activation of output cells as they are
	//resetted if memory disabled
	for ( unsigned int i = 0; i < this->inputCells.size();i++ )
	{
		this->inputCells[ i ] ->firstInput( tmpActivations[ i ] ) ;
	}
}

void NNet::setInputs( NNetInput &input )
{
	for ( int i = 0; i < inputCells.size();i++ )
	{
		inputCells[i]->firstInput( input.getValue( i ) );
	}
}

NNetInput::NNetInput( std::string fileName )
{
	// Specify file type and version
	HeaderTag *header = new HeaderTag();
	header->setFileType( "NNetInput-File" );
	header->setVersion( 0.1 );

	field = new DoubleField( "data" );

	// Define format, i.e. add tags
	addElement( header );
	addElement( field );

	load( fileName );
}

const double NNetInput::getValue( int i ) const
{
	return field->element( i )->getValue();
}

