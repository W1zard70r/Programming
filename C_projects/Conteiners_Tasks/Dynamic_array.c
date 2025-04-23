#include <stdio.h>
#include <stdlib.h>

typedef int T;

struct Array
{
    T* head;
    int size;
    int capacity;
};

typedef struct Array array;

void __try_increase_capacity(array* a) //увеличивает capacity в два раза, если size + 1 больше capacity
{
    if (a->size + 1 > a->capacity)
    {
        a->capacity *= 2;
        a->head = realloc(a->head, a->capacity * sizeof(void*));
    }
}

void __try_decrease_capacity(array* a) //уменьшает capacity, если size -1 меньше capacity в 4 раза
{
    if (a->size == 1)
    {
     free(a->head);
     a->head = NULL;
     a->capacity = 2;
    }
    else if (a->capacity / 4 >= a->size)
    {
        a->capacity /= 2;
        a->head = realloc(a->head, a->capacity * sizeof(void*));
    }
}


int get(array *a, size_t index) //получить значение по индексу index
{
    if (index >= a->size || index < 0)
        return NULL; //не особо придумал как разыграть ошибку
    return *(a->head+index);
}

void set(array *a, size_t index, T value) //изменить значение по индексу index на value
{
    if (index >= a->size || index < 0)
        return; //ничего не меняем
    *(a->head+index) = value;
}

void append(array* a, T value)
{
    __try_increase_capacity(a);

    *(a->head + a->size) = value;
    (a->size)++;
}

void delete(array* a) //удаление элемента с конца массива
{
    if (a->size == 0)
        return;

    __try_decrease_capacity(a);
    (a->size)--;
}

void insert(array* a, int index, T value)// вставить элемент на место index
{
    //примечание: если индекс вставки > длинны массива элемант вставляется в конец
    // можно конечно увеличивать динамически массив до данной величины, но думаю, что глупо хранить элементы массива не подряд, а фиг знает где.

    __try_increase_capacity(a);

    index = index > a->size ? a->size : index;

    for(int i = a->size - 1; i >= index; i--)
    {
        *(a->head + i + 1) = *(a->head + i);
    }

    *(a->head + index) = value;
    (a->size)++;
}

void array_remove(array* a, size_t index) //удалить элемент с индексом index (не удалось назвать функцию remove)
{
    if (a->size == 0)
        return;

    __try_decrease_capacity(a);

    index = index > a->size ? a->size : index;
    for(int i = index + 1; i < a->size; i++)
    {
        *(a->head + i - 1) = *(a->head + i);
    }
    (a->size)--;
}


int main()
{
    array Massiv1;
    size_t array_size = 4;

    Massiv1.size = array_size;
    Massiv1.capacity = array_size * 2;
    Massiv1.head = malloc(Massiv1.capacity * sizeof(void*));

    for(size_t i = 0; i < Massiv1.size; i++)
    {
        *(Massiv1.head + i) = i * i + 2;
    }

    for(size_t i = 0; i < Massiv1.size; i++)
    {
        printf("%d \t",*(Massiv1.head + i));
    }

//проверка get
//    printf("\n%d\n",get(&Massiv1, 0));

//проверка set
//    set(&Massiv1, 4, 52);
//    printf("\n");

//проверка delete
//    printf("\nsize = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    delete(&Massiv1);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    delete(&Massiv1);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    delete(&Massiv1);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    delete(&Massiv1);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);

//проверка append

//    printf("\nsize = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    append(&Massiv1, 3);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    append(&Massiv1, 4);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    append(&Massiv1, 6);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    append(&Massiv1, 7);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);


//проверка insert
//    printf("\nsize = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    insert(&Massiv1, 0, 52);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    insert(&Massiv1, 4, 12);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    insert(&Massiv1, 6, 32);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);

//проверка array_remove = remove
//    printf("\nsize = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    array_remove(&Massiv1, 0);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    array_remove(&Massiv1, 4);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);
//    array_remove(&Massiv1, 99);
//    printf("size = %d, capacity = %d\n", Massiv1.size, Massiv1.capacity);

    for(size_t i = 0; i < Massiv1.size; i++)
    {
        printf("%d \t",*(Massiv1.head + i));
    }

    free(Massiv1.head);
    return 0;
}
