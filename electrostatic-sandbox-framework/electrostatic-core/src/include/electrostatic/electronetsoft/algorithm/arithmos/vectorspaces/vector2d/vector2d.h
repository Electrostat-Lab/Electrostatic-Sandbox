/**
 * @brief Defines the API for a 2D vector (R(2) space) library, providing a
 *        powerful set of utilities for vector operations.
 * @author pavl_g.
 * @copyright arithmos-native.
 */
#ifndef __VECTOR_2D_H_
#define __VECTOR_2D_H_

#define ___ROTATION_MIN_THRESHOLD (0.00000012)

#include <math.h>
#include <electrostatic/electronetsoft/util/types.h>
#include <electrostatic/electronetsoft/util/utilities.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/vec_component.h>
#include <electrostatic/electronetsoft/algorithm/arithmos/vectorspaces/matrix/matrix.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Represents a vector in a 2-dimensional (R(2)) space, defined by
 *        x and y components.
 */
struct vector2d {
    /**
     * @brief The x-component (abscissa) of the vector.
     */
    vec_component x;

    /**
     * @brief The y-component (ordinate) of the vector.
     */
    vec_component y;

    matrix *orientation;
};

/**
 * @brief Represents a 2D coordinate system (a vector space) defined by two basis vectors.
 * @details A vector space is a collection of vectors and the operations that can be
 *          performed on them. By defining custom basis vectors (x_axis, y_axis), you can
 *          create a transformed coordinate system (e.g., rotated or scaled) relative
 *          to the standard Cartesian plane. Any vector can then be represented as a
 *          linear combination of these basis vectors.
 */
struct vec2d_space {
    /**
     * @brief The first basis vector, defining the direction of the local x-axis.
     */
    vector2d x_axis;
    /**
     * @brief The second basis vector, defining the direction of the local y-axis.
     */
    vector2d y_axis;

    vector2d ref_point;
};

/**
 * @brief Represents a 2D vector in polar coordinates.
 */
struct vec2d_polar {
    /**
     * @brief The radial distance from the origin (the vector's magnitude or length).
     */
    vec_component r;
    /**
     * @brief The angle (phi) in radians, measured counter-clockwise from the positive x-axis.
     */
    vec_component phi;
};

/**
 * @brief A structure of callback functions for handling the results of vector operations.
 *        This enables asynchronous or decoupled result processing.
 */
struct vec2d_processors {
    /**
     * @brief A function pointer to be called on a successful operation.
     * @param caller A void pointer to the original calling context or object.
     * @param result The vector2d result of the operation.
     */
    void (*on_op_success)(void *caller, vector2d result);
    /**
     * @brief A function pointer to be called on a failed operation.
     * @param caller A void pointer to the original calling context or object.
     * @param code The status_code indicating the reason for failure.
     */
    void (*on_op_failed)(void *caller, status_code code);
};

// --- Global Constant Vectors ---

extern vector2d VEC2_X_COMPONENT; // Unit vector for the x-axis (1, 0)
extern vector2d VEC2_Y_COMPONENT; // Unit vector for the y-axis (0, 1)
extern vector2d VEC2_XY_PLANE;    // Often a zero vector or placeholder in 2D context

// --- Function Prototypes ---


extern status_code vec2d_is_unit(vector2d v, vec2d_processors *procs);

/**
 * @brief Adds a scalar value to each component of a vector.
 * @param v The initial vector.
 * @param scalar The value to add.
 * @param out Pointer to store the resulting vector.
 * @param procs Pointer to callback handlers for the result.
 * @return A status code indicating the operation's outcome.
 */
extern status_code vec2d_scalar_add(vector2d v, vec_component scalar,
                                    vector2d *out, vec2d_processors *procs);

/**
 * @brief Creates a new vector from the components of two other vectors.
 * @param v1 The vector providing the x-component.
 * @param v2 The vector providing the y-component.
 * @param out Pointer to store the resulting vector.
 * @param procs Pointer to the callback handlers.
 * @return A status code.
 */
extern status_code vec2d_component(vector2d v1, vector2d v2,
                                   vector2d *out, vec2d_processors *procs);

