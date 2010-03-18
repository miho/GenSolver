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

/** @file 	libgensolvertpl.h
 * @brief 	template classes for genetic algorithms
 * @author 	Michael Hoffer (www.mihosoft.de)
 * @date 	13.03.06
 */

/** \mainpage
 * none.
 *
 * <h2>General Description </h2>
 * <p>
 * GenSolver is a basic genetic algorithm. It is written to be type and problem independent.
 * </p>
 * <p>
 * To use the classes provided by libgensolver, to build a genetic algorithm, you basically have
 * to write a fitness function that judges the solution of every chromosome i.e. individual
 * (each individual is represented by a chromosome) in the population. The algorithm now tries
 * to solve the problem by using a concept which is commonly known as "selection and adaption".
 * </p>
 * <p>
 * The GenSolver classes are in a very early state of development.
 * But still they work fine for easier problems and even give you the posssibility to influence the
 * genetic methods like crossOver() and mutate().
 * </p>
 * <h2>Features</h2>
 * <ol>
 * 		<li>type independent</li>
 *		<li>supports different sub gene sizes in one chromosome</li>
 *		<li>supports different chromosome sizes in one population</li>
 *		<li>sub gene sizes and chromosome sizes are initialized randomly</li>
 *		<li>mixing chromosomes of different size (even sub gene sizes may differ) is possible but maybe doesn't make sense :)</li>
 * </ol>
 * Now follows a basic example on how the classes do work.
 * <p>
 * We want to solve a very simple problem. All the same, this shows how libgensolver and genetic algorithms in general work. Let's assume we have
 * chromosomes which are integer vectors and 10 bits long. The bits of the chromosomes can be set to values between 0 and 9. A randomly assigned
 * chromosome might look like this: 8765385975. We want to get chromosomes of the form 0101010101. As already said, this is not a difficult
 * problem an it is very inefficient to use genetic algorithms to solve it. 
 * </p>
 * <p>
 * It is however a good example because writing a fitness function for this problem is really easy. Thats a very important point: you may have the
 * best and most efficient algorithm. It doesn't give you a solution if you are not able to write a good fitness function!
 * </p>
 * <p>
 * And here is the example code:
 * </p>
 * <pre>
 *
 * #include "librand.h"         //random functions
 * #include "libgensolvertpl.h" //this is the header for the genetic classes
 * 
 * //-----------------------------------------------------------------------------
 * //                Here we derive from the template classes
 * //-----------------------------------------------------------------------------
 * namespace GenInt
 * {
 *       class ChromosomeClass : public GenBase::ChromosomeClass<int>
 *       {
 *               public:
 *                       int randFunction(int minRand, int maxRand);
 *       };
 *
 *       class GenerationClass : public GenBase::GenerationClass<ChromosomeClass>
 *       {
 *               public: GenerationClass(int numberOfChromosomes) :
 *                       GenBase::GenerationClass<ChromosomeClass>(numberOfChromosomes){};
 *       };
 *
 *       class PopulationClass : public GenBase::PopulationClass<GenerationClass,ChromosomeClass>
 *       {
 *       };
 *
 *       class GenSolver : public GenBase::GenSolver<PopulationClass>
 *       {
 *       };
 *
 *       int ChromosomeClass::randFunction(int minRand, int maxRand )
 *       {
 *               return randInt(minRand,maxRand );
 *       }
 * }
 
 * //-----------------------------------------------------------------------------
 * //             Here we derive from the typespecific GenSolver class
 * //-----------------------------------------------------------------------------
 *
 * class BitSolver : public GenInt::GenSolver
 * {
 *       void parseChromosomes();
 * };
 
 * //-----------------------------------------------------------------------------
 * //                This is our fitness function
 * //-----------------------------------------------------------------------------
 *
 * void BitSolver::parseChromosomes()
 * {
 *       for ( unsigned int i = 0; i < newGeneration->size(); i++ )
 *       {
 *               double score = 0;
 *               for ( int j = 0; j < newGeneration->sizeOfChromosome( i ); j++ )
 *               {
 *                       if ( j % 2 == 0 )
 *                       {
 *                               if ( (*( *newGeneration ) ( i))(j) == 0 )
 *                               {
 *                                       score += 3;
 *                               }
 *                               else
 *                               {
 *                                       if ( score > 0 ) score -= 1;
 *                               }
 *                       }
 *                       else
 *                       {
 *                               if ( (*( *newGeneration ) ( i))(j) == 1 )
 *                               {
 *                                       score += 3;
 *                               }
 *                               else
 *                               {
 *                                       if ( score > 0 ) score -= 1;
 *                               }
 *                       }
 *               }
 *
 *               if ( score <= 0 ) score = 0.001;
 *                
 *               if (score >= 30) score = 1000;
 *
 *               ( *newGeneration ) ( i ) ->setFitness( score );
 *       }
 * }
 
 * //-----------------------------------------------------------------------------
 * //                main function
 * //-----------------------------------------------------------------------------
 *
 * int main( int argc, char *argv[] )
 * {
 *        BitSolver solver1;
 *        
 *       solver1.initialize(100,10,10,1,1,0,9);
 *       solver1.setMutationRate(0.01);  
 *       solver1.startSolving(200);
 *       solver1.newGeneration->print(29);
 *       
 *       return 0;
 * }
 * </pre>
 */

#ifndef LIBGENSOLVERTPL_H
#define LIBGENSOLVERTPL_H

#include <iostream>
#include <stdlib.h>
#include <cassert>
#include <vector>
#include <iomanip>
#include <cmath>

#include <librand.h>
#include <genutil.h>

using namespace std;

/**
 * The classes in this namespace are the base classes.
 *
 * This is a set of template based genetic classes. They have to be derived
 * because methods like ChromosomeClass::randFunction() are typespecific.
 * Fortunally this is not very difficult.
 *
 * @see		GenInt and GenFloat (they are good examples).
 */
namespace GenBase
{
	/**
	* Chromosome class, which is basically an extended STL- Vector.
	*
	* This class is basically an extended STL vector.
	* It is used to work as a virtual chromosome. It is
	* just used internally. So normally there should be
	* no reason why you should use it as independent
	* class.
	*/
	template <typename T>
	class ChromosomeClass : public vector <T>
	{
		public:
			//Initialization
			ChromosomeClass( );
			virtual ~ChromosomeClass();

			/**
			 * 			Initializes the chromosome randomly.
			 *
			 * 			It initializes
			 * 			the size of the chromosome, the number and size of
			 * 			the sub genes and the chromosome vector itself.
			 *
			 * @param minCSize 	The minimum chromosome size.
			 * @param maxCSize 	The maximum chromosome size.
			 * @param minSubSize 	The minimum sub gene size.
			 * @param maxSubSize 	The maximum sub gene size.
			 * @param minRand 	The minimum bit value.
			 * @param maxRand 	The maximum bit value.
			 */
			virtual void initializeChromosome( unsigned int minCSize, unsigned int maxCSize, unsigned int minSubSize,
			                                   unsigned int maxSubSize, T minRand, T maxRand );

			//Operators
			const T operator() ( unsigned int i ) const;
			T& operator() ( unsigned int i );

			//Access
			vector <T> getSubGene( unsigned int geneNumber, unsigned int subNumber );
			vector <T> getSubGene( unsigned int subGeneNumber );

			//Fitness
			/**
			 *                      Represents the fitness of the chromosome.
			 * @return 		Returns fitnes as const double value
			 */
			const double fitness() const;
			/**
			 *                      Sets the fitness of the chromosome.
			 * @param value 	The fitnes value.
			 */
			void setFitness( double value );

			/**
			 * 			Prints the chromosome vector.
			 *
			 *			It uses the "cout" function and therefore the standard output.
			 */
			void print();

