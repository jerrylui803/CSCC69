#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int hand;

int clock_evict() {
	// keep running the clock, check PG_REF each time
    // if it's 0, then set to 1 and return hand
    while(1){
        // if ref number is 1,then set to 0.
        if(coremap[hand].pte->frame & PG_REF) {
            // set the reference bit to 0
            coremap[hand].pte->frame = coremap[hand].pte -> frame & ~PG_REF;
            hand ++;
            hand = hand % memsize;
        }
        // If it's 0, then set to 1 and return the hand.
        else {
            coremap[hand].pte->frame = coremap[hand].pte -> frame | PG_REF;
            return hand;
        }
    }
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {
	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {
	hand = 0;
}
