#ifdef PROJECT_API_EXPORTS

#if defined(_MSC_VER)
#define PROJECT_API __declspec(dllexport) 
#else
#define PROJECT_API __attribute__((visibility("default")))
#endif

#else
	
#if defined(_MSC_VER)
#define PROJECT_API __declspec(dllimport) 
#else
#define PROJECT_API
#endif

#endif
