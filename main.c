#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedqueue.h"


// rand()/ RAND_MAX는 0.0~1사이의 값.
// rand()는 0~32767을 나타낸다고 하면 RAND_MAX는 32767임
// min_per_cust(x) = 60.0f / average_n_customers_per_hour;
// 평균 손님이 만약 30이라면 x는 2
// rand()/ RAND_MAX는 0.0~1 인데 2를 곱하면 false가 많아짐.
// x가 60보다 커서 x가 0.5이면 rand()/ RAND_MAX는 0.0~0.5가 되므로 무조건 true
bool newcustomer_visit(double x) {
    if (rand() * x / RAND_MAX < 1.0)
        return true;
    else
        return false;
}

struct cust get_customer(long arrival_time) {
    struct cust cust;
    cust.processtime = rand() %3 +1; //1~3까지의 숫자
    cust.arrival_time = arrival_time;

    return cust;
}

int main() {
    struct queue waiting_queue;

    int simulation_length_in_hours;
    int average_n_customers_per_hour;
    double min_per_cust;
    long cycle, cyclelimit;

    long n_lost_customers = 0;
    long n_queued_customers = 0;
    long n_served_customers = 0;
    long sum_line = 0;
    int wait_time = 0;

    long line_wait = 0;

    InitializeQueue(&waiting_queue);

    srand((unsigned int)time(0));

    printf("How many hours do you want to simulate? \n>> ");
    int flag;
    flag = scanf("%d", &simulation_length_in_hours);


    printf("How many customers per hour do you expect? \n>> ");
    flag = scanf("%d", &average_n_customers_per_hour);

    cyclelimit = simulation_length_in_hours * 60;
    min_per_cust = 60.0f / average_n_customers_per_hour;

    for (cycle = 1; cycle <= cyclelimit; cycle++) {
        if (newcustomer_visit(min_per_cust)) {
            if (QueueIsFull(&waiting_queue)) {
                n_lost_customers++;
                printf("%3ld : Customer lost\n", cycle);
            }
            else {
                n_queued_customers++;
                struct cust customer_ready = get_customer(cycle);
                EnQueue(customer_ready, &waiting_queue);
                printf("%3ld : a new customer enqueue.\n", cycle);
            }
        }
        if (wait_time <= 0 && !QueueIsEmpty(&waiting_queue)) {
            struct cust customer_ready;
            printf("%3ld : start serving a customer for %d minutes.\n",
                   cycle, customer_ready.processtime);
            wait_time = customer_ready.processtime;
            line_wait += cycle - customer_ready.arrival_time;
            n_served_customers++;
        }
        if (wait_time > 0 )
            wait_time--;

        sum_line += QueueItemCount(&waiting_queue);
    }

    printf("\n");

    if (n_queued_customers > 0) {
        printf("customers accepted: %ld\n", n_queued_customers);
        printf("  customers served: %ld\n", n_served_customers);
        printf("              Lost: %ld\n", n_lost_customers);
        printf("average queue size: %.2f\n", (double) sum_line / cyclelimit);
        printf(" average wait time: %.2f minutes\n", (double) line_wait / n_served_customers);

    }
    else
        puts("No customers!");

    EmptyTheQueue(&waiting_queue);


}