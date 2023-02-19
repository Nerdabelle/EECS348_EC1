/*
 * ExtraCredit.c
 *
 *  Created on: Feb 19, 2023
 *      Author: a473s013
 */
#include <stdio.h>

// define the number of departments and programmers
#define NUM_DEPTS 5
#define NUM_PROGS 5

// function to find the preferred department of a programmer
int findPreferredDept(int programmer, int preferences[NUM_DEPTS][NUM_PROGS], int assigned[])
{
    // loop through the programmer's preferences
    for (int i = 0; i < NUM_DEPTS; i++) {
        // check if the department is available
        if (!assigned[preferences[programmer][i] - 1]) {
            return preferences[programmer][i] - 1;
        }
    }
    // if all preferences are taken, return -1
    return -1;
}

int main()
{
    // define an array to keep track of which department is assigned to each programmer
    int assigned[NUM_DEPTS] = {0};

    // open the input file
    FILE *inputFile = fopen("test.txt", "r");

    // read the preferences of the departments from the input file
    int deptPref[NUM_DEPTS][NUM_PROGS];
    for (int i = 0; i < NUM_DEPTS; i++) {
        for (int j = 0; j < NUM_PROGS; j++) {
            fscanf(inputFile, "%d", &deptPref[j][i]);
        }
    }

    // read the preferences of the programmers from the input file
    int progPref[NUM_PROGS][NUM_DEPTS];
    for (int i = 0; i < NUM_PROGS; i++) {
        for (int j = 0; j < NUM_DEPTS; j++) {
            fscanf(inputFile, "%d", &progPref[j][i]);
        }
    }

    // close the input file
    fclose(inputFile);

    // assign each programmer to a department
    for (int i = 0; i < NUM_PROGS; i++) {
        // find the preferred department of the programmer
        int dept = findPreferredDept(i, progPref, assigned);
        // if the preferred department is available, assign the programmer to it
        if (dept != -1) {
            assigned[dept] = 1;
            printf("Department %d will get Programmer %d\n", i+1, dept+1);
        }
        // if the preferred department is not available, consult the programmer's preferences
        else {
            for (int j = 0; j < NUM_DEPTS; j++) {
                dept = deptPref[i][j] - 1;
                if (findPreferredDept(i, progPref, assigned) == dept) {
                    assigned[dept] = 1;
                    printf("Department %d will get Programmer %d\n", i+1, dept+1);
                    break;
                }
            }
        }
    }

    return 0;
}

