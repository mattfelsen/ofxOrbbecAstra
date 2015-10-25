#ifndef ASTRA_DEFINES_H
#define ASTRA_DEFINES_H

#ifdef  __cplusplus
# define ASTRA_BEGIN_DECLS  extern "C" {
# define ASTRA_END_DECLS    }
#else
# define ASTRA_BEGIN_DECLS
# define ASTRA_END_DECLS
#endif

# if defined (_MSC_VER)
#  define ASTRA_EXPORT __declspec(dllexport)
#  define ASTRA_IMPORT __declspec(dllimport)
#  define ASTRA_PUBLIC
#  define ASTRA_LOCAL
# else
#  if __GNUC__ >= 4 || defined (__clang__)
#    define ASTRA_PUBLIC __attribute__ ((visibility ("default")))
#    define ASTRA_LOCAL  __attribute__ ((visibility ("hidden")))
#    define ASTRA_EXPORT ASTRA_PUBLIC
#    define ASTRA_IMPORT
#  else
#    define ASTRA_PUBLIC
#    define ASTRA_LOCAL
#    define ASTRA_EXPORT
#    define ASTRA_IMPORT
#  endif
# endif

#ifndef ASTRA_API
#  ifdef ASTRA_BUILD
#    define ASTRA_API ASTRA_PUBLIC ASTRA_EXPORT
#  else
#    define ASTRA_API ASTRA_IMPORT
#  endif
#endif

#ifndef ASTRA_API_EX
#  ifdef ASTRA_BUILD_EX
#    define ASTRA_API_EX ASTRA_EXPORT
#  else
#    define ASTRA_API_EX ASTRA_IMPORT
#  endif
#endif

#endif /* ASTRA_DEFINES_H */
