#if !(defined __VECTOR_2D_H_ || defined __VECTOR_3D_H_)
#   error "Use vector2d or vector3d instead of this!"
#endif

#ifndef __VEC_COMPONENT_H_
#define __VEC_COMPONENT_H_

#include <math.h>
#include <inttypes.h>

#if defined (_VECTOR2D_USE_UINT8_)
#   define vec_component uint8_t
#   define mod_vec_component vec_component
#   define vector2d_pow(v, p) ((uint8_t) powf(v, p))
#   define vector2d_atan2(y, x) ((uint8_t) atan2f(y, x))
#   define vector2d_acos(v) ((uint8_t) acosf(v))
#   define vector2d_cos(v) ((uint8_t) cosf(v))
#elif defined (_VECTOR2D_USE_INT8_)
#   define vec_component int8_t
#   define mod_vec_component vec_component
#   define vector2d_pow(v, p) ((int8_t) powf(v, p))
#   define vector2d_atan2(y, x) ((int8_t) atan2f(y, x))
#   define vector2d_acos(v) ((int8_t) acosf(v))
#   define vector2d_cos(v) ((int8_t) cosf(v))
#elif defined (_VECTOR2D_USE_UINT16_)
#   define vec_component uint16_t
#   define mod_vec_component vec_component
#   define vector2d_pow(v, p) ((uint16_t) powf(v, p))
#   define vector2d_atan2(y, x) ((uint16_t) atan2f(y, x))
#   define vector2d_acos(v) ((uint16_t) acosf(v))
#   define vector2d_cos(v) ((uint16_t) cosf(v))
#elif defined (_VECTOR2D_USE_INT16_)
#   define vec_component int16_t
#   define mod_vec_component vec_component
#   define vector2d_pow(v, p) ((int16_t) powf(v, p))
#   define vector2d_atan2(y, x) ((int16_t) atan2f(y, x))
#   define vector2d_acos(v) ((int16_t) acosf(v))
#   define vector2d_cos(v) ((int16_t) cosf(v))
#elif defined (_VECTOR2D_USE_UINT32_)
#   define vec_component uint32_t
#   define mod_vec_component vec_component
#   define vector2d_pow(v, p) ((uint32_t) powf(v, p))
#   define vector2d_atan2(y, x) ((uint32_t) atan2f(y, x))
#   define vector2d_acos(v) ((uint32_t) acosf(v))
#   define vector2d_cos(v) ((uint32_t) cosf(v))
#elif defined (_VECTOR2D_USE_INT32_)
#   define vec_component int32_t
#   define mod_vec_component vec_component
#   define vector2d_pow(v, p) ((int32_t) powf(v, p))
#   define vector2d_atan2(y, x) ((int32_t) atan2f(y, x))
#   define vector2d_acos(v) ((int32_t) acosf(v))
#   define vector2d_cos(v) ((int32_t) cosf(v))
#elif defined (_VECTOR2D_USE_UINT64_)
#   define vec_component uint64_t
#   define mod_vec_component vec_component
#   define vector2d_pow(v, p) ((uint64_t) powl(v, p))
#   define vector2d_atan2(y, x) ((uint64_t) atan2l(y, x))
#   define vector2d_acos(v) ((uint64_t) acosl(v))
#   define vector2d_cos(v) ((uint64_t) cosf(v))
#elif defined (_VECTOR2D_USE_INT64_)
#   define vec_component int64_t
#   define mod_vec_component vec_component
#   define vector2d_pow(v, p) ((int64_t) powl(v, p))
#   define vector2d_atan2(y, x) ((int64_t) atan2l(y, x))
#   define vector2d_acos(v) ((int64_t) acosl(v))
#   define vector2d_cos(v) ((int64_t) cosf(v))
#elif defined (_VECTOR2D_USE_DOUBLE_)
#   define vec_component double
#   define mod_vec_component int64_t
#   define vector2d_pow(v, p) ((double) powl(v, p))
#   define vector2d_atan2(y, x) ((double) atan2l(y, x))
#   define vector2d_acos(v) ((double) acosl(v))
#   define vector2d_cos(v) ((double) cosf(v))
#else
// default program flow
typedef float vec_component;
typedef int32_t mod_vec_component;
#   define vector2d_pow(v, p) ((float) pow(v, p))
#   define vector2d_atan2(y, x) ((float) atan2f(y, x))
#   define vector2d_acos(v) ((float) acosf(v))
#   define vector2d_cos(v) ((float) cosf(v))
#   define vector2d_sin(v) ((float) sinf(v))
#endif

#define vector2d_sqrt(v) vector2d_pow(v, 0.5)
#define vector2d_abs(v) ((vec_component) vector2d_sqrt(vector2d_pow(v, 2)))

#endif // __VEC_COMPONENT_H_