			/**
			 * 			Prints the chromosome vector.
			 *
			 *			It uses the "cout" function and therefore the standard output.
			 * @param minFitness 	The minimum fitness at wich the chromosome is displayed.
			 */
			void print( double minFitness );

			/**
			 * 			Prints fitness ans size of the chromosome vector.
			 *
			 *			It uses the "cout" function and therefore the standard output.
			 */
			void printSizes() const;

			/**
			 *                      Prints fitness and size of the chromosome vector.
			 *
			 *			It uses the "cout" function and therefore the standard output.
			 * @param minFitness 	The minimum fitness at wich the chromosome is displayed.
			 */
			void printSizes( double minFitness ) const;

			/**
			 *                      Randomly changes a bit of the chromosome.
			 * @param i 		The bit index.
			 * @param minRandValue 	Minimum random value.
			 * @param maxRandValue 	Maximum random value.
			 */
			void mutate( unsigned int i , T minRandValue, T maxRandValue );

			const unsigned int numberOfGenes() const;
			
			//Variables
			vector <int> subGeneSizes;

		private:
			//Initialization of Sizes
			/**
			 *                      Returns a randomly chosen size for the actual sub gene.
			 *
			 * @param minSubSize 	Minimum sub gene size.
			 * @param maxSubSize 	Maximum sub gene size.
			 * @return 		The size of the actual subgene as integer value.
			 */
			const unsigned int getSubGeneSize( unsigned int minSubSize, unsigned int maxSubSize ) const;

			/**
			 * 			Returns a randomly chosen size for the chromosome.
			 * @param minCSize 	Minimum chromosome size.
			 * @param maxCSize 	Maximum chromosome size.
			 * @return 		The size of the chromosome.
			 */
			const unsigned int getChromosomeSize( unsigned int minCSize, unsigned int maxCSize ) const;

			/**
			 *			Random function.
			 *
			 *                      This function is the random function that will be used by the
			 * 			mutate() function.
			 * @param minRand	Minimum random value.
			 * @param maxRand	Maximum random value.
			 * @return		The random value.
			 * @todo		change input parameters so that they are of template type T.
			 */
			virtual T randFunction( T minRand, T maxRand );

			//Variables
			double _fitness;


	};


	/**
	* Vector of objects of ChromosomeClass.
	*
	* This class is a vector of chromosomes (objects of
	* ChromosomeClass). This class is just used internally.
	* There is no need to use it directly.
	*/
	template <class T, class ChromosomeTemplate>
	class GenerationClass : public vector<ChromosomeTemplate*>
	{
		public:
			//Initialization
			GenerationClass( unsigned int numberOfChromosomes );
			GenerationClass(const GenerationClass<T, ChromosomeTemplate>& source );
			GenerationClass<T, ChromosomeTemplate>& operator=(const GenerationClass<T, ChromosomeTemplate>& source );
			~GenerationClass();
			
			/**
			 * 			Initializes the generation randomly.
			 *
			 * 			It initializes
			 * 			the size of each chromosome, the number and size of
			 * 			the sub genes and the chromosome vector itself.
			 *
			 * @param minCSize 	The minimum chromosome size.
			 * @param maxCSize 	The maximum chromosome size.
			 * @param minSubSize 	The minimum sub gene size.
			 * @param maxSubSize 	The maximum sub gene size.
			 * @param minRand 	The minimum bit value.
			 * @param maxRand 	The maximum bit value.
			 */
			void initializeChromosomes( int minCSize, int maxCSize, int minSubSize,
			                            int maxSubSize, T minRand, T maxRand );

			/**
			 *                      This function returns the size of the generation.
			 *
			 *			It is an alternative to the std::vector::size() method.
			 * @return 		The size of the generation.
			 */
			const unsigned int numberOfChromosomes() const;

			/**
			 *                      Returns the size of a chromosome.
			 *
			 * @param i 		The index of the chromosome.
			 * @return 		The size of chromosome i.
			 */
			const unsigned int sizeOfChromosome( int i ) const;

			//Operators
			// 			const T operator() ( int i,int j ) const;
			// 			T& operator() ( int i,int j );
			const ChromosomeTemplate* operator() ( unsigned int i ) const;
			ChromosomeTemplate* operator() ( unsigned int i );


			/**
			 * 			Prints the generation vector.
			 *
			 *			It uses the "cout" function and therefore the standard output.
			 */
			void print() const;

			/**
			 * 			Prints the generation vector.
			 *
			 *			It uses the "cout" function and therefore the standard output.
			 * @param minFitness 	The minimum fitness at wich the chromosome is displayed.
			 */
			void print( double minFitness );

			/**
			 * 			Prints fitness ans size of all chromosomes in the generation vector.
			 *
			 *			It uses the "cout" function and therefore the standard output.
			 */
			void printSizes() const;

			/**
			 * 			Prints fitness ans size of all chromosomes in the generation vector.
			 *
			 *			It uses the "cout" function and therefore the standard output.
			 * @param minFitness 	The minimum fitness at wich the chromosome is displayed.
			 */
			void printSizes( double minFitness ) const;

			/**
			 *                      Loads a generation from file.
			 *
			 *			This function can be used to load a generation stored in a text file.
			 * @param fileName 	Filename with path.
			 * @return 		Returns true if loading was successful and false otherwise.
			 */
			bool loadGeneration( string fileName );


		private:
			bool readHeaderSection( ifstream &f, vector <string> &headerList );
			bool readDataSection( ifstream &f, vector <string> &dataList );
	};

