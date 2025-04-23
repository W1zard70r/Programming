#include <stdio.h>
#include <stdlib.h>

// Структура узла списка
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Функция для создания нового узла
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Функция для добавления элемента в стек (LIFO)
void push(Node** top, int data) {
    Node* new_node = create_node(data);
    new_node->next = *top;
    *top = new_node;
}

// Функция для удаления элементов, меньших или равных X
void remove_less_than(Node** head, int X) {
    Node *current = *head, *prev = NULL;
    while (current) {
        if (current->data <= X) {
            Node* temp = current;
            if (prev) {
                prev->next = current->next;
            } else {
                *head = current->next;
            }
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// Функция для формирования нового стека из четных элементов
Node* filter_even(Node* head) {
    Node* even_stack = NULL;
    while (head) {
        if (head->data % 2 == 0) {
            push(&even_stack, head->data);
        }
        head = head->next;
    }
    return even_stack;
}

// Функция для чтения данных из файла и формирования стека
Node* read_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("There's no file with name %s", filename);
        exit(1);
    }
    Node* stack = NULL;
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        push(&stack, num);
    }
    fclose(file);
    return stack;
}

// Функция для записи списка в файл
void write_to_file(const char* filename, Node* head) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        exit(1);
    }
    while (head) {
        fprintf(file, "%d\n", head->data);
        head = head->next;
    }
    fclose(file);
}

// Функция для вывода стека на экран
void print_stack(Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Функция для очистки памяти
void free_list(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    char input_filename[100], output_filename[100];
    int X;
    
    printf("Enter the name of Input File: ");
    scanf("%99s", input_filename);
    printf("Enter the name of Output File: ");
    scanf("%99s", output_filename);
    printf("Enter the value of X: ");
    scanf("%d", &X);

    Node* stack = read_from_file(input_filename);
    print_stack(stack);

    remove_less_than(&stack, X);
    if (stack)
    {
        print_stack(stack);

        Node* even_stack = filter_even(stack);
        if (even_stack)
        {
            write_to_file(output_filename, even_stack);
            print_stack(even_stack);    
        }
        else
        {
            printf("All elements of new linked list aren't even");
            write_to_file(output_filename, stack);    
        }
        free_list(even_stack);
    }
    else
    {
        printf("All elements of linked list are lower then X\n");
        printf("The output-file with name %s wasn't created", output_filename);
    }
    free_list(stack);
    return 0;
}
