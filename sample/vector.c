#include "brblue/br_vector.h"
#include "brblue/br_common.h"

int main(int argc, char **argv)
{
    int i = 0;
    int n = 0;
    int num[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    int *p = num;
    BR_VECTOR* v = br_vector_init(1024);
    
    for (i = 0; i < 10; i++)
    {
        br_vector_add(v, i, p+i);
    }
    
    n = br_vector_count(v);
    
    for (i = 0; i < n; i++)
    {
        p = (int *)br_vector_get(v, i);
        printf("%d: %d %p\n", i, *p, p);
    }
    br_vector_destroy(v);
    return 0;
}