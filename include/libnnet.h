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

#ifndef LIBNNET_H
#define LIBNNET_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <File.h>
#include <HeaderTag.h>
#include <DoubleField.h>

//using namespace std;

/** @file 	libnnet.h
* @brief 	classes for neural networks
* @author 	Michael Hoffer (www.mihosoft.de)
* @date 	27.05.06
*/


/**
 *	Basic neural cell class.
 *
 *	In combination with the NNet class you can build simple neural networks. A cell has some
 *	inputs (usually from other cells). And one or more outputs (these are connected with inputs of other cells).
 *	Internally the inputs are feeded to the sigmoid function ( sigmoid basically stands for s-shaped).
 *	Each connection has a wight with that the input is multiplied. Depending on the wight the connection has
 *	more or less influence on the output.
 */
class Cell
{
	public:
		/**
		 *               		Constructor.
		 *
		 *				The constructor initializes the Cell::signalSum value.
		 */
		Cell();

		/**
		 *               		Forwards input data to the cell (without any modifications).
		 *
		 *				This method is for setting Cell::signalSum value directly (without wights).
		 *				Common usage of this function is if you want to feed input data to the cell.
		 *
		 * @param value 		The input data value.
		 */
		void firstInput( double value );

		/**
		 *               		Increase or decrease Cell::signalSum value i.e. Cell::signalSum+=value.
		 *
		 * @param value 		The input value.
		 */
		void input( double value );

		/**
		 *               		Returns Cell::sigmoid(signalSum)*wights[i].
		 *
		 *				This method returns Cell::signalSum not directly but Cell::sigmoid(signalSum)*wights[i].
		 *				Therefore the result also depands on the wight.
		 *
		 * @param i
		 * @return
		 */
		double output( int i );
		double output();

		/**
		 *               		Returns Cell::signalSum directly.
		 *
		 *				This method usally is used for the last output.
		 *
		 * @return 			The Cell::signalSum value.
		 */
		double finalOutput();

		/**
		 *               		Sends the result of Cell::output() to each connected cell.
		 *
		 */
		void sendSignals();

		/**
		 *               		Connects two cells.
		 *
		 * @param c			Pointer to the cell we want to connect.
		 */
		void connect( Cell* c );

		/**
		 *				Connects two cells.
		 *
		 *               		Behaves like the above method, except that you can directly set
		 *				the weight of the connection.
		 *
		 * @param c			Pointer to the cell we want to connect.
		 * @param weight 		The wight.
		 */
		void connect( Cell* c, double weight );

		/**
		 *				Returns the modified Cell::signalSum.
		 *               		Returns 1 / ( 1 + exp( -activation ) ), whereas activation usually is the
		 *				Cell::signalSum value. It is a threshold function.
		 *
		 * @param activation		The activation of the cell.
		 * @return 			The actual output value of the cell (without wight).
		 */

		double sigmoid( double activation );

		/**
		 *               	Represents the summation of all inputs.
		 *
		 */
		double signalSum;

		/**
		 *			In this vector the weights of the connections are stored.
		 */
		std::vector <double> weights;

		/**
		 *			This vectores stores pointers to all connected cells.
		 */
		std::vector <Cell*> connections;

		/**
		 *			The index of the cell inside of a NNet object
		 */
		int netIndex;

		bool alreadyConnected;

};



/**
 * Stores initial values of input cells.
 *
 * The purpose of this class it to make it easier to load input data from file.
 * This is achieved by using the FlexPars library.
 */
class NNetInput : public File
{
	public :
		/**
		 * Constructor.
		 *
		 * Load data from file.
		 */
		NNetInput( std::string fileName );

		/**
		 * Returns value with index i.
		 */
		const double getValue( int i ) const;
	private:
		/**
		 * Stores the input data.
		 */
		DoubleField *field;
};

/**
		 *		Internal class, representing a connection between two cells
		 */
class netConnection
{
	public:
		netConnection( std::string senderStr, std::string receiverStr, std::string weightStr )
		{
			sender = atoi( senderStr.c_str() );
			receiver = atoi( receiverStr.c_str() );
			weight = atof( weightStr.c_str() );
		};
		netConnection( int senderInt, int receiverInt, int weightInt )
		{
			sender = senderInt;
			receiver = receiverInt;
			weight = weightInt;
		};
		int sender;
		int receiver;
		double weight;


};


/**
 * 	Basic neural network class.
 *
 *	This is an attempt to create a basic neural network class based on Cell classes. It only has one
 *	method that starts the send process. You can build networks that don't have to be feedforward nets.
 *	Of course there are input and output cells. But all cells can be connected freely. But be aware that
 *	if you connect cells of the second layer to cells of the first layer you are in an endless loop!
 */


