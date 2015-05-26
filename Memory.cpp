
template <typename T>
void Memory<T>::construct( Pointer memory, ConstReference value, Size count )
{
	Size i;
	for ( i = 0; i < count; ++i ) {
		new (memory + i) Value( value );
	}
}

template <typename T>
void Memory<T>::destroy( Pointer memory, Size count )
{
	Size i;
	for ( i = 0; i < count; ++i ) {
		(memory + i)->~Value( );
	}
}

template <typename T>
template <typename InputIterator>
void Memory<T>::copy( Pointer destination, InputIterator source, Size count )
{
	Size i;
	if ( count == 0 ) return;
	for ( i = 0; i < count; ++i ) {
		construct( destination++, *source++ );
	}
}

template <typename T>
void Memory<T>::move( Pointer destination, Pointer source, Size count )
{
	Size i;

	if ( count == 0 ) return;
	if ( destination < source ) {
		for ( i = 0; i < count; ++i ) {
			construct( destination++, *source );
			destroy( source++ );	
		}
	} else if ( destination > source ) {
		source = source + count - 1;
		destination = destination + count - 1;
		for ( i = 0; i < count; ++i ) {
			construct( destination--, *source );
			destroy( source-- );
		}			
	} 
}
