// all-monster-sorts.c - Sort monsters by name and weight.

/* The idea of sorting is simple: take unordered objects, and arrange them in an
   order.  It has a lot of uses, so there's been a lot of work done with it.  Here,
   we're going to demonstrate a few of the simpler, more classic sorting techniques.
   */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>

/* Monster structure and helper functions - DO NOT MODIFY THESE. */

typedef struct monster
{
	int id;
	char name[64];
	char element[64];
	int population;
	double weight;
} monster;

monster *make_some_monsters(int n)
{
  monster *monsters = malloc(sizeof(monster) * n);

  time_t t;

  srand((unsigned) time(&t));

  for(int i = 0; i < n; i++)
  {
    monsters[i].id = i;
    sprintf(monsters[i].name, "Monster #%d", rand());
    sprintf(monsters[i].element, "Element #%d", rand());
    monsters[i].population = rand();
    monsters[i].weight = 500.0 * ((double) rand() / (double) RAND_MAX);
  }

  return monsters;
}

void output_monster_list(monster *list, int n, char *title)
{
  printf("List %s:\n", title);
  for(int i = 0; i < n; i++) {
    printf("  Monster %d: %s %s %d %lf\n", i, list[i].name, list[i].element, list[i].population, list[i].weight);
  }
  printf("\n");
}

void print_clocks(clock_t clocks)
{
  printf("  %lfs CPU time used\n", ((double) clocks) / CLOCKS_PER_SEC);
}

void swap_monsters(monster *list, int i, int j)
{
  monster temp;

  memcpy(&temp, list + i, sizeof(monster));
  memcpy(list + i, list + j, sizeof(monster));
  memcpy(list + j, &temp, sizeof(monster));
}

/* The core comparison function. */ 

//compare monster based on weight or name
int compare_monsters(monster *m1, monster *m2, int use_name, int use_weight)
{

  if(use_name == 1)
  {
    return strcmp(m1->name, m2->name);
  }

  else if(use_weight == 1)
  {
    if(m1->weight < m2->weight) return -1;
    else if(m1->weight > m2->weight) return 1;
    else return 0;
  }
  else
  {
    return 0;
  }
}

//check if list is sorted and returns accordingly
void check_monster_sort(monster *list, int n, int use_name, int use_weight)
{
  for(int i = 1; i < n; i++)
  {
    if(compare_monsters(list + i - 1, list + i, use_name, use_weight) > 0)
    {
      printf("*** The list is NOT sorted.\n\n");
      return;
    }
  }
  printf("The list is sorted.\n\n");
}

/* Implement ascending quick sort. */

//sort element through repartition
int repartition(monster *list, int low_index, int high_index, int *comparisons, int *swaps,
                int use_name, int use_weight)
{
  monster *pivot = &list[high_index];
  int i = low_index;

  for(int j = low_index; j < high_index; j++)
  {
    (*comparisons)++;
  
    if(compare_monsters(&list[j], pivot, use_name, use_weight)<0)
    {
      (*swaps)++;
      swap_monsters(list, i, j);
      i++;
    }
  }

  swaps++;
  swap_monsters(list, i, high_index);
  return i;

}

/* Recursive function for quick sort. */

//sorts through quick sort and recursively calls it to divide and conquer
void quick_sort_recursive(monster *list, int low_index, int high_index, int *comparisons, int *swaps,
                          int use_name, int use_weight)
{
  int pivot_index = repartition(list, low_index, high_index, comparisons, swaps, use_name, use_weight);

  if(pivot_index-1 > low_index)
  {
    quick_sort_recursive(list, low_index, pivot_index-1, comparisons, swaps, use_name, use_weight);
  }
  if(high_index > pivot_index+1)
  {
  quick_sort_recursive(list, pivot_index+1, high_index, comparisons, swaps, use_name, use_weight);
  }

}

/* Shell function for quick sort. */

//quick sort caller
void quick_sort(monster *list, int n, int use_name, int use_weight)
{
  int comparisons = 0;
  int swaps = 0;
  clock_t start_cpu, end_cpu;

  printf("Quick sort %d monsters by %s...\n", n, use_name ? "name" : "weight");

  start_cpu = clock();
  quick_sort_recursive(list, 0, n-1, &comparisons, &swaps, use_name, use_weight);
  end_cpu = clock();

  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
}

/* Implement ascending bubble sort. */

//bubble sort elements
void bubble_sort(monster *list, int n, int use_name, int use_weight) 
{
  int i;
  int j;
  int temp;
  int comparisons = 0;
  int swaps = 0;
  clock_t start_cpu, end_cpu;

  printf("Bubble sort %d monsters by %s...\n", n, use_name ? "name" : "weight");

  start_cpu = clock();


  for(i = n-1; i >= 0; i--)
  {
    for(j = 0; j < i; j++)
    {
      comparisons++;
      //list[j] > list[j+1]
      if(compare_monsters(&list[j], &list[j+1], use_name, use_weight) > 0) // Are our elements out of order?
      {
        swaps++;
        swap_monsters(list, j, j+1);
      }
    }
  }

  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
}

