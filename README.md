# Boost.Astronomy Project 1 competency test

An affine transformation preserves collinearity ( points sit on a line before the transformation, they all sit on a line afterwards) and the ratios of distances between points on a line. This repository contains a file affine.hpp which contains a class which performs affine transformations on cartesian_represnetation.

**The following are transformations are present in the class:**

- Translation
- Rotation about the x-axis
- Rotation about the y-axis
- Rotation about the z-axis
- Scaling
- Shearing

**Helper functions:**

- **show_affine_matrix():** function to display affine matrix
- **set_affine_matrix():** This function sets the affine matrix. (This function is private)
- **affine_transform():** This function applies the respective transform chosen by the user 

test.cpp highlights the use of affine.hpp
