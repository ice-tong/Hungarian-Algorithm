#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

#define GIRL_NUM 3
#define BOY_NUM 3


int
find_girl_matched_by_boy(
    int boy, 
    int** matched,
    int matched_row_num
    )
{
    // Find a match girl of the given boy, else return -1.
    for (int i = 0; i < matched_row_num; i++) {
        if (matched[i][boy] == 1) return i;
    }
    return -1;
}

/*
A recursive function to match a boy for the given girl.
If a boy connect the given girl (in other words: edges[girl][boy] == 1)
Then check if this boy have be matched, \
    if true, recursive shift the boy-matched-girl to another boy as far as possible, \
    else this boy and the given girl match success!
*/
int
match_boy(
    int girl, 
    int* visited, 
    int** matched, 
    int** edges,
    int edges_row_num,
    int edges_col_num
    )
{
    for (int j = 0; j < edges_col_num; j++) { // for each boy
        // check if connected, else continue.
        if (edges[girl][j] == 0) continue;
        // check if visited, else continue.
        if (visited[j] == 1) continue;

        // Now, this boy is visited.
        visited[j] = 1;
        // Check if this boy have be matched.
        int girl_matched = find_girl_matched_by_boy(
            j, matched, edges_row_num
        );

        if (girl_matched == -1) {
            // This boy haven't be matched, happy ending!
            matched[girl][j] = 1;
            return 1;
        } else {
            // This boy have be matched, \
                let's try to shift the boy-matched-girl to another boy.
            int boy_shift_flag = match_boy(
                girl_matched, visited, matched, 
                edges, edges_row_num, edges_col_num
            );
            if (boy_shift_flag == 1) {
                // Shift sucess, don't forget to \
                    detach the orignal matched girl from this boy.
                matched[girl_matched][j] = 0;
                matched[girl][j] = 1;
                return 1;
            }
        }
        
    }
    return 0;
}


void
hungarian(
    int** matched, // A matrix stored match flag.
    int** edges, // A matrix stored edge relationship.
    int row_num, 
    int col_num
    )
{
    // For each girl, find a match boy as far as possible.
    for (int i = 0; i < row_num; i++) {
        // Init a zero array named visited, store the visited job flag.
        int* visited = init_array(col_num, 0);
        match_boy(
            i, visited, matched, 
            edges, row_num, col_num
        );
    }
}


void
main()
{
    // edges initialization
    int edges_[GIRL_NUM][BOY_NUM] = {
        {1, 0, 1},
        {0, 1, 0},
        {0, 0, 1}
    };
    int ** edges = (int**) malloc(sizeof(int*) * GIRL_NUM);
    for (int i = 0; i < GIRL_NUM; i++) {
        edges[i] = edges_[i];
    }

    printf("Edges: \n");
    print_matrix(edges, GIRL_NUM, BOY_NUM);

    // Using huangarian algorithm to find max match.
    int** matched = init_matrix(GIRL_NUM, BOY_NUM, 0);
    hungarian(matched, edges, GIRL_NUM, BOY_NUM);

    printf("Max Match: \n");
    print_matrix(matched, GIRL_NUM, BOY_NUM);

}
