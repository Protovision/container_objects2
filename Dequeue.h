#ifndef DEQUEUE_H
#define DEQUEUE_H

#include "LinkedList.h"

template <typename T, typename Container = LinkedList<T> >
class Dequeue {
private:
	Container	container_;
public:
	typedef typename Container::Value		Value;
	typedef typename Container::Reference		Reference;
	typedef typename Container::ConstReference	ConstReference;
	typedef typename Container::Size		Size;

	Dequeue( ) : container_() {}
	Dequeue( const Dequeue &dequeue ) : container_(dequeue.container_) {}

	Size		size( ) const
	{
		return container_.size( );
	}

	ConstReference	first( ) const
	{
		return *container_.begin( );
	}

	ConstReference	last( ) const
	{
		typename Container::Iterator it;

		it = container_.end();
		return *--it;
	}

	Reference	first( )
	{
		return *container_.begin( );
	}

	Reference	last( )
	{
		typename Container::Iterator it;

		it = container_.end();
		return *--it;
	}

	void		push( ConstReference value )
	{
		container_.insert( container_.begin(), value );
	}

	void		inject( ConstReference value )
	{
		container_.insert( container_.end(), value );
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

	Value		eject( )
	{
		Value value;
		typename Container::Iterator it;

		it = container_.end( );
		value = *--it;
		container_.remove( it );
		return value;
	}

	Dequeue &operator=( const Dequeue &dequeue )
	{
		container_ = dequeue.container_;
		return *this;
	}
};

#endif
