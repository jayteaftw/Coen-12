/*
 * File:        college.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        June 7 2019
 *
 *  Mehtod: Sorted Array by Age.
 * 
 * Description: This file contains the needed main function 
 *              for midterm application 1.
 *
 * Commands: 
 */


# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
# include "dataset.h"
#include <time.h>

# define maxElts 3000



int main()
{

    srand(time(0));
    //Initialize Set
    SET *class;
    class = createDataSet(maxElts);

    //Initial 1000 Generation.
    int idCreate = 0;
    int age;
    for(int i = 0; i < 1000; i++)
    {
        idCreate = idCreate + (rand() % 2) + 1;
        age = (rand() % 13) + 18; 
        insert(class, age, idCreate);
    }

    printf("\n \n \n \nSorted Array.\n");
    printingList(class);
    
    //Radmonly Generate a student age. If the age is there, it will delete all ID with that age from SET. 
    printf("\n \n \n \nGenerating a random student age.\n");
    bool found;
    age = (rand() % 12) + 18;
    int idx = binarySearchAge(class, age, &found);
    printf("\n");
    if(found == true)
        deletion(class, idx, age);
    printf("\n");
    
    
    printf("The age gap is %d years.\n\n", maxAgeGap(class));

    destroyDataSet(class);
}