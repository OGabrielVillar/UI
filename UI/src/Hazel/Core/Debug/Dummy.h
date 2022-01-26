#pragma once

#include "pch.h"

struct Dummy {
	Dummy() {
		std::cout << "Dummy Default Constructed!" << std::endl;
	}
	Dummy(const char* string_literal) 
		: name(string_literal)
	{
		std::cout <<  "\"" << string_literal << "\", The Dummy, Constructed With String Literal!" << std::endl;
	}
	~Dummy() {
		std::cout << name << ", The Dummy, Default Destructed!" << std::endl;
	}
	Dummy(const Dummy& other) 
		: name(other.name)
	{
		std::cout << name << ", The New Dummy, Copied from " << other.name << "!" << std::endl;
	}
	Dummy(Dummy&& other) noexcept
		: name(std::move(other.name))
	{
		std::cout << name << ", The New Dummy, Moved From "<< other.name << std::endl;
	}
	Dummy& operator = (const Dummy&) {
		std::cout << "Dummy Equals Operator!" << std::endl;
	}

	std::string name = "Dummy";
};
