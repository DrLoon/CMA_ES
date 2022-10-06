#include <iostream>
#include <vector>

#include "CMA_ES.hpp"
#include "Header.hpp"
#include "Jakobi.hpp"


double fitness(const std::vector<double>& x) {
	double result = 10 * x.size();
	for (auto i : x) result += i * i - 10 * cos(2 * additionl_staff::pi * i);
	return result;
}

int main()
{
    //CMA_ES model(fitness, 64, 10, 3);
	//model.optimize(10000);
	//model.print_results();

	LMatrix A(3, 3);
	std::vector<std::vector<double>> mat = { {2, 5,-2},
											 {3, 8, 0},
											 {1, 3, 5} };
	A.data = mat;

	// header
	LMatrix EV(3, 1);
	double eigenvalue;
	qbEIG_PIt(A, eigenvalue, EV);
	EV.console_out();
	std::cout << eigenvalue << '\n';

	std::cout << "\n\n\n";

	// jakobi
	LMatrix eigenVectors(A.n, A.m);
	std::vector<double> eigenValues(A.n, 0);
	eigenValues_eigenVectors(A, eigenValues, eigenVectors);
	eigenVectors.console_out();
	for(auto& i : eigenValues)
		std::cout << i << ' ';

	std::cout << "\n\n\n";

    return 0;
}