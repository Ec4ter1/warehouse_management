#pragma once
#include <vector>
#include <algorithm>
#include <random>   
#include <chrono>
#include <observer.h>
#include "produs.h"
using std::vector;
/*
  Clasa care implementeaza ideea de cos
*/

class Cos : public Observable{
	vector<Prod> inCos;
	int total = 0;
public:
	Cos() = default;

	void adauga(const Prod& p) {
		inCos.push_back(p);
		total += p.get_pret();
	}
	void goleste() noexcept {
		inCos.clear();
		total = 0;
	}

	int get_total() noexcept {
		return total;
	}
	/*
	Umple cosul aleator
	*/
	void umple(size_t cate, vector<Prod> all) {
		std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
		while (inCos.size() < cate && all.size() > 0) {
			inCos.push_back(all.back());
			total += all.back().get_pret();
			all.pop_back();
		}
	}

	const vector<Prod>& lista() const noexcept {
		return inCos;
	}
};

