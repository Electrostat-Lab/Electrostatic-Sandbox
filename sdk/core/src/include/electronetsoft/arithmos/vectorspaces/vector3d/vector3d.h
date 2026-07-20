/**
 * @brief The R(3) vectorspace to represent 3-dimensional vectors providing a
 *        powerful utility to operate on them.
 * @author pavl_g.
 * @copyright arithmos-native.
 */
#ifndef __VECTOR_3D_H_
#define __VECTOR_3D_H_

#include <math.h>
#include <electronetsoft/util/types.h>
#include <electronetsoft/util/utilities.h>
#include <electronetsoft/arithmos/vectorspaces/vec_component.h>
#include <electronetsoft/arithmos/vectorspaces/matrix/matrix.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Represents a set of three nested gimbals to track rotational state
 *        in the R(3) vectorspace.
 */
struct vec3d_gimbal {
    /** @brief Rotation around the x-axis (Pitch). */
    vec_component x_gimbal;
    /** @brief Rotation around the y-axis (Yaw). */
    vec_component y_gimbal;
    /** @brief Rotation around the z-axis (Roll). */
    vec_component z_gimbal;

    /** @brief Delta change in rotation around the x-axis. */
    vec_component delta_x;
    /** @brief Delta change in rotation around the y-axis. */
    vec_component delta_y;
    /** @brief Delta change in rotation around the z-axis. */
    vec_component delta_z;

    /** @brief Orientation matrix representing the cumulative gimbal rotation. */
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

    /**
     * @brief The z-coordinate (Vz->) component of this vector in the R(3) space.
     */
    vec_component z;

    /** @brief The gimbal state associated with this vector. */
    vec3d_gimbal gimbal;
};

/**
 * @brief Represents a coordinate space in R(3) defined by basis vectors
 *        and a reference point.
 */
struct vec3d_space {
    /** @brief The basis vector for the x-axis. */
    vector3d x_axis;
    /** @brief The basis vector for the y-axis. */
    vector3d y_axis;
    /** @brief The basis vector for the z-axis. */
    vector3d z_axis;
    /** @brief The origin or reference point of the coordinate space. */
    vector3d ref_point;
};

/**
 * @brief Represents a vector in spherical coordinates.
 */
struct vec3d_polar {
    /** @brief The radial distance from the origin (magnitude). */
    vec_component r;
    /** @brief The azimuthal angle in the xy-plane from the x-axis. */
    vec_component phi;
    /** @brief The polar angle (co-latitude) from the positive z-axis. */
    vec_component theta;
};

/**
 * @brief Represents a vector in cylindrical coordinates.
 */
struct vec3d_cylinderical {
    /** @brief The radial distance in the xy-plane. */
    vec_component r;
    /** @brief The azimuthal angle in the xy-plane from the x-axis. */
    vec_component phi;
    /** @brief The vertical height (z-component). */
    vec_component z;
};

/**
 * @brief Defines the encodings for a set of three gimbal axes.
 * @note Those encodings are constant numbers; the don't swap orientation
 * with one another.
 */
typedef enum {
    /** @brief Encoding for the X-axis gimbal. */
    GIMBAL_X = (INT16_MAX >> 8) ^ INT16_MAX,
    /** @brief Encoding for the Y-axis gimbal. */
    GIMBAL_Y = GIMBAL_X - 1,
    /** @brief Encoding for the Z-axis gimbal. */
    GIMBAL_Z = GIMBAL_Y - 1
} vector_gimbal;

