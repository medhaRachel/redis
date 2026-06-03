qsort(set_a->elements, set_a->size, sizeof(int), compare_ints);
qsort(set_b->elements, set_b->size, sizeof(int), compare_ints);

int i = 0, j = 0;
while (i < set_a->size && j < set_b->size) {
    if (set_a->elements[i] < set_b->elements[j]) {
        i++;
    } else if (set_a->elements[i] > set_b->elements[j]) {
        j++;
    } else {
        // process matching elements
        i++;
        j++;
    }
}