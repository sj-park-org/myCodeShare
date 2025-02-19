#include <stdio.h>
#include <stdlib.h>

#include "SimpleList.h"

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
    for (int n = 0; n<num; ++n) {
        struct movie new_item;
        if (fscanf(file, "%[^\n]%*c", new_item.title) != 1 ||
            fscanf(file, "%f%*c", &new_item.rating) != 1) {
            printf("ERROR: Wrong file format.\n");
            exit(1);
        }
        AddItem(new_item, plist);
    }
    fclose(file);
    printf("%d items have been read from the file.\n", num);
}

int input_int() {
    int input;
    while (1) {
        printf(">> ");
        if (scanf("%d%*c", &input) == 1) return input;
        else {
            printf("Please input an integer and press enter. Try again.\n");
            while (getchar() != '\n');
        }
    }
}


int input_menu() {
    while (1) {
        printf("Please select an option and press enter.\n");
        printf("1. Print all items       2. Print an item\n");
        printf("3. Edit an item          4. Add an item\n");
        printf("5. Insert an item        6. Delete an item\n");
        printf("7. Delete all items      8. Save file.\n");
        printf("9. Search by name        10. Quit\n");
        int input = input_int();
        if (input >= 1 && input <= 10) return input;
        else
            printf("%d is invalid. Please try again.\n", input);
    }
}

void print_an_item(struct movie item) {
    printf("\"%s\", %.1f\n", item.title, item.rating);
}

void print_all(const struct list* plist) {
    PrintAllItems(plist, print_an_item);
}
void find_and_print_an_item(const struct list* const plist) {
    printf("Input the index of item to print.\n");
    int index = input_int();
    struct movie* pitem;
    const bool flag = FindItemByIndex(plist, index, &pitem);
    if (flag == true) {
        printf("%d : ", index);
        print_an_item(*pitem);
    }
    else
        printf("Invalid item.\n");
}
void edit_an_item(struct list* plist) {
    printf("Input the index of item to edit.\n");
    int index = input_int();
    struct movie* pitem;
    const bool flag = FindItemByIndex(plist, index, &pitem);
    if (flag == true) {
        printf("%d : ", index);
        print_an_item(*pitem);
        struct movie new_item;
        printf("Input new title and press enter.\n");
        printf(">> ");
        int f = scanf("&[^\n]%*c", new_item.title);
        printf("Input new rating and press enter.\n");
        printf(">> ");
        f = scanf("%f%*c", &new_item.rating);
        *pitem = new_item;

        printf("%d : \n", index);
        print_an_item(*pitem);
    }
}

void add_an_item(struct list* plist) {
    printf("Input title and press enter.\n");
    printf(">> ");
    struct movie new_item;

    int f = scanf("%[^\n]%*c", new_item.title);
    printf("Input rating and press enter.\n");
    printf(">> ");
    f = scanf("%f%*c", &new_item.rating);
    AddItem(new_item, plist);

}

int main(void)
{
    struct list movie_list;
    InitializeList(&movie_list);
    read_file(&movie_list);
    while (1) {
        printf("\n");
        int s = input_menu();

        switch (s) {
            case 1:
                print_all(&movie_list);
                break;
            case 2:
                find_and_print_an_item(&movie_list);
                break;
            case 3:
                edit_an_item(&movie_list);
                break;
            case 4:
                add_an_item(&movie_list);
                break;
        }

    }







    return 0;
}

