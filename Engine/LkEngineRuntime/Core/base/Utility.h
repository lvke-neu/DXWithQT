#define SAFE_DELETE_SET_NULL(p) { if ((p)) { delete (p); (p) = nullptr; } } 

