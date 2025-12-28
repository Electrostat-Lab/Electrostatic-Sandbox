#include <electronetsoft/arithmos/vectorspaces/vector2d/vector2d.h>

/*
 * Here is how this formula yields a result: 
 *
 * # Formula:
 * u = [u1 u2], v = [v1, v2]
 * u x v = [u1] \ / [v1] = (u1 v2 - u2 v1).
 *         [u2] / \ [v2]
 * 
 * # Proof:
 * u x v = (u1i + u2j) x (v1i + v2j)
 *       = u1 v1 ixi + u1 v2 ixj + u2 v1 jxi + u2 v2 jxj
 *       = u1 v2 ixj - u2 v1 ixj
 *       = (u1 v2 - u2 v1)ixj
 * 
 * # Conclusion:
 * ixj is the projection k component which is congruent to z-axis in R(3) vectorspaces.
 */
status_code vec2d_cross_product(vector2d v0, vector2d v1,
                                vec_component *out, vec2d_processors *processors) {
    if (rvalue(out) == NULL) {
        return EUNDEFINEDBUFFER;
    }

    *out = v0.x * v1.y - v0.y * v1.x;

    return PASS;
}