/* Highest-value finder for selection sort. */

//find max element
int find_highest(monster *list, int n, int *comparisons, int use_name, int use_weight)
{
  monster *max = &list[0];
  int max_index = 0;
  int i;
  
  for(i = 0; i <= n; i++)
  {
    (*comparisons)++;
    //list[i] > max

    if(compare_monsters(&list[i], max, use_name, use_weight)>0)
    {
      max_index = i;
      max = &list[i];
    }
  }
  return max_index;
}

/* Implement ascending selection sort. */ 

//selection sort 
void selection_sort(monster *list, int n, int use_name, int use_weight)
{
  int i;
  int highest;
  int comparisons = 0;
  int swaps = 0;
  clock_t start_cpu, end_cpu;

  printf("Selection sort %d monsters by %s...\n", n, use_name ? "name" : "weight");
  start_cpu = clock();

  for(i = n-1; i >= 0; i--)
  {
    highest = find_highest(list, i, &comparisons, use_name, use_weight);
    if(highest != i)
    {
      swaps++;
      swap_monsters(list, highest, i);
    }
  }

  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
}

/* Find position for insertion sort. */

//find position of where we can insert into our sorted array
int insertion_sort_find_position(monster *list, int low_index, int high_index, monster *k, int *comparisons, int use_name, int use_weight)
{
  int j = low_index;
  int i = high_index;

  //iterate j from the front of the sorted list until we reach i or find an element with a value higher than element i
  while(j != i){

    (*comparisons)++;
    if(compare_monsters(&list[j], &list[i], use_name, use_weight) > 0) return j;
    j++; 

  }
  
  return j;
}

/* Implement insertion sort. */

//insertion sort
void insertion_sort_internal(monster *list, int n, int *comparisons, int *copies, int *block_copies, int use_name, int use_weight)
{

  int sorted_index = 0, unsorted_index, position;
  monster *curr_element;

  for(unsorted_index = 1; unsorted_index < n; unsorted_index++)
  {
    
    //grab element i
    (*copies)++;
    curr_element = &list[unsorted_index];

    //get position to insert element i
    position = insertion_sort_find_position(list, 0, unsorted_index, curr_element, comparisons, use_name, use_weight);
    

    //move elements j to i-1 to the right squashing i
    for(int upper_index = unsorted_index; upper_index > position; upper_index--)
    {

      (*copies)++;
      (*copies)++;
      swap_monsters(list, upper_index, upper_index-1);
    }
    (*block_copies)++;

  }
}

/* Shell for insertion sort. */

//calls insertion sort
void insertion_sort(monster *list, int n, int use_name, int use_weight)
{
  int comparisons = 0;
  int block_copies = 0;
  int total_copies = 0;
  clock_t start_cpu, end_cpu;
  printf("Insertion sort %d monsters by %s...\n", n, use_name ? "name" : "weight");
  start_cpu = clock();

  insertion_sort_internal(list, n, &comparisons, &total_copies, &block_copies, use_name, use_weight);

  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d block copies (%d total copies).\n", comparisons, block_copies, total_copies);
  print_clocks(end_cpu - start_cpu);
  return;
}

/* Merge function for merge sort.  Merges sub-arrays [l1..h1] and [l2..h2].
   Must have l2 = l1 + 1 or bad things will happen. */

//merge sorted subarrays passed onto it while sorting it
void merge_sort_merge(monster *list, int l1, int h1, int l2, int h2, 
                      int *comparisons, int *copies, int *block_copies, int *mallocs,
                      int use_name, int use_weight)
{

  int index = l1;
  int size = h2-l1+1;
  int l1_hold = l1;
  int h2_hold = h2;

  if(size<=0) return;

  monster *temp = malloc((sizeof(monster))*(size+600000));
  (*mallocs)++;

  //will iterate through both parts of array until one reaches its end & insert the lesser between the two elements of each array
  while (l1 <= h1 && l2 <= h2)
  {

    (*comparisons)++;

    if(compare_monsters(&list[l1], &list[l2], use_name, use_weight) <= 0){

      (*copies)++;
      temp[index] = list[l1];
      index++;
      l1++;

    }else
    {
      
      (*copies)++;
      temp[index] = list[l2];    
      index++; 
      l2++;   

    }
  }
  
  //now copy over remaining elements if there were any
  (*block_copies)++;

  //first half
  while(l1<=h1){
      (*copies)++;
      temp[index] = list[l1];  
      index++;
      l1++;
  }

  //second half
  while(l2<=h2){
    (*copies)++;
      temp[index] = list[l2];       
      index++;
      l2++;
  }

  //copy sorted list into original list
  (*block_copies)++;
  for(int i = l1_hold; i<= h2_hold; i++){
    (*copies)++;
    list[i] = temp[i];   
  }
  
  if(size > 0) free (temp);
  


}

