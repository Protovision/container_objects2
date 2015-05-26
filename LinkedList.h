#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Allocator.h"
#include "Memory.h"

template <typename T>
class LinkedList {
public:
	typedef typename Memory<T>::Value		Value; 
	typedef	typename Memory<T>::Pointer		Pointer;
	typedef typename Memory<T>::Reference		Reference;
	typedef typename Memory<T>::ConstPointer	ConstPointer;
	typedef typename Memory<T>::ConstReference	ConstReference;
	typedef typename Memory<T>::Size		Size;

	class Node {
	public:
		Value	value;
		Node	*previous;
		Node	*next;

		Node( );
		Node( const Node &node );
		Node( ConstReference value );

		Node	&operator=( const Node &node );	
	};

	class Iterator {
		friend class LinkedList;
	private:
		Node	*node_;
	public:
		Iterator( ) : node_(NULL) {}
		Iterator( const Iterator &iterator ) : node_(iterator.node_) {}
		Iterator( Node *node ) : node_(node) {}
		Reference	operator*( ) const	{ return node_->value; }
		Pointer		operator->( ) const	{ return &node_->value; }
		Iterator	&operator++( )		{ node_ = node_->next; return *this; }
		Iterator	operator++( int )	{ Iterator it(node_); operator++(); return it; }
		Iterator	&operator--( )		{ node_ = node_->previous; return *this; }
		Iterator	operator--( int )	{ Iterator it(node_); operator--(); return it; }
		bool		operator==( const Iterator &iterator ) const	{ return node_ == iterator.node_; }
		bool		operator!=( const Iterator &iterator ) const	{ return node_ != iterator.node_; }
		Iterator	&operator=( const Iterator &iterator )		{ node_ = iterator.node_; return *this; }
	};

	class ConstIterator {
		friend class LinkedList;
	private:
		const Node *node_;
	public:
		ConstIterator( ) : node_(NULL) {}
		ConstIterator( const ConstIterator &iterator ) : node_(iterator.node_) {}
		ConstIterator( const Node *node ) : node_(node) {}
		ConstReference	operator*( ) const	{ return node_->value; }
		ConstPointer	operator->( ) const	{ return &node_->value; }
		ConstIterator	&operator++( )		{ node_ = node_->next; return *this; }
		ConstIterator	operator++( int )	{ ConstIterator it(node_); operator++(); return it; }
		ConstIterator	&operator--( )		{ node_ = node_->previous; return *this; }
		ConstIterator	operator--( int )	{ ConstIterator it(node_); operator--(); return it; }
		bool		operator==( const ConstIterator &iterator ) const	{ return node_ == iterator.node_; }
		bool		operator!=( const ConstIterator &iterator ) const	{ return node_ != iterator.node_; }
		ConstIterator	&operator=( const ConstIterator &iterator )		{ node_ = iterator.node_; return *this; }
	};

	LinkedList( Allocator *allocator = &_default_allocator );
	LinkedList( const LinkedList &list );
	~LinkedList( );

	Size		size( ) const;
	ConstIterator	begin( ) const;
	ConstIterator	end( ) const;

	Iterator	begin( );
	Iterator	end( );	
	Iterator	insert( Iterator position, ConstReference value );
	template	<typename InputIterator>
	Iterator	insert( Iterator position, InputIterator source, Size count=1 );
	Iterator	remove( Iterator position, Size count=1 );
	void		clear( );

	LinkedList	&operator=( const LinkedList &list );

private:
	Size		size_;
	Node		*begin_;
	Node		end_;
	Allocator	*allocator_;
};

#include "LinkedList.cpp"

#endif
