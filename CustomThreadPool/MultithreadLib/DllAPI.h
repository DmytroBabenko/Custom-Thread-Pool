#pragma once

# ifndef MULTITHREADLIB_API
# ifndef _MULTITHREADLIB_EXPORT
#  define  MULTITHREADLIB_API __declspec(dllimport)
# else
#  define MULTITHREADLIB_API __declspec(dllexport)
# endif
# endif