	/**
	 * Contains a generation of objects of ChromosomeClass
	 *
	 * This class represents a hole population. It is
	 * designed to simulate evolution in the hope that it
	 * may find a solution to your problem.
	 */
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	class PopulationClass
	{
		public:
			//Initialization
			PopulationClass();
			virtual ~PopulationClass();

			/**
			 * 			Initializes the population randomly.
			 *
			 * 			It initializes
			 * 			the size of each chromosome in the generation , the number and size of
			 * 			the sub genes and the chromosome vector itself.
			 *
			 * @param generationSize The Size of the generation.
			 * @param minCSize 	The minimum chromosome size.
			 * @param maxCSize 	The maximum chromosome size.
			 * @param minSubSize 	The minimum sub gene size.
			 * @param maxSubSize 	The maximum sub gene size.
			 * @param minRand 	The minimum bit value.
			 * @param maxRand 	The maximum bit value.
			 */
			void initialize( unsigned int generationSize, unsigned int minCSize, unsigned int maxxCSize,
					 unsigned int minSubSize, unsigned int maxSubSize, T minRand, T maxRand );

			//Settings

			/**
			 *                      Sets the mutation rate.
			 *
			 *			You should usually try values between 0.01 and 0.1. But it may be possible
			 			that you have to use higher or lower values. That depends on the problem you
			 			are trying to solve.
			 * @param rate 		The mutation rate.
			 */
			void setMutationRate( double rate );

			/**
			 *                      Sets the crossover rate.
			 *
			 *			You should usually try values between 0.5 and 0.8. But it may be possible
			 *			that you have to use higher or lower values. That depends on the problem you
			 *			are trying to solve.
			 * @param rate 		The crossover rate.
			 */
			void setCrossOverRate( double rate );

			/**
			 *                      Sets crosspoint type.
			 *
			 *			You can specify if crosspoints of two parent chromosomes shall be equal (only
			 *			possible if minimum and maximum sub gene size are equal) or if they may be not.
			 *			If all chromosome sizes are equal this has the consequence that the cromosome
			 *			sizes never change!
			 * @param value 	The crosspoint type.
			 */
			void setEqualCrossPoints( bool value );

			/**
			 *                      Sets the range of the randomly chosen crosspoints.
			 *
			 *			You can specify the minimum and maximum crosspoint value. So you can influence
			 *			the way how much the #crossOver() method mixes the bits of
			 *			the chromosomes.
			 *
			 * @param min 		Minimum crosspoint value (in percent!)
			 * @param max 		Maximum crosspoint value (in percent!)
			 * @todo		Check validity of crosspoint values.
			 */
			void setCrossPointRange( double min, double max );

			/**
			 *                      Sets the range of one of the randomly chosen crosspoints.
			 *
			 *			You can specify the minimum and maximum crosspoint value. So you can influence
			 *			the way how much the #crossOver() method mixes the bits of
			 *			the chromosomes.
			 *
			 * @param cpIndex	Index of the crosspoint ( 0 or 1);
			 * @param min 		Minimum crosspoint value (in percent!)
			 * @param max 		Maximum crosspoint value (in percent!)
			 * @todo		Check validity of crosspoint values.
			 */
			void setCrossPointRange( unsigned int cpIndex, double min, double max );

			/**
			 *                      Sets random type.
			 *
			 *			If realRandom is enabled the pattern produced by the random generator is not static
			 *			but dynamically generated (dependant on time). Otherwise you will get ever the same pattern.
			 *
			 * @param value 
			 */
			void enableRealRandom( bool value );


			/**
			 *                      Sets initialization value for srand().
			 *
			 *			This method allows you to initialize srand() with a specific value. You can carantee
			 *			that the behavior of the genetic algorithms do not change until #srandValue has been changed.
			 *			If this method is called #realRandom will be automatically disabled.
			 * @param value 
			 */
			void setSrandValue( long int value );

			/**
			 *                      Defines weather "one-parent-inheritance" is allowed.
			 *
			 *			If cloneParents is enabled it may happen that one chromosome is chosen twice by
			 *			grabChromosome() and that therefore selectParents() chooses one chromosome twice.
			 *			The consequence is that one chromosome alone can produce two babies. Therefore it
			 *			represents parent1 and parent2. Look at selectParents() and crossOver() for further
			 *			information.
			 * @param value 
			 */
			void enableCloneParents( bool value );
			//Variables
			GenerationTemplate *newGeneration;


		protected:
			//Initialization
			/**
			 *			Initializes the Population.
			 *
			 *                      Calls GenerationClass::initializeChromosomes() and sets default parameters.
			 * @param minCSize
			 * @param maxCSize
			 * @param minSubSize
			 * @param maxSubSize
			 * @param minRand
			 * @param maxRand
			 * @see 		See GenerationClass::initializeChromosomes().
			 */
			void initializeGeneration( unsigned int minCSize, unsigned int maxCSize, unsigned int minSubSize,
					unsigned int maxSubSize, T minRand, T maxRand );

			//Genetic Methods

			/**
			 * 			Returns the index of a randomly (chance dependant on its fitness) chosen chromosome.
			 *
			 *			This method simulates the selection of an individual. The cance to be chosen depends
			 *			on the fitness of the chromosome. This means: if a chromosome has a very high fitness
			 *			it is probably (but not cartainly) chosen.
			 * @param generation 	The generation of that the chromosome shall be chosen.
			 * @return 		Index of the chosen chromosome.
			 * @todo		Solve the "very-small-fitness" problem for big generations.
			 */
			const unsigned int grabChromosome( const GenerationTemplate& generation );

			/**
			 *                      Selects two parents for crossOver() method.
			 *
			 *			This method chooses two parents by calling grabChromosome(). It takes care that two
			 *			different parents are chosen. So it is not possible to have clones as parents.
			 * @param generation	The generation of that the parents shall be chosen.
			 */
			void selectParents( const GenerationTemplate& generation );

			/**
			 * 			Creates two babies from two parents.
			 *
			 *			Selects two parents (see selectParents). Each
			 *			chromosome has a randomly defined cross point. Decide
			 *			randomly if crossing is done or not. Then mix the two
			 *			parents as follows:
			 *
			 *			#parent1: 1111111111111111 => 111122222
			 *
			 *			#parent2: 2222222222222222 => 22222222222111111111111
			 *
			 *			baby 1:	  11122222
			 *
			 *			baby 2:   22222222222111111111111
			 *
			 *			This is just a simplified sketch because each
			 *			gene consists of two sub genes. Each sub gene
			 *			has its own size.
			 *			Important: 	crosspoints can only be at the
			 *					beginning or the end of a subgene,
			 *					as otherwise the information on the
			 *					baby chromosome would be too much
				 *					damaged!
			 * @param generation 	The parent generation.
			 * @param baby1 	First baby.
			 * @param baby2 	Second baby.
			 */
			void crossOver( const GenerationTemplate& generation, ChromosomeTemplate& baby1,
			                ChromosomeTemplate& baby2 );

			/**
			 * 			Mutates a chromosome depending on #mutationRate.
			 *
			 *			It calls ChromosomeClass::mutate().
			 * @param chromosome 	The chromosome that shall be mutated.
			 */
			virtual void mutate( ChromosomeTemplate* chromosome );

			/**
			 * 			Creates a new generation.
			 *
			 *			To create a new generation it calls crossOver() until a hole new generation
			 *			is created. The size of a generation is constant.
			 */
			void createNewGeneration();

			//Variables
			bool initialized;
			bool equalCrossPoints;

			double minRandValue;
			double maxRandValue;

			unsigned int minSubGeneSize;
			unsigned int maxSubGeneSize;

			/**
			 *			mutation rate.
			 */
			double mutationRate;

			/**
			 *			crossover rate.
			 */
			double crossOverRate;



			vector <double> minCrossValue;
			vector <double> maxCrossValue;

			/**
			 *	realRandom
			 */
			bool realRandom;

			/**
			 *	srandValue
			 */
			long int srandValue;

			/**
			 *	cloneParents
			 */
			bool cloneParents;

			/**
			 *			parent1.
			 */
			const ChromosomeTemplate *parent1;

			/**
			 *			parent2.
			 */
			const ChromosomeTemplate *parent2;

			GenerationTemplate *oldGeneration;
	};

	/**
	 * This is the main class that gives easy access to the genetic algorithms.
	 *
	 * The purpose of this class is to give easy access to
	 * the genetic classes. As the fitness function and the
	 * parsing of chromosomes is highly problem specific
	 * this class is intentionally an abstract class. To be
	 * able to use the genetic algorithms it is necessary
	 * to write an implementation of the method
	 * parseChromosomes(). There you have also to decide
	 * weather the chromosomes do thair job well or not. It
	 * is impossible to get a solution of your problem if
	 * you are not able to write a fitness function!
	 */
	template <class T>
	class GenSolver : public T
	{
		public:
			GenSolver();
			~GenSolver();

			/**
			 * 			The final genetic algorithm.
			 *
			 *			This is the final solving algorithm. The final
			 *			generation is saved in the member #newGeneration. You
			 *			have to specify the maximum number of generations
			 *			(analogous to number of iteration constant ).
			 * @param maxGenerations The number of Iterations.
			 */
			void startSolving( unsigned int maxGenerations );

		protected:

			/**
			 *			Fitness-Function.
			 *
			 *			Parses all chromosomes of the Population and assigns
			 *			a fitness value to each chromosome. The problem that shall be
			 *			solved has to be formulated here.
			 */
			virtual void parseChromosomes() = 0;

			/**
			 *
			 *			Returns current generation.
			 */
			const unsigned int getCurrentGeneration();
			
			
			/**
			 * If this method is called, startSolving will stop.
			 */
			void foundSolution();
			
			bool _solution;
			
		private:
			unsigned int _currentGeneration;
			
	};
}




namespace GenBase
{
	/*-----------------------------------------------------------------------------
		Class:		ChromosomeClass

		Description:	This class is bsically an extended STL vector.
				It is used to work as a virtual chromosome. It is
				just used internally. So normally there should be
				no reason why you should use it as independent
				class.
	-----------------------------------------------------------------------------*/


