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
void findCitiesWithMaxPublishers(struct Book *books, int numBooks, const char *outputFilename);
void readBooksFromFile(struct Book **books, int *numBooks, const char *filename);
void writeResultToFile(const char *filename, const char *result);

int main() {
    const char *inputFilename = "data.txt";  // Фиксированное имя входного файла
    const char *outputFilename = "result.txt";  // Фиксированное имя выходного файла

    // Чтение данных из файла
    struct Book *books = NULL;
    int numBooks = 0;
    readBooksFromFile(&books, &numBooks, inputFilename);

    if (books == NULL) {
        printf("Failed to read books from the file.\n");
        return 1;
    }

    // Поиск городов с максимальным числом уникальных издательств и запись результата в файл
    findCitiesWithMaxPublishers(books, numBooks, outputFilename);

    // Освобождаем память, выделенную под массив книг
    free(books);

    printf("Result saved to %s\n", outputFilename);

    return 0;
}

// Функция для поиска городов с максимальным числом уникальных издательств и записи результата в файл
void findCitiesWithMaxPublishers(struct Book *books, int numBooks, const char *outputFilename) {
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

    // Формируем результат
    char result[MAX_STR_LENGTH * 10];  // Буфер для результата
    snprintf(result, sizeof(result), "Cities with the maximum number of unique publishers (%d):\n", maxPublishers);
    for (int i = 0; i < numCities; i++) {
        if (cityPublishers[i].count == maxPublishers) {
            strcat(result, "- ");
            strcat(result, cityPublishers[i].city);
            strcat(result, "\n");
        }
    }

    // Записываем результат в файл
    writeResultToFile(outputFilename, result);

    // Освобождаем память, выделенную под словарь городов
    free(cityPublishers);
}

// Функция для чтения данных о книгах из файла
void readBooksFromFile(struct Book **books, int *numBooks, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    // Читаем количество книг
    fscanf(file, "%d", numBooks);
    *books = malloc(*numBooks * sizeof(struct Book));
    if (*books == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    // Читаем данные о каждой книге
    for (int i = 0; i < *numBooks; i++) {
        fscanf(file, " %[^\n]", (*books)[i].title);
        fscanf(file, "%f", &(*books)[i].price);
        fscanf(file, "%d", &(*books)[i].num_pages);
        fscanf(file, " %[^\n]", (*books)[i].author);
        fscanf(file, " %[^\n]", (*books)[i].publisher.name);
        fscanf(file, "%d", &(*books)[i].publisher.year);
        fscanf(file, " %[^\n]", (*books)[i].publisher.city);
    }

    fclose(file);
}

// Функция для записи результата в файл
void writeResultToFile(const char *filename, const char *result) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    fprintf(file, "%s", result);
    fclose(file);
}