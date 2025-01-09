# 内存类

### 总览 [线程安全]

```c

#include <stdlib.h>
void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

```

#### `malloc` 申请内存

```c

void *malloc(size_t size);

/**
 * The malloc() function allocates size bytes and returns a pointer to the allocated memory.  The memory is not initialized.  * If size is 0, then malloc() returns either NULL, or a unique pointer value that can later be successfully passed to free().
*/

malloc() 申请的内存是字节数量，所以一般申请时都要计算字节，并且他申请的内存没有初始化

malloc(nmemb * size);

malloc(sizeof(val_type) * num) 这种方式更好

```
