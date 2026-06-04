/* Fixed buffer operation with proper bounds checking */
if (end > len) end = len;
while (start < end) {
  /* Safe buffer access with proper bounds checking */
  *dest++ = *src++;
  start++;
}
*dest = '\0'; /* Null terminate the result */