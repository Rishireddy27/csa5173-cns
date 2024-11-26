#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LANES 25
#define CAPACITY_LANES 9
#define RATE_LANES 16
typedef struct {
    uint64_t lanes[LANES];
} StateMatrix;
void initialize_state(StateMatrix *state) {
    for (int i = 0; i < LANES; i++) {
        state->lanes[i] = 0;
    }
}
void process_block(StateMatrix *state, uint64_t *block) {
    for (int i = 0; i < LANES; i++) {
        state->lanes[i] ^= block[i];
    }
}
int count_zero_lanes(StateMatrix *state) {
    int zero_count = 0;
    for (int i = 0; i < CAPACITY_LANES; i++) {
        if (state->lanes[RATE_LANES + i] == 0) {
            zero_count++;
        }
    }
    return zero_count;
}
int main() {
    StateMatrix state;
    initialize_state(&state);

    uint64_t block[LANES];
    for (int i = 0; i < LANES; i++) {
        block[i] = rand() | 1;  
    }
	int blocks_processed = 0;
    while (count_zero_lanes(&state) > 0) {
        process_block(&state, block);
        blocks_processed++;
    }
	printf("Blocks required: %d\n", blocks_processed);

    return 0;
}

