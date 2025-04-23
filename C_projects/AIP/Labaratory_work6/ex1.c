#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LENGTH 100

// Структура для издательства
struct Publisher {
    char name[MAX_STR_LENGTH];
    int year;
    char city[MAX_STR_LENGTH];
};

// Структура для книги
struct Book {
    char title[MAX_STR_LENGTH];
    float price;
    int num_pages;
    char author[MAX_STR_LENGTH];
    struct Publisher publisher;
};

// Прототипы функций
void findCitiesWithMaxPublishers(struct Book *books, int numBooks);
void inputBook(struct Book *book);
void inputFloat(const char *prompt, float *value);
void inputNumber(const char *prompt, int *value);
void inputString(const char *prompt, char *buffer, int maxLength);

int main() {
    int numBooks;
    inputNumber("Enter the number of books: ", &numBooks);

    // Динамическое выделение памяти под массив книг
    struct Book *books = malloc(numBooks * sizeof(struct Book));
    if (books == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Ввод данных о книгах
    for (int i = 0; i < numBooks; i++) {
        printf("\nEnter details for book %d:\n", i + 1);
        inputBook(&books[i]);
    }

    // Поиск городов с максимальным числом уникальных издательств
    findCitiesWithMaxPublishers(books, numBooks);

    // Освобождаем память, выделенную под массив книг
    free(books);

    return 0;
}

// Функция для поиска городов с максимальным числом уникальных издательств
void findCitiesWithMaxPublishers(struct Book *books, int numBooks) {
    struct CityPublishers {
        char city[MAX_STR_LENGTH];
        char publishers[MAX_STR_LENGTH][MAX_STR_LENGTH];
        int count;
    } *cityPublishers;

    int numCities = 0;

    // Выделяем память под словарь городов
    cityPublishers = malloc(numBooks * sizeof(struct CityPublishers));
    if (cityPublishers == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Проходим по всем книгам
    for (int i = 0; i < numBooks; i++) {
        char *currentCity = books[i].publisher.city;
        char *currentPublisher = books[i].publisher.name;

        // Ищем город в словаре
        int cityIndex = -1;
        int j = 0;
        while (j < numCities && cityIndex == -1) {
            if (strcmp(cityPublishers[j].city, currentCity) == 0) {
                cityIndex = j;
            }
            j++;
        }

        // Если город не найден, добавляем его в словарь
        if (cityIndex == -1) {
            strcpy(cityPublishers[numCities].city, currentCity);
            cityPublishers[numCities].count = 0;
            cityIndex = numCities;
            numCities++;
        }

        // Проверяем, есть ли издательство уже в списке
        int publisherExists = 0;
        int k = 0;
        while (k < cityPublishers[cityIndex].count && !publisherExists) {
            if (strcmp(cityPublishers[cityIndex].publishers[k], currentPublisher) == 0) {
                publisherExists = 1;
            }
            k++;
        }

        // Если издательство не найдено, добавляем его
        if (!publisherExists) {
            strcpy(cityPublishers[cityIndex].publishers[cityPublishers[cityIndex].count], currentPublisher);
            cityPublishers[cityIndex].count++;
        }
    }

    // Находим максимальное количество уникальных издательств
    int maxPublishers = 0;
    for (int i = 0; i < numCities; i++) {
        if (cityPublishers[i].count > maxPublishers) {
            maxPublishers = cityPublishers[i].count;
        }
    }

    // Выводим города с максимальным количеством уникальных издательств
    printf("Cities with the maximum number of unique publishers (%d):\n", maxPublishers);
    for (int i = 0; i < numCities; i++) {
        if (cityPublishers[i].count == maxPublishers) {
            printf("- %s\n", cityPublishers[i].city);
        }
    }

    // Освобождаем память, выделенную под словарь городов
    free(cityPublishers);
}

// Функция для ввода строки с проверкой на пустую строку
void inputString(const char *prompt, char *buffer, int maxLength) {
    while (1) {
        printf("%s", prompt);
        if (scanf("%99s", buffer) == 1) {  // Ограничение на длину строки
            break;
        }
    }
}

// Функция для ввода числа с проверкой на корректность
void inputNumber(const char *prompt, int *value) {
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", value) == 1) {
            break;
        }
        // Очистка буфера ввода в случае ошибки
        while (getchar() != '\n');
    }
}

// Функция для ввода числа с плавающей точкой с проверкой на корректность
void inputFloat(const char *prompt, float *value) {
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", value) == 1) {
            break;
        }
        // Очистка буфера ввода в случае ошибки
        while (getchar() != '\n');
    }
}

// Функция для ввода данных о книге
void inputBook(struct Book *book) {
    inputString("Enter book title: ", book->title, MAX_STR_LENGTH);
    inputFloat("Enter book price: ", &book->price);
    inputNumber("Enter number of pages: ", &book->num_pages);
    inputString("Enter book author: ", book->author, MAX_STR_LENGTH);
    inputString("Enter publisher name: ", book->publisher.name, MAX_STR_LENGTH);
    inputNumber("Enter publisher year: ", &book->publisher.year);
    inputString("Enter publisher city: ", book->publisher.city, MAX_STR_LENGTH);
}