#include <stdio.h>
#include <time.h>
#include <cstdlib>

#include "binSortTree.hpp"


void testRandData (const char *out_file_name, int quantity);
void testSortData (const char *out_file_name, int quantity);

 void SwapInt (int *a, int *b);


int main () {

    testRandData("binSearchTree_randData.txt", 100000);
    testSortData("binSearchTree_sortData.txt", 100000);

    return 0;
}


void testRandData (const char *out_file_name, int quantity) {

    FILE *out = fopen(out_file_name, "w");

    Node *root = nullptr;

    int *rand_data = (int*) calloc(quantity, sizeof(int));
    int *rand_swap = (int*) calloc(quantity, sizeof(int));

    for (int i = 0; i < quantity; i++) {

        rand_data[i] = rand();
        rand_swap[i] = rand_data[i];
    }

    for (int i = 0; i < quantity; i++) {

        SwapInt(&rand_swap[i], &rand_swap[rand() % quantity]);
    }

    clock_t time_start = clock();
    for (int i = 0; i < quantity; i++) {

        root = Insert(root, rand_data[i]);
    }
    clock_t time_end = clock();

    fprintf(out, "Insertion time: %lg ms\n", 1000.0 * ((double) (time_end - time_start)) / CLOCKS_PER_SEC);

    time_start = clock();
    for (int i = 0; i < quantity / 2; i++) {

        root = Delete(root, rand_swap[i]);
    }
    time_end = clock();

    fprintf(out, "Deletion time: %lg ms\n\n", 1000.0 * ((double) (time_end - time_start)) / CLOCKS_PER_SEC);

    fclose(out);
    free(rand_data);
 }

 void testSortData (const char *out_file_name, int quantity) {

    FILE *out = fopen(out_file_name, "w");

    Node *root = nullptr;

    int *rand_data = (int*) calloc(quantity, sizeof(int));
    int *rand_swap = (int*) calloc(quantity, sizeof(int));

    for (int i = 0; i < quantity; i++) {

        rand_data[i] = i;
        rand_swap[i] = rand_data[i];
    }

    for (int i = 0; i < quantity; i++) {

        SwapInt(&rand_swap[i], &rand_swap[rand() % quantity]);
    }

    clock_t time_start = clock();
    for (int i = 0; i < quantity; i++) {

        root = Insert(root, rand_data[i]);
    }
    clock_t time_end = clock();

    fprintf(out, "Insertion time: %lg ms\n", 1000.0 * ((double) (time_end - time_start)) / CLOCKS_PER_SEC);

    time_start = clock();
    for (int i = 0; i < quantity / 2; i++) {

        root = Delete(root, rand_swap[i]);
    }
    time_end = clock();

    fprintf(out, "Deletion time: %lg ms\n\n", 1000.0 * ((double) (time_end - time_start)) / CLOCKS_PER_SEC);

    fclose(out);
    free(rand_data);
 }

 void SwapInt (int *a, int *b) {

    if (!a || !b) return;

    int tmp = *a;
    *a = *b;
    *b = tmp;
 }
