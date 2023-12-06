#ifdef ZAJX_API_EXPORTS

#if defined(_MSC_VER)
#define ZAJX_API __declspec(dllexport) 
#else
#define ZAJX_API __attribute__((visibility("default")))
#endif

#else
	
#if defined(_MSC_VER)
#define ZAJX_API __declspec(dllimport) 
#else
#define ZAJX_API
#endif

#endif