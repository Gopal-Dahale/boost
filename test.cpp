#include <bits/stdc++.h>
#include <boost/astronomy/coordinate/cartesian_representation.hpp>
#include <boost/units/systems/si/length.hpp>
#include "affine.cpp"
using namespace std;
using namespace boost::astronomy::coordinate;
using namespace boost::units;
using namespace boost::units::si;

// function to display the transformed cartesian point
template <typename T>
void disp(T res)
{
    cout << res.get_x().value() << " ";
    cout << res.get_y().value() << " ";
    cout << res.get_z().value() << "\n\n";
}

int main()
{
    // cook your dish here
    const double pi = 3.14159;

    auto point = make_cartesian_representation(10.0 * meter, 20.0 * meter, 30.0 * meter);

    affine A;

    cout << "affine matrix after creation of object\n";
    A.show_affine_matrix();

    cout << "\naffine transformation by identiy matrix\n";
    disp(A.affine_transform(point));

    cout << "translation\n";
    A.translate(4, 2, 43);
    A.show_affine_matrix();
    disp(A.affine_transform(point));

    cout << "rotation about x axis\n";
    A.rotateX(pi / 4);
    A.show_affine_matrix();
    disp(A.affine_transform(point));

    cout << "rotation about y axis\n";
    A.rotateY(pi / 4);
    A.show_affine_matrix();
    disp(A.affine_transform(point));

    cout << "rotation about Z axis\n";
    A.rotateZ(pi / 4);
    A.show_affine_matrix();
    disp(A.affine_transform(point));

    cout << "shear\n";
    A.shear(1, 2, 3, 4, 5, 6);
    A.show_affine_matrix();
    disp(A.affine_transform(point));

    cout << "scale\n";
    A.scale(1, 2, 3);
    A.show_affine_matrix();
    disp(A.affine_transform(point));

    return 0;
}