#include <electronetsoft/util/filesystem/file_verify.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    char path[128];
    int __return = get_path_from_fd(STDOUT_FILENO, path, sizeof (path));
    if (!__return) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(errno);
    }
    fprintf(stdout, "The path of fd=%d is %s\n", STDOUT_FILENO, path);

    return 0;
}