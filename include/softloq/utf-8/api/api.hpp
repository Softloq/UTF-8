#ifndef SOFTLOQ_UTF_8_API_HPP
#define SOFTLOQ_UTF_8_API_HPP

#if   defined(SOFTLOQ_UTF_8_STATIC)
    #define SOFTLOQ_UTF_8_API
#elif defined(SOFTLOQ_UTF_8_EXPORTS)
    #define SOFTLOQ_UTF_8_API SOFTLOQ_UTF_8_EXPORT
#elif defined(SOFTLOQ_UTF_8_IMPORTS)
    #define SOFTLOQ_UTF_8_API SOFTLOQ_UTF_8_IMPORT
#endif

#ifndef SOFTLOQ_UTF_8_API
    #if   defined(SOFTLOQ_EXPORTS)
        #define SOFTLOQ_UTF_8_API SOFTLOQ_UTF_8_EXPORT
    #elif defined(SOFTLOQ_IMPORTS)
        #define SOFTLOQ_UTF_8_API SOFTLOQ_UTF_8_IMPORT
    #else
        #define SOFTLOQ_UTF_8_API
    #endif
#endif

#endif // SOFTLOQ_UTF_8_API_HPP