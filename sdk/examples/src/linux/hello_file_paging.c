#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <electronetsoft/util/filesystem/file_operations.h>

static inline void update_model_preprocessor(file_mem *mem, void *caller) {
    if (caller != &read_into_mem) {
        return;
    }

    int fd = open("/home/pavl-g/Downloads/gbbct1.seq", O_RDONLY);

    if (fd < 0) {
        fprintf(stderr, "Error Encountered: %s\n", strerror(errno));
        exit(errno);
    }

    mem->fd = fd;
    mem->__auto_update_attrs = 0;
    mem->__file_attrs_preprocessor = 0;
}

static inline void update_model_postprocessor(file_mem *mem, void *caller) {
    mem->pager->paging_factor = 10000;
    fprintf(stdout, "%ld\n", mem->file_size);  
    mem->file_size = (mem->file_size - 1)/10;
    fprintf(stdout, "%ld\n", mem->file_size);
    mem->__file_attrs_postprocessor = 0;
}

static inline void op_preprocessor(file_mem *mem, void *caller) {
    if (0 != mem->bytes_processed || caller != &read_into_mem) {
        return ;
    } 

    mem->buffer = calloc(mem->n_bytes + 1, sizeof(char));
    if (NULL == mem->buffer) {
        return ;
    }
	// NB: this works for the this app main thread
	// Running using valgrind may require 
	// resizing the stack, as well for the valgrind
	// memcheck tool; use:
	// valgrind -v --main-stacksize=83886080 
	// 			./sdk/examples/cmake-build/linux/x86-64/hello_file_paging.elf 
	struct rlimit limit = {0};

    if (getrlimit(RLIMIT_STACK, &limit) == -1) {
        perror("getrlimit");
        return ;
    }

    limit.rlim_cur *= mem->pager->n_pages;
    limit.rlim_max *= mem->pager->n_pages;
    
    if (setrlimit(RLIMIT_STACK, &limit) == -1) {
        perror("setrlimit");
        return ;
    }
	return ;
}

static inline void op_postprocessor(file_mem *mem, void *caller) { 
    fprintf(stdout, "%s", mem->buffer);

    if (has_bytes_processing_completed(mem) == ASSERTION_SUCCESS) {
        status_code __code = read_into_mem(mem, 
            &((op_processor) {
                    .op_postprocessor = &op_postprocessor,
                    .op_preprocessor = &op_preprocessor
            }), 
            &((update_op_processor) {
                .update_model_preprocessor = &update_model_preprocessor,
                .update_model_postprocessor = &update_model_postprocessor,
            }));

        if (PASS != __code) {
            fprintf(stderr, "Error Encountered: %s\n", strerror(__code));
            exit(__code);
        }

        return ;
    }

    fprintf(stdout, "\n");
    free(mem->buffer);
    mem->buffer = NULL;

    int __code = close(mem->fd);

    if (__code < 0) {
        fprintf(stderr, "Error Encountered: %s\n", strerror(errno));
        exit(errno);
    }
}

int main(int argc, char const *argv[]) {
	fprintf(stdout, "Hello File Paging Automata!\n");

    op_processor __op_processors = {
        .op_postprocessor = &op_postprocessor,
        .op_preprocessor = &op_preprocessor
    };

    file_pager _file_pager = {
    	.current = &((file_page) {
    	}),
    };

    file_mem _file_mem = {
        .fd = -1,
        .trailing = '\0',
        .buffer = NULL,
        .pager = &_file_pager,
        .n_bytes = -1,
        .file_size = -1,
        .file_pos = -1,
        .__auto_update_attrs = 1,
        .__continue_after_eof = 0,
        .__file_attrs_preprocessor = 1,
        .__file_attrs_postprocessor = 1
    };

    update_op_processor __update_processors = {
        .update_model_preprocessor = &update_model_preprocessor,
        .update_model_postprocessor = &update_model_postprocessor,
    };

    status_code __status = read_into_mem(&_file_mem, &__op_processors, &__update_processors);

    if (PASS != __status) {
        fprintf(stderr, "Error Encountered: %s\n", strerror(__status));
        exit(__status);
    }

	return 0;
}