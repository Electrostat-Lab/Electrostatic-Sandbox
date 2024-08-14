#if !(defined _vector2d_H_ || defined _vector3d_H_)
#   error "Use vector2d or vector3d instead of this!"
#endif

#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <math.h>
#include <inttypes.h>

#if defined (_VECTOR2D_USE_UINT8_)
#   define coordinate uint8_t
#   define mod_coordinate coordinate
#   define vector2d_pow(v, p) ((uint8_t) powf(v, p)) 
#   define vector2d_atan2(y, x) ((uint8_t) atan2f(y, x)) 
#   define vector2d_acos(v) ((uint8_t) acosf(v)) 
#elif defined (_VECTOR2D_USE_INT8_)
#   define coordinate int8_t
#   define mod_coordinate coordinate
#   define vector2d_pow(v, p) ((int8_t) powf(v, p)) 
#   define vector2d_atan2(y, x) ((int8_t) atan2f(y, x)) 
#   define vector2d_acos(v) ((int8_t) acosf(v)) 
#elif defined (_VECTOR2D_USE_UINT16_)
#   define coordinate uint16_t
#   define mod_coordinate coordinate
#   define vector2d_pow(v, p) ((uint16_t) powf(v, p)) 
#   define vector2d_atan2(y, x) ((uint16_t) atan2f(y, x)) 
#   define vector2d_acos(v) ((uint16_t) acosf(v)) 
#elif defined (_VECTOR2D_USE_INT16_)
#   define coordinate int16_t
#   define mod_coordinate coordinate
#   define vector2d_pow(v, p) ((int16_t) powf(v, p)) 
#   define vector2d_atan2(y, x) ((int16_t) atan2f(y, x)) 
#   define vector2d_acos(v) ((int16_t) acosf(v)) 
#elif defined (_VECTOR2D_USE_UINT32_)
#   define coordinate uint32_t
#   define mod_coordinate coordinate
#   define vector2d_pow(v, p) ((uint32_t) powf(v, p)) 
#   define vector2d_atan2(y, x) ((uint32_t) atan2f(y, x)) 
#   define vector2d_acos(v) ((uint32_t) acosf(v)) 
#elif defined (_VECTOR2D_USE_INT32_)
#   define coordinate int32_t
#   define mod_coordinate coordinate
#   define vector2d_pow(v, p) ((int32_t) powf(v, p)) 
#   define vector2d_atan2(y, x) ((int32_t) atan2f(y, x)) 
#   define vector2d_acos(v) ((int32_t) acosf(v)) 
#elif defined (_VECTOR2D_USE_UINT64_)
#   define coordinate uint64_t
#   define mod_coordinate coordinate
#   define vector2d_pow(v, p) ((uint64_t) powl(v, p)) 
#   define vector2d_atan2(y, x) ((uint64_t) atan2l(y, x)) 
#   define vector2d_acos(v) ((uint64_t) acosl(v)) 
#elif defined (_VECTOR2D_USE_INT64_)
#   define coordinate int64_t
#   define mod_coordinate coordinate
#   define vector2d_pow(v, p) ((int64_t) powl(v, p)) 
#   define vector2d_atan2(y, x) ((int64_t) atan2l(y, x)) 
#   define vector2d_acos(v) ((int64_t) acosl(v)) 
#elif defined (_VECTOR2D_USE_DOUBLE_)
#   define coordinate double
#   define mod_coordinate int64_t
#   define vector2d_pow(v, p) ((double) powl(v, p)) 
#   define vector2d_atan2(y, x) ((double) atan2l(y, x)) 
#   define vector2d_acos(v) ((double) acosl(v)) 
#elif defined (_VECTOR2D_USE_FLOAT_)
typedef float coordinate;
typedef int32_t mod_coordinate;
#   define vector2d_pow(v, p) ((float) pow(v, p)) 
#   define vector2d_atan2(y, x) ((float) atan2f(y, x)) 
#   define vector2d_acos(v) ((float) acosf(v)) 
#endif

#define vector2d_sqrt(v) vector2d_pow(v, 0.5)
#define vector2d_abs(v) ((coordinate) vector2d_sqrt(vector2d_pow(v, 2)))

#endif // _COORDINATE_H_
