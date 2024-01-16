#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"

typedef struct monster
{
    int id;
    char *name;
    char *element;
    int population;
} monster;
typedef struct region
{
    char *name;
    int nmonsters;
    int total_population;
    monster **monsters;
} region;
typedef struct itinerary
{
    int nregions;
    region **regions;
    int captures;
} itinerary;
typedef struct trainer
{
    char *name;
    itinerary *visits;
} trainer;

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

//gets number from string we are working with
int get_num_from_string(FILE *ifp)
{
    char str[201];
    int num = 0;

    get_next_nonblank_line(ifp, str, 200);
    sscanf(str, "%d", &num);
    return num;
}

//allocate space for monsters with size num_monsters
monster *make_monster_space(int num_monsters)
{
    monster *mnstr_ptr = malloc(sizeof(monster) * num_monsters);
    return mnstr_ptr;
}

//reads input file for info for monsters
void read_monster(FILE *ifp, char *name, char *element, char *population)
{
    char str[201];
    get_next_nonblank_line(ifp, str, 200);
    sscanf(str, "%s %s %s", name, element, population);
}

//constructor for monsters, fills the space we allocated
void load_monster_space(FILE *ifp, monster *mnstr_ptr, int id_r)
{
    //initializes all the vars we need to load for ptr_monsters
    char name_r[201];
    char element_r[201];
    char population_str[201];
    char str[201];

    read_monster(ifp, name_r, element_r, population_str);

    //loads all info into struct
    int population_r = atoi(population_str);
    mnstr_ptr->name = strdup(name_r);
    mnstr_ptr->element = strdup(element_r);
    mnstr_ptr->population = population_r;
    mnstr_ptr->id = id_r;
    //str_r indicates that it's a string to store what we're reading and not a struct element
}

//prints our monsters in console for debugging purposes
void print_monsters(monster *mnstr_ptr, int num_monsters)
{
    printf("\n%d monsters", num_monsters);
    int i;
    for (i = 0; i < num_monsters; i++)
    {
        printf("\n%d %s %s %d", (mnstr_ptr + i)->id, (mnstr_ptr + i)->name, (mnstr_ptr + i)->element, (mnstr_ptr + i)->population);
    }
    printf("\n");
}

//get the index of the monster in each region so that they can store in an array of pointers
int get_monster_index(FILE *ifp, monster *mnstr_ptr, int total_num_monsters)
{
    int i = 0;
    char monster_name[201];
    get_next_nonblank_line(ifp, monster_name, 200);

    for (i = 0; i < total_num_monsters; i++)
    {
        if (strcmp(monster_name, mnstr_ptr[i].name) == 0)
            return i;
    }

    return 0;
}

//frees monster from allocation
void free_monster(monster *mnstr_ptr, int num_monsters)
{
    int i;
    for (i = 0; i < num_monsters; i++)
    {
        if ((mnstr_ptr + i)->name != NULL)
        {
            free((mnstr_ptr + i)->name);
            (mnstr_ptr + i)->name = NULL;
        }
        if ((mnstr_ptr + i)->element != NULL)
        {
            free((mnstr_ptr + i)->element);
            (mnstr_ptr + i)->element = NULL;
        }
        (mnstr_ptr + i)->id = 0;
        (mnstr_ptr + i)->population = 0;
    }
    free(mnstr_ptr);
}

//allocate space for regions with size num_regions
region *make_region_space(int num_regions)
{
    region *reg_ptr = malloc(sizeof(region) * num_regions);
    return reg_ptr;
}

