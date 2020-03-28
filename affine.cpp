#include <bits/stdc++.h>
#include <boost/astronomy/coordinate/cartesian_representation.hpp>
#include <boost/geometry.hpp>
#include <boost/units/unit.hpp>
#include <boost/units/systems/si.hpp>

using namespace std;
namespace bu = boost::units;
namespace bg = boost::geometry;
namespace bac = boost::astronomy::coordinate;

// some quantity
typedef bu::quantity<bu::si::dimensionless, double> t;
typedef bu::quantity<bu::si::length, double> s;

/*
template class 
A : coordinate type
X : Xquantity
Y : Yquantity
Z : Zquantity
*/
template <class A, class X, class Y, class Z>
class affine
{
private:
    double tform[3][3]; // affine 3x3 matrix
    bg::model::point<A, 3, bg::cs::cartesian> p;

public:
    //constructor initialises tform matrix
    affine(double tform[3][3]);
    // function that operates on cartesian representation vector and returns the answer
    bac::cartesian_representation<A, X, Y, Z> transform_affine(bac::cartesian_representation<A, X, Y, Z>);
};

// tform initialisation
template <class A, class X, class Y, class Z>
affine<A, X, Y, Z>::affine(double tform[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            this->tform[i][j] = tform[i][j];
}

// logic
template <class A, class X, class Y, class Z>
bac::cartesian_representation<A, X, Y, Z> affine<A, X, Y, Z>::transform_affine(bac::cartesian_representation<A, X, Y, Z> v)
{
    XQuantity::from_value(bg::get<0>(this->point));
    bac::cartesian_representation<A, X, Y, Z> res;
    double r, temp[3], tres[3] = {0, 0, 0};

    X x = v.get_x();
    temp[0] = v.get_x().value();
    temp[1] = v.get_y().value();
    temp[2] = v.get_z().value();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            tres[i] += this->tform[i][j] * temp[j];
    }
    this->p.set<0>(temp[0]);
    this->p.set<1>(temp[1]);
    this->p.set<2>(temp[2]);

    res.set_x(X.) return res;
}

int main()
{
    bac::cartesian_representation<int, t, t, t> x;
    double mat[3][3] = {
        {3, 0, 0},
        {0, 4, 0},
        {0, 0, 1}};

    // affine<int, s, s, s> A(mat);
    s p;
    bg::model::point<int, 3, bg::cs::cartesian> point1(1, 3, 4);
    bg::se
    A.transform_affine(x);
    return 0;
}