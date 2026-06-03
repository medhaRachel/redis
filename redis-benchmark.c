redisContext* getRedisContext(const char* host, int port) {
    redisContext* context = redisConnectNonBlock(host, port);
    if (context == NULL) {
        return NULL;
    }
    
    // Wait for connection to complete with timeout
    int fd = context->fd;
    struct timeval tv;
    tv.tv_sec = 5;  // 5 second timeout
    tv.tv_usec = 0;
    
    fd_set write_fds;
    FD_ZERO(&write_fds);
    FD_SET(fd, &write_fds);
    
    int result = select(fd + 1, NULL, &write_fds, NULL, &tv);
    if (result <= 0) {
        redisFree(context);
        return NULL;
    }
    
    // Check if connection was successful
    int error = 0;
    socklen_t len = sizeof(error);
    if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len) < 0 || error != 0) {
        redisFree(context);
        return NULL;
    }
    
    return context;
}