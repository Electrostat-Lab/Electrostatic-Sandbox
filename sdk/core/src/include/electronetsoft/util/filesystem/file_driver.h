/**
 * @brief A virtual file driver API aims at providing
 * an intermediate software to process specific
 * types of database-like files (incl. txt, sqlite, and json).
 *
 * @author pavl_g.
 */
#ifndef _FILE_DRIVER_H_
#define _FILE_DRIVER_H_

#ifndef _ELECTRO_MIO

#ifdef __cplusplus
extern "C" {
#endif

#include <electronetsoft/util/utilities.h>

//file-name: {
//    key_0: data_0,
//    key_1: data_1,
//    key_2: data_2,
//    key_3: [
//        data_3, data_4, data_5, ...
//    ],
//    key_4: {
//        key_4_0: data_4,
//        key_4_1: data_5,
//        ...
//    },
//    ...
//    key_n: data_n
//}

/**
 * @brief A driver operations model compatible with List and Map ADTs.
 * @details The hypothetical logic of the driver operations is to
 * build a graph of nested elements by chaining objects of [list_element]
 * all the way to string data through the [map_element] API; through this
 * driver API; one may serialize a [map] or a [list] data structure seamlessly;
 * even graphs could be serialized through [linked_buffer]; a concrete
 * information structure of [list] type.
 * @note The driver operations is a user accessible interface.
 */
struct file_driver_op {
    status_code (*insert_title)(file_driver *, const char *);
    status_code (*remove_title)(file_driver *);
    /**
     * Inserts a hierarchy of [map_elements] into the
     * data buffer of the virtual driver under a specific
     * key.
     *
     * @note this operation may or may not involve key-hashing
     * depending on the concrete driver implementation.
     */
    status_code (*insert)(file_driver *, map_element);

    /**
     * Inserts a hierarchy of [map_elements] into the
     * data buffer of the virtual driver under a specific
     * key at a particular index.
     *
     * @note this operation may or may not involve key-hashing
     * depending on the concrete driver implementation.
     */
    status_code (*insert_at)(file_driver *, map_element, uint64_t);

    /**
     * Removes a hierarchy of [map_elements] from the
     * data buffer of the virtual driver under a specific
     * key.
     *
     * @note this operation may or may not involve key-hashing
     * depending on the concrete driver implementation.
     */
    status_code (*remove)(file_driver *, map_element);

    /**
     * Removes a specific element from a
     * hierarchy of [map_elements] from the
     * data buffer of the virtual driver under a specific
     * key.
     *
     * @note this operation may or may not involve key-hashing
     * depending on the concrete driver implementation.
     */
    status_code (*remove_at)(file_driver *, map_element, uint64_t);

    status_code (*retrieve)(file_driver *, map_element);

    status_code (*retrieve_at)(file_driver *, map_element, uint64_t);
};

struct file_processing_metadata {
    char *data;
    char *processed_chunk;
    __off_t pos;
    __off_t size;
};

struct driver_lexical_component {
    char *delimiter;
    uint8_t registry;
};

/**
 * The system examines the database buffer from the
 * [file_driver] or from the input the data structure;
 * and each tie
 */
struct driver_lexical_grammar {
    // '{' and ':'
    driver_lexical_component object_delimiter_0;
    driver_lexical_component object_delimiter_1;

    // '[' and ']'
    driver_lexical_component array_delimiter_0;
    driver_lexical_component array_delimiter_1;

    // ':' and ','
    driver_lexical_component data_delimiter_0;
    driver_lexical_component data_delimiter_1;

    // '{' and ':'
    driver_lexical_component key0_delimiter_0;
    driver_lexical_component key1_delimiter_1;

    /**
     * The start delimiter for the key
     * is usually the character ':'
     * at least for JSON and Maps
     * standards.
     */
     // ',' and ':'
    driver_lexical_component key_delimiter_0;
    /**
     * The end delimiter for the key
     * is usually the character ','
     * at least for JSON and Map
     * standards.
     */
    driver_lexical_component key_delimiter_1;
};

struct file_driver_processor {
    status_code (*on_file_preprocessed)(file_driver *);
    status_code (*on_file_processing)(file_driver *, file_processing_metadata);
    status_code (*on_file_processing_err_encountered)(file_driver *, file_processing_metadata, status_code);
    status_code (*on_file_postprocessed)(file_driver *);

    status_code (*on_lexical_encountered)(file_driver *, char *);
};

struct file_driver {
    typed_pointer driver;
    file_processing_metadata *metadata;
    file_driver_op *operations;
    char *file_name;
    char *file_ext;
    char *data;
};

status_code file_driver_init(file_driver *, typed_pointer);
status_code file_driver_linear_processing(file_driver *);
status_code file_driver_terminate(file_driver *);

#ifdef __cplusplus
};
#endif

#endif
#endif