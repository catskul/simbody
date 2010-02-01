#ifndef SimTK_SimTKCOMMON_COMMON_H_
#define SimTK_SimTKCOMMON_COMMON_H_

/* -------------------------------------------------------------------------- *
 *                      SimTK Core: SimTKcommon                               *
 * -------------------------------------------------------------------------- *
 * This is part of the SimTK Core biosimulation toolkit originating from      *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2005-9 Stanford University and the Authors.         *
 * Authors: Michael Sherman                                                   *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

/**@file
 * Mandatory first inclusion for any %SimTK source or header file.
 * 
 * Every source and most header files using %SimTK must include this 
 * header as its \e first inclusion. Declarations and definitions that 
 * must be available and compiler-and machine-specific issues are dealt
 * with here.
 *
 * This file must be includable from either C++ or ANSI C. It uses
 * the ANSI-C++ macro "__cplusplus" for any code that will compile
 * only under C++.
 */

// Provide doxygen documentation for the SimTK namespace.

/**@namespace SimTK
 *
 * This is the top-level %SimTK namespace into which all %SimTK names are 
 * placed to avoid collision with other symbols. If you get tired of prefacing 
 * every symbol with "SimTK::", include the statement "using namespace SimTK;" 
 * at the beginning of your %SimTK-using compilation units. Any names which 
 * cannot be put in the namespace (macro names, for example) begin with the 
 * prefix "SimTK_" instead. 
 */

// Define shared doxygen "modules" and sub-modules here. We'll put things 
// in them at various places when appropriate.

/**@defgroup GlobalFunctions Global Functions in the SimTK namespace
 *
 * These are functions at the top level of the SimTK namespace, meaning
 * that a function named funcName() is invoked as SimTK::funcName(), or
 * just funcName() if there is a "using namespace SimTK;" statement in effect.
 */

/**@defgroup ScalarFunctions Scalar Functions
 * @ingroup GlobalFunctions
 *
 * These functions are overloaded to act on %SimTK scalar types and C++
 * built-in types, including integral types when appropriate.
 */

/**@defgroup BitFunctions Bit-twiddling Functions
 * @ingroup GlobalFunctions
 *
 * These functions perform highly optimized bit-twiddling operations on
 * the built-in integral types, and sometimes on the representations of
 * floating point types as well.
 */

/*****************************/
/* ANSI-C COMPATIBLE SECTION */
/*****************************/

/* Set up a few compile-time options that affect all SimTK Core headers. */

/**
 * This compile-time constant determines the default precision used everywhere
 * in %SimTK Core code. Wherever a SimTK::Real, SimTK::Vector, SimTK::Matrix,
 * etc. appears with no precision specified, it will have this underlying precision.
 * We use 1==float, 2==double, 4==long double. Any other value will cause
 * a compile time error. The default is 2, i.e., double precision.
 */
#ifndef SimTK_DEFAULT_PRECISION
#   define SimTK_DEFAULT_PRECISION 2
#endif

#if   (SimTK_DEFAULT_PRECISION == 1)
/** This type is for use in C; in C++ use SimTK::Real instead. */
    typedef float SimTK_Real;
#elif (SimTK_DEFAULT_PRECISION == 2)
/** This type is for use in C; in C++ use SimTK::Real instead. */
    typedef double SimTK_Real;
#elif (SimTK_DEFAULT_PRECISION == 4)
/** This type is for use in C; in C++ use SimTK::Real instead. */
    typedef long double SimTK_Real;
#else
    #error ILLEGAL VALUE FOR DEFAULT PRECISION
#endif

#ifndef NDEBUG
    #if defined(__cplusplus)
        #include <cstdio>
        #define SimTK_DEBUG(s) std::printf("DBG: " s)
        #define SimTK_DEBUG1(s,a1) std::printf("DBG: " s,a1)	
        #define SimTK_DEBUG2(s,a1,a2) std::printf("DBG: " s,a1,a2)	
        #define SimTK_DEBUG3(s,a1,a2,a3) std::printf("DBG: " s,a1,a2,a3)	
        #define SimTK_DEBUG4(s,a1,a2,a3,a4) std::printf("DBG: " s,a1,a2,a3,a4)
    #else
        #include <stdio.h>
        #define SimTK_DEBUG(s) printf("DBG: " s)
        #define SimTK_DEBUG1(s,a1) printf("DBG: " s,a1)	
        #define SimTK_DEBUG2(s,a1,a2) printf("DBG: " s,a1,a2)	
        #define SimTK_DEBUG3(s,a1,a2,a3) printf("DBG: " s,a1,a2,a3)	
        #define SimTK_DEBUG4(s,a1,a2,a3,a4) printf("DBG: " s,a1,a2,a3,a4)
    #endif
