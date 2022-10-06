#pragma once

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

#include "LMatrix.hpp"

// Define error codes.
constexpr int QBEIG_MATRIXNOTSQUARE = -1;
constexpr int QBEIG_MAXITERATIONSEXCEEDED = -2;
constexpr int QBEIG_MATRIXNOTSYMMETRIC = -3;

// The qbEIG function (power iteration method).
int qbEIG_PIt(const LMatrix& X, double& eigenValue, LMatrix& eigenVector)
{
	// Make a copy of the input matrix.
	LMatrix inputMatrix = X;

	// Verify that the input matrix is square.
	/*if (!inputMatrix.IsSquare())
		return QBEIG_MATRIXNOTSQUARE;*/

	// Setup a random number generator.
	std::random_device myRandomDevice;
	std::mt19937 myRandomGenerator(myRandomDevice());
	std::uniform_int_distribution<int> myDistribution(1.0, 10.0);

	/* The number of eigenvectors and eigenvalues that we will compute will be
		equal to the number of rows in the input matrix. */
	int numRows = inputMatrix.n;

	// Create an identity matrix of the same dimensions.
	LMatrix identityMatrix(numRows, numRows);
	identityMatrix.SetToIdentity();

	/* **************************************************************
		Compute the eigenvector.
	************************************************************** */

	// Create an initial vector, v.
	LMatrix v(numRows, 1);
	for (int i = 0; i < numRows; ++i)
		v(i, 0) = static_cast<double>(myDistribution(myRandomGenerator));

	// Loop over the required number of iterations.
	LMatrix v1(numRows, 1);
	int numIterations = 1000;
	for (int i = 0; i < numIterations; ++i)
	{
		v1 = inputMatrix * v;
		double norm = 0;
		for (auto& i : v1.data)
			norm += i[0] * i[0];
		norm = sqrt(norm);
		v1 = v1 * (1 / norm);
		v = v1;
	}

	// Store this eigenvector.
	eigenVector = v1;

	/* **************************************************************
		Compute the eigenvalue corresponding to this eigenvector.
	************************************************************** */

	// Compute the cumulative sum.
	double cumulativeSum = 0.0;
	for (int i = 1; i < numRows; ++i)
		cumulativeSum += inputMatrix(0, i) * v1(i, 0);

	eigenValue = (cumulativeSum / v1(0, 0)) + inputMatrix(0, 0);

	return 0;
}