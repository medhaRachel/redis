redisContext* getRedisContext() {
    static redisContext* pool[10];
    static int pool_size = 0;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    
    pthread_mutex_lock(&mutex);
    if (pool_size > 0) {
        redisContext* c = pool[--pool_size];
        pthread_mutex_unlock(&mutex);
        return c;
    }
    pthread_mutex_unlock(&mutex);
    
    redisContext* c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        return NULL;
    }
    
    redisReply* reply = redisCommand(c, "PING");
    if (reply != NULL) {
        freeReplyObject(reply);
    } else {
        redisDisconnect(c);
        return NULL;
    }
    
    return c;
}

void returnRedisContext(redisContext* c) {
    static redisContext* pool[10];
    static int pool_size = 0;
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    
    if (c == NULL) return;
    
    pthread_mutex_lock(&mutex);
    if (pool_size < 10) {
        pool[pool_size++] = c;
        pthread_mutex_unlock(&mutex);
        return;
    }
    pthread_mutex_unlock(&mutex);
    
    redisDisconnect(c);
}