#else
    #define SimTK_DEBUG(s)
    #define SimTK_DEBUG1(s,a1)
    #define SimTK_DEBUG2(s,a1,a2)
    #define SimTK_DEBUG3(s,a1,a2,a3)	
    #define SimTK_DEBUG4(s,a1,a2,a3,a4)
#endif

/*
 * Shared libraries are messy in Visual Studio. We have to distinguish three
 * cases:
 *   (1) this header is being used to build the SimTKcommon shared library (dllexport)
 *   (2) this header is being used by a *client* of the SimTKcommon shared
 *       library (dllimport)
 *   (3) we are building the SimTKcommon static library, or the client is
 *       being compiled with the expectation of linking with the
 *       SimTKcommon static library (nothing special needed)
 * In the CMake script for building this library, we define one of the symbols
 *     SimTK_SimTKCOMMON_BUILDING_{SHARED|STATIC}_LIBRARY
 * Client code normally has no special symbol defined, in which case we'll
 * assume it wants to use the shared library. However, if the client defines
 * the symbol SimTK_USE_STATIC_LIBRARIES we'll suppress the dllimport so
 * that the client code can be linked with static libraries. Note that
 * the client symbol is not library dependent, while the library symbols
 * affect only the SimTKcommon library, meaning that other libraries can
 * be clients of this one. However, we are assuming all-static or all-shared.
 */

#ifdef _WIN32
    #ifdef _MSC_VER
    #pragma warning(disable:4231) // need to use 'extern' template explicit instantiation
    #pragma warning(disable:4251) // no DLL interface for type of member of exported class
    #endif
    #if defined(SimTK_SimTKCOMMON_BUILDING_SHARED_LIBRARY)
        #define SimTK_SimTKCOMMON_EXPORT __declspec(dllexport)
        /* Keep MS VC++ quiet when it tries to instantiate incomplete template classes in a DLL. */
        #ifdef _MSC_VER
        #pragma warning(disable:4661)
        #endif
    #elif defined(SimTK_SimTKCOMMON_BUILDING_STATIC_LIBRARY) || defined(SimTK_USE_STATIC_LIBRARIES)
        #define SimTK_SimTKCOMMON_EXPORT
    #else
        #define SimTK_SimTKCOMMON_EXPORT __declspec(dllimport)   // i.e., a client of a shared library
    #endif
	/* VC++ tries to be secure by leaving bounds checking on for STL containers
	 * even in Release mode. This macro exists to disable that feature and can
	 * result in a considerable speedup.
	 * CAUTION: every linked-together compilation unit must have this set the same
	 * way. Everyone who properly includes this file first is fine; but as of this
	 * writing Simmath's IpOpt doesn't do so.
     */
	/* (sherm 081204 disabling for now: doesn't work on VC++ 8 and is 
	 * tricky on VC++ 9 because all libraries, including 3rd party, must
	 * be built the same way)
	 #ifdef NDEBUG
	 	#undef _SECURE_SCL
	 	#define _SECURE_SCL 0
	 #endif
     */
#else
    #define SimTK_SimTKCOMMON_EXPORT // Linux, Mac
#endif

/* Every SimTK Core library must provide these two routines, with the library
 * name appearing after the "version_" and "about_".
 */
#if defined(__cplusplus)
extern "C" {
#endif
    /** Obtain version information for the currently-loaded SimTKcommon library. */
    SimTK_SimTKCOMMON_EXPORT void SimTK_version_SimTKcommon(int* major, int* minor, int* build);
    /** 
     * Obtain "about" information for the currently-loaded SimTKcommon library.
     * Available keywords are "version" (major.minor.build), "library", 
     * "type" (shared or static), "copyright", "svn_revision", "authors", 
     * "debug" (debug or release).
     */
    SimTK_SimTKCOMMON_EXPORT void SimTK_about_SimTKcommon(const char* key, int maxlen, char* value);
#if defined(__cplusplus)
}
#endif

