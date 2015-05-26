#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>

class Allocator {
public:
	typedef void		*Pointer;
	typedef const void	*ConstPointer;
	typedef size_t		Size;

	static const ConstPointer	null;
	
	virtual Pointer	allocate( Size size )
	{
		return ::malloc( size );
	}

	virtual void	deallocate( Pointer pointer )
	{
		::free( pointer );
	}
};

extern Allocator _default_allocator;

#endif
