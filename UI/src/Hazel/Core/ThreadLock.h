#pragma once

#include "pch.h"

namespace Hazel 
{
	
	class ThreadLock {
	 public:
		ThreadLock() = default;
		void Wait();
		void True();
	 private:
		std::condition_variable cv;
		bool b = false;
	};

}
