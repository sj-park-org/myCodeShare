#include <stdio.h>
#include <stdlib.h>

#include "SimpleList.h"

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void read_file(struct list* plist) {
    char filename[TSIZE] = {};
    printf("Please input filename to read and press Enter.\n");
    printf(">> ");
    if (scanf("%[^\n]%*c", filename) != 1) {
        printf("Wrong input. Terminating.\n");
        exit(1);
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR: Cannot open file.\n");
        exit(1);
    }
    int num;
    if (fscanf(file, "%d%*c", &num) != 1) {
        printf("ERROR: Wrong file format.\n");
        exit(1);
    }
    for (int n=0; n<num; ++n) {
        struct movie new_item;
        if (fscanf(file, "%[^\n]%*c", new_item.title) != 1 ||
            fscanf(file, "%f%*c", &new_item.rating) != 1) {
            printf("ERROR: Wrong file format.\n");
            exit(1);
        }
        AddItem(new_item, plist);
    }
    fclose(file);
    printf("%d items have been read from the file.\n");
}


int main(void)
{









    return 0;
}

