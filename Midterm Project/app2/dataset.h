# ifndef DATASET_H
# define DATASET_H

typedef struct set SET;

SET *createDataSet(int maxElts);

void destroyDataSet(SET *sp);

int searchID(SET *sp, int id);

void insert(SET *sp, int age, int id);

void deletion(SET *sp, int id); 

# endif /* SET_H */