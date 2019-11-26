#include "pch.h"

#pragma region Linkage specific
    #include "../DllHandler/DllHandler.cpp"
#pragma endregion 

using PRtlComputeCrc32 = DWORD(__stdcall *)( DWORD, const BYTE*, INT );

constexpr BYTE pbData[] = {
    'D', 'a', 't', 'a',
    ' ', 't', 'o', ' ',
    't', 'e', 's', 't'
};

TEST(Load, Existing)
{
    try
    {
        DLL_BEGIN( CNtLib, L"Ntdll.dll" )
            DLL_FUNCTION( PRtlComputeCrc32, RtlComputeCrc32 );
        DLL_END;

        CNtLib NtLib;
    }
    catch ( const CWin32Error& )
    {
        FAILURE;
    }
}

TEST(Load, Absent)
{
    try
    {
        DLL_BEGIN( CNtLib, L"NtdllAbsent.dll" )
            DLL_FUNCTION( PRtlComputeCrc32, RtlComputeCrc32 );
        DLL_END;

        CNtLib NtLib;

        FAILURE;
    }
    catch ( const CWin32Error& )
    {
        SUCCESS;
    }
}

TEST(Call, Possibility)
{
    DLL_BEGIN( CNtLib, L"Ntdll.dll" )
        DLL_FUNCTION( PRtlComputeCrc32, RtlComputeCrc32 )
    DLL_END;

    ASSERT_NO_THROW( CNtLib NtLib; );

    CNtLib NtLib;

    ASSERT_NO_THROW( NtLib.RtlComputeCrc32( 0, nullptr, 0); );
}

TEST(Call, Correctness)
{
    DLL_BEGIN( CNtLib, L"Ntdll.dll" )
        DLL_FUNCTION( PRtlComputeCrc32, RtlComputeCrc32 )
    DLL_END;

    //
    // Calculate Crc32 with our class
    //
    CNtLib NtLib;
    DWORD dwTested = NtLib.RtlComputeCrc32( 0, pbData, _countof( pbData ) );


    //
    // Calculate Crc32 via standard Windows way
    //
    HMODULE hNtLib = ::LoadLibrary( L"Ntdll.dll" );
    if(!hNtLib) {
        FAILURE;
    }

    auto pRtlComputeCrc32 = reinterpret_cast<PRtlComputeCrc32>(
        ::GetProcAddress( hNtLib, "RtlComputeCrc32" )
    );

    ::FreeLibrary( hNtLib );

    if(!pRtlComputeCrc32) {
        FAILURE;
    }

    DWORD dwExpected = pRtlComputeCrc32( 0, pbData, _countof( pbData ) );

    ASSERT_EQ( dwExpected, dwTested );
}

TEST(Attach, LoadLibrary)
{
    CDllHandler hDll = LoadLibrary( L"Ntdll.dll" );
    if(!hDll) {
        FAILURE;
    }

    auto pRtlComputeCrc32 = reinterpret_cast<PRtlComputeCrc32>(
        GetProcAddress( hDll, "RtlComputeCrc32" )
    );
    if(!pRtlComputeCrc32) {
        FAILURE;
    }

    ASSERT_NO_THROW( pRtlComputeCrc32( 0, pbData, _countof( pbData ) ) );
}

TEST(Attach, LoadLibrary_operator)
{
    CDllHandler hDll;

    hDll = LoadLibrary( L"Ntdll.dll" );
    if(!hDll) {
        FAILURE;
    }

    auto pRtlComputeCrc32 = reinterpret_cast<PRtlComputeCrc32>(
        GetProcAddress( hDll, "RtlComputeCrc32" )
    );
    if(!pRtlComputeCrc32) {
        FAILURE;
    }

    ASSERT_NO_THROW( pRtlComputeCrc32( 0, pbData, _countof( pbData ) ) );
}
