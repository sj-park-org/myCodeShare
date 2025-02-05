#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    //이전 변수를 생성. for문(new_movie를 생성하고, 데이터를 넣은 후에, prev->next에 new_movie
    //prev에 new_movie
    //그 후에 초기값이 NULL일때 처리)
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
    while (pnode != NULL) { //변수 pnode설정. head에서부터 NULL이 나올때까지 pnode->next로 회전 pnode는 node 포인터의 약자
        count++;
        pnode = pnode->next;
    }
    return count;
}
void write_file(struct moive* head) {
    char filename[TSIZE] = {};
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
    //변수 pnode를 설정. head에서부터 시작해서 pnode->next로 NULL이 나올때까지 전부 회전
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
        if (scanf("%d%*c", &input)==1) return input;
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
            printf("%d is invalid, Please try again.\n", input);
    }
}
void print_all(struct movie* head) {
    //pnode 설정 후 NULL이 나올때까지 pnode->next로 루프
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
    //검색과정에서 pnode가 NULL이 나올때까지 루프 & count++
    //중간에 count와 입력값(index)가 일치하면 중지
    if (pnode != NULL) {
        printf("%d : \"%s\", %.1f\n", count, pnode->title, pnode->rating);
    }else
        printf("Invalid item\n");
}
void edit_an_item(struct movie* head) {
    printf("Input the index of item to edit\n");
    int index = input_int();
    struct movie* pnode = head;
    int count =0;
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
    }else
            printf("Invalid item\n");
}
void add_an_item(struct movie** p_head) {
    printf("Input title and press enter.\n");
    printf(">> ");
    struct movie* new_movie = (struct movie*)malloc(sizeof(struct movie));
    if (new_movie == NULL) {
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
    printf("Input the index of item to insert.\n");
    int index = input_int();
    struct movie* pnode = *p_head;
    struct movie* prev = NULL;
    //노드 포인터와 이전 노드 포인터를 생성
    int count = 0;
    while (pnode != NULL) {
        if (count == index) break;
        prev=pnode; //이전 노드에 현재 노드를 대입
        pnode = pnode->next; //현재 노드를 다음 노드로 변경
        count++;
    }
    //인덱스 범위 초과
    if (pnode == NULL) {
        printf("Wrong index\n");
        return;
    }
    struct movie* new_movie = (struct moive*)malloc(sizeof(struct movie));
    if (new_movie==NULL) {
        printf("ERROR: malloc() failed.\n");
        exit(1);
    }
    new_movie->next = NULL;
    printf("Input title and press enter.\n");
    printf(">> ");
    int f = scanf("%[^\n]%*c", new_movie->title);
    printf("Input rating and press enter.\n");
    printf(">> ");
    f = scanf("%f%*c", &new_movie->rating);
    printf("%d : \"%s\", %.1f\n", index, new_movie->title, new_movie->rating);
    if (prev == NULL)
        *p_head = new_movie; // 헤드가 NULL일때
    else
        prev->next = new_movie;
    new_movie->next = pnode;
    //pnode는 현재노드, prev는 이전 노드, new_movie는 중간에 넣을 노드
}
void delete_an_item(struct movie** p_head) {
    printf("Input the index of \n");
    int index = input_int();
    struct movie* pnode = *p_head; // 현재노드 + 초기화
    struct movie *prev = NULL;// 이전노드
    int count = 0;
    while (pnode != NULL) {
        if (count == index) break;
        prev = pnode;
        pnode = pnode->next;
        count++;
    }
    if (pnode ==NULL) { //찾는 인덱스가 없음.
        printf("Wrong index\n");
        return;
    }
    if (prev==NULL) // 이전 노드가 없다는 것은, 첫 노드가 일치한다는 뜻.
        *p_head==pnode->next;
    else
        prev->next = pnode->next;
    free(pnode);
}
void delete_all_items(struct movie** p_head) {
    if (*p_head ==NULL) {
        printf("Nothing to delete.\n");
        return;
    }
    int count = 0;
    struct movie* search = *p_head; //search는 지역변수이므로 함수 종료와 함께 삭제
    struct movie* temp =NULL;
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
        printf("Wrong input\n");
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


int main(void)
{









    return 0;
}