/************************************/
/* END OF ANSI-C COMPATIBLE SECTION */
/************************************/

#if defined(__cplusplus)

#include <cstddef>
#include <cassert>
#include <cmath>
#include <cfloat>
#include <complex>
#include <limits>
#include <typeinfo>


/* Currently (Microsoft VC++ 9) these C99-compatible floating point functions are
 * missing. We'll create them here and install them into namespace std.
 * TODO: This should be removed when these are available.
 */
#ifdef _MSC_VER
namespace std {
inline bool isfinite(float f) {return _finite(f) != 0;}
inline bool isfinite(double d) {return _finite(d) != 0;}
inline bool isfinite(long double l) {return _finite(l) != 0;}
inline bool isnan(float f) {return _isnan(f) != 0;}
inline bool isnan(double d) {return _isnan(d) != 0;}
inline bool isnan(long double l) {return _isnan(l) != 0;}
inline bool isinf(float f) {return std::abs(f)==std::numeric_limits<float>::infinity();}
inline bool isinf(double d) {return std::abs(d)==std::numeric_limits<double>::infinity();}
inline bool isinf(long double l) {return std::abs(l)==std::numeric_limits<double>::infinity();}
inline bool signbit(float f) {return (*reinterpret_cast<unsigned*>(&f) & 0x80000000U) != 0;}
inline bool signbit(double d) {return (*reinterpret_cast<unsigned long long*>(&d)
                               & 0x8000000000000000ULL) != 0;}
inline bool signbit(long double l) {return (*reinterpret_cast<unsigned long long*>(&l)
                                    & 0x8000000000000000ULL) != 0;}
}
#endif


