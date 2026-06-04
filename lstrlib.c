char *buffer = malloc(size);
if (buffer == NULL) return NULL; /* Handle allocation failure */
memcpy(buffer, source, strlen(source) + 1); /* Safe copy with bounds checking */
/* Additional secure operations */