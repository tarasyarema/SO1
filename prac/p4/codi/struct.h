#include <stddef.h>
#include <unistd.h>

#define DEBUG 0
#if DEBUG
#  define eprint(x ...) fprintf(stderr, x)
#else
#  define eprint(x ...) do {} while (0)
#endif

#define SIZE_META_DATA  sizeof(struct m_meta_data)
typedef struct m_meta_data *p_meta_data;

/* This structure has a size multiple of 8 */

struct m_meta_data {
    size_t  size_bytes;
    int     available;
    int     magic;
    p_meta_data next;
    p_meta_data previous;
};




