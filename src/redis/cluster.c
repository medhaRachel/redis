void setClusterKeyHashTag(clusterNode *node, clusterSlot *slot) {
    /* Asynchronous non-blocking call */
    updateClusterSlotsConfigurationAsync();
    /* ... rest of function */
}