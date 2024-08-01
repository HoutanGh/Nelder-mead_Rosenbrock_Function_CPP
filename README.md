# Nelder-mead_Rosenbrock_Function_CPP

# NMRB.cpp

## Overview
This program implements the Nelder-Mead optimization algorithm to find the minimum of the Rosenbrock function. The Rosenbrock function is a well-known test problem for optimization algorithms and is defined as:

$f(x, y) = 100(y - x^2)^2 + (1 - x)^2$

## Features
- **Initialisation of Simplex**: The program initializes a simplex with three points.
- **Termination Criteria**: The algorithm terminates when the maximum number of iterations is reached or the difference between the highest and lowest function values in the simplex is below a certain threshold.
- **Centroid Calculation**: Calculates the centroid of the simplex excluding the worst point.
- **Reflection, Contraction, Expansion, and Shrink Operations**: Implements the reflection, contraction, expansion, and shrink operations to iteratively improve the simplex.
 
