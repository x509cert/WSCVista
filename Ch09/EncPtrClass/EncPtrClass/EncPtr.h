class EncodedPointer
{
public:
   EncodedPointer() : m_pv( NULL ), m_pReference( NULL ){
   }

   void Set( void* pIn ) {
      m_pv = EncodePointer( pIn );
      m_pReference = MakeRefPtr( pIn );
   }

   void* Get() {
      if( m_pv == NULL )
         return NULL;

      void* pRet = DecodePointer( m_pv );
      
      // Now double-check for tampering
      if( MakeRefPtr( pRet ) != m_pReference )
         return NULL;

      return pRet;
   }

#ifdef _DEBUG
   // testing only 
   void Corrupt() {
	   m_pv = (void*)((char*)m_pv + 1);
   }
#endif

private:
	void* MakeRefPtr( void* pIn ){
		return reinterpret_cast< void* >( 
			   reinterpret_cast< size_t >( pIn ) ^ 
			   reinterpret_cast< size_t >( this ) );
	}

	void* m_pv;
	void* m_pReference;
};
