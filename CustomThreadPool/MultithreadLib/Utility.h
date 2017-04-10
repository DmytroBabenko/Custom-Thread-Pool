#pragma once

#include "DllAPI.h"

class  Utility
{
public:
	MULTITHREADLIB_API static unsigned GenerateUniqueID();

private:
	static std::mutex m_mutex;
};