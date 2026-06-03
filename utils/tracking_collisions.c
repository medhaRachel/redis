#define MAX_COLLISIONS 10000
#define DISTANCE_THRESHOLD 100

// Sort collisions by x-coordinate
qsort(collisions, collision_count, sizeof(collision), compare_by_x);

// Process collisions with spatial optimization
for (int i = 0; i < collision_count; i++) {
    // Check only nearby collisions within threshold
    int start_j = i - 1;
    int end_j = i + 1;
    
    // Find range of potential collisions
    while (start_j >= 0 && 
           collisions[i].x - collisions[start_j].x < DISTANCE_THRESHOLD) {
        start_j--;
    }
    
    while (end_j < collision_count && 
           collisions[end_j].x - collisions[i].x < DISTANCE_THRESHOLD) {
        end_j++;
    }
    
    // Check collisions in the range
    for (int j = start_j + 1; j < end_j; j++) {
        if (i != j && check_collision(collisions[i], collisions[j])) {
            handle_collision(collisions[i], collisions[j]);
        }
    }
}

// Helper comparison function
int compare_by_x(const void *a, const void *b) {
    return ((struct Collision*)a)->x - ((struct Collision*)b)->x;
}