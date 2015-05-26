
template <typename T>
Array<T>::Array( Allocator *allocator ) : 
	array_(NULL), size_(0), capacity_(0), allocator_(allocator) {}

template <typename T>
Array<T>::Array( const Array &array ) :
	array_(NULL), size_(0), capacity_(0), allocator_(array.allocator_)
{
	operator=( array );
}

template <typename T>
Array<T>::~Array( )
{
	clear( );
	if ( array_ != NULL ) {
		allocator_->deallocate( array_ );
		array_ = NULL;
	}
}

template <typename T>
typename Array<T>::Size Array<T>::size( ) const
{
	return size_;
}

template <typename T>
typename Array<T>::ConstIterator Array<T>::begin( ) const
{
	return array_;
}

template <typename T>
typename Array<T>::ConstIterator Array<T>::end( ) const
{
	return array_ + size_;
}

template <typename T>
typename Array<T>::Iterator Array<T>::begin( )
{
	return array_;
}

template <typename T>
typename Array<T>::Iterator Array<T>::end( )
{
	return array_ + size_;
}

template <typename T>
typename Array<T>::Iterator Array<T>::insert( Iterator position, ConstReference value )
{
	Difference diff;
	
	diff = position - array_;
	reserve( size_ + 2 );
	position = array_ + diff;
	Memory<T>::move( position+1, position, array_+size_-position );
	Memory<T>::construct( position, value );
	++size_;
	return position;
}

template <typename T>
template <typename InputIterator>
typename Array<T>::Iterator Array<T>::insert( Iterator position, InputIterator iterator, Size count )
{
	Difference diff;

	diff = position - array_;
	reserve( size_ + count + 2 );
	position = array_ + diff;
	Memory<T>::move( position+count, position, count );
	Memory<T>::copy( position, iterator, count );
	size_ += count;
	return position;
}

template <typename T>
typename Array<T>::Iterator Array<T>::remove( Iterator position, Size count )
{
	Memory<T>::destroy( position, count );
	Memory<T>::move( position, position+count, array_+size_-(position+count) );
	size_ -= count;
	return position;
}

template <typename T>
void Array<T>::clear( )
{
	if ( array_ != NULL ) {
		Memory<T>::destroy( array_, size_ );
	}
	size_ = 0;
}

template <typename T>
typename Array<T>::Size Array<T>::nextPow2( Size n ) const
{
	n -= 1;
	n |= ( n >> 1 );
	n |= ( n >> 2 );
	n |= ( n >> 4 );
	n |= ( n >> 8 );
	n |= ( n >> 16 );
	return n + 1;
}

template <typename T>
void Array<T>::reserve( Size size )
{
	Size newCapacity;
	Pointer newArray;

	if ( size < capacity_ ) return;
	newCapacity = nextPow2( size );
	newArray = (Pointer)allocator_->allocate( newCapacity );
	Memory<T>::move( newArray, array_, size_ );
	allocator_->deallocate( array_ );
	array_ = newArray;
	capacity_ = newCapacity;	
}

template <typename T>
void Array<T>::resize( Size size )
{
	Size i;

	reserve( size );
	if ( size > size_ ) {
		Memory<T>::construct( array_+size_, typename Memory<T>::Value(), size-size_ );
	} else if ( size < size_ ) {
		Memory<T>::destroy( array_+size, size_-size );	
	}
	size_ = size;
}

template <typename T>
void Array<T>::push( ConstReference value )
{
	insert( end(), value );
}

template <typename T>
typename Array<T>::Value Array<T>::pop( )
{
	Value value;
	Iterator it;

	it = end( );
	value = *--it;
	remove( it );
	return value;
}

template <typename T>
typename Array<T>::Reference Array<T>::operator[]( Size index )
{
	return array_[index];
}

template <typename T>
typename Array<T>::ConstReference Array<T>::operator[]( Size index ) const
{
	return array_[index];
}
