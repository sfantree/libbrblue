#include "brblue/br_vector.h"
#include "brblue/br_common.h"

BR_VECTOR* br_vector_init(int size)
{
    BR_VECTOR* vector = NULL;
    if(size < 0)
    {
        return NULL;
    }
    vector = (BR_VECTOR *)t_malloc(sizeof(BR_VECTOR));
    if(!vector)
    {
        return NULL;
    }
    
    vector->mem = t_malloc(size*sizeof(void *));
    if(!vector->mem)
    {
        t_free(vector);
        return NULL;
    }
    memset(vector->mem, 0, size);
    
    vector->size = size;
    vector->used = 0;
    
    return vector;
}

void* br_vector_add(BR_VECTOR *vector, int index, void *item)
{
    if(index<0 || index>vector->size)
        return NULL;
 
    vector->mem[index]=item;
    vector->used++;

    return item;
}

void* br_vector_del(BR_VECTOR *vector, int index)
{
    void *save;
    if(index<0 ||index>vector->size)
        return NULL;
    save = vector->mem[index];
    vector->mem[index]=NULL;
    vector->used--;
    return save;
}

void* br_vector_get(BR_VECTOR *vector, int index)
{
    if(index<0 ||index>vector->size)
        return NULL;
    return vector->mem[index];
}

int br_vector_destroy(BR_VECTOR *vector)
{
    if(!vector)
       return 1;
    if(vector->mem)
    {
        t_free(vector->mem);
    }
    t_free(vector);
    return 0;
}

