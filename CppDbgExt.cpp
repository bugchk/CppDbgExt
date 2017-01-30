//----------------------------------------------------------------------------
//
// CppDbgExt.cpp
//
// EngExtCpp-style extension.
//
// Copyright (C) Microsoft Corporation, 2005.
//
//----------------------------------------------------------------------------

#include <engextcpp.hpp>
#include <string.h>

//----------------------------------------------------------------------------
//
// Base extension class.
// Extensions derive from the provided ExtExtension class.
//
// The standard class name is "Extension".  It can be
// overridden by providing an alternate definition of
// EXT_CLASS before including engextcpp.hpp.
//
//----------------------------------------------------------------------------

class EXT_CLASS : public ExtExtension
{
private:
	bool m_NeedsSessionRefresh;

	//
	// OVERLOAD for ExtExtension
	// This is activated once per breakin to refresh session based information
	//
	void OnSessionActive(_In_ ULONG64 Argument)
	{
		m_NeedsSessionRefresh = true;
	}

	//
	// OVERLOAD for ExtExtension 
	// This runs each time an extension is run
	//
	void WINAPI	ExInitialize(void)
	{
		if (m_ExInitialized == false)
		{

		}

		if (m_NeedsSessionRefresh)
		{
			m_NeedsSessionRefresh = false;
		}


		// have to do this after the refresh code for some reason.
		if (m_ExInitialized == false)
		{
			// turn off line numbers because they are annoying
			ULONG options;
			if (SUCCEEDED(g_Ext->m_Symbols->GetSymbolOptions(&options)))
			{
				g_Ext->m_Symbols->SetSymbolOptions(options & ~(0x10));
			}

			m_ExInitialized = true;
		}
	}


public:

	EXT_COMMAND_METHOD(example);

};

// EXT_DECLARE_GLOBALS must be used to instantiate
// the framework's assumed globals.
EXT_DECLARE_GLOBALS();

EXT_COMMAND(example,
	"Example extension method",
	"{;e,o,d=0;Address;Address of object}")
{

}