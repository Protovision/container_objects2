#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "Allocator.h"
#include "Memory.h"

template <typename T>
class SinglyLinkedList {
public:
	typedef typename Memory<T>::Value		Value;
	typedef typename Memory<T>::Pointer		Pointer;
	typedef typename Memory<T>::ConstPointer	ConstPointer;
	typedef typename Memory<T>::Reference		Reference;
	typedef typename Memory<T>::ConstReference	ConstReference;
	typedef typename Memory<T>::Size		Size;

	class Node {
	public:
		Value	value;
		Node	*next;

		Node( ) : value(), next(NULL) {}
		Node( const Node &node ) : value(node.value), next(node.next) {}
		Node( ConstReference value_ ) : value(value_), next(NULL) {}
		Node	&operator=( const Node &node )
		{
			value = node.value;
			next = node.next;
			return *this;
		}
	};

	class Iterator {
		friend class SinglyLinkedList;
	private:
		Node	*node_;
		Node	*previous_;
	public:
		Iterator( ) : node_(NULL), previous_(NULL) {}
		Iterator( const Iterator &it ) : node_(it.node_), previous_(it.previous_) {}
		Iterator( Node *node, Node *previous ) : node_(node), previous_(previous) {}
		Reference	operator*( ) const	{ return node_->value; }
		Pointer		operator->( ) const	{ return &node_->value; }
		Iterator	&operator++( )
		{
			previous_ = node_;
			node_ = node_->next;
			return *this;
		}
		Iterator	operator++( int )
		{
			Iterator it( *this );
			operator++( );
			return it;
		}
		bool		operator==( const Iterator &it ) const
		{
			return node_ == it.node_;
		}
		bool		operator!=( const Iterator &it ) const
		{
			return node_ != it.node_;
		}
		Iterator	operator=( const Iterator &it )
		{
			node_ = it.node_;
			previous_ = it.previous_;
			return *this;
		}
	};
	class ConstIterator {
		friend class SinglyLinkedList;
	private:
		Node	*node_;
		Node	*previous_;
	public:
		ConstIterator( ) : node_(NULL), previous_(NULL) {}
		ConstIterator( const ConstIterator &it ) : node_(it.node_), previous_(it.previous_) {}
		ConstIterator( const Iterator &it ) : node_(it.node_), previous_(it.previous_) {}
		ConstIterator( Node *node, Node *previous ) : node_(node), previous_(previous) {}
		ConstReference	operator*( ) const	{ return node_->value; }
		ConstPointer	operator->( ) const	{ return &node_->value; }
		ConstIterator	&operator++( )
		{
			previous_ = node_;
			node_ = node_->next;
			return *this;
		}
		ConstIterator	operator++( int )
		{
			ConstIterator it( *this );
			operator++( );
			return it;
		}
		bool		operator==( const ConstIterator &it ) const
		{
			return node_ == it.node_;
		}
		bool		operator!=( const ConstIterator &it ) const
		{
			return node_ != it.node_;
		}
		ConstIterator	operator=( const ConstIterator &it )
		{
			node_ = it.node_;
			previous_ = it.previous_;
			return *this;
		}
	};
private:
	Size		size_;
	Node		*first_;
	Node		*last_;
	Allocator	*allocator_;
public:
	Size		size( ) const
	{
		return size_;
	}
	ConstIterator	begin( ) const
	{
		return ConstIterator( first_, NULL );
	}
	ConstIterator	end( ) const
	{
		return ConstIterator( NULL, last_ );
	}
	
	Iterator	begin( )
	{
		return Iterator( first_, NULL );
	}
	Iterator	end( )
	{
		return Iterator( NULL, last_ );
	}
	Iterator	insert( Iterator position, ConstReference value );
	template	<typename InputIterator>
	Iterator	insert( Iterator position, InputIterator source, Size count );
	Iterator	remove( Iterator position, Size count=1 );
	void		clear( );
	void		unshift( ConstReference value );
	Value		shift( );
	ConstReference	first( ) const
	{
		return first_->value;
	}
	Reference	first( )
	{
		return first_->value;
	}

	SinglyLinkedList	&operator=( const SinglyLinkedList &list );
	
	SinglyLinkedList( Allocator *allocator = &_default_allocator ) :
		allocator_(allocator), first_(NULL), last_(NULL), size_(0) {}
	SinglyLinkedList( const SinglyLinkedList &list ) :
		allocator_(list.allocator_), first_(NULL), last_(NULL), size_(0)
	{
		operator=( list );
	}
	~SinglyLinkedList( )
	{
		clear( );
	}

};

#include "SinglyLinkedList.cpp"

#endif
