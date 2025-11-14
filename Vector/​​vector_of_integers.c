#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define TRUE    1
#define FALSE   0

typedef int     GLint;
typedef int     status_t;
typedef struct  vector_int vector_int_t;

struct   vector_int
{
    int* p_array;
    int  size;
};

vector_int_t*   allocate_vector_int(void);
status_t        push_back_vector_int(vector_int_t* p_vec_int, int new_data);
void            show_vector_int(vector_int_t* p_vec_int);
status_t        release_vector_int(vector_int_t* p_vec_int);

int main(void)
{
    vector_int_t* vector_for_kb_ints = NULL;
    int choice;
    int num;

    vector_for_kb_ints = allocate_vector_int();

    while(TRUE)
    {
        printf("Do you want to enter one more integer? [1|0]:");
        scanf("%d", &choice);
        if(choice != 1)
        {
            break;
        }
        printf("Enter an integer:");
        scanf("%d", &num);
        push_back_vector_int(vector_for_kb_ints, num);
    }
    printf("byte size of vector %d\n", sizeof(GLint)*vector_for_kb_ints->size);
    printf("size of vector %d\n", vector_for_kb_ints->size);

    show_vector_int(vector_for_kb_ints);
    release_vector_int(vector_for_kb_ints);

    return (EXIT_SUCCESS);
}

// Definition of interface functions
vector_int_t* allocate_vector_int(void)
{
    vector_int_t* p_new_vector=NULL;
    p_new_vector = (vector_int_t*)malloc(sizeof(vector_int_t));
    if(NULL == p_new_vector)
    {
        fprintf(stderr, "malloc(): fatal: out of memory\n");
        exit(EXIT_FAILURE);
    }
        p_new_vector->p_array = NULL;
    p_new_vector->size = 0;

    return(p_new_vector);
}

status_t push_back_vector_int(vector_int_t* p_vec_int, int new_data)
{
    p_vec_int->p_array = (GLint*)realloc(p_vec_int -> p_array, (p_vec_int->size + 1) * sizeof(GLint));

    printf(" newly allocated size in byte %d\n", sizeof(GLint)*p_vec_int->size);

    if(NULL == p_vec_int->p_array)
    {
        fprintf(stderr, "realloc():fatal:out of memory\n");
        exit(EXIT_FAILURE);
    }

    p_vec_int-> size += 1;
    printf("%d\n", p_vec_int->size);
    p_vec_int->p_array[p_vec_int->size-1] = new_data;
    return (SUCCESS);
}

void show_vector_int(vector_int_t* p_vec_int)
{
    int i;
    for(i = 0; i < p_vec_int->size; ++i)
    {
        printf("p_vec_int->p_array[%d]:%d\n", i, p_vec_int->p_array[i]);
    }

}
status_t release_vector_int(vector_int_t* p_vec_int)
{
    free(p_vec_int->p_array);
    free(p_vec_int);
    return(SUCCESS);

}
