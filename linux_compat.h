#ifndef LINUX_COMPAT_H
#define LINUX_COMPAT_H

#ifndef _MSC_VER
#define __forceinline inline __attribute__((always_inline))
#define __declspec(x) __attribute__((x))
#endif

#endif
