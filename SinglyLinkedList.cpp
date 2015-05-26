template <typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::insert( Iterator position, ConstReference value )
{
	Node *newNode;

	newNode = (Node*)allocator_->allocate( sizeof(Node) );
	Memory<Node>::construct( newNode, value );

	if ( position.previous_ ) {
		position.previous_->next = newNode;
	}

	newNode->next = position.node_;

	if ( newNode->next == NULL ) {
		last_ = newNode;
	}
	if ( position.node_ == first_ ) {
		first_ = newNode;
	}
	++size_;
	return Iterator( newNode, position.previous_ );
}

template <typename T>
template <typename InputIterator>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::insert( Iterator position, InputIterator source, Size count )
{
	Size i;
	Iterator it;

	it = insert( position, *source++ );
	position = it;
	++position;
	--count;
	for ( i = 0; i < count; ++i ) {
		position = insert( position, *source++ );
		++position;		
	}
	return it;
}

template <typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::remove( Iterator position, Size count )
{
	Size i;
	Iterator it;

	for ( i = 0; i < count; ++i ) {
		if ( position.previous_ ) {
			position.previous_->next = position.node_->next;
		}
		if ( position.node_ == first_ ) {
			first_ = position.node_->next;
		}
		if ( position.node_ == last_ ) {
			last_ = position.previous_;
		}
		it = Iterator( position.node_->next, position.previous_ );
		Memory<Node>::destroy( position.node_ );
		allocator_->deallocate( position.node_ );
		position = it;
		--size_;
	}
	return it;
}

template <typename T>
void SinglyLinkedList<T>::clear( )
{
	Node *node, *next;
	for ( node = first_; node != NULL; node = next ) {
		next = node->next;
		Memory<Node>::destroy( node );
		allocator_->deallocate( node );
	}
	size_ = 0;
	first_ = NULL;
	last_ = NULL;
}

template <typename T>
void SinglyLinkedList<T>::unshift( ConstReference value )
{
	insert( begin(), value );
}

template <typename T>
typename SinglyLinkedList<T>::Value SinglyLinkedList<T>::shift( )
{
	Value value;
	Iterator it;
	
	it = begin();
	value = *it;
	remove( it );
	return value;
}

template <typename T>
SinglyLinkedList<T>	&SinglyLinkedList<T>::operator=( const SinglyLinkedList &list )
{
	ConstIterator it;

	for ( it = list.begin(); it != list.end(); ++it ) {
		insert( end(), *it );
	}
	return *this;
}
