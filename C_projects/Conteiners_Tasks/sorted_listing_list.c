#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node* next;
};
typedef struct node node;

node* create_LL(int arr[], int n, int i) //создаёт узлы с значениями массива, возвращает указатель на первый узел
{
    if (i == n)
        return NULL;
    node* pointer_head = malloc(sizeof(node));
    pointer_head->value = arr[i];
    pointer_head->next = create_LL(arr, n, i + 1);
    return pointer_head;
}

void* clear_LL(node* head) //чистит узлы после данного до узла с NULL
{
    if (head->next != NULL)
        {
        clear_LL(head->next);
        if (head->next->next == NULL)
            free(head->next);
            head->next = NULL;
        }
}

void full_clear_LL(node* head) //чистит данный узел и узлы после данного до узла с NULL
{
    clear_LL(head);
    free(head);
    head = NULL;
}

void print_LL(node* head) //вывод в консоль
{
    node *iterhead = head;
    for(; iterhead->next != NULL;)
    {
         printf("value = %d, next* = %p\n",iterhead->value, iterhead->next);
         iterhead = iterhead->next;
    }
    printf("value = %d, next* = %p\n",iterhead->value, iterhead->next);
}

void delete_dublicates(node* head) //удаление дубликатов
{
    node* first = head;
    node* second = head->next;
    node* previous_second = head;

    //если между first и second есть дубликаты, то мы отвяжем их и отчистим память, затем свяжем first и second

    while(second->next != NULL)
    {
        if (first->value == second->value)
        {
            second = second->next;
            previous_second = previous_second->next;
        }
        else
        {
            if (previous_second == first)
            {
                first = second;
                previous_second = second;
                second = second->next;
            }
            else
            {
                previous_second->next = NULL;
                clear_LL(first);
                first->next = second;

                first = second;
                previous_second = second;
                second = second->next;
            }
        }
    }

    if (first->value == second->value)
    {
        clear_LL(first);
    }
    else
    {
        if (previous_second != first)
        {
            previous_second->next = NULL;
            clear_LL(first);
            first->next = second;
        }
    }
}

void reversing(node* first, node* second, node** head)
{
    //рекурсивно сначала удаляет связи, затем добавляет в обратном порядке
    first->next = NULL;
    if (second->next != NULL)
    {
        reversing(second, second->next, head);
    }
    else
    {
        *head = second;
    }
    second->next = first;
}

node* reverse_LL(node* head)
{
    node* new_head = head;
    reversing(head, head->next, &new_head);
    return new_head;
}

int main()
{
    const int n = 10;
    int arr[10] = {2,2,2,3,4,4,6,6,6,10};
    node* head = create_LL(arr, n, 0);

    printf("head = %p\n", head);
    print_LL(head);

    delete_dublicates(head);
    head = reverse_LL(head);

    printf("\n");
    printf("head = %p\n", head);
    print_LL(head);


    full_clear_LL(head);

    return 0;
}












//int main()
//{
//    int *a = 41;
//    return 0;
//
//}











