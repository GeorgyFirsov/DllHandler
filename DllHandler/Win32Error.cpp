#include "stdafx.h"

#include "Win32Error.h"


CWin32Error::CWin32Error( DWORD dwErrorCode )
{
    LPWSTR szDescription = nullptr;

    DWORD cchWritten = ::FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        dwErrorCode,
        MAKELANGID( LANG_NEUTRAL, SUBLANG_SYS_DEFAULT ),
        reinterpret_cast<LPWSTR>( &szDescription ),
        0 /* nSize */,
        nullptr
    );

    if(!cchWritten) 
    {
        std::wstringstream stream;
        stream << L"No description available for code 0x"
               << std::hex
               << m_dwCode;
        m_sDescription = stream.str();
    }

    m_dwCode = dwErrorCode;
    m_sDescription = std::wstring( szDescription, cchWritten );

    ::LocalFree( szDescription );
}
