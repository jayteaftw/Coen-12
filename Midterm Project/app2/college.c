/*
 * File:        college.c
 *
 * Author:      JT Vinolus
 * 
 * Date:        June 7 2019
 *
 *  * Mehtod: Array where ID Matches index. ID is determined if age array is not equal to -1.
 * 
 * Description: This file contains the needed main function 
 *              for midterm application 2.
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

    
    //Radmonly Generate a student record. If the ID is there, it will delete the ID from SET. If not, it will add the ID to the SET.
    printf("\n \n \n \nCreating a random student record.\n");
    int id = rand() % 2000 + 1;
    age = rand() % 12 + 18;
    if(searchID(class, id) == -1)
        insert(class, age, id);
    else
        deletion(class, id);
    
    
    destroyDataSet(class);
    

}