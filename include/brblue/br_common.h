#ifndef __BR_COMMON_H
#define __BR_COMMON_H

#include <stdio.h> /* for convenience */
#include <stdlib.h> /* for convenience */
#include <stddef.h> /* for offsetof */
#include <string.h> /* for convenience */
#include <unistd.h> /* for convenience */
#include <signal.h> /* for SIG_ERR */

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
 
#ifndef container_of
#define container_of(ptr, type, member) ({   \
        const typeof( ((type *)0)->member ) *__mptr = (ptr); \
        (type *)( (char *)__mptr - offsetof(type,member) );})
#endif


#ifdef MEM_LEAK_CHECK
static inline void *_t_malloc(size_t size, const char *file, unsigned int line)
{
    void *ptr;
    if ((ptr = malloc (size)))
        memset (ptr, 0, size);
    printf ("MALLOC,0x%p @%s:%u\n", ptr, file, line);
    return ptr;
}

static inline void _t_free(void *ptr, const char *file, unsigned int line)
{
    printf ("FREE,0x%p @%s:%u\n", ptr, file, line);
    free(ptr);
}
#else
static inline void *_t_malloc(size_t size)
{
    void *ptr;
    if ((ptr = malloc (size)))
        memset (ptr, 0, size);
    return ptr;
}

static inline void _t_free(void *ptr)
{
    free(ptr);
}
#endif

#ifdef MEM_LEAK_CHECK
#define t_free(p)    if(p){ _t_free(p, __FILE__, __LINE__); p=NULL; }
#define t_malloc(s)  _t_malloc(s, __FILE__, __LINE__)
#else
#define t_free(p)    if(p){ _t_free(p); p=NULL; }
#define t_malloc(s)  _t_malloc(s)
#endif

#endif