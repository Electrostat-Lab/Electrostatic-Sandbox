#include <electrostatic/electronetsoft/util/filesystem/file_operations.h>
#include <electrostatic/electronetsoft/util/filesystem/file_verify.h>

status_code init_serializer(pipe_serializer *serializer,
                            serializer_op_processor *_processor,
                            update_op_processor *__processor) {
    if (NULL == serializer) {
        return EUNDEFINEDBUFFER;
    }

    if (NULL != _processor && NULL != _processor->serializer_init_preprocessor) {
        _processor->serializer_init_preprocessor(serializer);
    }

    if (serializer->read_end.fd == serializer->write_end.fd) {
        return -1;
    }

    status_code ___status = update_file_attrs(&serializer->read_end, __processor);
    if (PASS != ___status) {
        return ___status;
    }

    ___status = update_file_attrs(&serializer->write_end, __processor);
    if (PASS != ___status) {
        return ___status;
    }

    if (NULL != _processor && NULL != _processor->serializer_init_postprocessor) {
        _processor->serializer_init_postprocessor(serializer);
    }

    return PASS;
}