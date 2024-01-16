#define _DEFAULT_SOURCE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"


//---- STRUCTURES ----
            

//structure for failcircles queue of fish
struct failfish_struct
{
    int num;

    struct failfish_struct *next;
    struct failfish_struct *prev;
};
typedef struct failfish_struct failfish;
struct failcircle_struct
{
    failfish *head;
    failfish *tail;
};
typedef struct failcircle_struct failfish_queue;
//structure for failgroups
struct failgroup_struct
{
    int pond_number;
    char *pond_name;
    int num_failfish;
    int eating_counter;
    int min_threshold;
    failfish_queue *failfish_list;
    

    struct failgroup_struct *next;
    struct failgroup_struct *prev;
};
typedef struct failgroup_struct failgroup;
//structure for list of failgroups NEED TO SORT
struct failgroup_list_struct
{
    failgroup *head;
    failgroup *tail;
};
typedef struct failgroup_list_struct failgroup_list;


//---- READING METHODS ----


// Remove carriage return and/or line feed characters from a string.
void remove_crlf(char *str)
{
    char *train_ptr = str + strlen(str);
    train_ptr--;
    while ((train_ptr >= str) && (*train_ptr == '\n' || *train_ptr == '\r'))
    {
        *train_ptr = '\0';
        train_ptr--;
    }
}
//Get the next line from an input file that isn'train_ptr blank
void get_next_nonblank_line(FILE *ifp, char *str, int max_length)
{
    str[0] = '\0';

    while (str[0] == '\0')
    {
        fgets(str, max_length, ifp);
        remove_crlf(str);
    }
}


//---- FAILFISH CREATION/DISPOSAL/PRINTING/----


//FAILFISH CONSTRUCTOR : CREATION
failfish *create_failfish(int sequence_number)
{
    failfish *fish = malloc(sizeof(failgroup));
    fish->num = sequence_number;
    fish->next=NULL;
    fish->prev=NULL;

    return fish;
}
//FAILFISH DECONSTRUCTOR : DISPOSAL
void dispose_failfish(failfish *fish)
{
    fish->num = 0;
    free(fish);
}
//PRINTS FAILFISH AND WHAT ELEMENT IS LINKED TO : PRINTING
void print_failfish(FILE *ofp, failfish *f)
{
    fprintf(ofp, "%d ", f->num);
}
void print_failfish_debug(failfish *fish)
{
    printf(" %d", fish->num);
}


//---- FAILCIRCLE CREATION/DISPOSAL/PRINTING/ADDITION/DELETION/FILLING ----
//---- ENQUEUE, DEQUEQUE, PEEK, ISEMPTY ----


