#include "stdafx.h"

#include "DllHandler.h"
#include "Win32Error.h"


CDllHandler::CDllHandler( LPCTSTR szLibraryName )
    : m_hDll( nullptr )
{
    m_hDll = ::LoadLibrary( szLibraryName );
    if(!m_hDll)
    {
        //
        // Dll cannot be loaded :(
        //
        WIN32_ERROR_THROW_LAST();
    }
}

CDllHandler::CDllHandler( LPCTSTR szLibraryName, DWORD dwErrorCode )
    : m_hDll( nullptr )
{
    m_hDll = ::LoadLibrary( szLibraryName );
    if(!m_hDll)
    {
        //
        // Dll cannot be loaded :(
        // The difference is that here I throw custom error code.
        //
        WIN32_ERROR_THROW( dwErrorCode );
    }
}

CDllHandler::~CDllHandler()
{
    if (!m_hDll) 
    {
        ::FreeLibrary( m_hDll );
        m_hDll = nullptr;
    }
}