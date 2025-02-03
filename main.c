#include <stdio.h>
#include <stdlib.h>

#define TSIZE 45

struct movie {
    char title[TSIZE];
    float rating;
    struct movie* next;
};

void read_file(struct movie** p_head) {
    char filename[TSIZE] = {};
    printf("Please input filename to read and press Enter.\n");
    printf(">> ");
    if (scanf("%[^\n]%*c", filename) != 1) {
        printf("Wrong input. Terminating.\n");
        exit(1);
    }
    FILE* file = fopen(filename, "r");
    if (file ==NULL) {
        printf("ERROR: Cannot open file.\n");
        exit(1);
    }
    int num;
    if (fscanf(file, "%d%*c", &num) != 1) {
        printf("ERROR: Wrong file format.\n");
        exit(1);
    }
    struct movie* prev = *p_head;
    for (int n = 0; n<num; ++n) {
        struct movie* new_movie = malloc(sizeof(struct movie));
        new_movie->next = NULL;
        if (fscanf(file, "%[^\n]%*c", new_movie->title) !=1 ||
            fscanf(file, "%f%*c", &new_movie->rating)!=1) {
            printf("ERROR: Wrong file format.\n");
            exit(1);
            }
        if (prev == NULL) {
            *p_head = new_movie;
            prev = new_movie;
        }else {
            prev->next = new_movie;
            prev = new_movie;
        }
        fclose(file);
        printf("%d items have been read from the file.\n", num);
    }
}
unsigned int count_items(const struct movie* head) {
    unsigned int count = 0;
    struct movie* pnode = head;
    while (pnode != NULL) {
        count++;
        pnode = pnode->next;
    }
    return count;
}
void write_file(struct moive* head) {
    char filename;
}



int main(void)
{









    return 0;
}

