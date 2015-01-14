#ifdef UNDONE_EXPORTS
#define UNDONE_API __declspec(dllexport) 
#else
#define UNDONE_API __declspec(dllimport) 
#endif
