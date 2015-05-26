#ifndef MEMORY_H
#define MEMORY_H

#include "Allocator.h"
#include <stddef.h>
#include <new>

template <typename T>
class Memory {
public:
	typedef T		Value;
	typedef T		*Pointer;
	typedef T		&Reference;
	typedef const T		*ConstPointer;
	typedef const T		&ConstReference;
	typedef size_t		Size;
	typedef ptrdiff_t	Difference;

	static void	construct( Pointer memory, ConstReference value, Size count=1 );
	static void	destroy( Pointer memory, Size count=1 );
	template	<typename InputIterator>
	static void	copy( Pointer destination, InputIterator source, Size count=1 );
	static void	move( Pointer destination, Pointer source, Size count=1 );
};

#include "Memory.cpp"

#endif