/**
 * @brief Subtracts a scalar value from each component of a vector.
 * @param v The initial vector.
 * @param scalar The value to subtract.
 * @param out Pointer to store the resulting vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_scalar_subtract(vector2d v, vec_component scalar,
                                         vector2d *out, vec2d_processors *procs);

/**
 * @brief Multiplies each component of a vector by a scalar (scales the vector).
 * @param v The initial vector.
 * @param scalar The value to multiply by.
 * @param out Pointer to store the resulting vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_scalar_multiply(vector2d v, vec_component scalar,
                                         vector2d *out, vec2d_processors *procs);

/**
 * @brief Divides each component of a vector by a scalar.
 * @param v The initial vector.
 * @param scalar The value to divide by.
 * @param out Pointer to store the resulting vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_scalar_divide(vector2d v, vec_component scalar,
                                       vector2d *out, vec2d_processors *procs);

/**
 * @brief Calculates the unit vector of a given vector (a vector with length 1).
 * @param in The original vector.
 * @param out Pointer to store the resulting unit vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_normalize(vector2d in, vector2d *out, vec2d_processors *procs);

/**
 * @brief Adds two vectors component-wise.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param out Pointer to store the vector sum.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_add(vector2d v1, vector2d v2, vector2d *out, vec2d_processors *procs);

/**
 * @brief Divides two vectors component-wise.
 * @param v1 The dividend vector.
 * @param v2 The divisor vector.
 * @param out Pointer to store the resulting vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_divide(vector2d v1, vector2d v2, vector2d *out, vec2d_processors *procs);

/**
 * @brief Subtracts the second vector from the first, component-wise.
 * @param v1 The minuend vector.
 * @param v2 The subtrahend vector.
 * @param out Pointer to store the vector difference.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_subtract(vector2d v1, vector2d v2, vector2d *out, vec2d_processors *procs);

/**
 * @brief Linearly interpolates between two vectors.
 * @param v1 The starting vector.
 * @param v2 The ending vector.
 * @param scale The interpolation factor (usually [0, 1]).
 * @param out Pointer to store the interpolated vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_interpolate(vector2d v1, vector2d v2, vec_component scale,
                                     vector2d *out, vec2d_processors *procs);

/**
 * @brief Linearly extrapolates from a line defined by two vectors.
 * @details This is mathematically identical to interpolation but implies the `scale`
 *          is outside the `[0, 1]` range.
 * @param v1 The first vector on the line.
 * @param v2 The second vector on the line.
 * @param scale The extrapolation factor.
 * @param out Pointer to store the extrapolated vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_extrapolate(vector2d v1, vector2d v2, vec_component scale,
                                     vector2d *out, vec2d_processors *procs);

/**
 * @brief Computes the dot product of two vectors.
 * @details The dot product is a scalar that relates to the angle between two vectors.
 *          It is calculated as: `v1.x * v2.x + v1.y * v2.y`.
 *          - If `dot(v1, v2) > 0`, the angle is less than 90°.
 *          - If `dot(v1, v2) < 0`, the angle is greater than 90°.
 *          - If `dot(v1, v2) = 0`, the vectors are perpendicular.
 *          It can also be expressed as `|v1| * |v2| * cos(theta)`.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param out Pointer to store the resulting scalar dot product.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_dot_product(vector2d v1, vector2d v2,
                                     vec_component *out, vec2d_processors *procs);

/**
 * @brief Performs component-wise multiplication (Hadamard product).
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param out Pointer to store the resulting vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_product(vector2d v1, vector2d v2,
                                 vector2d *out, vec2d_processors *procs);

/**
 * @brief Computes the 2D pseudo cross product, which yields a scalar.
 * @details In 2D, the cross product is not a vector but a scalar representing the
 *          magnitude of the Z-component of the 3D cross product. It is calculated as:
 *          `v1.x * v2.y - v1.y * v2.x`.
 *          The result is the signed area of the parallelogram formed by the two vectors.
 *          - A positive value means v2 is counter-clockwise from v1.
 *          - A negative value means v2 is clockwise from v1.
 *          - A zero value means the vectors are collinear.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param out Pointer to store the resulting scalar.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_cross_product(vector2d v1, vector2d v2,
                                       vec_component *out, vec2d_processors *procs);

/**
 * @brief Finds the angle in radians between two vectors.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param out Pointer to store the angle in radians.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_angle(vector2d v1, vector2d v2,
                               vec_component *out, vec2d_processors *procs);

/**
 * @brief Finds the length (magnitude or L2 norm) of a vector.
 * @param v The vector to measure.
 * @param out Pointer to store the scalar length.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_length(vector2d v, vec_component *out, vec2d_processors *procs);

/**
 * @brief Converts a vector from rectangular (Cartesian) to polar coordinates.
 * @param v The rectangular coordinate vector.
 * @param out Pointer to a polar coordinate struct to store the result.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_retrieve_polar(vector2d v, vec2d_polar *out, vec2d_processors *procs);

/**
 * @brief Converts a vector from polar to rectangular (Cartesian) coordinates.
 * @param polar The polar coordinate vector.
 * @param out Pointer to a vector2d struct to store the result.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_retrieve_rectangular(vec2d_polar polar, vector2d *out, vec2d_processors *procs);

/**
 * @brief Applies a modulo operation on each component of a vector by the components of a second vector.
 * @param v1 The dividend vector.
 * @param v2 The divisor vector.
 * @param out Pointer to store the resulting vector of remainders.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_moduluo(vector2d v1, vector2d v2,
                                 vector2d *out, vec2d_processors *procs);

/**
 * @brief Calculates the Euclidean distance between two points (represented as vectors).
 * @param v1 The first point/vector.
 * @param v2 The second point/vector.
 * @param out Pointer to store the resulting scalar distance.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_distance(vector2d v1, vector2d v2,
                                  vec_component *out, vec2d_processors *procs);

/**
 * @brief Tests whether two vectors are linearly dependent (collinear).
 * @details Two vectors `u` and `v` are linearly dependent if one is a scalar multiple
 *          of the other (i.e., `u = c*v` for some scalar `c`). In 2D, this means they
 *          lie on the same line through the origin. This can be checked by seeing if
 *          their 2D cross product is zero.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param procs Pointer to callback handlers for the boolean result.
 * @return A status code indicating if the check was performed.
 */
