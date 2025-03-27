#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;
#include <assert.h>

class DTO
{
	string nume;
	int count = 0 ;
public:
	DTO() = default;
	DTO(string nume): nume{nume}, count {1}{}

	string get_nume() {
		return nume;
	}
	int get_count() noexcept{
		return count;
	}
	void inc_count() noexcept{
		count++;
	}
};


