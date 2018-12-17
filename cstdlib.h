#pragma once
#define CSTDLIB_H

#ifndef _WINDOWS_
#define min(a,b) ((a)>(b))?(b):(a)
#define max(a,b) ((a)>(b))?(a):(b)
#endif
inline float abs(float a)
{
	if (a < 0) return 0 - a;
	return a;
}
