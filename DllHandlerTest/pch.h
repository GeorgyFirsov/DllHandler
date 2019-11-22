//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"

#include "../DllHandler/stdafx.h"
#include "../DllHandler/DllHandler.h"
#include "../DllHandler/LibraryCall.h"
#include "../DllHandler/Win32Error.h"

#define FAILURE ASSERT_EQ( true, false )
#define SUCCESS ASSERT_EQ( true, true )