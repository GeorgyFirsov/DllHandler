// ******************************************************************
// Author:  Firsov Georgy
// Contact: gfirsov007@gmail.com
// Date:    23.11.2019
// ******************************************************************
// License: GNU GPL v3
// ******************************************************************
// Class CDllHandler: wrapper over Windows' dynamic library
// ******************************************************************

#pragma once
#include "stdafx.h"

#ifndef TLIBRARYFUNCTIONINTERNAL_DECLARED
    #include  "LibraryCall.h"
#endif // !TLIBRARYFUNCTIONINTERNAL_DECLARED


// ******************************************************************
// These macro can be used to easily declare your own class that
// will represent dynamic library with specified functions loaded
// from it.
// Some constructors and operators are deleted to provide safity
// from assigning or construction wrong way.
// ******************************************************************
#define DLL_BEGIN( _LibClassName, _LibName )            \
    class _LibClassName: public CDllHandler             \
    {                                                   \
    public:                                             \
        _LibClassName( HANDLE ) = delete;               \
        _LibClassName( HMODULE ) = delete;              \
        _LibClassName( LPCTSTR ) = delete;              \
        _LibClassName( LPCTSTR, DWORD ) = delete;       \
        _LibClassName& operator=( HANDLE ) = delete;    \
        _LibClassName& operator=( HMODULE ) = delete;   \
        _LibClassName()                                 \
            : CDllHandler( _LibName ) { }                

#define DLL_BEGIN_CUSTOM_ERROR( _LibClassName, _LibName, _ErrorCode )   \
    class _LibClassName: public CDllHandler                             \
    {                                                                   \
    public:                                                             \
        _LibClassName( HANDLE ) = delete;                               \
        _LibClassName( HMODULE ) = delete;                              \
        _LibClassName( LPCTSTR ) = delete;                              \
        _LibClassName( LPCTSTR, DWORD ) = delete;                       \
        _LibClassName& operator=( HANDLE ) = delete;                    \
        _LibClassName& operator=( HMODULE ) = delete;                   \
        _LibClassName()                                                 \
            : CDllHandler( _LibName, _ErrorCode ) { }        

//
// Function can not be declared as static, because these macro
// can be used inside functions and define local classes
//
#define DLL_FUNCTION( _PfnType, _Name ) \
    TLibraryFunctionInternal<_PfnType> _Name = { m_hDll, #_Name };

#define DLL_FUNCTION_CUSTOM_NAME( _PfnType, _Name, _MemberName )    \
    TLibraryFunctionInternal<_PfnType> _MemberName = { m_hDll, _Name };

#define DLL_END    }



// ******************************************************************
// This class represents dynamic library. It is wrapper over it, so
// you can use it seprately, but it is the ground of custom classes
// wrapping a dll, that allow you to use this dll's functions just
// like normal class methods.
// ******************************************************************
class CDllHandler
{
public:
    CDllHandler();

    explicit 
    CDllHandler( LPCTSTR szLibraryName );
    CDllHandler( LPCTSTR szLibraryName, DWORD dwErrorCode );

    CDllHandler( HMODULE hDll );
    CDllHandler( HANDLE hDll );
    
    CDllHandler& operator=( HMODULE hDll );
    CDllHandler& operator=( HANDLE hDll );

    ~CDllHandler() { _Detach(); }

    operator HMODULE() const { return m_hDll; }
    operator HANDLE() const  { return m_hDll; }
    operator bool() const    { return m_hDll != nullptr; }

    //
    // Restrict copying to prevent null-pointer
    // dereference in not deleted copies.
    //
    CDllHandler( const CDllHandler& ) = delete;
    CDllHandler& operator=( const CDllHandler& ) = delete;

    //
    // Restrict moving too, because inherited classes
    // declared with macro from this file cannot
    // be invalidated
    //
    CDllHandler( CDllHandler&& ) = delete;
    CDllHandler& operator=( CDllHandler&& ) = delete;

private:
    void _Detach();

protected:
    HMODULE m_hDll;
};