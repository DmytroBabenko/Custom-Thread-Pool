#include "stdafx.h"

#include "Utility.h"
std::mutex Utility::m_mutex;

unsigned Utility::GenerateUniqueID()
{
	std::lock_guard<std::mutex> locker(m_mutex);
	static unsigned id = 0;
	return id++;

}