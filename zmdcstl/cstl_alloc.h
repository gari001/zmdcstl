#ifndef MYCSTL_ALLOC_H
#define MYCSTL_ALLOC_H

#include <stddef.h>
#include <stdlib.h>

#include "cstl_def.h"
#include "eaplatform.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef CSTL_ALIGN_OF
#if   defined(_MSC_VER) && (_MSC_VER < 1700)
    // Workaround for this VS 2010 compiler bug: https://connect.microsoft.com/VisualStudio/feedback/details/682695
#define CSTL_ALIGN_OF(...) ( (sizeof(__VA_ARGS__)*0) + (__alignof(__VA_ARGS__)) )
#elif !defined(__GNUC__) || (__GNUC__ >= 3) // GCC 2.x doesn't do __alignof correctly all the time.
#define CSTL_ALIGN_OF __alignof
#else
#define CSTL_ALIGN_OF(type) ((size_t)offsetof(struct{ char c; type m; }, m))
#endif
#endif

#ifndef NDEBUG
#define cstl_alloc(type, n) cstl_alloc_(__FILE__,__LINE__,((size_t)(sizeof(type)*n)),CSTL_ALIGN_OF(type))
#define cstl_alloc_ex(elesize,align,n) cstl_alloc_(__FILE__,__LINE__,((size_t)(elesize*n)),(align))
#else
#define cstl_alloc(type, n) cstl_alloc_(0,0,((size_t)(n)),CSTL_ALIGN_OF(type))
#define cstl_alloc_ex(elesize,align,n) cstl_alloc_(0,0,((size_t)(elesize*n)),(align))
#endif

#define cstl_free(p) free(*((void**) p - 1))

extern void* cstl_alloc_(const char* file, int line, size_t n, size_t alignment);

#ifdef __cplusplus
}
#endif

#endif
