#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

template <typename T, typename Container = LinkedList<T> >
class Stack {
private:
	Container	container_;
public:
	typedef typename Container::Value		Value;
	typedef typename Container::Reference		Reference;
	typedef typename Container::ConstReference	ConstReference;
	typedef typename Container::Size		Size;

	Stack( ) : container_() {}
	Stack( const Stack &stack ) : container_(stack.container_) {}

	Size		size( ) const
	{
		return container_.size( );
	}

	ConstReference	peek( ) const
	{
		typename Container::ConstIterator it;

		it = container_.end( );
		return *--it;
	}

	Reference	peek( )
	{
		typename Container::Iterator it;

		it = container_.end( );
		return *--it;
	}

	void		push( ConstReference value )
	{
		container_.insert( container_.end(), value );
	}

	Value		pop( )
	{
		Value value;
		typename Container::Iterator it;

		it = container_.end( );
		value = *--it;
		container_.remove( it );
		return value;
	}
	
	Stack	&operator=( const Stack &stack )
	{
		container_ = stack.container_;	
		return *this;
	}
};

#endif