namespace SimTK {
// This utility answers the question "if I put this integral value in an int and then
// get it back, will its value be the same?".
inline bool canStoreInInt(bool)            {return true;}
inline bool canStoreInInt(char)            {return true;}
inline bool canStoreInInt(unsigned char)   {return true;}
inline bool canStoreInInt(signed char)     {return true;}
inline bool canStoreInInt(short)           {return true;}
inline bool canStoreInInt(unsigned short)  {return true;}
inline bool canStoreInInt(int)             {return true;}
inline bool canStoreInInt(unsigned int  u) {return (unsigned int)(int(u)) == u;}
inline bool canStoreInInt(long i)          {return long(int(i)) == i;}
inline bool canStoreInInt(unsigned long u) {return (unsigned long)(int(u)) == u;}
inline bool canStoreInInt(long long i)          {return (long long)(int(i)) == i;}
inline bool canStoreInInt(unsigned long long u) {return (unsigned long long)(int(u)) == u;}

// This utility answers the question "is this integral value a nonnegative number
// that can be stored in an int?".
inline bool canStoreInNonnegativeInt(bool)             {return true;}
inline bool canStoreInNonnegativeInt(char c)           {return c >= 0;}
inline bool canStoreInNonnegativeInt(unsigned char c)  {return true;}
inline bool canStoreInNonnegativeInt(signed char c)    {return c >= 0;}
inline bool canStoreInNonnegativeInt(short s)          {return s >= 0;}
inline bool canStoreInNonnegativeInt(unsigned short s) {return true;}
inline bool canStoreInNonnegativeInt(int  i)           {return i >= 0;}
inline bool canStoreInNonnegativeInt(long l)           {return canStoreInInt(l) && l >= 0;}
inline bool canStoreInNonnegativeInt(long long l)      {return canStoreInInt(l) && l >= 0;}
inline bool canStoreInNonnegativeInt(unsigned int  u)  {return canStoreInInt(u);}
inline bool canStoreInNonnegativeInt(unsigned long u)  {return canStoreInInt(u);}
inline bool canStoreInNonnegativeInt(unsigned long long u) {return canStoreInInt(u);}

// This utility answers the question of whether an integer is suitable as a size
// limited by the given maximum size. Signed types must be checked for being
// nonegative; doing that with unsigned types leads to compiler warnings.

// char can be signed or unsigned depending on the compiler; assume signed.
inline bool isSizeInRange(char           sz, char           mx){return 0<=sz&&sz<=mx;}
inline bool isSizeInRange(signed char    sz, signed char    mx){return 0<=sz&&sz<=mx;}
inline bool isSizeInRange(short          sz, short          mx){return 0<=sz&&sz<=mx;}
inline bool isSizeInRange(int            sz, int            mx){return 0<=sz&&sz<=mx;}
inline bool isSizeInRange(long           sz, long           mx){return 0<=sz&&sz<=mx;}
inline bool isSizeInRange(long long      sz, long long      mx){return 0<=sz&&sz<=mx;}
inline bool isSizeInRange(unsigned char  sz, unsigned char  mx){return sz<=mx;}
inline bool isSizeInRange(unsigned short sz, unsigned short mx){return sz<=mx;}
inline bool isSizeInRange(unsigned int   sz, unsigned int   mx){return sz<=mx;}
inline bool isSizeInRange(unsigned long  sz, unsigned long  mx){return sz<=mx;}
inline bool isSizeInRange(unsigned long long sz, unsigned long long mx){return sz<=mx;}

// This utility answers the question of whether an integer is suitable as an index
// for an array limited by the given maximum size. Signed types must be checked for being
// nonegative; doing that with unsigned types leads to compiler warnings. This is just
// like the "size in range" check above except the maximum value allowed for an index
// is one less that the size.

// char can be signed or unsigned depending on the compiler; assume signed.
inline bool isIndexInRange(char           ix, char           sz){return 0<=ix&&ix<sz;}
inline bool isIndexInRange(signed char    ix, signed char    sz){return 0<=ix&&ix<sz;}
inline bool isIndexInRange(short          ix, short          sz){return 0<=ix&&ix<sz;}
inline bool isIndexInRange(int            ix, int            sz){return 0<=ix&&ix<sz;}
inline bool isIndexInRange(long           ix, long           sz){return 0<=ix&&ix<sz;}
inline bool isIndexInRange(long long      ix, long long      sz){return 0<=ix&&ix<sz;}
inline bool isIndexInRange(unsigned char  ix, unsigned char  sz){return ix<sz;}
inline bool isIndexInRange(unsigned short ix, unsigned short sz){return ix<sz;}
inline bool isIndexInRange(unsigned int   ix, unsigned int   sz){return ix<sz;}
inline bool isIndexInRange(unsigned long  ix, unsigned long  sz){return ix<sz;}
inline bool isIndexInRange(unsigned long long ix, unsigned long long sz){return ix<sz;}

// This utility answers the question: is this integral value nonnegative? The answer
// is always true for unsigned types and you'll get a warning from some compilers if
// you check.

inline bool isNonnegative(bool           n){return true;}
// char can be signed or unsigned depending on the compiler; assume signed.
inline bool isNonnegative(char           n){return n>=0;}
inline bool isNonnegative(signed char    n){return n>=0;}
inline bool isNonnegative(short          n){return n>=0;}
inline bool isNonnegative(int            n){return n>=0;}
inline bool isNonnegative(long           n){return n>=0;}
inline bool isNonnegative(long long      n){return n>=0;}
inline bool isNonnegative(unsigned char  n){return true;}
inline bool isNonnegative(unsigned short n){return true;}
inline bool isNonnegative(unsigned int   n){return true;}
inline bool isNonnegative(unsigned long  n){return true;}
inline bool isNonnegative(unsigned long long n){return true;}

// A NaN-like value for unique index types created using the macro
// SimTK_DEFINE_UNIQUE_INDEX_TYPE(). A unique, typed constant with
// this numerical value is created for each index type.
static const int InvalidIndex = -1111111111;
}

