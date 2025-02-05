#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TSIZE 45
// #define LMAX 10

struct movie {
    char title[TSIZE];
    float rating;
    struct movie* next;
};


void read_file(struct movie** p_head) {
    char filename[TSIZE] = {0,};
    printf("Please input filename to read and press Enter.\n");
    printf(">> ");
    if(scanf("%[^\n]%*c", filename) != 1) {
        printf("Wrong input. Terminating.\n");
        exit(1);
    }
    FILE* file = fopen(filename, "r");
    if (file==NULL) {
        printf("ERROR: Cannot open file.\n");
        exit(1);
    }

    int num;
    if (fscanf(file,  "%d%*c", &num) !=  1) {
        printf("ERROR: Wrong file format.\n");
        exit(1);
    }
    struct movie* prev = *p_head;
    //연결리스트를 만드는 과정에서 직전 노드의 next와 이후 노드를 연결할 필요가 있음
    for (int n =0; n< num; ++n) {
        struct movie* new_movie = (struct movie*)malloc(
          sizeof(struct movie));
        new_movie->next = NULL;
        if (fscanf(file, "%[^\n]%*c", new_movie->title) != 1 ||
            fscanf(file, "%f%*c", &new_movie->rating) != 1) {
            printf("ERROR: Wrong file format.\n");
            exit(1);
        }
        if (prev == NULL) {//첫 반복문의 노드는 head임
            *p_head = new_movie;
            prev = new_movie;
            //1. prev ==NULL을 넘기기 위해서 new_movie를 대입
            //2. prev.next에 new_movie를 대입하기 위해 new_movie를 대입
        }else {
            prev->next = new_movie; //연결리스트를 만듦
            prev = new_movie;
        }
        // *ptr_n_items += 1;
    }
    // assert(*ptr_n_items == num);
    fclose(file);
    printf("%d items have been read from the file.\n", num);

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


void write_file(struct movie* head) {
    char filename[TSIZE] = {0,};
    printf("Please input filename to write and press Enter.\n");
    printf(">> ");
    if (scanf("%[^\n]%*c", filename) != 1) {
        printf("Wrong input. Terminating.\n");
        exit(1);
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("ERROR: Cannot open file.\n");
        exit(1);
    }
    int count = 0;
    fprintf(file, "%d\n", (int)count_items(head));
    struct movie* pnode = head;
    while (pnode != NULL) {
        fprintf(file, "%s\n", pnode->title);
        fprintf(file, "%.1f\n", pnode->rating);
        pnode = pnode->next;
        count++;
    }
    fclose(file);
    assert(count == (int)count_items(head));
    printf("%d items have been saved to the file.\n", count);
}

int input_int() {
    int input;
    while (1) {
        printf(">> ");
        if(scanf("%d%*c", &input)==1) return input;
        else {
            printf("Please input an integer and press enter. Try again.\n");
            while (getchar() != '\n') continue;
        }
    }
}

int input_menu() {
    while (1) {
        printf("Please select an option and press enter.\n");
        printf("1. Pring all items       2. Print an item\n");
        printf("3. Edit an item          4. Add an item\n");
        printf("5. Insert an item        6. Delete an item\n");
        printf("7. Delete all item       8. Save file\n");
        printf("9. Search by name        10. Quit\n");
        int input = input_int();
        if (input >= 1 && input <= 10) return input;
        else
            printf("%d is invalid. Please try again.\n", input);

    }
}

void print_all(struct movie* head) {
    struct movie* pnode = head;
    int count=0;
    while (pnode != NULL) {
        printf("%d : \"%s\",%.1f\n", count, pnode->title, pnode->rating);
        pnode = pnode->next;
        count++;
    }
}

void print_an_item(struct movie* head) {
    printf("Input the index of item to print.\n");
    int index = input_int();

    struct movie* pnode = head;
    int count = 0;
    while (pnode != NULL) {
        if (count == index) break;
        pnode = pnode->next;
        count++;
    }
    if (pnode != NULL) //검색하려는 pnode가 없지 않을때. pnode가 NULL이 아닐때
        printf("%d : \"%s\", %.1f\n", count, pnode->title, pnode->rating);
    else
        printf("Invalid item\n");
}

void edit_an_item(struct movie* head) {
    printf("Input the index of item to edit.\n");
    int index = input_int();
    struct movie* pnode = head;
    int count = 0;

    while (pnode != NULL) {
        if (count == index) break;
        pnode = pnode->next;
        count++;
    }

    if (pnode != NULL) {
        printf("%d : \"%s\", %.1f\n", index, pnode->title, pnode->rating);
        printf("Input new title and press enter.\n");
        printf(">> ");
        int f = scanf("%[^\n]%*c", pnode->title);
        printf("Input new rating and press enter.\n");
        printf(">> ");
        f = scanf("%f%*c", &pnode->rating);
        printf("%d : \"%s\", %.1f\n", index, pnode->title, pnode->rating);
    }else {
        printf("Invalid item.\n");
    }
}

//ptr_n_items는 +1이 된 상태임.(index가 아니라 아이템의 갯수, 그러므로 추가시에 ptr_n_items을 그래도 사용)
void add_an_item(struct movie** p_head) {
    // if(*ptr_n_items == LMAX) {
    //     printf("No more space\n");
    //     return;}
    // const int index = *ptr_n_items;
    // edit_movie(&movie_list[index], index);
    // *ptr_n_items += 1;
    printf("Input title and press enter.\n");
    printf(">> ");
    struct movie* new_movie = (struct movie*)malloc(sizeof(struct movie));
    if (new_movie ==NULL) {
        printf("ERROR: malloc() failed.\n");
        exit(1);
    }
    new_movie->next = NULL;
    int f = scanf("%[^\n]%*c", new_movie->title);
    printf("Input rating and press enter.\n");
    printf(">> ");
    f = scanf("%f%*c", &new_movie->rating);
    int count = 0;
    struct movie* pnode = *p_head;
    if (pnode == NULL)
        *p_head = new_movie;
    else {
        while (pnode->next != NULL) {
            pnode = pnode->next;
            count++;
        }
        pnode->next = new_movie;
        count++;
    }
    printf("%d : \"%s\", %.1f\n", count, new_movie->title, new_movie->rating);

}


void insert_an_item(struct movie** p_head) {
    // if(*ptr_n_items == LMAX) {
    //     printf("No more space.\n");
    //     return
    // }
    printf("Input the index of item to insert.\n");
    int index = input_int();

    // //메모리를 통째로 이동.
    // memmove(&movie_list[index+1], &movie_list[index],sizeof(struct movie)*(*ptr_n_items-index));
    // //거꾸로 시작해서 요소별로 메모리를 순차이동
    // for (int i = *ptr_n_items -1; i>= index; i--) {
    //     strcpy(movie_list[i+1].title, movie_list[i].title);
    //     movie_list[i+1].rating = movie_list[i].rating;
    // }
    // edit_movie(&movie_list[index], index);
    // *ptr_n_items +=1;

    struct movie* pnode = *p_head;
    struct movie* prev = NULL;
    int count = 0;
    while (pnode != NULL) {
        if (count == index) break;
        prev=pnode;
        pnode = pnode->next;
        count++;
    }
    if (pnode == NULL) {
        printf("Wrong index\n");
        return;
    }
    struct movie* new_movie = (struct movie*)malloc(sizeof(struct movie));
    if (new_movie==NULL) {
        printf("ERROR: malloc() failed.");
        exit(1);
    }
    new_movie->next =NULL;
    printf("Input title and press enter.\n");
    printf(">> ");
    int f = scanf("%[^\n]%*c", new_movie->title);
    printf("Input rating and press enter.\n");
    printf(">> ");
    f = scanf("%f%*c", &new_movie->rating);
    printf("%d : \"%s\", %.1f\n", index, new_movie->title, new_movie->rating);

    //struct movie* temp = pnode->next;
    if (prev == NULL)
        *p_head = new_movie;
    else
        prev->next = new_movie;
    new_movie->next = pnode;
}

void delete_an_item(struct movie** p_head) {
    printf("Input the index of \n");
    int index = input_int();
    // memmove(&movie_list[index],&movie_list[index+1],sizeof(struct movie) * (*ptr_n_items - index));
    // *ptr_n_items -=1;

    struct movie* pnode = *p_head; //pnode는 삭제대상
    struct movie* prev = NULL;
    int count =0;
    while (pnode != NULL) {
        if (count == index) break;
        prev = pnode;
        pnode = pnode->next;
        count++;
    }
    if (pnode == NULL) {
        printf("Wrong index\n");
        return;
    }
    if (prev==NULL)
        *p_head = pnode->next;
    else
        prev->next = pnode->next;
    free(pnode);
}
void delete_all_items(struct movie** p_head) {
    if (*p_head == NULL) {
        printf("Nothing to delete.\n");
        return;
    }
    int count = 0;
    struct movie* search = *p_head;
    struct movie* temp = NULL;
    while (search!=NULL) {
        printf("%s is deleted.\n", search->title);
        temp=search->next;
        free(search);
        search=temp;
        count++;
    }
    *p_head =NULL;
    printf("%d items deleted.\n", count);

}



void search_by_name(struct movie* head) {
    printf("Input title to search and press enter.\n");
    printf(">> ");
    char title[TSIZE] = {};
    if (scanf("%[^\n]%*c", title)!=1) {
        printf("Wrong input.\n");
        return;
    }

    struct movie* pnode = head;
    int count = 0;
    while (pnode != NULL) {
        if (strcmp(pnode->title, title)==0) break;
        pnode = pnode->next;
        count++;
    }
    if (pnode == NULL) {
        printf("No movie found : %s\n", title);
        return;
    }
    printf("%d : \"%s\", %.1f\n", count, pnode->title, pnode->rating);
}

int main()
{
    struct movie* head = NULL;

    read_file(&head);

    while(1) {
        printf("\n");
        int s = input_menu();
        switch(s) {
            case 1:
                print_all(head);
                break;
            case 2:
                print_an_item(head);
                break;
            case 3:
                edit_an_item(head);
                break;
            case 4:
                add_an_item(&head);
                break;
            case 5:
                insert_an_item(&head);
                break;
            case 6:
                delete_an_item(&head);
                break;
            case 7:
                // n_items =0;
                    delete_all_items(&head);
                break;
            case 8:
                write_file(head);
                break;
            case 9:
                search_by_name(head);
                break;
            case 10:
                printf("Good bye\n");
                delete_all_items(&head);
                exit(0);
            default:
                printf("%d is not inplement.\n", s);
        }
    }
    return 0;
}
