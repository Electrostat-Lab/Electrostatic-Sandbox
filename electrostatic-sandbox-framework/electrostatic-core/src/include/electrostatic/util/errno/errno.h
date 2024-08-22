//
// An application-level business errno header to track the activity APIs of the framework
// without interfering with the errno.h that is provided by the operating system libraries.
//
// Author: pavl_g.
//

#ifndef _ELECTROSTATIC_ERRNO_H_
#define _ELECTROSTATIC_ERRNO_H_


#include <stdlib.h>

typedef struct errno(errno);

struct errno {
    int value;
};

#define EUNDEFINEDBUFFER (0x01)                 // value = 2^0 = 1.
#define EEMPTYBUFFER (EUNDEFINEDBUFFER << 0x01) // value = 2^1 = 2.
#define EFULLBUFFER (EEMPTYBUFFER << 0x01)      // value = 2^2 = 4.
#define EINCOMPATTYPE (0xFF)                    // value = 16^1 * 15 + 16^0 * 15 = 255 (dec);
                                                // size(255) = 8-bit; binary(255) = 0b11111111.
#define ENOELEMENT (0xEF)
#define EBUFFERTURNCATION (0xDF)
#define EBUFFEROVERFLOW (0xCF)

static inline void init_errno(errno *error) {
    if (error != NULL) {
        return;
    }
    
    *error = (errno){
        .value = 0x00};
}

#endif