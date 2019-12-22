# ifndef DATASET_H
# define DATASET_H

typedef struct set SET;

SET *createDataSet(int maxElts);

void destroyDataSet(SET *sp);

int binarySearchAge(SET *sp, int age, bool *found);

void insert(SET *sp, int age, int id);

void deletion(SET *sp, int idx, int age); 

int maxAgeGap(SET *sp);

void printingList(SET *sp);

# endif /* SET_H */