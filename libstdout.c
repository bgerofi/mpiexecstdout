#define _GNU_SOURCE
#include <dlfcn.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#undef openat
#undef open

typedef int (*__open_fn)(const char *pathname,
	int flags,
	mode_t mode);

static __open_fn orig_open = 0;


int dup_stdout(const char *path)
{
	if (!getenv("LIBSTDOUT_FILENAME") ||
		strcmp(getenv("LIBSTDOUT_FILENAME"), path)) {
		return 0;
	}

	return dup(1);
}


int open(const char *pathname, int flags, mode_t mode)
{
	int fd;

	if (!orig_open) {
		orig_open =
			(__open_fn)dlsym(RTLD_NEXT, "open");
	}

	fd = dup_stdout(pathname);
	if (fd > 0)
		return fd;

	return orig_open(pathname, flags, mode);
}


typedef int (*__openat_fn)(int dirfd,
	const char *pathname,
	int flags,
	mode_t mode);

static __openat_fn orig_openat = 0;


int openat(int dirfd,
	const char *pathname,
	int flags,
	mode_t mode)
{
	int fd;

	if (!orig_openat) {
		orig_openat =
			(__openat_fn)dlsym(RTLD_NEXT, "openat");
	}

	fd = dup_stdout(pathname);
	if (fd > 0)
		return fd;

	return orig_openat(dirfd, pathname, flags, mode);
}

