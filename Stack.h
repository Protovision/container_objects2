#ifndef STACK_H
#define STACK_H

#include "SinglyLinkedList.h"

template <typename T, typename Container = SinglyLinkedList<T> >
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
		return *container_.begin();
	}

	Reference	peek( )
	{
		return *container_.begin();
	}

	void		push( ConstReference value )
	{
		container_.insert( container_.begin(), value );
	}

	Value		pop( )
	{
		Value value;
		typename Container::Iterator it;

		it = container_.begin( );
		value = *it;
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
