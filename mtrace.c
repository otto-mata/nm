#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>

static void *(*real_malloc)(size_t) = NULL;
static void (*real_free)(void *) = NULL;
static void *(*real_mmap)(void *, size_t, int, int, int, off_t) = NULL;
static int (*real_munmap)(void *, size_t) = NULL;

static void mtrace_init(void)
{
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    real_free = dlsym(RTLD_NEXT, "free");
    real_mmap = dlsym(RTLD_NEXT, "mmap");
    real_munmap = dlsym(RTLD_NEXT, "munmap");

    if (!real_malloc || !real_free || !real_mmap || !real_munmap)
    {
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
    }
}

void *malloc(size_t size)
{
    if (real_malloc == NULL)
    {
        mtrace_init();
    }

    void *p = NULL;
    fprintf(stderr, "malloc(%zu) = ", size);
    p = real_malloc(size);
    fprintf(stderr, "%p\n", p);
    return p;
}

void free(void *p)
{
    if (real_free == NULL)
    {
        mtrace_init();
    }

    fprintf(stderr, "free(%p)\n", p);
    real_free(p);
}

static size_t mmap_size_to_pages(size_t length)
{
    int ps = getpagesize();
    return (((length / ps) + 1) * ps);
}

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    if (real_mmap == NULL)
    {
        mtrace_init();
    }

    fprintf(stderr, "mmap(%p, %zu (%zu), %d, %d, %d, %zu) = ",
            addr, length, mmap_size_to_pages(length), prot, flags, fd, offset);
    void *p = real_mmap(addr, length, prot, flags, fd, offset);
    fprintf(stderr, "%p\n", p);
    return (p);
}

int munmap(void *addr, size_t length)
{
    if (real_munmap == NULL)
    {
        mtrace_init();
    }

    fprintf(stderr, "munmap(%p, %zu) = ", addr, length);
    int ret = real_munmap(addr, length);
    fprintf(stderr, "%d\n", ret);
    return ret;
}