class NNet
{
	public:
		NNet();

		/**
		 *	Constructs NNet instance from file
		 *
		  * @param fileName 	Filename with path.
		 *
		 */
		NNet( std::string fileName );

		/**
		 * Copy constructor.
		 */
		NNet( const NNet &net );

		/**
		 * Assignment operator
		 */
		NNet & operator=( const NNet &net );


		/**
		 *			Generates feed forward network.
		 * @param numberOfInputs Size of the input layer.
		 * @param numberOfOutputs Size of the output layer.
		 * @param layerSize	Each element of the vector represents the size of one layer.
		 * 			The number of elements defines the number of hidden layers.
		 *
		 */
		NNet( int numberOfInputs, int numberOfOutputs, std::vector<int> layerSize );

		/**
		 *			Generates feed forward network.
		 * @param numberOfInputs Size of the input layer.
		 * @param numberOfOutputs Size of the output layer.
		 * @param layerSize	Each element of the vector represents the size of one layer.
		 * 			The number of elements defines the number of hidden layers.
		 *
		 */
		bool createNet( int numberOfInputs, int numberOfOutputs, std::vector<int> layerSize );

		Cell* input( int i );
		Cell* output( int i );


		/**
		 *			Vector with pointers to all input cells.
		 *
		 *			Pointers to all cells that get direct input via Cell::firstInput() should
		 *			be stored in this vector.
		 */
		std::vector <Cell*> inputCells;

		/**
		 *			Vector with pointers to all output cells.
		 *
		 *			Pointers to all cells that return direct output via Cell::finalOutput() should
		 *			be stored in this vector.
		 */
		std::vector <Cell*> outputCells;


//		/*
//		 *			Vector with pointers to all hidden cells.
//		 *
//		 *			Pointers to all cells that are not directly connected to routines outside of the
//		 *			neural Net should be stored in this vector.
//		 */
// 		vector <Cell*> hiddenCells;

		/**
		 *			Vector with pointers to all cells.
		 *
		 *			Pointers to all cells of the net.
		 */
		std::vector <Cell*> allCells;

		/**
		 * 			Initializes input cells with specific values.
		 */
		void setInputs( NNetInput &input );

		/**
		 *			Starts the send process.
		 */
		void sendSignals();

		/**
		 *               	Loads net from file.
		 *
		 *			With this method you can load a net from file.
		 *
		 * @param fileName 	Filename with path.
		 * @return 		Returns true if loading was successful and false otherwise.
		 */
		bool loadNet( std::string fileName );

		/**
		 *               	Saves net as file.
		 *
		 *			With this method you can save a net as file.
		 *
		 * @param fileName 	Filename with path.
		 * @return 		Returns true if saving was successful and false otherwise.
		 */
		bool saveNet( std::string fileName );

		/**
		 *	Returns number of connections.
		 */
		const int numberOfConnections() const;

		/**
		 *			Standard destructor.
		 *
		 *			Frees memory of all cells.
		 *
		 */
		~NNet();




		/**
		 *               Generates NNet.
		 *		 This method generates a neural net.
		 * @param inputs Vector with indices of all cells that are input cells.
		 * @param outputs Vector with indices of all cells that are output cells.
		 * @param connections Vector with the connections.
		 * @return true (at the moment)
		 */
		bool generateNet( std::vector<int>inputs, std::vector<int>outputs, std::vector<netConnection>connections );

		void setWeights( std::vector<double>newWeights );

		/**
		 * Defines whether cells are always resetted or not.
		 */
		void setMemory( bool value );

		void reset();

	private:


		std::vector<int>inputList;
		std::vector<int>outputList;
		std::vector<netConnection>connectionList;



		const int getNumberOfCells() const;

		void generateCells( unsigned int numberOfCells );
		void storeInputCells();
		void storeOutputCells();
		void connectCells();

		/*file specific methods*/

		bool readHeaderSection( std::ifstream &f, std::vector <std::string> &headerList );
		bool readInputSection( std::ifstream &f );
		bool readOutputSection( std::ifstream &f );
		bool readConnectionSection( std::ifstream &f );

		void writeHeaderSection( std::ofstream &f, double version ) const;
		void writeInputSection( std::ofstream &f ) const;
		void writeOutputSection( std::ofstream &f ) const;
		void writeConnectionSection( std::ofstream &f ) const;

		/**
		 * Defines whether cells are always resetted or not.
		 */
		bool enableMemory;

};

#endif /*LIBNNET_H*/