struct vec3d_processors {
    /**
     * @brief A function pointer to be called on a gimbal lock trap. A gimbal trap is a
     * software trap that is executed when a potential angle that could produce gimbal
     * lock is being floating-point approached or reached.
     * @param rotated the rotated vector in the R(3) vectorspace.
     * @param gimbal the gimbal around which the rotational motion is being executed.
     * @param angle the last angle that triggered this gimbal trap
     *              (it shouldn't have to be PI/2 or -PI/2).
     */
    void (*on_gimbal_lock_trap)(vector3d rotated, vector_gimbal gimbal, vec_component angle);
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

/** @brief Unit vector for the X-axis (1, 0, 0). */
extern vector3d VEC3_X_COMPONENT;

/** @brief Unit vector for the Y-axis (0, 1, 0). */
extern vector3d VEC3_Y_COMPONENT;

/** @brief Unit vector for the Z-axis (0, 0, 1). */
extern vector3d VEC3_Z_COMPONENT;

/**
 * @brief Retrieves the orientation of the input axis given by the
 * vector3d component; and returns the gimbal encoding for this orientation.
 *
 * @param axis the input axis.
 */
static inline vector_gimbal get_vec_gimbal(vector3d axis) {
    vector3d __axis = {
        .x = fabsf(axis.x),
        .y = fabsf(axis.y),
        .z = fabsf(axis.z)
    };

    if ((__axis.x > ___ROTATION_MIN_THRESHOLD) &&
        ((__axis.y >= 0) && (__axis.y < 1.0f)) &&
        ((__axis.z >= 0) && (__axis.z < 1.0f))) {

        return GIMBAL_X;
    } else if ((__axis.y > ___ROTATION_MIN_THRESHOLD) &&
               ((__axis.x >= 0) && (__axis.x < 1.0f)) &&
               ((__axis.z >= 0) && (__axis.z < 1.0f))) {

        return GIMBAL_Y;
    } else if ((__axis.z > ___ROTATION_MIN_THRESHOLD) &&
               ((__axis.y >= 0) && (__axis.y < 1.0f)) &&
               ((__axis.x >= 0) && (__axis.x < 1.0f))) {

        return GIMBAL_Z;
    }
    return -1;
}

/**
 * @brief Adds a scalar value to the vector components and returns a new vector.
 *
 * @param vector3d the initial vector in R(3) space.
 * @param vec_component the value to add to that vector.
 * @return status code.
 */
extern status_code vec3d_scalar_add(vector3d, vec_component,
                                    vector3d *, vec3d_processors *);

/**
 * @brief Creates a new vector in R(3) space using the components of two given vectors.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d.
 */
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
 * @brief Subtracts the second vector components from first vector components in a R(3) space returning a new vector.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(3) space.
 */
extern status_code vec3d_subtract(vector3d, vector3d, vector3d *, vec3d_processors *);

/**
 * @brief Interpolates between the first vector components and the second vector components with a scale in a R(3) space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(3) space.
 */
extern status_code vec3d_interpolate(vector3d, vector3d, vec_component,
                                     vector3d *, vec3d_processors *);

/**
 * @brief Extrapolates from the first vector components and the second vector components with a scale in a R(3) space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(3) space.
 */
extern status_code vec3d_extrapolate(vector3d, vector3d, vec_component,
                                     vector3d *, vec3d_processors *);

/**
 * @brief Performs a matrix multiplication operation on two vectors in the R(3) space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(3) space.
 */
extern status_code vec3d_dot_product(vector3d, vector3d,
                                     vec_component *, vec3d_processors *);

/**
 * @brief Performs a scalar multiplication operation on the first vector components using the
 *        second vector components in a R(3) vector-space returning a new vector.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(3) space.
 */
extern status_code vec3d_product(vector3d, vector3d,
                                 vector3d *, vec3d_processors *);

/**
 * @brief Performs a cross-product or vector product which resembles the direction of the plane those 2 vectors are making in the R(3) vector-space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return the cross product component.
 */
extern status_code vec3d_cross_product(vector3d, vector3d,
                                       vec_component *, vec3d_processors *);

/**
 * @brief Finds the angle between two vectors in the R(3) space by dividing their dot product by the product of their norms.
 * @note The angle is in radians by default!
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return a new vector3d in the R(3) space.
 */
extern status_code vec3d_angle(vector3d, vector3d,
                               vec_component *, vec3d_processors *);

/**
 * @brief Finds the length (aka. norm) of a vector in the R(3) space by using the Pythagorean theorem on its components.
 *
 * @param vector3d a vector in the R(3) space to find its length.
 * @return a scalar value representing the length of this vector in the R(3) space.
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
 * @brief Converts a rectangular coordinate vector into its cylindrical equivalent in R(3).
 *
 * @param vector3d a rectangular coordinate vector.
 * @return the cylindrical coordinate value.
 */
extern status_code vec3d_retrieve_cylinderical(vector3d, vec3d_cylinderical *, vec3d_processors *);

/**
 * @brief Converts spherical coordinates back to rectangular coordinates in R(3).
 *
 * @param vec3d_polar the spherical coordinates.
 * @return the rectangular coordinate vector.
 */
extern status_code vec3d_from_polar(vec3d_polar, vector3d *, vec3d_processors *);

/**
 * @brief Converts cylindrical coordinates back to rectangular coordinates in R(3).
 *
 * @param vec3d_cylinderical the cylindrical coordinates.
 * @return the rectangular coordinate vector.
 */
extern status_code vec3d_from_cylinderical(vec3d_cylinderical, vector3d *, vec3d_processors *);

/**
 * @brief Converts spherical coordinates to cylindrical coordinates.
 *
 * @param vec3d_polar the spherical coordinates.
 * @return the cylindrical coordinates.
 */
extern status_code vec3d_spherical_to_cylinderical(vec3d_polar, vec3d_cylinderical *, vec3d_processors *);

/**
 * @brief Converts cylindrical coordinates to spherical coordinates.
 *
 * @param vec3d_cylinderical the cylindrical coordinates.
 * @return the spherical coordinates.
 */
extern status_code vec3d_cylinderical_to_spherical(vec3d_cylinderical, vec3d_polar *, vec3d_processors *);

/**
 * @brief Applies a moduluo (integer division) on vector components, returning the remainder
 *        of the integer division in a new vector3d in a R(3) space.
 *
 * @param vector3d a rectangular coordinate vector.
 * @return the polar coordinate value in radians.
 */
extern status_code vec3d_moduluo(vector3d, vector3d,
                                 vector3d *, vec3d_processors *);

/**
 * @brief Finds the metric distance between two vectors in a R(3) space by calculating the
 *        norm of the their subtraction.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return the metric distance between the specified vectors.
 */
extern status_code vec3d_distance(vector3d, vector3d,
                                  vec_component *, vec3d_processors *);

/**
 * @brief Tests whether two vectors are dependent in a R(3) vector-space.
 * @note Two vectors are said to be dependent if they are multiplies of one another,
 *       such that, the [u = cv], where u and v are vectors and c is a scalar value not equal to zero.
 * @note Linear dependent vectors are coincident vectors in a R(3) space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return (1) for true if the two vectors are dependent or (0) for false otherwise.
 */
extern status_code vec3d_are_dependent(vector3d, vector3d, vec3d_processors *);

/**
 * @brief Tests whether two vectors are perpendicular in a R(3) vector-space.
 * @note Two vectors are said to be perpendicular if and only if their dot-product is zero
 *       because, cos(90) is zero, so u.v = |u|.|v|.cos(90) = 0.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return (1) for true if the two vectors are perpendicular or (0) for false otherwise.
 */
extern status_code vec3d_are_perpendicular(vector3d, vector3d, vec3d_processors *);

/**
 * @brief Tests whether two vectors are parallel in a R(3) vector-space.
 * @note Two vectors are said to be parallel if and only if their dot-product
 *       is equal to the product of their norms (lengths);
 *       because, cos(0) is 1, so u.v = |u|.|v|.cos(0) = |u|.|v|.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return (1) for true if the two vectors are parallel or (0) for false otherwise.
 */
extern status_code vector3d_are_parallel(vector3d, vector3d, vec3d_processors *);

/**
 * @brief Tests whether two vectors are equal in R(3) space.
 *
 * @param vector3d the first vector.
 * @param vector3d the second vector.
 * @return (1) for true if equal, (0) otherwise.
 */
extern status_code vec3d_are_equal(vector3d, vector3d, vec3d_processors *);

/**
 * @brief Rotates a vector around an axis in R(3) space.
 *
 * @param vector3d the vector to rotate.
 * @param vector3d the axis to rotate around.
 * @param vec_component the angle of rotation in radians.
 * @return status code.
 */
extern status_code vec3d_rotate(vector3d, vector3d, vec_component, vector3d *, vec3d_processors *);

/**
 * @brief Computes the absolute value of each component of a vector in R(3) space.
 *
 * @param vector3d the input vector.
 * @return status code.
 */
extern status_code vec3d_abs(vector3d, vector3d *, vec3d_processors *);

/**
 * @brief Safely executes the success processor.
 *
 * @param vector3d the result vector.
 * @param void the caller context.
 * @param vec3d_processors the processors to use.
 */
extern void vec3d_safe_exec_success(vector3d, void *, vec3d_processors *);

/**
 * @brief Safely executes the failure processor.
 *
 * @param void the caller context.
 * @param vec3d_processors the processors to use.
 * @param status_code the failure code.
 */
extern void vec3d_safe_exec_failure(void *, vec3d_processors *, status_code);

#ifdef __cplusplus
}
#endif

#endif //_vector3d_H_
