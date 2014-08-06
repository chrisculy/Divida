//
// pch.h
// Header for standard system include files.
//

#ifndef _divida_precompiled_header_h_
#define _divida_precompiled_header_h_

#ifdef WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#endif

#include <algorithm>
#include <iomanip>
#include <memory>
#include <string>
#include <sstream>

#ifndef __clang__
#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 9)
namespace std
{

template<typename T, typename ...Args>
unique_ptr<T> make_unique(Args&& ...args)
{
	return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}
#endif
#endif

#endif