//constructor for regions, fills the space we allocated
void load_regions(FILE *ifp, region *reg_ptr, monster *mnstr_ptr, int num_total_monsters)
{

    //initializes vars
    char name_r[201];
    get_next_nonblank_line(ifp, name_r, 200);
    int i = 0;
    int monster_index = 0;
    int total_population_r = 0;

    //fills the struct elements
    reg_ptr->name = strdup(name_r);
    reg_ptr->nmonsters = get_num_from_string(ifp);
    reg_ptr->monsters = (monster **)malloc(sizeof(mnstr_ptr) * reg_ptr->nmonsters);

    for (i = 0; i < reg_ptr->nmonsters; i++)
    {
        monster_index = get_monster_index(ifp, mnstr_ptr, num_total_monsters);
        reg_ptr->monsters[i] = (mnstr_ptr + monster_index);
        total_population_r += reg_ptr->monsters[i]->population;
    }
    reg_ptr->total_population = total_population_r;
}

//prints region index to console for debugging purposes
void print_regions(region *reg_ptr, int num_regions)
{
    int i;
    int k;

    for (int i = 0; i < num_regions; i++)
    {
        printf("\n%d %s\n%d\n", (reg_ptr + i)->total_population, (reg_ptr + i)->name, (reg_ptr + i)->nmonsters);
        for (k = 0; k < (reg_ptr + i)->nmonsters; k++)
            printf("%s\n", (reg_ptr + i)->monsters[k]->name);
    }
}

//get the index of the region we can store in an array of pointers
int get_region_index(FILE *ifp, region *reg_ptr, int total_region_num)
{
    int i = 0;
    char region_name[201];
    get_next_nonblank_line(ifp, region_name, 200);

    for (i = 0; i < total_region_num; i++)
    {
        if (strcmp(region_name, reg_ptr[i].name) == 0)
            return i;
    }
    return 0;
}

//frees regions from allocation
void free_region(region *reg_ptr, int num_regions)
{
    int i;
    int k;
    for (i = 0; i < num_regions; i++)
    {
        if ((reg_ptr + i)->name != NULL)
        {
            free((reg_ptr + i)->name);
            (reg_ptr + i)->name = NULL;
        }
        for (k = 0; k < (reg_ptr + i)->nmonsters; k++)
        {
            (reg_ptr + i)->monsters[k] = NULL;
        }
        (reg_ptr + i)->nmonsters = 0;
        (reg_ptr + i)->total_population = 0;
        free((reg_ptr + i)->monsters);
    }
    free(reg_ptr);
}

//allocate space for trainers with size num_traomers
trainer *make_trainer_space(int num_trainers)
{
    trainer *train_ptr = malloc(sizeof(trainer) * num_trainers);
    return train_ptr;
}

//constructor for itinerary, fills the space we allocated
void load_itinerary(FILE *ifp, itinerary *it, region *reg_ptr, trainer *train_ptr, int num_total_regions)
{
    int i = 0;
    int region_index = 0;

    it->captures = get_num_from_string(ifp);
    it->nregions = get_num_from_string(ifp);
    it->regions = (region **)malloc(sizeof(it) * it->nregions);

    //filling up regions
    for (i = 0; i < it->nregions; i++)
    {
        region_index = get_region_index(ifp, reg_ptr, num_total_regions);
        it->regions[i] = (reg_ptr + region_index);
    }
}

//constructor for trainers, fills the space we allocated
void load_trainers(FILE *ifp, trainer *train_ptr, region *reg_ptr, int num_total_regions, int num_trainers)
{
    int i = 0;
    char name_r[201];
    get_next_nonblank_line(ifp, name_r, 200);
    train_ptr->name = strdup(name_r);
    train_ptr->visits = malloc(sizeof(train_ptr) * num_trainers);

    //load visits
    load_itinerary(ifp, (train_ptr->visits) + i, reg_ptr, train_ptr, num_total_regions);
}

//prints trainers index to console for debugging purposes
void print_trainers(trainer *train_ptr, int num_trainers)
{
    int i;
    int k;

    for (int i = 0; i < num_trainers; i++)
    {
        printf("\n%s \n%d captures\n%d regions\n", (train_ptr + i)->name, (train_ptr + i)->visits->captures, (train_ptr + i)->visits->nregions);
        for (k = 0; k < (train_ptr + i)->visits->nregions; k++)
            printf("%s\n", (train_ptr + i)->visits->regions[k]->name);
    }
}

