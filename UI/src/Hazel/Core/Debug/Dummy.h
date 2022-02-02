#pragma once

#include "pch.h"

namespace Hazel {

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
		void* operator new(std::size_t sz){
			std::cout << "Dummy New Operator!" << std::endl;
			if (sz == 0)
				++sz; // avoid std::malloc(0) which may return nullptr on success
 
			if (void *ptr = std::malloc(sz))
				return ptr;
 
			throw std::bad_alloc{}; // required by [new.delete.single]/3
		}
		std::string name = "Dummy";
	};

	template <class _CharT, class _Traits>
    std::basic_ostream<_CharT, _Traits>& operator<<(
        std::basic_ostream<_CharT, _Traits>& _Os, const Dummy& dummy) {
        return _Os << dummy.name;
    }

}
