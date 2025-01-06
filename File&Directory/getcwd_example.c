#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h> // For PATH_MAX

// --- Replacement for err_sys from "apue.h" ---
void err_sys(const char *msg) {
    perror(msg);
    exit(1);
}

// --- Simplified replacement for path_alloc ---
// In a real "apue.h" implementation, this might dynamically
// allocate memory and potentially resize it if needed.
// This simplified version allocates a fixed-size buffer.
char* path_alloc(size_t *size) {
    long pathmax;
    errno = 0;
    if ((pathmax = pathconf("/", _PC_PATH_MAX)) == -1) {
        if (errno == 0) {
            pathmax = 1024; // Default if PATH_MAX is indeterminate
        } else {
            return NULL; // Error getting path max
        }
    } else {
        pathmax++; // Add 1 for null terminator
    }
    if ((*size = (size_t)pathmax) < 0) {
        return NULL; // Should not happen with PATH_MAX
    }
    return malloc(*size);
}

int main(void) {
    char *ptr;
    size_t size;

    // Try to change the current working directory
    if (chdir("/usr/spool/uucppublic") < 0) {
        err_sys("chdir failed");
    }

    // Allocate memory to hold the current working directory path
    if ((ptr = path_alloc(&size)) == NULL) {
        err_sys("path_alloc failed");
    }

    // Get the current working directory
    if (getcwd(ptr, size) == NULL) {
        err_sys("getcwd failed");
    }

    // Print the current working directory
    printf("cwd = %s\n", ptr);

    free(ptr); // Free the allocated memory
    exit(0);
}