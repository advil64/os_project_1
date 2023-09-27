/*
* Add NetID and names of all project partners
*
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/* Part 1 - Step 1 and 2: Do your tricks here
 * Your goal must be to change the stack frame of caller (main function)
 * such that you get to the line after "r2 = *( (int *) 0 )"
 */
void signal_handle(int signalno) {

    printf("handling segmentation fault!\n");

    /* Step 2: Handle segfault and change the stack*/
    int instr_len = 8;
    int addr_offset = 0xffffffffffffffd4;

    /* Step 3: Find the location of the program counter on the stack using GDB */
    char *signal_no_address = (char *)(&signalno);
    char *program_counter = signal_no_address - addr_offset;

    /* Step 4: Calculate the new program counter value */
    *program_counter += 8;
}


int main(int argc, char *argv[]) {

    int r2 = 0;

    /* Step 1: Register signal handler first*/
    signal(SIGSEGV, signal_handle);

    r2 = *( (int *) 0 ); // This will generate segmentation fault

    r2 = r2 + 1 * 30;
    printf("result after handling seg fault %d!\n", r2);

    return 0;
}