//FAILCIRCLE CONSTRUCTOR : CREATION
failfish_queue *create_failfish_queue(char *pondname, int n, int e, int th)
{
    failfish_queue *failcircle = malloc(sizeof(failfish_queue));
    failcircle->head = NULL;
    failcircle->tail = NULL;

    return failcircle;
    
}
//FAILCIRCLE DECONSTRUCTOR : DISPOSAL
void dispose_failcircle(failfish_queue *failcircle)
{
    failfish *failfish_holder = failcircle->head;
    failfish *failfish_holder_next;

    //if failfish is null then simply free it and the failcircle
    if(failfish_holder == NULL)
    {
        free(failfish_holder);
        free(failcircle);
        return;
    }

    //else dispose each failfish within failcircle then friee failcircle
    do{
        failfish_holder_next = failfish_holder->next;
        dispose_failfish(failfish_holder);
        failfish_holder = failfish_holder_next;
    }while(failfish_holder != failcircle->head);
    free(failcircle);
}
//ADDS ELEMENT TO FAILCIRCLE : ADDITION : ENQUEQUE
void enqueue(failfish_queue *queue, failfish *fish)
{

    //if list is empty then we're going to set head, tail, prev, next as new failgroup else add normally
    if(queue->head == NULL)
    {
        queue->head = fish;
        queue->tail = fish;
        fish->prev = fish;
        fish->next = fish;
    }else
    {
        fish->next = queue->head;
        fish->prev = queue->tail;

        queue->head->prev = fish;
        queue->tail->next = fish;

        queue->tail = fish;

    }
}
//RETURN ELEMENT AT HEAD AND MOVES HEAD POSITION FORWARD : DEQUEQUE
failfish *dequque(failfish_queue *queue)
{
    failfish *fish = queue->head;

    if(queue->head != NULL)
    {
        queue->head = queue->head->next;
    }

    if(queue->head == NULL)
    {
        queue->tail = NULL;
    }
    return fish;
}
//CHECKS HEAD OF QUEUE : PEEK
failfish *peek(failfish_queue *queue)
{
    return queue->head;
}
//CHECK IF QUEUE IS EMPTY : ISEMPTY
int is_empty(failfish_queue *queue)
{
    if(peek(queue) == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//DELETES ELEMENTS FROM FAILCIRCLE : DELETION
void failfish_delete(failfish_queue *failcircle_holder, failfish *failfish_to_delete)
{

    //check if list has only one element and disposes
    if(failcircle_holder->head == failcircle_holder->tail)
    {
        failcircle_holder->head = NULL;
        failcircle_holder->tail = NULL;
        dispose_failfish(failfish_to_delete);
        return;
    }

    //if has more than one elemnet then repairs the heads and tails failgroup_struct
    if(failcircle_holder->head == failfish_to_delete)
    {
        failcircle_holder->head = failfish_to_delete->next;
    }
    if(failcircle_holder->tail == failfish_to_delete)
    {
        failcircle_holder->tail = failfish_to_delete->prev;
    }

    //then move prev and next and finally delete element with no ptr on it
    failfish_to_delete->prev->next = failfish_to_delete->next;
    failfish_to_delete->next->prev = failfish_to_delete->prev;
    dispose_failfish(failfish_to_delete);

}
//PRINTS FAILCIRCLE AND WHAT EACH ELEMENT IS LINKED TO : PRINTING
void print_failfish_queue(FILE *ofp, failfish_queue *q)
{
    failfish *failfish_holder = q->head;
    failfish *failfish_holder_next;

    do{
        failfish_holder_next = failfish_holder->next;
        print_failfish(ofp, failfish_holder);
        failfish_holder = failfish_holder_next;
    }while(failfish_holder != q->head);
}
//PRINTS FAILCIRCLE AND WHAT EACH ELEMENT IS LINKED TO : PRINTING
void print_failfish_queue_debug(failfish_queue *failcircle)
{
    failfish *failfish_holder = failcircle->head;
    failfish *failfish_holder_next;

    do{
        failfish_holder_next = failfish_holder->next;
        print_failfish_debug(failfish_holder);
        failfish_holder = failfish_holder_next;
    }while(failfish_holder != failcircle->head);
}
//fills failcircle of each failgroup : FILLING
void fill_failfish_list(failgroup_list *grouplist)
{
    failgroup *group = grouplist->head;

    do{
        failfish_queue *queue =  create_failfish_queue(group->pond_name, group->pond_number, group->eating_counter, group->eating_counter);
        for(int j = 1; j<=group->num_failfish; j++)
        {
            enqueue(queue, create_failfish(j));
        }
        group->failfish_list = queue;
        group = group->next;
    }while(group != grouplist->head);
}


//---- FAILGROUP CREATION/DISPOSAL/PRINTING ----


//FAILGROUP CONSTRUCTOR : CREATION 
failgroup *new_failgroup(FILE *ifp)
{

    int pond_number;
    char pond_name[500];
    int num_failfish;
    int eating_counter;
    int min_threshold;
    char str[500];

    //get next non blank line then start scanning in info
    get_next_nonblank_line(ifp, str, 500);
    sscanf(str, "%d %s %d %d %d", &pond_number, pond_name, &num_failfish, &eating_counter, &min_threshold);

    //start setting info
    failgroup *group = malloc(sizeof(failgroup));
    group->pond_name = strdup(pond_name);
    group->pond_number = pond_number;
    group->num_failfish = num_failfish;
    group->eating_counter = eating_counter;
    group->min_threshold = min_threshold;
    group->next = NULL;
    group->prev = NULL;

    return group;
}
//FAILGROUP DECONSTRUCTOR : DISPOSAL
void dispose_failgroup(failgroup *group)
{
    free(group->pond_name);
    group->pond_number = 0;
    group->num_failfish = 0;
    group->eating_counter = 0;
    group->min_threshold = 0;
    group->next = NULL;
    group->prev = NULL;
    dispose_failcircle(group->failfish_list);
    free(group);
}
//PRINTS FAILGROUP AND INFO : PRINTING DEBUG
void print_failgroup_debug(failgroup *group)
{
    printf("%d %s ", group->pond_number, group->pond_name); //HERE
    print_failfish_queue_debug(group->failfish_list);
    printf("\n");
}
//PRINTS FAILGROUP AND INFO : PRINTING
void print_failgroup(FILE *ofp, failgroup *group)
{
    fprintf(ofp,"%d %s ", group->pond_number, group->pond_name);
    print_failfish_queue(ofp, group->failfish_list);
    fprintf(ofp, "\n");
}


//---- FAILGROUP LIST CREATION/DISPOSAL/ADDITION/DELETION/PRINTING ----


//FAILGROUP LIST CONSTRUCTOR : CREATION
failgroup_list *new_failgroup_list()
{
    failgroup_list *failgroup_list = malloc(sizeof(failgroup_list));
    failgroup_list->head = NULL;
    failgroup_list->tail = NULL;

    return failgroup_list;
}
//FAILGROUP LIST DECONSTRUCTOR : DISPOSAL
void dispose_failgroup_list(failgroup_list *failgroup_list)
{
    failgroup *failgroup_holder = failgroup_list->head;
    failgroup *failgroup_holder_next;

    if(failgroup_holder == NULL)
    {
        dispose_failgroup(failgroup_holder);
        return;
    }

    do{
        failgroup_holder_next = failgroup_holder->next;
        dispose_failgroup(failgroup_holder);
        failgroup_holder = failgroup_holder_next;
    }while(failgroup_holder != failgroup_list->head);
    
}
//add failgroup to head of list
void failgroup_list_add_head(failgroup_list *failgroup_list_holder, failgroup *new_failgroup)
{

    //if list is empty then we're going to set head, tail, prev, next as new failgroup else add normally
    if(failgroup_list_holder->head == NULL)
    {
        failgroup_list_holder->head = new_failgroup;
        failgroup_list_holder->tail = new_failgroup;
        new_failgroup->prev = new_failgroup;
        new_failgroup->next = new_failgroup;
    }
    else
    {
        new_failgroup->next = failgroup_list_holder->head;
        new_failgroup->prev = failgroup_list_holder->tail;

        failgroup_list_holder->head->prev = new_failgroup;
        failgroup_list_holder->tail->next = new_failgroup;

        failgroup_list_holder->head = new_failgroup;
    }
}
//deleting from failgrouplist : DELETION
void failgroup_list_delete(failgroup_list *failgroup_list_holder, failgroup *failgroup_to_delete)
{

    //check if list has only one element and disposes
    if(failgroup_list_holder->head == failgroup_list_holder->tail)
    {
        failgroup_list_holder->head = NULL;
        failgroup_list_holder->tail = NULL;
        dispose_failgroup(failgroup_to_delete);
        return;
    }

    //if has more than one elemnet then repairs the heads and tails
    if(failgroup_list_holder->head == failgroup_to_delete)
    {
        failgroup_list_holder->head = failgroup_to_delete->next;
    }
    if(failgroup_list_holder->tail == failgroup_to_delete)
    {
        failgroup_list_holder->tail = failgroup_to_delete->prev;
    }

    //then move prev and next and finally delete element with no ptr on it
    failgroup_to_delete->prev->next = failgroup_to_delete->next;
    failgroup_to_delete->next->prev = failgroup_to_delete->prev;
    dispose_failgroup(failgroup_to_delete);

}
//printing failgrouplist : PRINTING DEBUG
void print_failgroup_list_debug(failgroup_list *failgroup_list_holder,int num_failgroups)
{
    failgroup *failgroup_holder = failgroup_list_holder->head;
    failgroup *failgroup_holder_next;

    do{
        failgroup_holder_next = failgroup_holder->next;
        print_failgroup_debug(failgroup_holder);
        failgroup_holder = failgroup_holder_next;
    }while(failgroup_holder != failgroup_list_holder->head);

}
//printing failgrouplist : PRINTING
void print_failgroup_list(FILE *ofp, failgroup_list *failgroup_list_holder)
{
    failgroup *failgroup_holder = failgroup_list_holder->head;
    failgroup *failgroup_holder_next;

    do{
        failgroup_holder_next = failgroup_holder->next;
        print_failgroup(ofp, failgroup_holder);
        failgroup_holder = failgroup_holder_next;
    }while(failgroup_holder != failgroup_list_holder->head);
}


//---- FAILGROUP LIST SORT SWAP/BUBBLESORT ----


//switching data of each node : SWAP
void swap(failgroup *failgroup_holder_one, failgroup *failgroup_holder_two)
{
    
    //hold first failgroup data in temporary holders
    char *temp_name = failgroup_holder_one->pond_name;
    int temp_pond_number = failgroup_holder_one->pond_number;
    int temp_num_failfish = failgroup_holder_one->num_failfish;
    int temp_eating_counter = failgroup_holder_one->eating_counter;
    int temp_min_threshold = failgroup_holder_one->min_threshold;

    //set holder one data to holder two data
    failgroup_holder_one->pond_name = failgroup_holder_two->pond_name;
    failgroup_holder_one->pond_number = failgroup_holder_two->pond_number;
    failgroup_holder_one->num_failfish = failgroup_holder_two->num_failfish;
    failgroup_holder_one->eating_counter = failgroup_holder_two->eating_counter;
    failgroup_holder_one->min_threshold = failgroup_holder_two->min_threshold;

    //set holder data two to temp data which holds holder data one
    failgroup_holder_two->pond_name = temp_name;
    failgroup_holder_two->pond_number = temp_pond_number;
    failgroup_holder_two->num_failfish = temp_num_failfish;
    failgroup_holder_two->eating_counter = temp_eating_counter;
    failgroup_holder_two->min_threshold = temp_min_threshold;
}
//bubble sorts are linked list of failgroups from least to greatest: BUBBLE SORT
void bubble_sort(failgroup_list *failgroup_list_holder)
{
    failgroup *failgroup_holder_one = failgroup_list_holder->head;
    failgroup *failgroup_holder_two = failgroup_holder_one->next;
    failgroup *failgroup_holder_last = failgroup_list_holder->tail;

    //check if empty
    if(failgroup_holder_one == NULL) return;


    //bubble sort
    do{

       //check if need to swap 
        if(failgroup_holder_one->pond_number>failgroup_holder_two->pond_number)
        {
            swap(failgroup_holder_one, failgroup_holder_two);
        }
        
        //iterate through list
        failgroup_holder_one = failgroup_holder_one->next;
        failgroup_holder_two = failgroup_holder_two->next;

        //if reached end of list we will reset back to beginning & move endPtr
        if(failgroup_holder_one == failgroup_holder_last)
        {
            failgroup_holder_one = failgroup_list_holder->head;
            failgroup_holder_two = failgroup_holder_one->next;

            //change the end back since largest would be at the end already
            failgroup_holder_last = failgroup_holder_last->prev;
        }


    }while(failgroup_holder_last != failgroup_list_holder->head); 
}


//---- FIRST COURSE ----


//goes through first course for each failgroup passed into it
void first_course(FILE *ofp, failgroup *failgroup_holder)
{
    failfish_queue *fc = failgroup_holder->failfish_list;
    failfish *fish = fc->head;
    int eating_counter = failgroup_holder->eating_counter;
    int min = failgroup_holder->min_threshold;
    int num = failgroup_holder->pond_number;
    char *name = failgroup_holder->pond_name;
    int curr_size = failgroup_holder->num_failfish;
    int curr_index = 1;

    //deletes every three fish in failcircle
    fprintf(ofp, "\nPond %d: %s",num, name);
    while(curr_size>min)
    {
        if(curr_index%eating_counter == 0)
        {
            fprintf(ofp, "\nFailfish %d eaten", fish->num);
            failfish_delete(fc, fish);
            curr_size--;
            curr_index = 1;
        }
        else
        {
            curr_index++;

        }
   
        fish = fish->next;

    }
    fprintf(ofp, "\n");
}
//goes through failgroup list and passes each group into first course
void failgroup_list_first_course(FILE *ofp, failgroup_list *failgroup_list_holder)
{
    failgroup *failgroup_holder = failgroup_list_holder->head;
    do{
        first_course(ofp, failgroup_holder);
        failgroup_holder = failgroup_holder->next;
    }while(failgroup_holder != failgroup_list_holder->head);
}


//---- SECOND COURSE ----
            

//find max number of all heads of queue in list of failgroups
failfish *find_Max(failgroup_list *failgroup_holder_list)
{
    failgroup *failgroup_holder = failgroup_holder_list->head;
    failfish *max_fish = peek(failgroup_holder->failfish_list);

    do{
        failfish *curr_fish = peek(failgroup_holder->failfish_list);
        if(curr_fish->num > max_fish->num)
        {
            max_fish = curr_fish;
        }
        failgroup_holder = failgroup_holder->next;

    }while(failgroup_holder != failgroup_holder_list->head);
    return max_fish;
}
//eat ALL queue of given failgroup and deletes given failgroup
void eat_queue_all(FILE *ofp, failgroup_list *failgroup_list_holder, failgroup *failgroup_to_eat)
{
    //while queue is not empty eat the queue then end by deleting failgroup
    while(!(is_empty(failgroup_to_eat->failfish_list)))
    {
        failfish *curr_fish = peek(failgroup_to_eat->failfish_list);
        fprintf(ofp, "\nEaten: Failfish %d from pond %d", curr_fish->num, failgroup_to_eat->pond_number );
        failfish_delete(failgroup_to_eat->failfish_list, curr_fish);
    }
    failgroup_list_delete(failgroup_list_holder, failgroup_to_eat);
}
//eat last queue and leaves last number, does not delete failgroup
int eat_queue_last(FILE *ofp, failgroup *failgroup_to_eat)
{

    //while queue is not empty eat the queue then end by deleting failgroup
    while(failgroup_to_eat->failfish_list->head != failgroup_to_eat->failfish_list->tail)
    {
        failfish *curr_fish = peek(failgroup_to_eat->failfish_list);
        fprintf(ofp, "\nEaten: Failfish %d from pond %d", curr_fish->num, failgroup_to_eat->pond_number );
        failfish_delete(failgroup_to_eat->failfish_list, curr_fish);
    }
    return failgroup_to_eat->failfish_list->head->num;
}
//eat the failgroups that containt the max number but stops when one is left
void eat_groups_max(FILE *ofp, failgroup_list *failgroup_holder_list, int curr_max)
{
    failgroup *failgroup_holder = failgroup_holder_list ->head;
    if(failgroup_holder == failgroup_holder_list->tail) return; //check if one left

    int passed_tail = 0; //checked if passed tail to break out of loop;
    do{
        //check if passed tail to break & if one group left (break condition)
        if(failgroup_holder == failgroup_holder_list->tail) passed_tail = 1;
        if(failgroup_holder_list->head == failgroup_holder_list->tail) return;

        //check if head are equal to current max and will eat queue if so
        failfish *curr_fish = peek(failgroup_holder->failfish_list);
        int curr_num = curr_fish->num;
        if(curr_num == curr_max)
        {
            eat_queue_all(ofp, failgroup_holder_list, failgroup_holder);
            failgroup_holder = failgroup_holder_list->head;
            continue;
        }
        failgroup_holder = failgroup_holder->next;//moves on

    }while(passed_tail == 0);
    
}
//goes through second course for failgroup list passed into it
int failgroup_list_second_course(FILE *ofp, failgroup_list *failgroup_list_holder)
{
    failgroup *failgroup_holder = failgroup_list_holder->head;
    int max_num;
    int last_fish;

    // find max and eat the queue with that max, repeat until one group left
    do{
        failfish *max_fish = find_Max(failgroup_list_holder);
        max_num = max_fish->num;
        eat_groups_max(ofp, failgroup_list_holder, max_num);
        failgroup_holder = failgroup_list_holder->head;
    }while(failgroup_list_holder->head != failgroup_list_holder->tail);
    
    //eat last queue and get last fish num for output
    last_fish = eat_queue_last(ofp, failgroup_list_holder->head);
    return last_fish;
}

int main(void)
{

    atexit(report_mem_leak);

    //variables
    int last_fish;
    int num_failgroups;
    failgroup *group;
    failgroup_list *grouplist = new_failgroup_list();

    FILE *ifp;
    FILE *ofp;
    ifp = fopen("cop3502-as2-input.txt", "r");
    ofp = fopen("cop3502-as2-output-ruiz-trishaesther.txt", "w");

    fscanf(ifp, "%d", &num_failgroups);
    
    for(int i = 0; i<num_failgroups; i++)
    {
        group = new_failgroup(ifp);
        failgroup_list_add_head(grouplist, group);
    }
    
    //sorts our list
    bubble_sort(grouplist);

    //creates failfish list or failfish queue for each failgroup
    fill_failfish_list(grouplist);

    //prints initial pond
    fprintf(ofp, "Initial Pond Status\n");
    print_failgroup_list(ofp, grouplist);

    //first course begins 
    fprintf(ofp, "\nFirst Course\n");
    failgroup_list_first_course(ofp, grouplist);

    //prints end of first course pond
    fprintf(ofp, "\nEnd of Course Pond Status\n");
    print_failgroup_list(ofp, grouplist);

    //second course begins
    fprintf(ofp, "\nSecond Course\n");

    //saves last fish to survive
    last_fish = failgroup_list_second_course(ofp, grouplist);
    fprintf(ofp, "\n\nFailfish %d from pond %d remains", last_fish, grouplist->head->pond_number);
    failgroup_list_delete(grouplist, grouplist->head);

    //free list
    free(grouplist);
    return 0;
}