#pragma once
#include "Hazel/Core/core.h"

namespace fileio {

	template<typename ... args>
	struct command {
		command(const std::string& typename_in, std::function<void(args ...)> lambda_in)
			: m_lambda(lambda_in), m_typename(typename_in)
		{}
		void operator()(args ... a) {
			return m_lambda(a ...);
		}
		bool Check(const std::string& cmd_in) {
			return cmd_in == m_typename;
		}
	private:
		std::string m_typename;
		std::function<void(args ...)> m_lambda;
	};

	template<typename... Ts> void func(Ts... args) {
		const int size = sizeof...(args) + 2;
		int res[size] = { 1,args...,2 };
		// since initializer lists guarantee sequencing, this can be used to
		// call a function on each element of a pack, in order:
		int dummy[sizeof...(Ts)] = { (std::cout << args, 0)... };
	}

	class FileReader {
	private:
	public:
		FileReader(const std::string& filepath) : myfile(filepath), state(myfile.operator bool()) {	}

		bool Get(std::string& out) {
			out.erase();
			char c;
			bool reading(false); // return true if found any string;
			while (myfile.get(c)) {
				if (!reading)
				{ //look up for commands
					if (c > 32) {
						out.push_back(c);
						reading = true;
					}
				}
				else
				{ //continue pushing chars into the string
					if (c > 32)
						out.push_back(c);
					else
						return true;
				}
			}
			return reading;
		}
		std::string Get() {
			std::string out;
			char c;
			bool reading(false); // return true if found any string;
			while (myfile.get(c)) {
				if (!reading)
				{ //look up for commands
					if (c > 32) {
						out.push_back(c);
						reading = true;
					}
				}
				else
				{ //continue pushing chars into the string
					if (c > 32)
						out.push_back(c);
					else
						return out;
				}
			}
			return out;
		}

		operator bool() {
			return state;
		}

	private:
		std::ifstream myfile;
		bool state; //true = good(file exists).
	};

}