//frees trainer from allocation
void free_trainer(trainer *train_ptr, int num_trainer)
{
    int i;
    int k;
    for (i = 0; i < num_trainer; i++)
    {
        if ((train_ptr + i)->name != NULL)
        {
            free((train_ptr + i)->name);
            (train_ptr + i)->name = NULL;
        }
        for (k = 0; k < (train_ptr + i)->visits->nregions; k++)
        {
            //free((train_ptr + i)->visits->regions[k]);
            (train_ptr + i)->visits->regions[k] = NULL;
        }
        (train_ptr + i)->visits->captures = 0;
        (train_ptr + i)->visits->nregions = 0;
        free((train_ptr + i)->visits);
        free((train_ptr + i)->visits->regions);
    }
    free(train_ptr);
}

//calculates the final output and prints it out to ofp
void calculate(FILE *ofp, trainer *ptr_trainers, int num_trainers)
{
    int i;
    int k;
    int j;
    int ans;
    double divided;
    int captures;
    double relative_population;
    double total_population;

    for (i = 0; i < num_trainers; i++)
    {
        //makes newline between each trainer for formatting
        if (i != 0)
            fprintf(ofp, "\n\n");

        fprintf(ofp, "%s", (ptr_trainers + i)->name);
        for (k = 0; k < (ptr_trainers + i)->visits->nregions; k++)
        {
            fprintf(ofp, "\n%s", (ptr_trainers + i)->visits->regions[k]->name);
            for (j = 0; j < (ptr_trainers + i)->visits->regions[k]->nmonsters; j++)
            {
                relative_population = (ptr_trainers + i)->visits->regions[k]->monsters[j]->population;
                total_population = (ptr_trainers + i)->visits->regions[k]->total_population;
                divided = relative_population / total_population;
                captures = (ptr_trainers + i)->visits->captures;
                ans = round(divided * captures);

                //printing out per monster and its result
                if (ans != 0)
                {
                    fprintf(ofp, "\n%d %s", ans, (ptr_trainers + i)->visits->regions[k]->monsters[j]->name);
                }
            }
        }
    }
}

int main(void)
{
    atexit(report_mem_leak);

    //opens input files and output files
    FILE *ifp;
    FILE *ofp;
    ifp = fopen("cop3502-as1-input.txt", "r");
    ofp = fopen("cop3502-as1-output-ruiz-trishaesther.txt", "w");

    //variables
    int num_monsters = 0;
    monster *ptr_monsters;
    int num_regions = 0;
    region *ptr_regions;
    int num_trainers = 0;
    trainer *ptr_trainers;
    int i;

    //make monster index
    num_monsters = get_num_from_string(ifp);
    ptr_monsters = make_monster_space(num_monsters);
    for (i = 0; i < num_monsters; i++)
    {
        load_monster_space(ifp, ptr_monsters + i, i);
    }

    //make region index
    num_regions = get_num_from_string(ifp);
    ptr_regions = make_region_space(num_regions);
    for (i = 0; i < num_regions; i++)
    {
        load_regions(ifp, ptr_regions + i, ptr_monsters, num_monsters);
    }

    //make trainer index
    num_trainers = get_num_from_string(ifp);
    ptr_trainers = make_trainer_space(num_trainers);
    int num_trainers_temp = num_trainers;
    for (i = 0; i < num_trainers; i++)
    {
        load_trainers(ifp, ptr_trainers + i, ptr_regions, num_regions, num_trainers);
    }

    //calculate final output
    calculate(ofp, ptr_trainers, num_trainers);

    //debugging to console
    // print_monsters(ptr_monsters, num_monsters);
    // print_regions(ptr_regions, num_regions);
    // print_trainers(ptr_trainers, num_trainers);

    //frees every struct
    free_trainer(ptr_trainers, num_trainers);
    free_region(ptr_regions, num_regions);
    free_monster(ptr_monsters, num_monsters);
    fclose(ifp);
    fclose(ofp);
    return 0;
}
