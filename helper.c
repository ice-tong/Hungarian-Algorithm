#include <stdio.h>
#include <stdlib.h>
#include "helper.h"


int get_min(int* arr);

void print_matrix(int** matrix, int row_num, int col_num);

int* init_array(int lenght, int init_value);

int** init_matrix(int row_num, int col_num, int init_value);


int
get_min(int* arr)
{
    int arr_min = arr[0];
    int arr_lenght = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < arr_lenght; i++) {
        if (arr_min > arr[i]) arr_min = arr[i];
    }
    return arr_min;
}


void
print_matrix(
    int** matrix, 
    int row_num, 
    int col_num
    )
{
    for (int i = 0; i < row_num; i++) {
        for (int j = 0; j < col_num; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}


int*
init_array(int lenght, int init_value)
{
    int* array;
    array = (int*) malloc(sizeof(int) * lenght);
    for (int i = 0; i < lenght; i++) {
        array[i] = init_value;
    }
    return array;
}


int**
init_matrix(int row_num, int col_num, int init_value)
{
    int** matrix;
    matrix = (int**) malloc(sizeof(int*) * row_num);
    for (int i = 0; i < row_num; i++) {
        matrix[i] = (int*) malloc(sizeof(int) * col_num);
        for (int j = 0; j < col_num; j++) {
            matrix[i][j] = init_value;
        }
    }
    return matrix;
}