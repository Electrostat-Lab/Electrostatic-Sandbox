/**
 * @brief The R(2) vectorspace to represent 2-dimensional vectors providing a 
 *        powerful utility to operate on them.
 * @author pavl_g.
 * @copyright arithmos-native.
 */
#ifndef _vector2d_H_
#define _vector2d_H_

#include <math.h>
#define _VECTOR2D_USE_FLOAT_
#include <electrostatic/algorithm/arithmos/vectorspaces/coordinate.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Represents a 2-dimensional (aka. R(2) space) vector point 
 *        with a x-component and a y-component. 
 */
typedef struct {
    /**
     * @brief The x-coordinate (Vx->) component of this vector in the R(2) space. 
     */
    coordinate x;

    /**
     * @brief The y-coordinate (Vy->) component of this vector in the R(2) space. 
     */
    coordinate y;
} vector2d;

/**
 * @brief Adds a scalar value to the vector components and returns a new vector.
 * 
 * @param vector2d the initial vector in R(2) space.
 * @param coordinate the value to add to that vector.
 * @return a new vector2d with x and y components. 
 */
extern vector2d vector2d_scalar_add(vector2d, coordinate);

/**
 * @brief Subtracts a scalar value from the vector components and returns a new vector.
 * 
 * @param vector2d the initial vector in R(2) space.
 * @param coordinate the value to subtract from that vector.
 * @return a new vector2d with x and y components. 
 */
extern vector2d vector2d_scalar_subtract(vector2d, coordinate);

/**
 * @brief Multiplies a scalar value with the vector components and returns a new vector.
 * 
 * @param vector2d the initial vector in R(2) space.
 * @param coordinate the value to multiply to that vector.
 * @return a new vector2d with x and y components. 
 */
extern vector2d vector2d_scalar_multiply(vector2d, coordinate);

/**
 * @brief Divides a scalar value by the vector components and returns a new vector.
 * 
 * @param vector2d the initial vector in R(2) space.
 * @param coordinate the value to divide by that vector.
 * @return a new vector2d with x and y components. 
 */
extern vector2d vector2d_scalar_divide(vector2d, coordinate);

/**
 * @brief Finds the uint vector of a vector in R(2) space which represents the direction of that vector.
 * 
 * @param vector2d the original vector in R(2) space.
 * @return a new vector2d representing the uint vector of the input vector.
 */
extern vector2d vector2d_normalize(vector2d);

/**
 * @brief Adds two vector2d components together in a R(2) space returning a new vector.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return a new vector2d in the R(2) space.
 */
extern vector2d vector2d_add(vector2d, vector2d);

/**
 * @brief Divides the first vector by the second vector in a R(2) space returning a new vector.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return a new vector2d in the R(2) space. 
 */
extern vector2d vector2d_divide(vector2d, vector2d);

/**
 * @brief Subtracts the second vector components from first vector components in a R(2) space returning a new vector.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return a new vector2d in the R(2) space.
 */
extern vector2d vector2d_subtract(vector2d, vector2d);

/**
 * @brief Interpolates between the first vector components and the second vector components with a scale in a R(2) space.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return a new vector2d in the R(2) space.
 */
extern vector2d vector2d_interpolate(vector2d, vector2d, coordinate);

/**
 * @brief Extrapolates from the first vector components and the second vector components with a scale in a R(2) space.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return a new vector2d in the R(2) space.
 */
extern vector2d vector2d_extrapolate(vector2d, vector2d, coordinate);

/**
 * @brief Performs a matrix multiplication operation on two vectors in the R(2) space.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return a new vector2d in the R(2) space.
 */
extern coordinate vector2d_dot_product(vector2d, vector2d);

/**
 * @brief Performs a scalar multiplication operation on the first vector components using the 
 *        second vector components in a R(2) vector-space returning a new vector.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return a new vector2d in the R(2) space.
 */
extern vector2d vector2d_product(vector2d, vector2d);

/**
 * @brief Performs a cross-product or vector product which resembles the direction of the plane
 *        those 2 vectors are making in the R(2) vector-space.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return the cross product component. 
 */
extern coordinate vector2d_cross_product(vector2d vec0, vector2d vec1);

/**
 * @brief Finds the angle between two vectors in the R(2) space by dividing their dot product by the product of their norms.
 * @note The angle is in radians by default!
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return a new vector2d in the R(2) space.
 */
extern coordinate vector2d_angle(vector2d, vector2d);

/**
 * @brief Finds the length (aka. norm) of a vector in the R(2) space by using the Pythagorean theorem on its components.
 * 
 * @param vector2d a vector in the R(2) space to find its length.
 * @return a scalar value representing the length of this vector in the R(2) space.
 */
extern coordinate vector2d_length(vector2d);

/**
 * @brief Converts the rectangular coordinate into a polar coordinate by finding 
 *        the inverse of the tangent of Y/X.
 * @note The angle is with the postive direction of x-axis and in rads!
 * 
 * @param vector2d a rectangular coordinate vector.
 * @return the polar coordinate value in radians.
 */
extern coordinate vector2d_polar(vector2d);

/**
 * @brief Applies a moduluo (integer division) on vector components, returing the remainder 
 *        of the integer division in a new vector2d in a R(2) space.
 * 
 * @param vector2d a rectangular coordinate vector.
 * @return the polar coordinate value in radians.
 */
extern vector2d vector2f_scalar_moduluo(vector2d, coordinate);

/**
 * @brief Finds the metric distance between two vectors in a R(2) space by calculating the 
 *        norm of the their subtraction.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return the metric distance between the specified vectors.
 */
extern coordinate vector2d_distance(vector2d, vector2d);

/**
 * @brief Tests whether two vectors are dependent in a R(2) vector-space.
 * @note Two vectors are said to be dependent if they are multiplies of one another,
 *       such that, the [u = cv], where u and v are vectors and c is a scalar value not equal to zero.
 * @note Linear dependent vectors are coincident vectors in a R(2) space.
 *  
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return (1) for true if the two vectors are dependent or (0) for false otherwise.
 */
extern uint8_t vector2d_is_dependent(vector2d, vector2d);

/**
 * @brief Tests whether two vectors are perpendicular in a R(2) vector-space.
 * @note Two vectors are said to be perpendicular if and only if their dot-product is zero
 *       because, cos(90) is zero, so u.v = |u|.|v|.cos(90) = 0.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return (1) for true if the two vectors are perpendicular or (0) for false otherwise.
 */
extern uint8_t vector2d_are_perpendicular(vector2d, vector2d);

/**
 * @brief Tests whether two vectors are parallel in a R(2) vector-space.
 * @note Two vectors are said to be parallel if and only if their dot-product 
 *       is equal to the product of their norms (lengths);
 *       because, cos(0) is 1, so u.v = |u|.|v|.cos(0) = |u|.|v|.
 * 
 * @param vector2d the first vector.
 * @param vector2d the second vector.
 * @return (1) for true if the two vectors are parallel or (0) for false otherwise.
 */
extern uint8_t vector2d_are_parallel(vector2d, vector2d);

#ifdef __cplusplus
}
#endif

#endif //_vector2d_H_
