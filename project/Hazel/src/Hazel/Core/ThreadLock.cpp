#include "pch.h"
#include "ThreadLock.h"

namespace Hazel {

	void ThreadLock::Wait()
	{
		std::mutex m;
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [this]{return b;});
		b = false;
	}

	void ThreadLock::True()
	{
		b = true;
		cv.notify_all();
	}

}