/* Recursive function for merge sort. */

//recursive merge sort calling itself until size is 1
void merge_sort_recursive(monster *list, int low_index, int high_index, 
                          int *comparisons, int *copies, int *block_copies, int *mallocs,
                          int use_name, int use_weight)
{
  int mid = (low_index + high_index)/2;
  int size = high_index-low_index+1;

  if(size == 1)
  {
    return;
  }

  
  //first find the mid then call merge sort on first half and second of list

  merge_sort_recursive(list, low_index, mid, comparisons, copies, block_copies, mallocs, use_name, use_weight);
  
  merge_sort_recursive(list, mid+1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);

  merge_sort_merge(list, low_index, mid, mid+1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);
}

/* Implement merge sort. */

//merge sorts elements
void merge_sort(monster *list, int n, int use_name, int use_weight)
{
  int comparisons = 0;
  int copies = 0;
  int block_copies = 0;
  int mallocs = 0;
  clock_t start_cpu, end_cpu;

  printf("Merge sort %d monsters...\n", n);

  start_cpu = clock();
  merge_sort_recursive(list, 0, n-1, &comparisons, &copies, &block_copies, &mallocs,
                       use_name, use_weight);
  end_cpu = clock();

  printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
  print_clocks(end_cpu - start_cpu);
}

/* Recursive function for merge-insertion sort. */

//recursively calls itself to divide into subarray until size is less and equal to threshold which passes to insertion sort
void merge_insertion_sort_recursive(monster *list, int low_index, int high_index, 
                                    int *comparisons, int *copies, int *block_copies, int *mallocs,
                                    int use_name, int use_weight)
{

  int size = high_index-low_index;
  int mid = (low_index + high_index)/2;

  if(size <= 25){


    monster sub_arr_holder[size+1];


    //copy sub array into another array
    for(int i = low_index; i <= high_index; i++){
      sub_arr_holder[i-low_index] = list[i];
    }

    //sort sub array
    insertion_sort_internal(sub_arr_holder, size+1, comparisons, copies, block_copies, use_name, use_weight);

    //copy back into original list
    for(int i = low_index; i <= high_index; i++){
      list[i] = sub_arr_holder[i-low_index];
    }
    return;
    
  }else{


    mid = (low_index + high_index)/2;

    merge_insertion_sort_recursive(list, low_index, mid, comparisons, copies, block_copies, mallocs, use_name, use_weight);

    merge_insertion_sort_recursive(list, mid+1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);

    merge_sort_merge(list, low_index, mid, mid+1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);
    return;  
  }
  
}

/* Implement merge sort. */

//calls merge insertion recursion
void merge_insertion_sort(monster *list, int n, int use_name, int use_weight)
{
  int comparisons = 0;
  int copies = 0;
  int block_copies = 0;
  int mallocs = 0;
  clock_t start_cpu, end_cpu;

  printf("Merge-insertion sort %d monsters...\n", n);

  start_cpu = clock();
  merge_insertion_sort_recursive(list, 0, n-1, &comparisons, &copies, &block_copies, &mallocs,
                                 use_name, use_weight);
  end_cpu = clock();

  printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
  print_clocks(end_cpu - start_cpu);
}

/* Main program. */

void run_all_sorts(int n, int only_fast, int use_name, int use_weight) {
  monster *our_list = make_some_monsters(n);
  monster *our_unsorted_list = malloc(sizeof(monster) * n);

  printf("SORT SET: n = %d, %s, by %s\n\n", n, only_fast ? "fast sorts only" : "all sorts", use_name ? "name" : "weight");

  if(only_fast == 0) {
    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    bubble_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);

    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    selection_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);
    
    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    insertion_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);
  }

  memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
  quick_sort(our_unsorted_list, n, use_name, use_weight);
  check_monster_sort(our_unsorted_list, n, use_name, use_weight);

  memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
  merge_sort(our_unsorted_list, n, use_name, use_weight);
  check_monster_sort(our_unsorted_list, n, use_name, use_weight);

  memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
  merge_insertion_sort(our_unsorted_list, n, use_name, use_weight);
  check_monster_sort(our_unsorted_list, n, use_name, use_weight);

  printf("SORT SET COMPLETE\n\n");

  free(our_list);
  free(our_unsorted_list);
  
}

int main(void) {

   
  run_all_sorts(50, 0, 0, 1); 
  run_all_sorts(50, 0, 1, 0);
  run_all_sorts(500, 0, 0, 1);
  run_all_sorts(500, 0, 1, 0);
  run_all_sorts(5000, 0, 0, 1);
  run_all_sorts(5000, 0, 1, 0);
  run_all_sorts(50000, 1, 0, 1);
  run_all_sorts(50000, 1, 1, 0);
  run_all_sorts(500000, 1, 0, 1);
  run_all_sorts(500000, 1, 1, 0);
  
  
}