#ifndef BOOST_ASTRO_AFFINE
#define BOOST_ASTRO_AFFINE

#include <boost/astronomy/coordinate/cartesian_representation.hpp>
#include <iostream>
#include <math.h>
#define size 4
using namespace boost::units;
using namespace boost::units::si;
using namespace boost::astronomy::coordinate;

namespace boost::astronomy::coordinate
{

class affine
{
private:
    double tform[size][size];
    void set_affine_matrix(double[size][size]);

public:
    affine();

    void translate(double, double, double);
    void scale(double, double, double);
    void rotateX(double);
    void rotateY(double);
    void rotateZ(double);
    void shear(double, double, double, double, double, double);
    void show_affine_matrix();
    template <
        template <typename...> class Representation,
        typename... Args>
    auto affine_transform(Representation<Args...> const &);
};

/* creates a 4x4 identity matrix and assign it to affine matrix*/
affine::affine()
{
    for (unsigned int i = 0; i < size; i++)
        for (unsigned j = 0; j < size; j++)
            this->tform[i][j] = ((i == j) ? 1 : 0);
}
/* sets the affine matrix  */
void affine::set_affine_matrix(double mat[size][size])
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            this->tform[i][j] = mat[i][j];
}
/*function to translate the given point in x, y, z by tx, ty, tz respectively */
void affine::translate(double tx, double ty, double tz)
{
    double mat[size][size] = {
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0, 1}};
    this->set_affine_matrix(mat);
}
/*function to scale by sx, sy, sz*/
void affine::scale(double sx, double sy, double sz)
{
    double mat[size][size] = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}};
    this->set_affine_matrix(mat);
}

/*function to rotate a point about x axis by 'angle' radians  */
void affine::rotateX(double angle) //radian
{
    double c = std::cos(angle);
    double s = std::sin(angle);
    double mat[size][size] = {
        {1, 0, 0, 0},
        {0, c, -s, 0},
        {0, s, c, 0},
        {0, 0, 0, 1}};
    this->set_affine_matrix(mat);
}

/*function to rotate a point about y axis by 'angle' radians */
void affine::rotateY(double angle)
{
    double c = std::cos(angle);
    double s = std::sin(angle);
    double mat[size][size] = {
        {c, 0, s, 0},
        {0, 1, 0, 0},
        {-s, 0, c, 0},
        {0, 0, 0, 1}};
    this->set_affine_matrix(mat);
}

/*function to rotate a point about z axis by 'angle' radians  */
void affine::rotateZ(double angle)
{
    double c = std::cos(angle);
    double s = std::sin(angle);
    double mat[size][size] = {
        {c, -s, 0, 0},
        {s, c, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};
    this->set_affine_matrix(mat);
}

/*function to shear */
void affine::shear(double sxy, double syx, double sxz, double szx, double syz, double szy)
{
    double mat[size][size] = {
        {1, sxy, sxz, 0},
        {syx, 1, syz, 0},
        {szx, szy, 1, 0},
        {0, 0, 0, 1}};

    this->set_affine_matrix(mat);
}

/*function to display the affine matrix */
void affine::show_affine_matrix()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            std::cout << this->tform[i][j] << " ";
        std::cout << "\n";
    }
}

/*function to apply affine transformation  */
template <
    template <typename...> class Rep, // representation
    typename... Args>
auto affine::affine_transform(Rep<Args...> const &vec)
{
    auto v = make_cartesian_representation(vec);
    typedef decltype(v) vtype;

    double x[size];
    double b[size] = {0, 0, 0, 0};
    x[0] = v.get_x().value();
    x[1] = v.get_y().value();
    x[2] = v.get_z().value();
    x[3] = 1;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            b[i] += this->tform[i][j] * x[j];
        }
    }
    v.set_x(static_cast<typename vtype::type>(b[0]) *
            typename vtype::quantity1::unit_type());
    v.set_y(static_cast<typename vtype::type>(b[1]) *
            typename vtype::quantity2::unit_type());
    v.set_z(static_cast<typename vtype::type>(b[2]) *
            typename vtype::quantity3::unit_type());
    return Rep<Args...>(v);
}
} // namespace boost::astronomy::coordinate

#endif
