/// \file   genutil.h
/// \author Michael Hoffer
/// \date   2007
/// \brief Contains macros for better Debug-Output.

#include <iostream>

#ifndef UTIL_H
#define UTIL_H
/**
* Macros for better Debug-Output.
* \author Michael Hoffer, 2007
*/

#ifdef NDEBUG
#define GEN_ASSERT(x,y)
#elif DEBUG == 0
#define GEN_ASSERT(x,y) \
if ( y == 0 ) \
{ \
	if( !( x ) ) \
{ \
		std::cout << "\nDEBUG-Level: 0\n"; \
		std::cout << "\nERROR: Assertion (" << #x << ") failed\n"; \
		std::cout << "\t>> in line " << __LINE__ << "\n"; \
		std::cout << "\t>> in File " << __FILE__ << "\n\n"; \
} \
}
#elif DEBUG == 1
#define GEN_ASSERT(x,y) \
if ( y <= 1 ) \
{ \
	if( !( x ) ) \
	{ \
		std::cout << "\nDEBUG-Level: 1\n"; \
		std::cout << "\nERROR: Assertion (" << #x << ") failed\n"; \
		std::cout << "\t>> in line " << __LINE__ << "\n"; \
		std::cout << "\t>> in File " << __FILE__ << "\n\n"; \
	} \
}
#elif DEBUG == 2
#define GEN_ASSERT(x,y) \
if ( y <= 2 ) \
{ \
	if( !( x ) ) \
	{ \
		std::cout << "\nDEBUG-Level: 2\n"; \
		std::cout << "\nERROR: Assertion (" << #x << ") failed\n"; \
		std::cout << "\t>> in line " << __LINE__ << "\n"; \
		std::cout << "\t>> in File " << __FILE__ << "\n\n"; \
	} \
}
#elif DEBUG == 3
#define GEN_ASSERT(x,y) \
if ( y <= 3 ) \
{ \
	if( !( x ) ) \
	{ \
		std::cout << "\nDEBUG-Level: 3\n"; \
		std::cout << "\nERROR: Assertion (" << #x << ") failed\n"; \
		std::cout << "\t>> in line " << __LINE__ << "\n"; \
		std::cout << "\t>> in File " << __FILE__ << "\n\n"; \
	} \
	else \
	{ \
		std::cout << "\nDEBUG-Level: 3\n"; \
		std::cout << "Assertion (" << #x << ") OK\n\n"; \
	} \
}
#endif

#ifdef NDEBUG
#define GEN_DISPLAY( x, y )
#elif DEBUG == 0
#define GEN_DISPLAY( x, y ) \
	if ( y == 0) std::cout << x << std::endl;
#elif DEBUG == 1
#define GEN_DISPLAY( x, y ) \
	if ( y <= 1) std::cout << x << std::endl;
#elif DEBUG == 2
#define GEN_DISPLAY( x, y ) \
	if ( y <= 2) std::cout << x << std::endl;
#elif DEBUG == 3
#define GEN_DISPLAY( x, y ) \
	if ( y <= 3) std::cout << x << std::endl;
#endif

#define REACHED printf("REACHED %s:%d\n", __FILE__, __LINE__);

#endif /*UTIL_H*/
