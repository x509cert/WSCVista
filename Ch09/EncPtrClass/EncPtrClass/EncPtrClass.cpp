#include "stdafx.h"

int main(void) {

char buf[2];

EncodedPointer ePtr;

ePtr.Set( buf );

if( ePtr.Get() == NULL )
	printf("Ptr is corrupt or NULL\n");
else
	printf("Valid!\n");
	return 0;
}