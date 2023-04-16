#include <stdio.h>
#include <time.h>
#include <cstdlib>

#include "AVL.hpp"


void testRandData (const char *out_insert_file_name, const char *out_delete_file_name, int quantity);
void testSortData (const char *out_insert_file_name, const char *out_delete_file_name, int quantity);

void SwapInt (int *a, int *b);


int main () {

    for (int i = 100000; i <= 1000000; i += 100000) {

        testRandData("AVL_randData_insert.txt", "AVL_randData_delete.txt", i);
        testRandData("AVL_sortData_insert.txt", "AVL_sortData_delete.txt", i);
    }

    return 0;
}


void testRandData (const char *out_insert_file_name, const char *out_delete_file_name, int quantity) {

    FILE *out_insert = fopen(out_insert_file_name, "a");
    FILE *out_delete = fopen(out_delete_file_name, "a");

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

    fprintf(out_insert, "%d %lg\n", quantity, 1000.0 * ((double) (time_end - time_start)) / CLOCKS_PER_SEC);
    fclose(out_insert);

    time_start = clock();
    for (int i = 0; i < quantity / 2; i++) {

        root = Delete(root, rand_swap[i]);
    }
    time_end = clock();

    fprintf(out_delete, "%d %lg\n", quantity, 1000.0 * ((double) (time_end - time_start)) / CLOCKS_PER_SEC);
    fclose(out_delete);

    free(rand_data);
 }

 void testSortData (const char *out_insert_file_name, const char *out_delete_file_name, int quantity) {

    FILE *out_insert = fopen(out_insert_file_name, "a");
    FILE *out_delete = fopen(out_delete_file_name, "a");

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

    fprintf(out_insert, "Insertion time: %lg ms\n", 1000.0 * ((double) (time_end - time_start)) / CLOCKS_PER_SEC);
    fclose(out_insert);

    time_start = clock();
    for (int i = 0; i < quantity / 2; i++) {

        root = Delete(root, rand_swap[i]);
    }
    time_end = clock();

    fprintf(out_delete, "Deletion time: %lg ms\n\n", 1000.0 * ((double) (time_end - time_start)) / CLOCKS_PER_SEC);
    fclose(out_delete);

    free(rand_data);
 }

 void SwapInt (int *a, int *b) {

    if (!a || !b) return;

    int tmp = *a;
    *a = *b;
    *b = tmp;
 }
