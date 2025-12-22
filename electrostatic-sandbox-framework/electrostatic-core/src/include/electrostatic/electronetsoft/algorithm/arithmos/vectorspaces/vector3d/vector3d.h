/**
 * @brief The R(3) vectorspace to represent 3-dimensional vectors providing a
 *        powerful utility to operate on them.
 * @author pavl_g.
 * @copyright arithmos-native.
 */
#ifndef __VECTOR_3D_H_
#define __VECTOR_3D_H_

#include <math.h>
#include <electrostatic/electronetsoft/util/types.h>
#include <electrostatic/electronetsoft/util/utilities.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vec_component.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/matrix/matrix.h>

#ifdef __cplusplus
extern "C" {
#endif

struct vec3d_gimbal {
    vec_component x_gimbal;
    vec_component y_gimbal;
    vec_component z_gimbal;

    matrix *orientation;
};

/**
 * @brief Represents a 3-dimensional (aka. R(3) space) vector point
 *        with a x-component, a y-component, and z-component.
 */
struct vector3d {
    /**
     * @brief The x-coordinate (Vx->) component of this vector in the R(3) space.
     */
    vec_component x;

    /**
     * @brief The y-coordinate (Vy->) component of this vector in the R(3) space.
     */
    vec_component y;

    vec_component z;

    vec3d_gimbal gimbal;
};

struct vec3d_space {
    vector3d x_axis;
    vector3d y_axis;
    vector3d z_axis;
    vector3d ref_point;
};

struct vec3d_polar {
    vec_component r; // the length of the vector; the radius of the unit sphere
    vec_component phi; // angle with +ve direction of x-axis
    vec_component theta; // angle with +ve direction of xy plane
};

struct vec3d_processors {
    /**
     * @brief A function pointer to be called on a successful operation.
     * @param caller A void pointer to the original calling context or object.
     * @param result The vector3d result of the operation.
     */
    void (*on_op_success)(void *caller, vector3d result);
    /**
     * @brief A function pointer to be called on a failed operation.
     * @param caller A void pointer to the original calling context or object.
     * @param code The status_code indicating the reason for failure.
     */
    void (*on_op_failed)(void *caller, status_code code);
};

extern vector3d VEC3_X_COMPONENT;

extern vector3d VEC3_Y_COMPONENT;

extern vector3d VEC3_Z_COMPONENT;

/**
 * @brief Adds a scalar value to the vector components and returns a new vector.
 *
 * @param vector3d the initial vector in R(3) space.
 * @param vec_component the value to add to that vector.
 * @return status code.
 */
extern status_code vec3d_scalar_add(vector3d, vec_component,
                                    vector3d *, vec3d_processors *);

extern status_code vec3d_component(vector3d, vector3d,
                                   vector3d *, vec3d_processors *);

/**
 * @brief Subtracts a scalar value from the vector components and rewrites the vector.
 *
 * @param vector3d the initial vector in R(3) space.
 * @param vec_component the value to subtract from that vector.
 * @return a status code.
 */
extern status_code vec3d_scalar_subtract(vector3d, vec_component,
                                         vector3d *, vec3d_processors *);

/**
 * @brief Multiplies a scalar value with the vector components and rewrites the given vector.
 *
 * @param vector3d the initial vector in R(3) space.
 * @param vec_component the value to multiply to that vector.
 * @return a status code.
 */
extern status_code vec3d_scalar_multiply(vector3d, vec_component,
                                         vector3d *, vec3d_processors *);

/**
 * @brief Divides a scalar value by the vector components and rewrites the given vector.
 *
 * @param vector3d the initial vector in R(3) space.
 * @param vec_component the value to divide by that vector.
 * @return a status code.
 */
extern status_code vec3d_scalar_divide(vector3d, vec_component,
                                       vector3d *, vec3d_processors *);

/**
 * @brief Finds the uint vector of a vector in R(3) space which represents the direction of that vector.
 *
 * @param in the original vector in R(3) space.
 * @param out the output vector in R(3) space from this operation.
 * @return a status code.
 */
extern status_code vec3d_normalize(vector3d, vector3d *, vec3d_processors *);

/**
 * @brief Adds two vector components together in a R(3) space putting the result in the third vector
 * structure.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a status code.
 */
extern status_code vec3d_add(vector3d, vector3d, vector3d *, vec3d_processors *);

/**
 * @brief Divides the first vector by the second vector in a R(3) space putting the result in the third vector
 * structure.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a status code.
 */
extern status_code vec3d_divide(vector3d, vector3d, vector3d *, vec3d_processors *);

/**
 * @brief Subtracts the second vector components from first vector components in a R(2) space returning a new vector.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(2) space.
 */
extern status_code vec3d_subtract(vector3d, vector3d, vector3d *, vec3d_processors *);

/**
 * @brief Interpolates between the first vector components and the second vector components with a scale in a R(2) space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(2) space.
 */
extern status_code vec3d_interpolate(vector3d, vector3d, vec_component,
                                     vector3d *, vec3d_processors *);

/**
 * @brief Extrapolates from the first vector components and the second vector components with a scale in a R(2) space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(2) space.
 */
extern status_code vec3d_extrapolate(vector3d, vector3d, vec_component,
                                     vector3d *, vec3d_processors *);

/**
 * @brief Performs a matrix multiplication operation on two vectors in the R(2) space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(2) space.
 */
extern status_code vec3d_dot_product(vector3d, vector3d,
                                     vec_component *, vec3d_processors *);

/**
 * @brief Performs a scalar multiplication operation on the first vector components using the
 *        second vector components in a R(2) vector-space returning a new vector.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(2) space.
 */
extern status_code vec3d_product(vector3d, vector3d,
                                 vector3d *, vec3d_processors *);

/**
 * @brief Performs a cross-product or vector product which resembles the direction of the plane those 2 vectors are making in the R(2) vector-space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return the cross product component.
 */
extern status_code vec3d_cross_product(vector3d, vector3d,
                                       vec_component *, vec3d_processors *);

/**
 * @brief Finds the angle between two vectors in the R(2) space by dividing their dot product by the product of their norms.
 * @note The angle is in radians by default!
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(2) space.
 */
extern status_code vec3d_angle(vector3d, vector3d,
                               vec_component *, vec3d_processors *);

/**
 * @brief Finds the length (aka. norm) of a vector in the R(2) space by using the Pythagorean theorem on its components.
 *
 * @param vector3d a vector in the R(2) space to find its length.
 * @return a scalar value representing the length of this vector in the R(2) space.
 */
extern status_code vec3d_length(vector3d, vec_component *, vec3d_processors *);

/**
 * @brief Converts the rectangular coordinate into a polar coordinate by finding
 *        the inverse of the tangent of Y/X.
 * @note The angle is with the positive direction of x-axis and in rads!
 *
 * @param vector3d a rectangular coordinate vector.
 * @return the polar coordinate value in radians.
 */
extern status_code vec3d_retrieve_polar(vector3d, vec3d_polar *, vec3d_processors *);

/**
 * @brief Applies a moduluo (integer division) on vector components, returning the remainder
 *        of the integer division in a new vector3d in a R(2) space.
 *
 * @param vector3d a rectangular coordinate vector.
 * @return the polar coordinate value in radians.
 */
extern status_code vec3d_moduluo(vector3d, vector3d,
                                 vector3d *, vec3d_processors *);

/**
 * @brief Finds the metric distance between two vectors in a R(2) space by calculating the
 *        norm of the their subtraction.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return the metric distance between the specified vectors.
 */
extern status_code vec3d_distance(vector3d, vector3d,
                                  vec_component *, vec3d_processors *);

/**
 * @brief Tests whether two vectors are dependent in a R(2) vector-space.
 * @note Two vectors are said to be dependent if they are multiplies of one another,
 *       such that, the [u = cv], where u and v are vectors and c is a scalar value not equal to zero.
 * @note Linear dependent vectors are coincident vectors in a R(2) space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return (1) for true if the two vectors are dependent or (0) for false otherwise.
 */
extern status_code vec3d_are_dependent(vector3d, vector3d, vec3d_processors *);

/**
 * @brief Tests whether two vectors are perpendicular in a R(2) vector-space.
 * @note Two vectors are said to be perpendicular if and only if their dot-product is zero
 *       because, cos(90) is zero, so u.v = |u|.|v|.cos(90) = 0.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return (1) for true if the two vectors are perpendicular or (0) for false otherwise.
 */
extern status_code vec3d_are_perpendicular(vector3d, vector3d, vec3d_processors *);

/**
 * @brief Tests whether two vectors are parallel in a R(2) vector-space.
 * @note Two vectors are said to be parallel if and only if their dot-product
 *       is equal to the product of their norms (lengths);
 *       because, cos(0) is 1, so u.v = |u|.|v|.cos(0) = |u|.|v|.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return (1) for true if the two vectors are parallel or (0) for false otherwise.
 */
extern status_code vector3d_are_parallel(vector3d, vector3d, vec3d_processors *);

extern status_code vec3d_are_equal(vector3d, vector3d, vec3d_processors *);

extern status_code vec3d_rotate(vector3d, vector3d, vec_component, vector3d *, vec3d_processors *);

extern status_code vec3d_abs(vector3d, vector3d *, vec3d_processors *);


#ifdef __cplusplus
}
#endif

#endif //_vector3d_H_
