# DllHandler
[![Version][]]() [![Tests][]]() [![License][]]()

[Version]:		   https://img.shields.io/badge/Version-v1.0-blue
[Tests]:		   https://img.shields.io/badge/Tests-passed-brightgreen
[License]:		   https://img.shields.io/badge/License-GNU%20GPL%20v.3-blue

This is a wrapper over Windows' dll `HMODULE`. This class provides automatic release of handle at exit from scope.

### Usage
This class has really simple usage:

```cpp
CDllHandler hDll;

hDll = LoadLibraryA( L"Ntdll.dll" );

// Here you can use it as normal HMODULE handle

// No need to release
```

But the main feature of this small library is possibility to easily use exported functions.
Here is an example:

```cpp
// ...

using PRtlComputeCrc32 = DWORD(__stdcall *)( DWORD, const BYTE*, INT );

// It is a class declaration.
// This class can be local - it contains no static members
DLL_BEGIN( CNtLib, L"Ntdll.dll" )
    DLL_FUNCTION( PRtlComputeCrc32, RtlComputeCrc32 )
DLL_END;

try
{
    CNtLib NtLib;  // <- this object contains dll
    DWORD dwHash = NtLib.RtlComputeCrc32( 0, pData, GetSize( pData ) );
    // That's it! Nothing more to do to use exported functions!
    // ...
}
catch( const CWin32Error& e )
{
    // Handle error
}
```

In case of any error during library loading or function search this class (and helper template) generates a `CWin32Error` exception, 
that contains an error code and its description:

```cpp
try
{
    // ...
}

catch( const CWin32Error& e )
{
    e.Code()         // Obtain error code
    e.Description()  // Obtain error description (available only for system errors)
}
```