/**
 * Use this macro to define a unique "Index" type which is just a type-safe
 * non-negative int, augmented with a "NaN" value given by the predefined
 * int constant SimTK::InvalidIndex. We also allow the Index to take on
 * the value -1 if that is produced by a subtraction operation acting on a 
 * previously-valid Index, since that can occur during loops which are 
 * processed from the end towards the beginning. -1 is then allowed in 
 * comparision operators but not in any other operations, including further 
 * decrementing.
 *
 * No namespace is assumed for the newly-defined type; if you want the 
 * symbol in a namespace be sure to invoke the macro within that namespace. 
 * Make sure that the statement "#include <cassert>" appears somewhere before 
 * the point of invocation of this macro, because the defined Index type uses 
 * the assert() macro when in Debug mode.
 *
 * For most uses it will behave like an int, and it has an implicit
 * conversion \e to int. Importantly though, it has no implicit conversion
 * \e from int so you can't pass some other kind of number where a particular
 * kind of Index was expected. This is used to create Index types
 * which can be used as array indices but which prevent accidental mixing
 * of types. Examples: SubsystemIndex, ConstraintIndex.
 *
 * If you create a type "ThingIndex" you will also get a constant of
 * type ThingIndex named "InvalidThingIndex" which will be the initial
 * value of any objects of type ThingIndex, and will have the same numerical
 * value as SimTK::InvalidIndex.
 */

/// Define a global (that is, SimTK namespace level) Index class that
/// is not exported in MS VC++ DLLs.
#define SimTK_DEFINE_UNIQUE_INDEX_TYPE(NAME)                   \
    SimTK_DEFINE_AND_EXPORT_UNIQUE_LOCAL_INDEX_TYPE(,,,NAME)   \
    static const NAME Invalid ## NAME;

/// Define a global (that is, SimTK namespace level) Index class with
/// a MS VC++ "export" specification for DLLs.
#define SimTK_DEFINE_AND_EXPORT_UNIQUE_INDEX_TYPE(EXPORT,NAME)     \
    SimTK_DEFINE_AND_EXPORT_UNIQUE_LOCAL_INDEX_TYPE(EXPORT,,,NAME) \
    static const NAME Invalid ## NAME;

/// Define a local Index class within a Parent class.
#define SimTK_DEFINE_UNIQUE_LOCAL_INDEX_TYPE(PARENT,NAME) \
    SimTK_DEFINE_AND_EXPORT_UNIQUE_LOCAL_INDEX_TYPE(,PARENT,::,NAME)

