#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include "LinkedList.h"

template <typename T>
LinkedList<T>::Node::Node( ) : value( ), previous( NULL ), next( NULL ) {}

template <typename T>
LinkedList<T>::Node::Node( const Node &node ) :
	value( node.value ), previous( node.previous ), next( node.next ) {}

template <typename T>
LinkedList<T>::Node::Node( ConstReference _value ) :
	value( _value ), previous( NULL ), next( NULL ) {}

template <typename T>
typename LinkedList<T>::Node &LinkedList<T>::Node::operator=( const Node &node )
{
	value = node.value;
	previous = node.previous;
	next = node.next;
	return *this;
}

template <typename T>
void LinkedList<T>::clear( )
{
	Node *node, *next;

	node = begin_;
	if ( node == NULL ) node = &end_;
	for ( ; node != &end_; node = next ) {
		next = node->next;
		Memory<Node>::destroy( node );
		allocator_->deallocate( node );
	}

	begin_ = NULL;
	end_ = Node( );
	size_ = 0;
}

template <typename T>
LinkedList<T>::LinkedList( Allocator *allocator ) :
	size_( 0 ), begin_( NULL ), end_( ), allocator_( allocator ) {}

template <typename T>
LinkedList<T>::LinkedList( const LinkedList &list ) :
	size_( 0 ), begin_( NULL ), end_( ), allocator_( list.allocator_ )
{
	operator=( list );
}

template <typename T>
LinkedList<T>::~LinkedList( )
{
	clear( );
}

template <typename T>
typename LinkedList<T>::Size LinkedList<T>::size( ) const
{
	return size_;
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::begin( ) const
{
	if ( begin_ == NULL ) return ConstIterator( &end_ );
	return ConstIterator( begin_ );
}

template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::end( ) const
{
	return ConstIterator( &end_ );
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin( )
{
	if ( begin_ == NULL ) return Iterator( &end_ );
	return Iterator( begin_ );
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end( )
{
	return Iterator( &end_ );
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::insert( Iterator position, ConstReference value )
{
	Node *node, *newNode;

	node = position.node_;
	if ( node == NULL ) node = &end_;

	newNode = (Node*)allocator_->allocate( sizeof(Node) );
	Memory<Node>::construct( newNode, value );

	if ( node->previous != NULL ) {
		newNode->previous = node->previous;
		newNode->previous->next = newNode;
	} else {
		newNode->previous = NULL;
		begin_ = newNode;
	}

	newNode->next = node;
	newNode->next->previous = newNode;

	++size_;

	return Iterator( newNode );
}

template <typename T>
template <typename InputIterator>
typename LinkedList<T>::Iterator LinkedList<T>::insert( Iterator position, InputIterator iterator, Size count )
{
	Size i;
	Iterator it;

	it = insert( position, *iterator++ );
	--count;
	for ( i = 0; i < count; ++i ) {
		insert( position, *iterator++ );
	}
	return it;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::remove( Iterator position, Size count )
{
	Size i;
	Node *node, *next;

	node = position.node_;
	for ( i = 0; i < count; ++i ) {
		if ( node->previous != NULL ) {
			node->previous->next = node->next;
		} else {
			begin_ = node->next;
		}
		if ( node->next != NULL ) {
			node->next->previous = node->previous;
			next = node->next;
		} else {
			end_.previous = node->previous;
			next = &end_;
		}
		Memory<Node>::destroy( node );
		allocator_->deallocate( node );
		--size_;
	}
	return Iterator( next );
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=( const LinkedList &list )
{
	ConstIterator it, end_it;

	clear( );
	it = list.begin( );
	end_it = list.end( );
	while ( it != end_it ) {
		insert( end(), *it++ );
	}

	return *this;	
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::push( ConstReference value )
{
	return insert( end(), value );
}

template <typename T>
typename LinkedList<T>::Value LinkedList<T>::pop( )
{
	Value value;
	Iterator it;

	it = end( );
	value = *--it;
	remove( it );
	return value;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::unshift( ConstReference value )
{
	return insert( begin(), value );
}

template <typename T>
typename LinkedList<T>::Value LinkedList<T>::shift( )
{
	Value value;
	Iterator it;

	it = begin( );
	value = *it;
	remove( it );
	return value;
}

template <typename T>
typename LinkedList<T>::Reference LinkedList<T>::first( )
{
	return *begin( );
}

template <typename T>
typename LinkedList<T>::ConstReference LinkedList<T>::first( ) const
{
	return *begin( );
}

template <typename T>
typename LinkedList<T>::Reference LinkedList<T>::last( )
{
	return *--end( );
}

template <typename T>
typename LinkedList<T>::ConstReference LinkedList<T>::last( ) const
{
	return *--end( );
}

#endif
