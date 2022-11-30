namespace Twinkle
{

    #define SAFE_DELETE_SETNULL(p)              \
    {	                                        \
        if((p))                                   \
        {                                       \
		    delete (p);                           \
            (p)=nullptr;                          \
         }                                      \
    }

    #define SAFE_RELEASE(p)              \
    {	                                        \
        if((p))                                   \
        {                                       \
	        (p)->Release();                          \
        }\
    }

}

