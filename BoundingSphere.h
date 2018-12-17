/***************************************************************************
 * Bounding Sphere class has methods to generate a bounding sphere for a
 * Mesh or a Sphere and has the intersection method.
 */

#include <Eigen/Core>
#include "Intersection.h"
#include "Ray.h"

class BoundingSphere {
public:
    float diameter;
    Eigen::Vector3f centre;

    BoundingSphere();
    void setupBoundingSphere(Eigen::MatrixXf v);
    void setupBoundingSphere(float diameter, Eigen::Vector3f centre);
    Intersection intersect(Ray ray);
};
