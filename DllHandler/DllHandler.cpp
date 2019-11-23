#include "stdafx.h"

#include "DllHandler.h"
#include "Win32Error.h"


CDllHandler::CDllHandler()
    : m_hDll( nullptr )
{ }

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

CDllHandler::CDllHandler( HMODULE hDll )
    : m_hDll( hDll )
{ }

CDllHandler::CDllHandler( HANDLE hDll )
    : m_hDll( static_cast<HMODULE>( hDll ) )
{ }

CDllHandler& CDllHandler::operator=( HMODULE hDll )
{
    if(m_hDll) {
        _Detach();
    }
    m_hDll = hDll;
    return *this;
}

CDllHandler& CDllHandler::operator=( HANDLE hDll )
{
    if(m_hDll) {
        _Detach();
    }
    m_hDll = static_cast<HMODULE>( hDll );
    return *this;
}

void CDllHandler::_Detach()
{
    if (m_hDll) 
    {
        ::FreeLibrary( m_hDll );
        m_hDll = nullptr;
    }
}