/// The most general form allows a MS VC++ "export" specification for DLLs,
/// and a Parent class (with SEP=::) for local Index names.
#define SimTK_DEFINE_AND_EXPORT_UNIQUE_LOCAL_INDEX_TYPE(EXPORT,PARENT,SEP,NAME)   \
class EXPORT NAME {                         \
    int ix;                                 \
public:                                     \
    NAME() : ix(SimTK::InvalidIndex) { }       \
    explicit NAME(int i) : ix(i)      {assert(i>=0 || i==SimTK::InvalidIndex);} \
    explicit NAME(long l): ix((int)l) {assert(SimTK::canStoreInNonnegativeInt(l));}    \
    explicit NAME(unsigned int  u)  : ix((int)u)  {assert(SimTK::canStoreInInt(u));}   \
    explicit NAME(unsigned long ul) : ix((int)ul) {assert(SimTK::canStoreInInt(ul));}  \
    operator int() const {return ix;}               \
    bool isValid() const {return ix>=0;}            \
    bool isValidExtended() const {return ix>=-1;}   \
    void invalidate(){ix=SimTK::InvalidIndex;}      \
    \
    bool operator==(int  i) const {assert(isValidExtended() && isValidExtended(i)); return ix==i;}    \
    bool operator==(long l) const {assert(isValidExtended() && isValidExtended(l)); return ix==(int)l;}  \
    bool operator==(unsigned int  u)  const {assert(isValidExtended() && isValid(u)); return ix==(int)u;}   \
    bool operator==(unsigned long ul) const {assert(isValidExtended() && isValid(ul)); return ix==(int)ul;} \
    bool operator!=(int  i)           const {return !operator==(i);}    \
    bool operator!=(long l)           const {return !operator==(l);}    \
    bool operator!=(unsigned int  u)  const {return !operator==(u);}    \
    bool operator!=(unsigned long ul) const {return !operator==(ul);}   \
    \
    bool operator< (int  i) const {assert(isValidExtended() && isValidExtended(i)); return ix<i;}        \
    bool operator< (long l) const {assert(isValidExtended() && isValidExtended(l)); return ix<(int)l;}   \
    bool operator< (unsigned int  u)  const {assert(isValidExtended() && isValid(u));  return ix<(int)u;}    \
    bool operator< (unsigned long ul) const {assert(isValidExtended() && isValid(ul)); return ix<(int)ul;}   \
    bool operator>=(int  i)           const {return !operator<(i);}    \
    bool operator>=(long l)           const {return !operator<(l);}    \
    bool operator>=(unsigned int  u)  const {return !operator<(u);}    \
    bool operator>=(unsigned long ul) const {return !operator<(ul);}   \
    \
    bool operator> (int  i) const {assert(isValidExtended() && isValidExtended(i)); return ix>i;}        \
    bool operator> (long l) const {assert(isValidExtended() && isValidExtended(l)); return ix>(int)l;}   \
    bool operator> (unsigned int  u)  const {assert(isValidExtended() && isValid(u));  return ix>(int)u;}    \
    bool operator> (unsigned long ul) const {assert(isValidExtended() && isValid(ul)); return ix>(int)ul;}   \
    bool operator<=(int  i)           const {return !operator>(i);}    \
    bool operator<=(long l)           const {return !operator>(l);}    \
    bool operator<=(unsigned int  u)  const {return !operator>(u);}    \
    bool operator<=(unsigned long ul) const {return !operator>(ul);}   \
    \
    const NAME& operator++() {assert(isValid()); ++ix; return *this;}       /*prefix */   \
    NAME operator++(int)     {assert(isValid()); ++ix; return NAME(ix-1);}  /*postfix*/   \
    const NAME& operator--() {assert(isValid()); --ix; return *this;}       /*prefix */   \
    NAME operator--(int)     {assert(isValid()); --ix; return NAME(ix+1);}  /*postfix*/   \
    \
    NAME& operator+=(int i)  {assert(isValid() && isValidExtended(ix+i)); ix+=i; return *this;}     \
    NAME& operator-=(int i)  {assert(isValid() && isValidExtended(ix-i)); ix-=i; return *this;}     \
    NAME& operator+=(long l) {assert(isValid() && SimTK::canStoreInInt(l) && isValidExtended(ix+(int)l)); ix+=(int)l; return *this;}     \
    NAME& operator-=(long l) {assert(isValid() && SimTK::canStoreInInt(l) && isValidExtended(ix-(int)l)); ix-=(int)l; return *this;}     \
    NAME& operator+=(unsigned int  u)  {assert(isValid()&& SimTK::canStoreInInt(u)  && isValid(ix+(int)u));  ix+=(int)u;  return *this;}  \
    NAME& operator-=(unsigned int  u)  {assert(isValid()&& SimTK::canStoreInInt(u)  && isValidExtended(ix-(int)u));  ix-=(int)u;  return *this;}  \
    NAME& operator+=(unsigned long ul) {assert(isValid()&& SimTK::canStoreInInt(ul) && isValid(ix+(int)ul)); ix+=(int)ul; return *this;}  \
    NAME& operator-=(unsigned long ul) {assert(isValid()&& SimTK::canStoreInInt(ul) && isValidExtended(ix-(int)ul)); ix-=(int)ul; return *this;}  \
    \
    static const NAME& Invalid() {static const NAME invalid; return invalid;}       \
    static bool isValid(int  i) {return i>=0;}                                      \
    static bool isValid(long l) {return SimTK::canStoreInNonnegativeInt(l);}        \
    static bool isValid(unsigned int  u)  {return SimTK::canStoreInInt(u);}         \
    static bool isValid(unsigned long ul) {return SimTK::canStoreInInt(ul);}        \
    static bool isValidExtended(int  i) {return i>=-1;}                             \
    static bool isValidExtended(long l) {return SimTK::canStoreInInt(l) && l>=-1;}  \
    /* IndexTraits for use in Array_<T,X> with this as X; same as int */            \
    typedef int size_type;                                      \
    typedef int difference_type;                                \
    static size_type max_size()                                 \
        {return std::numeric_limits<difference_type>::max();}   \
};

