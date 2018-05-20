#ifndef __BR_VECTOR_H
#define __BR_VECTOR_H

typedef struct _BR_VECTOR
{
    int size;
    int used;
    void **mem;
} BR_VECTOR;

#define br_vector_count(v)  ((v) ? (v)->used : 0)
#define br_vector_size(v)  ((v) ? (v)->size : 0)
 
BR_VECTOR *br_vector_init(int size);
void *br_vector_add(BR_VECTOR *vector, int index, void *item);
void *br_vector_del(BR_VECTOR *vector, int index);
void *br_vector_get(BR_VECTOR *vector, int index);
int br_vector_destroy(BR_VECTOR *vector);

#endif