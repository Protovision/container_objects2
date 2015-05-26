#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

template <typename T, typename Container = LinkedList<T> >
class Queue {
private:
	Container	container_;
public:
	typedef typename Container::Value		Value;
	typedef typename Container::Reference		Reference;
	typedef typename Container::ConstReference	ConstReference;
	typedef typename Container::Size		Size;

	Queue( ) : container_() {}
	Queue( const Queue &queue ) : container_(queue.container_) {}

	Size		size( ) const
	{
		return container_.size( );
	}

	ConstReference	peek( ) const
	{
		typename Container::Iterator it;

		it = container_.end();
		return *--it;
	}

	Reference	peek( )
	{
		typename Container::Iterator it;

		it = container_.end();
		return *--it;
	}

	void		push( ConstReference value )
	{
		container_.insert( container_.begin(), value );
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

	Queue		&operator=( const Queue &queue )
	{
		container_ = queue.container_;
		return *this;
	}

};

#endif