	/*-----------------------------------------------------------------------------
		Class:		ChromosomeClass

		Public Members:
	-----------------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		ChromosomeClass // Constructor

		Description:	-

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T>
	ChromosomeClass<T>::ChromosomeClass() : vector <T> ( 0 )
	{
		_fitness = 0;
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		ChromosomeClass // Destructor

		Description:	-

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/
	template <typename T>
	ChromosomeClass<T>::~ChromosomeClass()
	{}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		initializeChromosome

		Description:	Initializes the chromosome randomly. It initializes
				the size of the chromosome, the number and size of
				the sub genes and the chromosome vector itself.

		Input:		minimum chromosome size, maximum chromosome size
				minimum sub gene size, maximum sub gege size, minimum
				random value (for bit on chromosome), maximum random
				value (for bit on chromosome)

		Output:		-
	-----------------------------------------------------------------------------*/
	template <typename T>
	void ChromosomeClass<T>::initializeChromosome( unsigned int minCSize, unsigned int maxCSize,
	        unsigned int minSubSize, unsigned int maxSubSize, T minRand, T maxRand )
	{
		unsigned int chromosomeSize = getChromosomeSize( minCSize, maxCSize );
		unsigned int tmpSize = 0;
		while ( tmpSize < chromosomeSize )
		{
			int tmpSubGeneSize = getSubGeneSize( minSubSize, maxSubSize );
			subGeneSizes.push_back( tmpSubGeneSize );
			tmpSize += tmpSubGeneSize;
		}

		for ( unsigned int i = 0; i < tmpSize; i++ )
		{
			this->push_back( randFunction( minRand, maxRand ) );
		}
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		fitness

		Description:	-

		Input:		-

		Output:		fitness of chromosome
	-----------------------------------------------------------------------------*/

	template <typename T>
	const double ChromosomeClass<T>::fitness() const
	{
		return _fitness;
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		setFitness

		Description:	sets the fitness

		Input:		fitness value

		Output:		-
	-----------------------------------------------------------------------------*/
	template <typename T>
	void ChromosomeClass<T>::setFitness( double value )
	{
		_fitness = value;
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		operator

		Description:	-

		Input:		index of vector entry

		Output:		vector entry
	-----------------------------------------------------------------------------*/
	template <typename T>
	const T ChromosomeClass<T>::operator() ( unsigned int i ) const
	{
		assert( i>=0 );
		assert( i < this->size() );
		return ( *this ) [ i ];
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		operator

		Description:	-

		Input:		index of vector entry

		Output:		reference to vector entry
	-----------------------------------------------------------------------------*/
	template <typename T>
	T& ChromosomeClass<T>::operator() ( unsigned int i )
	{
		assert( i>=0 );
		assert( i < this->size() );
		return ( *this ) [ i ];
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		print

		Description:	prints the chromosome vector

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/
	template <typename T>
	void ChromosomeClass<T>::print()
	{
		cout << "\tFitness: " << this->fitness() << " ";
		cout << "\tDecode:\t";

		for ( int k = 0; k < this->subGeneSizes.size(); k++ )
		{
			vector <T> tmp = this->getSubGene( k );
			for ( int j = 0;j < tmp.size();j++ ) cout << tmp[ j ];
			cout << ",";
		}
		cout << endl << "\t\t\t\t\t";

		for ( int k = 0; k < this->numberOfGenes(); k++ )
		{
			cout << "(";
			vector <T> tmp = this->getSubGene( k, 0 );
			for ( int j = 0;j < tmp.size();j++ ) cout << tmp[ j ];
			cout << "->";
			tmp = this->getSubGene( k, 1 );
			for ( int j = 0;j < tmp.size();j++ ) cout << tmp[ j ];
			cout << ") ";
		}
		cout << endl << "\t\t\t\t\t";
		for ( int k = 0; k < this->size(); k++ )
		{
			cout << ( *this ) ( k );
		}
		cout << ":: " << this->subGeneSizes.size();
		cout << endl;
	}

	template <typename T>
	void ChromosomeClass<T>::print( double minFitness )
	{
		if ( this->fitness() >= minFitness )
		{
			cout << "\tFitness: " << this->fitness() << " ";
			cout << "\tDecode:\t";

			for ( int k = 0; k < this->subGeneSizes.size(); k++ )
			{
				vector <T> tmp = this->getSubGene( k );
				for ( int j = 0;j < tmp.size();j++ ) cout << tmp[ j ];
				cout << ",";
			}
			cout << endl << "\t\t\t\t\t";

			for ( int k = 0; k < this->numberOfGenes(); k++ )
			{
				cout << "(";
				vector <T> tmp = this->getSubGene( k, 0 );
				for ( int j = 0;j < tmp.size();j++ ) cout << tmp[ j ];
				cout << "->";
				tmp = this->getSubGene( k, 1 );
				for ( int j = 0;j < tmp.size();j++ ) cout << tmp[ j ];
				cout << ") ";
			}
			cout << endl << "\t\t\t\t\t";
			for ( int k = 0; k < this->size(); k++ )
			{
				cout << ( *this ) ( k );
			}
			cout << ":: " << this->subGeneSizes.size();
			cout << endl;
		}
	}




	template <typename T>
	void ChromosomeClass<T>::printSizes() const
	{

		cout << setprecision( 4 ) << setiosflags( ios::fixed );

		cout << "Fitness: " << this->fitness() << " :: " << this->subGeneSizes.size();
		cout << endl;

	}
	template <typename T>
	void ChromosomeClass<T>::printSizes( double minFitness ) const
	{
		cout << setprecision( 4 ) << setiosflags( ios::fixed );

		for ( unsigned int i = 0; i < this->size();i++ )
		{

			if ( ( *this ) ( i ) ->fitness() >= minFitness )
			{
				cout << "Fitness: " << this->fitness() << " :: " << this->subGeneSizes.size();
				cout << endl;
			}
		}
	}


	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		numberOfGenes

		Description:	-

		Input:		-

		Output:		number of genes
	-----------------------------------------------------------------------------*/
	template <typename T>
	const unsigned int ChromosomeClass<T>::numberOfGenes() const
	{
		return this->subGeneSizes.size() / 2;
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		getSubGene

		Description:	Returns specified sub gene as vector.

		Input:		index of gene, number of sub gene

		Output:		sub gene as vector
	-----------------------------------------------------------------------------*/
	template <typename T>
	vector<T> ChromosomeClass<T>::getSubGene( unsigned int geneNumber, unsigned int subNumber )
	{
		if ( geneNumber == 0 )
		{
			return getSubGene( geneNumber + subNumber );
		}
		else
		{
			return getSubGene( geneNumber * 2 + subNumber );
		}
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		getSubGene

		Description:	Returns specified sub gene as vector.

		Input:		index of sub gene

		Output:		sub gene as vector
	-----------------------------------------------------------------------------*/
	template <typename T>
	vector<T> ChromosomeClass<T>::getSubGene( unsigned int subGeneNumber )
	{
		vector <T> gene;

		int startIndex = 0;
		int endIndex = 0;

		if ( subGeneNumber == 0 )
		{
			startIndex = 0;
		}
		else
		{
			for ( unsigned int i = 0; i < subGeneNumber;i++ )
			{
				startIndex += subGeneSizes[ i ];
			}
		}

		endIndex = startIndex + subGeneSizes[ subGeneNumber ];

		for ( unsigned int i = startIndex; i < endIndex;i++ )
		{
			gene.push_back( ( *this ) ( i ) );
		}



		return gene;
	}


	/*-----------------------------------------------------------------------------
		Class:		ChromosomeClass

		Private Members:
	-----------------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		getChromosomeSize

		Description:	-

		Input:		minimum chromosome size, maximum chromosome size

		Output:		randomly chosen chromosome size
	-----------------------------------------------------------------------------*/

	template <typename T>
	const unsigned int ChromosomeClass<T>::getChromosomeSize( unsigned int minCSize, unsigned int maxCSize ) const
	{
		return randInt( minCSize, maxCSize );
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		getSubGeneSize

		Description:	-

		Input:		minimum sub gene size, maximum sub gene size

		Output:		randomly chosen sub gene size
	-----------------------------------------------------------------------------*/

	template <typename T>
	const unsigned int ChromosomeClass<T>::getSubGeneSize( unsigned int minSubSize, unsigned int maxSubSize ) const
	{
		return randInt( minSubSize, maxSubSize );
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		randFunction

		Description:	-

		Input:		minimum random value, maximum random value

		Output:		random value
	-----------------------------------------------------------------------------*/

	template <typename T>
	T ChromosomeClass<T>::randFunction( T minRand, T maxRand )
	{
		// virtual
		return 0;
	}

	/*-----------------------------------------------------------------------------

		Class:		ChromosomeClass

		Member:		randFunction

		Description:	randomly changes bit i of the chromosome

		Input:		index of bit, minimum random value, maximum random
				value

		Output:		-
	-----------------------------------------------------------------------------*/

	template <typename T>
	void ChromosomeClass<T>::mutate( unsigned int i, T minRandValue, T maxRandValue )
	{
		( *this ) ( i ) = randFunction( minRandValue, maxRandValue );
	}

	/*-----------------------------------------------------------------------------
		Class:		GenerationClass

		Description:	This class is a vector of chromosomes (objects of
				ChromosomeClass). This class is just used internally.
				There is no need to use it directly.
	-----------------------------------------------------------------------------*/


	/*-----------------------------------------------------------------------------
		Class:		GenerationClass

		Public Members:
	-----------------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		GenerationClass //constructor

		Description:	-

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/

	template <class T, class ChromosomeTemplate>
	GenerationClass<T, ChromosomeTemplate>::GenerationClass( unsigned int numberOfChromosomes ) :
			vector <ChromosomeTemplate*>( numberOfChromosomes )
	{
		//ALLOC_MEM
		for ( unsigned int i = 0; i < numberOfChromosomes; i++ )
		{
			( *this ) [ i ] = new ChromosomeTemplate( );
		}
	}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		GenerationClass //copy-constructor

		Description:	-

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class ChromosomeTemplate>
	GenerationClass<T, ChromosomeTemplate>::GenerationClass(const GenerationClass<T, ChromosomeTemplate>& source ):
		vector <ChromosomeTemplate*>( source.size() )
	{
		//DEBUG-Output
		//GEN_DISPLAY("Copy-Ctor",1);
		
				
		//INIT
		for ( unsigned int i = 0; i < source.numberOfChromosomes; i++ )
		{
			(*this)[ i ] = new ChromosomeTemplate( );
		}
				
		//COPY
		for ( unsigned int i = 0; i < source.numberOfChromosomes(); i++ )
		{
			*(*this)[ i ] = *source[i];
		}
				
	}
			
	/*-----------------------------------------------------------------------------

			Class:		GenerationClass

			Member:		GenerationClass //assignment-operator

			Description:	-

			Input:		-

			Output:		-
			-----------------------------------------------------------------------------*/
	template <class T, class ChromosomeTemplate>
	GenerationClass<T, ChromosomeTemplate>& GenerationClass<T, ChromosomeTemplate>
	::operator=(const GenerationClass<T, ChromosomeTemplate>& source )
	{
		//DEBUG-Output
		//GEN_DISPLAY("Assignment-Op",1);
		
		//DEALLOC
		for ( unsigned int i = 0; i < this->numberOfChromosomes(); i++ )
		{
			if ( ( *this ) [ i ] != NULL )
			{
				delete ( *this ) [ i ];
				( *this ) [ i ] = NULL;
			}
		}
				
		//INIT
		for ( unsigned int i = 0; i < source.numberOfChromosomes(); i++ )
		{
			(*this)[ i ] = new ChromosomeTemplate( );
		}
				
		//COPY
		for ( unsigned int i = 0; i < source.numberOfChromosomes(); i++ )
		{
			*(*this)[ i ] = *source[i];
		}
		
		return *this;
		
	}
	
	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		~GenerationClass //destructor

		Description:	-

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class ChromosomeTemplate>
	GenerationClass<T, ChromosomeTemplate>::~ GenerationClass()
	{
		//DEALLOC
		for ( unsigned int i = 0; i < this->size(); i++ )
		{
			if ( ( *this ) [ i ] != NULL )
			{
				delete ( *this ) [ i ];
				( *this ) [ i ] = NULL;
			}
		}
	}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		initializeChromosomes

		Description:	initializes all chromosomes randomly

		Input:		minimum chromosome size, maximum chromosome size
				minimum sub gene size, maximum sub gege size, minimum
				random value (for bit on chromosome), maximum random
				value (for bit on chromosome)

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class ChromosomeTemplate>
	void GenerationClass<T, ChromosomeTemplate>::initializeChromosomes( int minCSize, int maxCSize,
	        int minSubSize, int maxSubSize, T minRand, T maxRand )
	{

		for ( unsigned int i = 0; i < this->size(); i++ )                   //i < numberOfChromosomes
		{
			( *this ) ( i ) -> initializeChromosome( minCSize, maxCSize, minSubSize,
			        maxSubSize, minRand, maxRand );
		}
	}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		numberOfChromosomes

		Description:	returns the size of the generation

		Input:		-

		Output:		number of chromosomes
	-----------------------------------------------------------------------------*/

	template <class T, class ChromosomeTemplate>
	const unsigned int GenerationClass<T, ChromosomeTemplate>::numberOfChromosomes() const
	{
		return this->size();
	}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		numberOfChromosomes

		Description:	returns the size of a specific chromosome

		Input:		index of chromosome

		Output:		size of chromosome
	-----------------------------------------------------------------------------*/
	template <class T, class ChromosomeTemplate>
	const unsigned int GenerationClass<T, ChromosomeTemplate>::sizeOfChromosome( int i ) const
	{
		return ( *this ) [ i ] ->size();
	}


	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		operator ( i,j )

		Description:	Allows access to an entry j of chromosome i

		Input:		index of chromosome, index of entry in the chromosome

		Output:		entry j of chromosome i
	-----------------------------------------------------------------------------*/

	// 		template <class T>
	// 		const T GenerationClass<T>::operator() ( int i,int j ) const
	// 		{
	// 			assert( i < this->size() );             //number of chromosomes
	// 			assert( j < ( *this ) [ i ] ->size() ); //size of chromosomes
	// 			return ( *( *this ) [ i ] ) ( j );      //bit j of chromosome i
	// 		}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		operator ( i,j )

		Description:	Allows access to an entry j of chromosome i

		Input:		index of chromosome, index of entry in the chromosome

		Output:		reference to entry j of chromosome i
	-----------------------------------------------------------------------------*/ 
	// 		template <typename T>
	// 		T& GenerationClass<T>::operator() ( int i,int j )
	// 		{
	// 			assert( i < this->size() );             //number of chromosomes
	// 			assert( j < ( *this ) [ i ] ->size() ); //size of chromosomes
	// 			return ( *( *this ) [ i ] ) ( j );              //bit j of chromosome i
	// 		}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		operator ( i )

		Description:	Allows access to chromosome i

		Input:		index of chromosome

		Output:		constant pointer to chromosome i
	-----------------------------------------------------------------------------*/
	template <class T, class ChromosomeTemplate>
	const ChromosomeTemplate* GenerationClass<T, ChromosomeTemplate>::operator() ( unsigned int i ) const
	{
		return ( *this ) [ i ];                 //pointer to chromosome i
	}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		operator ( i )

		Description:	Allows access to chromosome i

		Input:		index of chromosome

		Output:		pointer to chromosome i
	-----------------------------------------------------------------------------*/
	template <class T, class ChromosomeTemplate>
	ChromosomeTemplate* GenerationClass<T, ChromosomeTemplate>::operator() ( unsigned int i )
	{
		return ( *this ) [ i ];                 //pointer to chromosome i
	}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		print

		Description:	prints all chromosomes

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class ChromosomeTemplate>
	void GenerationClass<T, ChromosomeTemplate>::print() const
	{
		cout << setprecision( 4 ) << setiosflags( ios::fixed );

		for ( unsigned int i = 0; i < this->size(); i++ )                 //i < numberOfChromosomes
		{
			( *this ) [ i ] ->print();
		}
	}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		print

		Description:	prints size and fitness of all chromosomes

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/

	template <class T, class ChromosomeTemplate>
	void GenerationClass<T, ChromosomeTemplate>::printSizes() const
	{
		for ( unsigned int i = 0; i < this->size(); i++ )                 //i < numberOfChromosomes
		{
			( *this ) ( i ) ->printSizes();
		}
	}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		printSizes

		Description:	prints size and fitness if the fittest of all
				chromosomes

		Input:		minimum fitness

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class ChromosomeTemplate>
	void GenerationClass<T, ChromosomeTemplate>::printSizes( double minFitness ) const
	{
		cout << setprecision( 4 ) << setiosflags( ios::fixed );

		for ( unsigned int i = 0; i < this->size(); i++ )                  //i < numberOfChromosomes
		{
			( *this ) ( i ) ->printSizes( minFitness );
		}
	}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		print

		Description:	prints  the fittest of all chromosomes

		Input:		minimum fitness

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class ChromosomeTemplate>
	void GenerationClass<T, ChromosomeTemplate>::print( double minFitness )
	{
		cout << setprecision( 4 ) << setiosflags( ios::fixed );

		for ( unsigned int i = 0; i < this->size(); i++ )                   //i < numberOfChromosomes
		{
			( *this ) ( i ) ->print( minFitness );
		}
	}


	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		loadGeneration

		Description:	loads generation from file

		Input:		Filename with path

		Output:		-
	-----------------------------------------------------------------------------*/

	template <class T, class ChromosomeTemplate>
	bool GenerationClass<T, ChromosomeTemplate>::loadGeneration( string fileName )
	{
		// List with header informations
		vector <string> headerList;

		// The file stream
		ifstream f( fileName.c_str() );

		if ( !f )
		{
			cerr << "Error: File doesn't exist!" << endl;
			return false;
		};

		if ( !this->readHeaderSection( f, headerList ) ) return false;

		if ( !this->readDataSection( f ) ) return false;

		// 		if ( !this->readOutputSection( f ) ) return false;
		//
		// 		if ( !this->readConnectionSection( f ) ) return false;

		f.close();

		// 		generateNet( inputList, outputList, connectionList );

		return true;
	}

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		readHeaderSection

		Description:	reads header section and verifies version

		Input:		ifstream to the corresponding file, string list

		Output:		-
	-----------------------------------------------------------------------------*/

	template <class T, class ChromosomeTemplate>
	bool GenerationClass<T, ChromosomeTemplate>::readHeaderSection( ifstream &f, vector <string> &headerList )
	{
		/*-----------------------------------------
			  Read Header Information
		------------------------------------------*/

		while ( !f.eof() )
		{
			string tmpStr;
			f >> tmpStr;
			headerList.push_back( tmpStr );
			if ( tmpStr == "</header>" ) break;
		}

		/*-----------------------------------------
		   Error Handling for Header Information
		------------------------------------------*/

		if ( headerList[ 0 ] != "<header>" )
		{
			cerr << "Error: Unknown file format!" << endl;
			return false;
		}

		if ( headerList[ headerList.size() - 1 ] != "</header>" )
		{
			cerr << "Error: Missing </header>!" << endl;
			return false;
		}

		if ( headerList[ 1 ] != "GenSolver-File" )
		{
			cerr << "Error: Unknown file format!" << endl;
			return false;
		}

		if ( atof( headerList[ 2 ].c_str() ) == 0 )
		{
			cerr << "Error: Can't verify version of file format!" << endl;
			return false;
		}
		else
		{
			if ( atof( headerList[ 2 ].c_str() ) > 0.1 )
			{
				cerr << "Error: File is made by newer version of this program!" << endl;
				return false;
			}
		}
		return true;
	};

	/*-----------------------------------------------------------------------------

		Class:		GenerationClass

		Member:		readDataSection

		Description:	reads chromosomes and stores them in a string list

		Input:		ifstream to the corresponding file, string list

		Output:		-
	-----------------------------------------------------------------------------*/

	template <class T, class ChromosomeTemplate>
	bool GenerationClass<T, ChromosomeTemplate>::readDataSection( ifstream &f, vector <string> &dataList )
	{
		vector <string> inputStrList;
		/*-----------------------------------------
			   Read Input-Cell Indices
		------------------------------------------*/

		while ( !f.eof() )
		{
			string tmpStr;
			f >> tmpStr;
			inputStrList.push_back( tmpStr );
			if ( tmpStr == "</data>" ) break;
		}


		if ( inputStrList[ 0 ] != "<data>" )
		{
			cerr << "Error: Data section missing!" << endl;
			return false;
		}
		if ( inputStrList[ inputStrList.size() - 1 ] != "</data>" )
		{
			cerr << "Error: Missing </data>!" << endl;
			return false;
		}

// 		for ( unsigned int i = 1;i < inputStrList.size() - 1;i++ )
// 		{
// 			int tmpVal = atoi( inputStrList[ i ].c_str() );
// 			if ( ( inputStrList[ i ] != "0" ) && ( tmpVal == 0 ) )
// 			{
// 				cerr << "Error: Entry " << i << " in \"<inputs> </inputs>\" - Section is not a valid integer number!" << endl;
// 				return 1;
// 			}
// 			inputList.push_back( tmpVal );
// 		}

		return true;
	};


	/*-----------------------------------------------------------------------------
		Class:		PopulationClass

		Description:	This class represents a hole population. It is
				designed to simulate evolution in the hope that it
				may give you a solution to your problem.
	-----------------------------------------------------------------------------*/


	/*-----------------------------------------------------------------------------
		Class:		PopulationClass

		Public Members:
	-----------------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		PopulationClass //constructor

		Description:	-

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	PopulationClass<T, GenerationTemplate, ChromosomeTemplate>::PopulationClass( ) : minCrossValue ( 2 ), maxCrossValue ( 2 )
	{
		initialized = false;
		
		newGeneration = NULL;
		oldGeneration = NULL;
		
		parent1 = NULL;
		parent2 = NULL;
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		PopulationClass //destructor

		Description:	-

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	PopulationClass<T, GenerationTemplate, ChromosomeTemplate>::~PopulationClass( )
	{
		if( newGeneration!= NULL)
		{
			delete newGeneration;
			newGeneration = NULL;
		}
		
		if( oldGeneration!= NULL)
		{
			delete oldGeneration;
			oldGeneration = NULL;
		}
		
// 		if( parent1!= NULL)
// 		{
// 			delete parent1;
// 			parent1 = NULL;
// 		}
// 		
// 		if( parent2!= NULL)
// 		{
// 			delete parent2;
// 			parent2 = NULL;
// 		}
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		initialize

		Description:	This method must be called before starting the solving
				method

		Input:		size of one generation, minimum chromosome size,
				maximum chromosome size, minimum sub gene size,
				maximum sub gene size, minimum random value (for bit
				on chromosome), maximum random value (for bit on
				chromosome)


		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::initialize
	( unsigned int generationSize, unsigned int minCSize, unsigned int maxCSize, unsigned int minSubSize, unsigned int maxSubSize, T minRand, T maxRand )
	{

		assert( generationSize % 2 == 0 );
		assert( !initialized );

		initialized = true;

		this->srandValue = 0;

		if ( this->realRandom )
		{
			this->srandValue = time( NULL ); //init srandValue by calling time(NULL)
		}

		cout << "srand constant: " << this->srandValue << endl;

		srand( this->srandValue );

		newGeneration = new GenerationTemplate( generationSize );
		oldGeneration = new GenerationTemplate( generationSize );

		//srand( time( 0 ) );
		this->initializeGeneration( minCSize, maxCSize, minSubSize, maxSubSize, minRand, maxRand );

		minRandValue = minRand;
		maxRandValue = maxRand;

		minSubGeneSize = minSubSize;
		maxSubGeneSize = maxSubSize;

		mutationRate = 0.02;
		crossOverRate = 0.7;

// 		realRandom = true;
// 		srandValue = 0;
		cloneParents = true;

		if ( ( minCSize == maxCSize ) && ( minSubSize == maxSubSize ) )
		{
			equalCrossPoints = true;
		}
		else
		{
			equalCrossPoints = false;
		}

		minCrossValue[ 0 ] = 0;
		maxCrossValue[ 0 ] = 100;

		minCrossValue[ 1 ] = 0;
		maxCrossValue[ 1 ] = 100;
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		enableRealRandom()

		Description:	-

		Input:		value

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::enableRealRandom( bool value )
	{
		realRandom = value;
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		setSrandValue()

		Description:	-

		Input:		value

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::setSrandValue( long int value )
	{
		this->enableRealRandom( false );
		srandValue = value;
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		enableCloneParents()

		Description:	-

		Input:		value

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::enableCloneParents( bool value )
	{
		cloneParents = value;
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		setCrossOverRate

		Description:	-

		Input:		crossover rate (usually something like 0.8)

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::setCrossOverRate( double rate )
	{
		crossOverRate = rate;
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		setMutationRate

		Description:	-

		Input:		mutation rate (usually something like 0.02)

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::setMutationRate( double rate )
	{
		mutationRate = rate;
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		setCrossPointRange

		Description:	Defines a range within the crosspoints are randomly
				chosen. If you like your chromosomes to be of
				different sizes than you may choose values like
				10 % as minimum and 90 % as maximum.Values like 50 %
				as minimum and 50 % as maximum ensure that the size
				of chromosomes is not changed by crossover method.
	 			But this is only true if sub gene sizes are constant!

		Input:		minimum cross point position, maximum cross point
				position (in percent)

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass<T, GenerationTemplate, ChromosomeTemplate>::setCrossPointRange( double min, double max )
	{
		assert ( min > 0 );
		assert ( min < 100 );
		assert ( max > 0 );
		assert ( max < 100 );
		assert ( max >= min );

		minCrossValue[ 0 ] = min;
		maxCrossValue[ 0 ] = max;

		minCrossValue[ 1 ] = min;
		maxCrossValue[ 1 ] = max;
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		setCrossPointRange

		Description:	Defines a range within crosspoint i is randomly
				chosen. If you like your chromosomes to be of
				different sizes than you may choose values like
				10 % as minimum and 90 % as maximum. Values like 50 %
				as minimum and 50 % as maximum ensure that the size
				of chromosomes is not changed by crossover method.
				But this is only true if sub gene sizes are constant!

		Input:		crosspoint index (0 or 1),minimum cross point
				position, maximum cross point, position (in percent)

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::setCrossPointRange( unsigned int cpIndex, double min, double max )
	{
		assert ( min >= 0 );
		assert ( min <= 100 );
		assert ( max > 0 );
		assert ( max <= 100 );
		assert ( max >= min );

		assert ( cpIndex >= 0 );
		assert ( cpIndex <= 1 );

		minCrossValue[ cpIndex ] = min;
		maxCrossValue[ cpIndex ] = max;
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		setEqualCrossPoints

		Description:	Defines weather the crosspoints of the chosen parents
				are equal or not. If so, the chromosome sizes will
				never change if all chromosomes of the parent
				generation have the same size! The sub gene sizes have
				to be equal, if equalCrossPoints is set. This method
				influences the behavior of the member crossover()

		Input:		bool value

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::setEqualCrossPoints( bool value )
	{
		assert( value && ( minSubGeneSize == maxSubGeneSize ) );
		equalCrossPoints = value;
	}


	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		mutate

		Description:	dependant on the mutation rate change an entry of the
				cromosome vector randomly

		Input:		chromosome

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::mutate( ChromosomeTemplate* chromosome )
	{
		for ( unsigned int i = 0; i < chromosome->size(); i++ )
		{
			if ( randFloat() < mutationRate )
			{
				chromosome->mutate( i , minRandValue, maxRandValue );
			}
		}

	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		crossOver

		Description:	Selects two parents (see selectParents). Each
				chromosome has a randomly defined cross point. Decide
				randomly if crossing is done or not. Then mix the two
				parents as follows:

					cross point 1
					      |
				parent 1: 1111111111111111 => 111122222

				parent 2: 2222222222222222 => 22222222222111111111111
						    |
						cross point 2

				baby 1:	  11122222
				baby 2:   22222222222111111111111

				This is just a simplified sketch because each
				gene consists of two sub genes. Each sub gene
				has its own size.

				Important: 	crosspoints can only be at the
						beginning or the end of a subgene,
						as otherwise the information on the
						baby chromosome would be too much
	 					damaged!


		Input:		size of one generation, two baby chromosomes

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::crossOver
	( const GenerationTemplate& generation, ChromosomeTemplate & baby1, ChromosomeTemplate & baby2 )
	{
		selectParents( generation );

		double minCrossPoint1 = 1. * ( parent1->subGeneSizes.size() - 1 ) / 100 * minCrossValue[ 0 ];
		double maxCrossPoint1 = 1. * ( parent1->subGeneSizes.size() - 1 ) / 100 * maxCrossValue[ 0 ];

		unsigned int crossPoint1 = randInt( int ( minCrossPoint1 ), int( maxCrossPoint1 ) );

		unsigned int realCrossPoint1 = 0;


		for ( unsigned int i = 0; i < crossPoint1; i++ )
		{
			realCrossPoint1 += parent1->subGeneSizes[ i ];
		}

		double minCrossPoint2 = 1. * ( parent2->subGeneSizes.size() - 1 ) / 100 * minCrossValue[ 1 ];
		double maxCrossPoint2 = 1. * ( parent2->subGeneSizes.size() - 1 ) / 100 * maxCrossValue[ 1 ];

		unsigned int crossPoint2 = randInt( int( minCrossPoint2 ), int( maxCrossPoint2 ) );

		unsigned int realCrossPoint2 = 0;

		for ( unsigned int i = 0; i < crossPoint2; i++ )
		{
			realCrossPoint2 += parent2->subGeneSizes[ i ];
		}

		if ( equalCrossPoints )
		{
			crossPoint2 = crossPoint1;
			realCrossPoint2 = realCrossPoint1;
		}
		else
		{
			// take values as initialized before
		}

		// 		cout << "CP: " << crossPoint1 << " " << crossPoint2 << endl;
		// 		cin.get();
		if ( randFloat() < crossOverRate )
		{

			vector <int> tmpSubGeneSizes1;
			vector <int> tmpSubGeneSizes2;

			ChromosomeTemplate tmpBaby1;
			ChromosomeTemplate tmpBaby2;


			for ( unsigned int i = 0; i < realCrossPoint1; i++ )
			{
				tmpBaby1.push_back( ( *parent1 ) ( i ) );
			}

			for ( unsigned int i = realCrossPoint2; i < parent2->size(); i++ )
			{
				tmpBaby1.push_back( ( *parent2 ) ( i ) );
			}

			for ( unsigned int i = 0; i < realCrossPoint2; i++ )
			{
				tmpBaby2.push_back( ( *parent2 ) ( i ) );
			}

			for ( unsigned int i = realCrossPoint1; i < parent1->size(); i++ )
			{
				tmpBaby2.push_back( ( *parent1 ) ( i ) );
			}

			for ( unsigned int i = 0; i < crossPoint1; i++ )
			{
				tmpSubGeneSizes1.push_back( ( *parent1 ).subGeneSizes[ i ] );
			}

			for ( unsigned int i = crossPoint2; i < parent2->subGeneSizes.size(); i++ )
			{
				tmpSubGeneSizes1.push_back( ( *parent2 ).subGeneSizes[ i ] );
			}

			for ( unsigned int i = 0; i < crossPoint2; i++ )
			{
				tmpSubGeneSizes2.push_back( ( *parent2 ).subGeneSizes[ i ] );
			}

			for ( unsigned int i = crossPoint1; i < parent1->subGeneSizes.size(); i++ )
			{
				tmpSubGeneSizes2.push_back( ( *parent1 ).subGeneSizes[ i ] );
			}

			baby1 = tmpBaby1;
			baby2 = tmpBaby2;
			baby1.subGeneSizes = tmpSubGeneSizes1;
			baby2.subGeneSizes = tmpSubGeneSizes2;

		}
		else
		{
			baby1 = *parent1;
			baby2 = *parent2;
		}
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		grabChromosome

		Description:	chooses randomly a chromosome dependant on its
				fitness.

		Input:		the generation from which the chromosome shall be
				chosen.

		Output:		index of the chromosome
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	const unsigned int PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::grabChromosome( const GenerationTemplate& generation )
	{
		long double totalFitness = 0;
		long double tmpFitness = 0;

		unsigned int selectedChromosome = 0;

		for ( unsigned int i = 0; i < generation.size(); i++ )
		{
			totalFitness += generation( i ) ->fitness();
		}

		double randomFitness = randFloat() * totalFitness; // here we decide were to stop the wheel

		unsigned int i = 0;

		while ( tmpFitness <= randomFitness )
		{
			i++;
			if ( i >= (unsigned int) generation.size() ) i = 0;

			tmpFitness += generation( i ) ->fitness();
		}
		selectedChromosome = i;

		return selectedChromosome;
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		selectParents

		Description:	Selects to different parent chromosomes. The
				chromosomes are selected randomly dependant on their
				fitness.The parents are protected menbers of
				PopulationClass.

		Input:		generation from which parents shall be chosen

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::selectParents( const GenerationTemplate & generation )
	{
		unsigned int iTmp1 = grabChromosome( generation );
		unsigned int iTmp2 = iTmp1;

		parent1 = generation( iTmp1 );

		if ( cloneParents )
		{
			iTmp2 = grabChromosome( generation );
		}
		else
		{
			//we want to ensure to get two different chromosomes as parents
			while ( iTmp2 == iTmp1 )
			{
				iTmp2 = grabChromosome( generation );
			}
		}

		parent2 = generation( iTmp2 );
	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		createNewGeneration

		Description:	Creates a new generation with use of crossover,
				mutation and so on (apparently as in real life). The
				generations are members of PopulationClass

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::createNewGeneration()
	{
		//swap generationPointers
		GenerationTemplate * tmpPointer = oldGeneration;
 		oldGeneration = newGeneration;
		newGeneration = tmpPointer;
		
// 		*oldGeneration = *newGeneration;

		
				
		for ( unsigned int i = 0; i < newGeneration->size() - 1; i += 2 )
		{
			ChromosomeTemplate * arg1 = ( *newGeneration ) ( i );
			ChromosomeTemplate * arg2 = ( *newGeneration ) ( i + 1 );
			
			crossOver( *oldGeneration, *arg1, *arg2 );

			mutate( ( *newGeneration ) ( i ) );
			mutate( ( *newGeneration ) ( i + 1 ) );

		}

	}

	/*-----------------------------------------------------------------------------

		Class:		PopulationClass

		Member:		initializeGeneration

		Description:	Initializes randomly the hole start generation.

		Input:		-

		Output:		-
	-----------------------------------------------------------------------------*/

	template <class T, class GenerationTemplate, class ChromosomeTemplate>
	void PopulationClass< T, GenerationTemplate, ChromosomeTemplate>::initializeGeneration
	( unsigned int minCSize, unsigned int maxCSize, unsigned int minSubSize, unsigned int maxSubSize, T minRand, T maxRand )
	{
		newGeneration->initializeChromosomes( minCSize, maxCSize, minSubSize, maxSubSize, minRand, maxRand );
	}


	/*-----------------------------------------------------------------------------
		Class:		GenSolver

		Description:	The purpose of this class is to give easy access to
				the genetic classes. As the fitness function and the
				parsing of chromosomes is highly problem specific
				this class is intentionally an abstract class. To be
				able to use the genetic algorithms it is necessary
				to write an implementation of the method
				parseChromosomes. There you have also to decide
				weather the cromosomes do thair job well or not. It
				is impossible to get a solution of your problem if
				you are not able to write a fitness function!
	-----------------------------------------------------------------------------*/


	/*-----------------------------------------------------------------------------
		Class:		GenSolver

		Public Members:
	-----------------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------------

		Class:		GenSolver

		Member:		GenSolver //constructor

		Description:	-

		Input:		size of one generation

		Output:		-
	-----------------------------------------------------------------------------*/
	template <typename T>
	GenSolver<T>::GenSolver()
	{
		_currentGeneration = 0;
		_solution = false;
	}

	/*-----------------------------------------------------------------------------

		Class:		GenSolver

		Member:		GenSolver //destructor

		Description:	-

		Input:		size of one generation

		Output:		-
	-----------------------------------------------------------------------------*/
	template <typename T>
	GenSolver<T>::~GenSolver()
	{}


	/*-----------------------------------------------------------------------------

		Class:		GenSolver

		Member:		getCurrentGeneration

		Description:	-

		Input:		-

		Output:		current generation as integer
	-----------------------------------------------------------------------------*/
	template <typename T>
	const unsigned int GenSolver<T>::getCurrentGeneration()
	{
		return _currentGeneration;
	}
	
	/*-----------------------------------------------------------------------------

	Class:		GenSolver

	Member:		foundSolution

	Description:	-

	Input:		-

	Output:		-
	-----------------------------------------------------------------------------*/
	template <typename T>
	void GenSolver<T>::foundSolution()
	{
		_solution = true;
	}

	/*-----------------------------------------------------------------------------

		Class:		GenSolver

		Member:		startSolving

		Description:	This is the final solving algorithm. The final
				generation is saved in the member newGeneration.

		Input:		maximum number of generations

		Output:		-
	-----------------------------------------------------------------------------*/
	template <class T>
	void GenSolver<T>::startSolving( unsigned int maxGenerations )
	{

		assert( this->initialized );

// 		if ( this->realRandom )
// 		{
// 			this->srandValue = time( NULL ); //init srandValue by calling time(NULL)
// 		}
// 
// 		cout << "srand constant: " << this->srandValue << endl;
// 
// 		srand( this->srandValue );

		for ( unsigned int i = 0; i < maxGenerations; i++ )
		{
			this->parseChromosomes();
			this->createNewGeneration();
			_currentGeneration = i;
			cout << "--- New Generation: " << i << " ---"<< endl;
			
			if (_solution)
			{
				cout << ">> STOPPING: Solution found!" << endl; 
				break;
			}
		}
		//this->parseChromosomes();
		
		
	}
}

#endif /*LIBGENSOLVERTPL_H*/
