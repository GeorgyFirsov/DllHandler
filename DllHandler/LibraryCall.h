// ******************************************************************
// Author:  Firsov Georgy
// Contact: gfirsov007@gmail.com
// Date:    23.11.2019
// ******************************************************************
// License: GNU GPL v3
// ******************************************************************
// Class template TLibraryFunctionInternal: wrapper over a function
//                                          from dynamic library.
// ******************************************************************

#pragma once
#include "stdafx.h"

#include "Win32Error.h"

#define TLIBRARYFUNCTIONINTERNAL_DECLARED


// ******************************************************************
// Template class that represents a function from
// dynamic library. You don't need to use it explicitly,
// just consider macro definition from DllHandler.h.
// ******************************************************************
template<class PfnType>
class TLibraryFunctionInternal
{
public:
    TLibraryFunctionInternal( HMODULE hLib, LPCSTR szName )
        : m_pfnCallee( nullptr )
        , m_szName( szName )
        , m_hLib( hLib )
    { }

    operator PfnType()
    {
        if (!m_pfnCallee) 
        {
            m_pfnCallee = reinterpret_cast<PfnType>(
                ::GetProcAddress( m_hLib, m_szName )
            );

            if (!m_pfnCallee) 
            {
                //
                // In case of error we obtain last error code
                // set by GetProcAddress
                //
                WIN32_ERROR_THROW_LAST();
            }
        }

        return m_pfnCallee;
    }

private:
    volatile PfnType m_pfnCallee;
    LPCSTR             m_szName;
    HMODULE             m_hLib;
};
