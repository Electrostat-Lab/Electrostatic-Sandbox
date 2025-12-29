#if !(defined __UNIX_RES_H_ && defined _ELECTRO_MIO)
#define __UNIX_RES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <electronetsoft/util/utilities.h>

typedef struct uprocess uprocess;
typedef struct unix_exe unix_exe;
typedef struct uprocess_runtime uprocess_runtime;
typedef struct uprocess_pipe uprocess_pipe;
typedef struct uprocess_lifecycle uprocess_lifecycle;

struct uprocess {
    pid_t proc_id;
    uprocess_runtime *runtime;
    uint8_t is_active;
    int is_pendant;
    char *name;
    int __stdout;
    int __stdin;
    int __stderr;
};

struct unix_exe {
    const char *filename;
    char **const argv;
    char **const env;
};

struct uprocess_runtime { // a ready-to run automata for any newly forked process -- run these routines
    status_code (*pipe_read_process)(uprocess *, uprocess_pipe *, uprocess_lifecycle *);
    status_code (*exec)(unix_exe *); // first execute the program
    status_code (*pipe_write_process)(uprocess *, uprocess_pipe *, uprocess_lifecycle *); // then forward the [stdout] or others to a pipe to be read by other processes
};

struct uprocess_pipe { // a bidirectional pipe with unidirectional properties at the time of operation (half duplex channel).
    int pipe[2];
    uprocess *master;
    uprocess *slave;
};

struct uprocess_lifecycle {
    status_code (*on_process_fork)(uprocess *);
    void (*on_process_exit)(int __status, void *__arg);
    status_code (*current_process_runtime)(uprocess *);
    status_code (*forked_process_runtime)(uprocess *); // call this function from the SDK to start the forking runtime autoamta; that will invoke the lifecycle functions
    status_code (*fork_process_exec_runtime)(uprocess *, unix_exe *);
    status_code (*fork_failure)(uprocess *, status_code);
    status_code (*on_pipe_allocated)(uprocess *, uprocess_pipe *);
    status_code (*on_pipe_deallocated)(uprocess *, uprocess_pipe *);
    status_code (*on_pipe_write)(uprocess *, uprocess_pipe *);
    status_code (*on_pipe_read)(uprocess *, uprocess_pipe *);
    api_lifecycle apiLifecycle;
};

status_code init_uprocess_lifecycle(uprocess_lifecycle *); // initialize with defaults
status_code init_uprocess_lifecycle_from(uprocess_lifecycle *from, uprocess_lifecycle *to);

status_code init_uprocess_runtime_from(uprocess_runtime *from, uprocess_runtime *to);
status_code init_uprocess_runtime(uprocess_runtime *); // initialize with defaults

status_code fork_subprocess(uprocess *, uprocess_lifecycle *);
status_code exit_subprocess(uprocess *, uprocess_lifecycle *, status_code);

status_code fork_subprocess_exec(uprocess *, uprocess_lifecycle *, unix_exe *);

/**
 * @brief Allocates (i.e., Opens for R/W) an IO pipe and calls the lifecycle handlers after finishing or on error.
 */
status_code allocate_pipe(uprocess_pipe *, uprocess_lifecycle *);

/**
 * @brief Deallocates (i.e., Closes) an IO pipe and calls the lifecycle handlers after finishing or on error.
 */
status_code deallocate_pipe(uprocess_pipe *, uprocess_lifecycle *);

/**
 * @brief Writes the assigned process [stdout] buffer into the write end of the IO pipe.
 */
status_code pipe_write_process(uprocess *, uprocess_pipe *, uprocess_lifecycle *);

/**
 * @brief Reads the IO pipe buffer from the read-end and copies it to the [stdin] buffer of the assigned process.
 */
status_code pipe_read_process(uprocess *, uprocess_pipe *, uprocess_lifecycle *);

/**
 * @brief Writes data buffer directly onto the write end of the IO pipe.
 */
status_code pipe_write(uprocess_pipe *, uprocess_lifecycle *, void *, size_t); // writes data into the write end of the pipe

/**
 * @brief Reads a data buffer directly from the IO pipe.
 */
status_code pipe_read(uprocess_pipe *, uprocess_lifecycle *, void *, size_t);

#ifdef __cplusplus
};
#endif

#endif