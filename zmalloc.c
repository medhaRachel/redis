void *zmalloc(size_t size) {
    if (size == 0) return NULL;
    void *ptr = malloc(size);
    if (!ptr) return NULL;
    return ptr;
}