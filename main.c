#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TMAX 40

struct item {
    char character[TMAX];
    char name[TMAX];
};

void print_items_array(struct item items[], int size);
int compare_items(const void* first, const void* second);

const struct item* sequential_search(const struct item items[], const int size, const char name[TMAX]);
const struct item* binary_search(const struct item items[], const int size, const char name[TMAX]);

int main(void) {
    struct item items[] = {
        {"Iron Man", "Tony Stark"},
        {"Thor", "Thor Odinson"},
        {"Ant-Man", "Hank Pym"},
        {"Wasp", "Janet van Dyne"},
        {"Hulk", "Bruce Banner"},
        {"Captain America", "Steve Rogers"},
        {"Scarlet Witch", "Wanda Maximoff"},
        {"Black Widow", "Natasha Romanoff"},
        {"Dr. Strange", "Stephen Strange"},
        {"Daredevil", "Matthew Murdock"},
        {"Punisher", "Frank Castle"},
        {"Batman", "Bruce Wayne"}
    };
        int n = sizeof(items) / sizeof(items[0]);

    print_items_array(items, n);

    qsort(items, n, sizeof(struct item), compare_items);

    print_items_array(items, n);

    while (1) {
        char key[TMAX] = "";
        printf("Input key >> ");

        fgets(key, TMAX, stdin);
        if ((strlen(key) >0) && (key[strlen(key) -1] == '\n'))
            key[strlen(key) -1] = '\0';
        if (strcmp(key, "exit") == 0)
            break;

        const struct item* found = sequential_search(items, n, key);
        found = binary_search(items, n, key);

        if (found == NULL)
            printf("Not in the list.\n\n");
        else
            printf("%s is %s\n\n", found->character, found->name);

    }
    return 0;
}

void print_items_array(struct item items[], int size) {
    int i;
    for (i = 0; i<size; i++)
        printf("%s (%s)\n", items[i].character, items[i].name);
    printf("\n");
}

int compare_items(const void* first, const void* second) {
    struct item* first_item = (struct item*)first;
    struct item* second_item = (struct item*)second;

    return strcmp(first_item->character, second_item->character);
}

const struct item* sequential_search(const struct item items[], const int size, const char key[TMAX]) {
    for (int i = 0; i< size; ++i)
        if (strcmp(items[i].character, key) ==0)
            return &items[i];
    return NULL;
}

const struct item* binary_search(const struct item items[], const int size, const char key[TMAX]) {
    int first = 0;
    int last = size - 1;

    while (first <= last) {
        int middle = (first + last) /2;
        int comp = strcmp(items[middle].character, key);
        if (comp <0)
            first = middle +1;
        else if (comp ==0)
            return &items[middle];
        else
            last = middle -1;

    }
    return NULL;
}