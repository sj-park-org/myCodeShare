#include <stdio.h>
#include <stdlib.h>

#include "SimpleList2.h"

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void read_file(struct list* plist) {
    char filename[TSIZE] = {0,};
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
            fscanf(file, "%f%*c", &new_item.rating) != 1 ) {
            printf("ERROR: Wrong file format.\n");
            exit(1);
        }
        AddItem(new_item, plist);
    }
    fclose(file);
    printf("%d items have been read from the file.\n", num);
}
unsigned int count_items(const struct list* const plist) {
    return CountItems(plist);
}
void write_an_item(FILE* const file, const struct movie item) {
    fprintf(file, "%s\n", item.title);
    fprintf(file, "%.1f\n", item.rating);
}
void write_file(const struct list* const plist) {
    char filename[TSIZE] = {0,};
    printf("Please input filename to write and press Enter.\n");
    printf(">> ");
    if (scanf("%[^\n]%*c", filename) != 1) {
        printf("Wrong input. Terminating.\n");
        exit(1);
    }
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("ERROR: Cannot open file.\n");
        exit(1);
    }
    unsigned int num = CountItems(plist);
    fprintf(file, "%d\n", num);
    unsigned int count = WriteAllItems(plist, file, &write_an_item);
    assert(count == num);
    fclose(file);
}
int input_int() {
    int input;
    while (1) {
        printf(">> ");
        if (scanf("%d%*c", &input) ==1 ) return input;
        else {
            printf("Please input an integer and press enter. Try again.\n");
            while (getchar() != '\n') continue;
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
    PrintAllItems(plist, print_an_item); // 재사용이 되는 함수들은 외부함수로 사용.
}
void find_and_print_an_item(const struct list* const plist) {
    printf("Input the index of item to print.\n");
    int index = input_int();
    struct movie* pitem;//원본이 struct movie* pitem이다, 원본을 바꾸러면 이중 포인터가 들어가야 함
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
        int f = scanf("%[^\n]%*c", new_item.title);
        printf("Input new rating and press enter.\n");
        printf(">> ");
        f = scanf("%f%*c", &new_item.rating);
        *pitem = new_item;

        printf("%d : \n", index);
        print_an_item(*pitem);
    }
    else
        printf("Invalid item.\n");
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
    printf("%d : \"%s\", %.1f\n", CountItems(plist) - 1, new_item.title, new_item.rating);
}
void insert_an_item(struct list* plist) {
    printf("Input the index of item to insert.\n");
    int index = input_int();

    struct movie* pitem;
    const bool flag = FindItemByIndex(plist, index, &pitem);

    if (flag == false) {
        printf("Wrong index\n");
        return;
    }

    struct movie new_item;

    printf("Input title and press enter.\n");
    printf(">> ");
    int f = scanf("%[^\n]%*c", new_item.title);
    printf("Input rating and press enter.\n");
    printf(">> ");
    f = scanf("%f%*c", &new_item.rating);

    printf("%d : \"%s\", %.1f\n", index, new_item.title, new_item.rating);
    InsertByIndex(new_item, plist, index);
}
void delete_an_item(struct list* plist) {
    printf("Input the index of item to delete.\n");
    int index = input_int();

    struct movie* pitem;
    const bool flag = FindItemByIndex(plist, index, &pitem);

    if (flag == false) {
        printf("Wrong index\n");
        return;
    }
    RemoveByIndex(plist, index);
}

void delete_all_items(struct list *plist) {
    ClearList(plist);
}
bool compare_items(struct movie a, struct movie b) {
    if (strcmp(a.title, b.title) ==0)
        return true;
    else
        return false;
}
void search_by_name(const struct list* plist) {
    printf("Input title to search and press enter.\n");
    printf(">> ");
    struct movie item_to_find;
    char title[TSIZE]={0,};
    if (scanf("%[^\n]%*c", item_to_find.title) != 1) {
        printf("Wrong input.\n");
        return;
    }
    struct movie item_found;
    int index;
    if (Find(plist, item_to_find, &index, &item_found, compare_items) == 0 ) {
        printf("No movie found : %s\n", item_to_find.title);
        return;
    }
    else
        printf("%d : \"%s\", %.1f\n", index, item_found.title, item_found.rating);
}

int main() {
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
            case 5:
                insert_an_item(&movie_list);
                break;
            case 6:
                delete_an_item(&movie_list);
                break;
            case 7:
                delete_all_items(&movie_list);
                break;
            case 8:
                write_file(&movie_list);
                break;
            case 9:
                search_by_name(&movie_list);
                break;
            case 10:
                printf("Good bye\n");
                delete_all_items(&movie_list);
                exit(0);
            default:
                printf("%d is not implemeted.\n",s);
        }
    }
}



