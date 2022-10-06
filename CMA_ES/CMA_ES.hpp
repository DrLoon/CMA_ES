#pragma once
#include <vector>
#include <functional>

#include "LMatrix.hpp"

std::vector<double> norm_dist(const double mean, const double s, const double n) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<double> dist(mean, s);

	std::vector<double> r(n);
	for (auto& i : r)
		i = dist(gen);
	return r;
}


class CMA_ES
{
public:
	double upper_bound = 1;
	double lower_bound = -1;


	CMA_ES(const std::function<double(const std::vector<double>&)>& _fitness_function,
		const int _pop_size, const int gen_size, const double _sigma) :
		fitness_function(_fitness_function), pop_size(_pop_size), sigma(_sigma)
	{
		pop.resize(pop_size);
		for (auto& i : pop)
			i.resize(gen_size, 0);

		mean.resize(gen_size);
	}

	void optimize(const int max_generations) {
		for (int it = 0; it < max_generations; ++it) {
			rand_popution();
			sort();
			move_mean();
			update_C();
			update_sigma();
		}
	}

	void print_results() {
		std::cout << "Best - " << fitness_function(pop[0]) << '\n';
	}

private:
	LMatrix C;

	const std::function<double(const std::vector<double>&)> fitness_function;
	const int pop_size;
	std::vector<double> mean;
	double sigma;
	std::vector<std::vector<double>> pop;

	void rand_popution() {
		for (auto& gen : pop) {
			auto v = norm_dist(0, 1, gen.size());
			for (int i = 0; i < gen.size(); ++i)
				gen[i] = mean[i] + v[i];//////////
		}
	}

	void sort() {

	}

	void move_mean() {

	}

	void update_C() {

	}

	void update_sigma() {

	}

};