/**
 * Add public static method declaration in class derived from an abstract
 * parent to assist in downcasting objects of the parent type to the 
 * derived type.
 */
#define SimTK_DOWNCAST(Derived,Parent) \
    static bool isA(const Parent& p)                        \
        { return dynamic_cast<const Derived*>(&p) != 0; }   \
    static const Derived& downcast(const Parent& p)         \
        { return dynamic_cast<const Derived&>(p); }         \
    static Derived& updDowncast(Parent& p)                  \
        { return dynamic_cast<Derived&>(p); }				\
	static Derived& downcast(Parent& p)                     \
        { return dynamic_cast<Derived&>(p); }

/**
 * This is like SimTK_DOWNCAST except it allows for an intermediate
 * "helper" class between Derived and Parent.
 */
#define SimTK_DOWNCAST2(Derived,Helper,Parent) \
    static bool isA(const Parent& p)                                        \
        { return Helper::isA(p); }                                          \
    static const Derived& downcast(const Parent& p)                         \
        { return reinterpret_cast<const Derived&>(Helper::downcast(p)); }   \
    static Derived& updDowncast(Parent& p)									\
        { return reinterpret_cast<Derived&>(Helper::downcast(p)); }		    \
	static Derived& downcast(Parent& p)                                     \
        { return reinterpret_cast<Derived&>(Helper::downcast(p)); }


// Similar to the above but for private implementation abstract classes, that
// is, abstract class hierarchies where the virtual function table is 
// hidden on the library side.
#define SimTK_PIMPL_DOWNCAST(Derived, Parent)           \
    static bool           isInstanceOf(const Parent&);  \
    static const Derived& downcast(const Parent&);      \
    static Derived&       updDowncast(Parent&)

