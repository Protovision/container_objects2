#ifndef ARRAY_H
#define ARRAY_H

#include "Allocator.h"
#include "Memory.h"

template <typename T>
class Array {
public:
	typedef typename Memory<T>::Value		Value;
	typedef typename Memory<T>::Pointer		Pointer;
	typedef typename Memory<T>::Reference		Reference;
	typedef typename Memory<T>::ConstPointer	ConstPointer;
	typedef typename Memory<T>::ConstReference	ConstReference;
	typedef typename Memory<T>::Size		Size;
	typedef typename Memory<T>::Difference		Difference;
	
	typedef Pointer		Iterator;
	typedef ConstPointer	ConstIterator;

	Array( Allocator *allocator = &_default_allocator );
	Array( const Array &array );
	~Array( );

	Size		size( ) const;
	ConstIterator	begin( ) const;
	ConstIterator	end( ) const;

	Iterator	begin( );
	Iterator	end( );
	Iterator	insert( Iterator position, ConstReference value );
	template	<typename InputIterator>
	Iterator	insert( Iterator position, InputIterator iterator, Size count );	
	Iterator	remove( Iterator position, Size count=1 );
	void		clear( );

	Array		&operator=( const Array &array );

	ConstReference	operator[] ( Size index ) const;
	Reference	operator[]( Size index );

	void		resize( Size size );

	void		push( ConstReference value );
	Value		pop( );

private:
	Pointer		array_;
	Size		size_;
	Size		capacity_;
	Allocator	*allocator_;

	Size	nextPow2( Size n ) const;
	void	reserve( Size size );
};

#include "Array.cpp"

#endif
