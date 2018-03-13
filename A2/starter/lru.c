#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

int *frame_num;

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int lru_evict() {
    // find the index of the oldest key in the array
    int old = 0;
    int old_index = 0;
    for (int i = 0; i < memsize; i++){
        if (frame_num[i] > old){
            old = frame_num[i];
            old_index = i;
        }
    }
    return old_index;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
    // increment age of every frame, then set the age of the frame being
    // referenced to 0
    int frame = PGTBL_INDEX(p->frame) ;
    for (int i = 0; i < memsize; i++){
        // if the frame was used before
        frame_num[i] = frame_num[i] + 1;
    }
    frame_num[frame] = 0;
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
    // set the the array
    // the element at index i represents the age of frame i
    frame_num = malloc(sizeof(int) * memsize);
    for (int i = 0; i < memsize; i++){
        frame_num[i] = 0;
    }
}

