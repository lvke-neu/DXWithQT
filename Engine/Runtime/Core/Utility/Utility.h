#define SAFE_DELETE_SETNULL(p)              \
{	                                        \
    if((p))                                   \
    {                                       \
		delete (p);                           \
        (p)=nullptr;                          \
     }                                      \
}