extern status_code vec2d_is_dependent(vector2d v1, vector2d v2, vec2d_processors *procs);

/**
 * @brief Tests whether two vectors are perpendicular (orthogonal).
 * @details Two non-zero vectors are perpendicular if and only if their dot product is zero.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param procs Pointer to callback handlers for the boolean result.
 * @return A status code.
 */
extern status_code vec2d_are_perpendicular(vector2d v1, vector2d v2, vec2d_processors *procs);

/**
 * @brief Tests whether two vectors are parallel.
 * @details Two vectors are parallel if their 2D cross product is zero. This is a more
 *          robust check for collinearity than comparing angles.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param procs Pointer to callback handlers for the boolean result.
 * @return A status code indicating if the check was performed.
 */
extern status_code vector2d_are_parallel(vector2d v1, vector2d v2, vec2d_processors *procs);

/**
 * @brief An alias for `vec2d_is_dependent`. Tests for collinearity.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param procs Pointer to callback handlers for the boolean result.
 * @return A status code.
 */
extern status_code vec2d_are_dependent(vector2d v1, vector2d v2, vec2d_processors *procs);

/**
 * @brief Computes the projection of vector v1 onto vector v2.
 * @details Vector projection finds the "shadow" that `v1` casts onto the line defined by `v2`.
 *          It results in a vector parallel to `v2`. The formula is:
 *          `proj_v2(v1) = ( (v1 . v2) / |v2|^2 ) * v2`
 *          This is geometrically equivalent to finding the closest point on the line of `v2` to the tip of `v1`.
 * @param v1 The vector to be projected.
 * @param v2 The vector to project onto.
 * @param out Pointer to store the resulting projection vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_projection_vector(vector2d v1, vector2d v2, vector2d *out, vec2d_processors *procs);

/**
 * @brief Rotates a vector around a specified pivot point.
 * @details To rotate a vector `v` around a pivot `p`, we first translate the system so the
 *          pivot is at the origin (`v' = v - p`). Then, we apply the standard 2D rotation matrix:
 *          `x_new = x' * cos(angle) - y' * sin(angle)`
 *          `y_new = x' * sin(angle) + y' * cos(angle)`
 *          Finally, we translate the system back by adding the pivot (`result = v_rotated + p`).
 * @param v The vector to rotate.
 * @param axis The axis from which the angle of rotation is applied.
 * @param angle The angle of rotation in radians (counter-clockwise).
 * @param out Pointer to store the rotated vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_rotate(vector2d v, vector2d axis, vec_component angle, vector2d *out, vec2d_processors *procs);

/**
 * @brief Creates a 2D vector space (a coordinate system) from two basis vectors.
 * @param basis1 The first basis vector (e.g., the new x-axis).
 * @param basis2 The second basis vector (e.g., the new y-axis).
 * @param out Pointer to store the created subspace.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_create_subspace(vector2d basis1, vector2d basis2, vec2d_space *out, vec2d_processors *procs);

/**
 * @brief Tests if vector `v2` is a rotated version of `v1` by a specific angle.
 * @param v1 The original vector.
 * @param v2 The vector to check.
 * @param angle The angle of rotation in radians to test against.
 * @param procs Pointer to callback handlers for the boolean result.
 * @return A status code.
 */
extern status_code vec2d_is_rotated(vector2d v1, vector2d v2, vec_component angle, vec2d_processors *procs);

/**
 * @brief Tests if two vectors are equal within a small tolerance.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @param procs Pointer to callback handlers for the boolean result.
 * @return A status code.
 */
extern status_code vec2d_are_equal(vector2d v1, vector2d v2, vec2d_processors *procs);

/**
 * @brief Swaps the x and y components of a vector.
 * @param v The input vector.
 * @param out Pointer to store the vector with swapped components.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_swap_components(vector2d v, vector2d *out, vec2d_processors *procs);

/**
 * @brief Negates both components of a vector, reversing its direction.
 * @param v1 The vector to negate.
 * @param v2 (Note: This parameter appears unused and could be deprecated for clarity).
 * @param out Pointer to store the negated vector.
 * @param procs Pointer to callback handlers.
 * @return A status code.
 */
extern status_code vec2d_negate(vector2d v1, vector2d v2, vector2d *out, vec2d_processors *procs);

#ifdef __cplusplus
}
#endif

#endif //__VECTOR_2D_H_