namespace SimTK {
    
namespace Options { }
namespace Exception { }

/// This is the default compiled-in floating point type for SimTK, either
/// float or double.
/// @see SimTK_DEFAULT_PRECISION
typedef SimTK_Real              Real;
/// This is the default complex type for SimTK, with precision for
/// the real and imaginary parts set to the compiled-in Real type.
/// @see Real
typedef std::complex<Real>      Complex;

/// A convenient struct for anything requiring an offset and length
/// to specify a segment of some larger sequence.
struct Segment {
    Segment() : length(0), offset(0) { }
    explicit Segment(int l, int ofs=0) : length(l), offset(ofs) { 
        assert(l>=0 && ofs>=0);
    }
    // default copy, assignment, destructor
    int length;
    int offset;
};  


/** This is a special type used for causing invocation of a particular
constructor or method overload that will avoid making a copy of the source.
Typically these methods will have some dangerous side effects so make sure
you know what you're doing. **/
struct DontCopy {};
/** This is a special type used for causing invocation to a particularly
dangerous constructor or method overload; don't use this unless you are an
advanced user and know exactly what you're getting into. **/
struct TrustMe {};

/** This is a compile-time equivalent of "false", used in compile-time
condition checking in templatized implementations. **/
struct FalseType {};
/** This is a compile-time equivalent of "true", used in compile-time
condition checking in templatized implementations. **/
struct TrueType {};

/** This is an operator for and-ing compile-time truth types. */
template <class L, class R> struct AndOpType {};
template<> struct AndOpType<FalseType,FalseType> {typedef FalseType Result;};
template<> struct AndOpType<FalseType,TrueType>  {typedef FalseType Result;};
template<> struct AndOpType<TrueType, FalseType> {typedef FalseType Result;};
template<> struct AndOpType<TrueType, TrueType>  {typedef TrueType  Result;};

/** This is an operator for or-ing compile-time truth types. */
template <class L, class R> struct OrOpType {};
template<> struct OrOpType<FalseType,FalseType> {typedef FalseType Result;};
template<> struct OrOpType<FalseType,TrueType>  {typedef TrueType  Result;};
template<> struct OrOpType<TrueType, FalseType> {typedef TrueType  Result;};
template<> struct OrOpType<TrueType, TrueType>  {typedef TrueType  Result;};

/** This is an operator for exclusive or-ing compile-time truth types. */
template <class L, class R> struct XorOpType {};
template<> struct XorOpType<FalseType,FalseType> {typedef FalseType Result;};
template<> struct XorOpType<FalseType,TrueType>  {typedef TrueType  Result;};
template<> struct XorOpType<TrueType, FalseType> {typedef TrueType  Result;};
template<> struct XorOpType<TrueType, TrueType>  {typedef FalseType Result;};

/** Compile-time type test: is this one of the built-in integral types?. **/
template <class T> struct IsIntegralType {
    /** This typedef is TrueType if the template type T is an integral type;
    otherwise it is FalseType. **/
    typedef FalseType Result;
};
template<> struct IsIntegralType<bool> {typedef TrueType Result;};
template<> struct IsIntegralType<char> {typedef TrueType Result;};
template<> struct IsIntegralType<wchar_t> {typedef TrueType Result;};
template<> struct IsIntegralType<signed char> {typedef TrueType Result;};
template<> struct IsIntegralType<unsigned char> {typedef TrueType Result;};
template<> struct IsIntegralType<short> {typedef TrueType Result;};
template<> struct IsIntegralType<unsigned short> {typedef TrueType Result;};
template<> struct IsIntegralType<int> {typedef TrueType Result;};
template<> struct IsIntegralType<unsigned int> {typedef TrueType Result;};
template<> struct IsIntegralType<long> {typedef TrueType Result;};
template<> struct IsIntegralType<unsigned long> {typedef TrueType Result;};
template<> struct IsIntegralType<long long> {typedef TrueType Result;};
template<> struct IsIntegralType<unsigned long long> {typedef TrueType Result;};

/** Compile-time type test: is this one of the built-in floating point types?. **/
template <class T> struct IsFloatingType {
    /** This typedef is TrueType if the template type T is a floating point type;
    otherwise it is FalseType. **/
    typedef FalseType Result;
};
template<> struct IsFloatingType<float> {typedef TrueType Result;};
template<> struct IsFloatingType<double> {typedef TrueType Result;};
template<> struct IsFloatingType<long double> {typedef TrueType Result;};

/** Compile-time type test: is this the void type?. **/
template <class T> struct IsVoidType {
    /** This typedef is TrueType if the template type T is "void";
    otherwise it is FalseType. **/
    typedef FalseType Result;
};
template<> struct IsVoidType<void> {typedef TrueType Result;};

template <class T> struct IsArithmeticType {
    /** This typedef is TrueType if the template type T is one of the integral;
    or floating types, otherwise it is FalseType. **/
    typedef OrOpType<typename IsIntegralType<T>::Result,
                     typename IsFloatingType<T>::Result>    Result;
};



template <class T> class TypeInfo {
public:
    static const char* name() {return typeid(T).name();}
};

#define SimTK_TYPEINFO_SPECIALIZE(T)            \
template <> class TypeInfo< T > {               \
public:                                         \
    static const char* name() { return #T; }    \
};
// Built-in types
SimTK_TYPEINFO_SPECIALIZE(bool);            SimTK_TYPEINFO_SPECIALIZE(signed char); 
SimTK_TYPEINFO_SPECIALIZE(char);            SimTK_TYPEINFO_SPECIALIZE(unsigned char);
SimTK_TYPEINFO_SPECIALIZE(short);           SimTK_TYPEINFO_SPECIALIZE(int); 
SimTK_TYPEINFO_SPECIALIZE(long);
SimTK_TYPEINFO_SPECIALIZE(unsigned short);  SimTK_TYPEINFO_SPECIALIZE(unsigned int); 
SimTK_TYPEINFO_SPECIALIZE(unsigned long);
SimTK_TYPEINFO_SPECIALIZE(float);           SimTK_TYPEINFO_SPECIALIZE(double); 
SimTK_TYPEINFO_SPECIALIZE(long double);
SimTK_TYPEINFO_SPECIALIZE(std::complex<float>);
SimTK_TYPEINFO_SPECIALIZE(std::complex<double>); 
SimTK_TYPEINFO_SPECIALIZE(std::complex<long double>); 


} // namespace SimTK

#endif /* C++ stuff */

#endif /* SimTK_SimTKCOMMON_COMMON_H_ */
