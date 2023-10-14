//-----------------------------------------------------------------------------
//     Author : hiyohiyo
//       Mail : hiyohiyo@crystalmark.info
//        Web : http://openlibsys.org/
//    License : The modified BSD license
//
//                          Copyright 2007 OpenLibSys.org. All rights reserved.
//-----------------------------------------------------------------------------

#pragma once

#include "OlsApiInitDef.h"

//-----------------------------------------------------------------------------
//
// Prototypes
//
//-----------------------------------------------------------------------------

BOOL InitOpenLibSys(HMODULE *hModule);
BOOL DeinitOpenLibSys(HMODULE *hModule);

//-----------------------------------------------------------------------------
//
// Funtions
//
//-----------------------------------------------------------------------------

// DLL
_GetDllStatus GetDllStatus = NULL;
_GetDllVersion GetDllVersion = NULL;
_GetDriverVersion GetDriverVersion = NULL;
_GetDriverType GetDriverType = NULL;

#ifdef _OPEN_LIB_SYS
_InstallOpenLibSys InstallOpenLibSys = NULL;
_UninstallOpenLibSys UninstallOpenLibSys = NULL;
#endif

_InitializeDll InitializeDll = NULL;
_DeinitializeDll DeinitializeDll = NULL;

// CPU
_IsCpuid IsCpuid = NULL;
_IsMsr IsMsr = NULL;
_IsTsc IsTsc = NULL;

_Hlt Hlt = NULL;
_Rdmsr Rdmsr = NULL;
_Wrmsr Wrmsr = NULL;
_Rdpmc Rdpmc = NULL;
_Cpuid Cpuid = NULL;
_Rdtsc Rdtsc = NULL;

_HltEx HltEx = NULL;
_RdmsrEx RdmsrEx = NULL;
_WrmsrEx WrmsrEx = NULL;
_RdpmcEx RdpmcEx = NULL;
_CpuidEx CpuidEx = NULL;
_RdtscEx RdtscEx = NULL;

// IO
_ReadIoPortByte ReadIoPortByte = NULL;
_ReadIoPortWord ReadIoPortWord = NULL;
_ReadIoPortDword ReadIoPortDword = NULL;

_WriteIoPortByte WriteIoPortByte = NULL;
_WriteIoPortWord WriteIoPortWord = NULL;
_WriteIoPortDword WriteIoPortDword = NULL;

// Memory
_ReadPhysicalMemory ReadPhysicalMemory = NULL;
_WritePhysicalMemory WritePhysicalMemory = NULL;

// PCI
_SetPciMaxBusIndex SetPciMaxBusIndex = NULL;

_ReadPciConfigByte ReadPciConfigByte = NULL;
_ReadPciConfigWord ReadPciConfigWord = NULL;
_ReadPciConfigDword ReadPciConfigDword = NULL;

_WritePciConfigByte WritePciConfigByte = NULL;_WritePciConfigWord WritePciConfigWord = NULL;
_WritePciConfigDword WritePciConfigDword = NULL;

_FindPciDeviceById FindPciDeviceById = NULL;
_FindPciDeviceByClass FindPciDeviceByClass = NULL;

//-----------------------------------------------------------------------------
//
// Initialize
//
//-----------------------------------------------------------------------------

BOOL InitOpenLibSys(HMODULE *hModule)
{

#ifdef _OPEN_LIB_SYS

#ifdef _M_X64
	*hModule = LoadLibrary(_T("OpenLibSysX64.dll"));
#else
	*hModule = LoadLibrary(_T("OpenLibSys.dll"));
#endif

#else

#ifdef _M_X64
	*hModule = LoadLibrary(_T("WinRing0x64.dll"));
#else
    *hModule = LoadLibrary(L"WinRing0.dll");
#endif

#endif

	if(*hModule == NULL)
	{
		return FALSE;
	}

	//-----------------------------------------------------------------------------
	// GetProcAddress
	//-----------------------------------------------------------------------------
	// DLL
	GetDllStatus =			(_GetDllStatus)			GetProcAddress (*hModule, "GetDllStatus");
	GetDllVersion =			(_GetDllVersion)		GetProcAddress (*hModule, "GetDllVersion");
	GetDriverVersion =		(_GetDriverVersion)		GetProcAddress (*hModule, "GetDriverVersion");
	GetDriverType =			(_GetDriverType)		GetProcAddress (*hModule, "GetDriverType");

#ifdef _OPEN_LIB_SYS
	InstallOpenLibSys =		(_InstallOpenLibSys)	GetProcAddress (*hModule, "InstallOpenLibSys");
	UninstallOpenLibSys =	(_UninstallOpenLibSys)	GetProcAddress (*hModule, "UninstallOpenLibSys");
#endif

	InitializeDll =			(_InitializeDll)		GetProcAddress (*hModule, "InitializeDll");
	DeinitializeDll =		(_DeinitializeDll)		GetProcAddress (*hModule, "DeinitializeDll");

	// CPU
	IsCpuid =				(_IsCpuid)				GetProcAddress (*hModule, "IsCpuid");
	IsMsr =					(_IsMsr)				GetProcAddress (*hModule, "IsMsr");
	IsTsc =					(_IsTsc)				GetProcAddress (*hModule, "IsTsc");
	Hlt =					(_Hlt)					GetProcAddress (*hModule, "Hlt");
	Rdmsr =					(_Rdmsr)				GetProcAddress (*hModule, "Rdmsr");
	Wrmsr =					(_Wrmsr)				GetProcAddress (*hModule, "Wrmsr");
	Rdpmc =					(_Rdpmc)				GetProcAddress (*hModule, "Rdpmc");
	Cpuid =					(_Cpuid)				GetProcAddress (*hModule, "Cpuid");
	Rdtsc =					(_Rdtsc)				GetProcAddress (*hModule, "Rdtsc");
	HltEx =					(_HltEx)				GetProcAddress (*hModule, "HltEx");
	RdmsrEx =				(_RdmsrEx)				GetProcAddress (*hModule, "RdmsrEx");
	WrmsrEx =				(_WrmsrEx)				GetProcAddress (*hModule, "WrmsrEx");
	RdpmcEx =				(_RdpmcEx)				GetProcAddress (*hModule, "RdpmcEx");
	CpuidEx =				(_CpuidEx)				GetProcAddress (*hModule, "CpuidEx");
	RdtscEx =				(_RdtscEx)				GetProcAddress (*hModule, "RdtscEx");

	// IO
	ReadIoPortByte =		(_ReadIoPortByte)		GetProcAddress (*hModule, "ReadIoPortByte");
	ReadIoPortWord =		(_ReadIoPortWord)		GetProcAddress (*hModule, "ReadIoPortWord");
	ReadIoPortDword =		(_ReadIoPortDword)		GetProcAddress (*hModule, "ReadIoPortDword");

	WriteIoPortByte =		(_WriteIoPortByte)		GetProcAddress (*hModule, "WriteIoPortByte");
	WriteIoPortWord =		(_WriteIoPortWord)		GetProcAddress (*hModule, "WriteIoPortWord");
	WriteIoPortDword =		(_WriteIoPortDword)		GetProcAddress (*hModule, "WriteIoPortDword");

	// Memory
	ReadPhysicalMemory =	(_ReadPhysicalMemory)	GetProcAddress (*hModule, "ReadPhysicalMemory");
	WritePhysicalMemory =	(_WritePhysicalMemory)	GetProcAddress (*hModule, "WritePhysicalMemory");

	// PCI
	SetPciMaxBusIndex =		(_SetPciMaxBusIndex)	GetProcAddress (*hModule, "SetPciMaxBusIndex");

	ReadPciConfigByte =		(_ReadPciConfigByte)	GetProcAddress (*hModule, "ReadPciConfigByte");
	ReadPciConfigWord =		(_ReadPciConfigWord)	GetProcAddress (*hModule, "ReadPciConfigWord");
	ReadPciConfigDword =	(_ReadPciConfigDword)	GetProcAddress (*hModule, "ReadPciConfigDword");

	WritePciConfigByte =	(_WritePciConfigByte)	GetProcAddress (*hModule, "WritePciConfigByte");
	WritePciConfigWord =	(_WritePciConfigWord)	GetProcAddress (*hModule, "WritePciConfigWord");
	WritePciConfigDword =	(_WritePciConfigDword)	GetProcAddress (*hModule, "WritePciConfigDword");

	FindPciDeviceById =		(_FindPciDeviceById)	GetProcAddress (*hModule, "FindPciDeviceById");
	FindPciDeviceByClass =	(_FindPciDeviceByClass)	GetProcAddress (*hModule, "FindPciDeviceByClass");

	//-----------------------------------------------------------------------------
	// Check Functions
	//-----------------------------------------------------------------------------
	if(!(
		GetDllStatus
	&&	GetDllVersion
	&&	GetDriverVersion
	&&	GetDriverType
#ifdef _OPEN_LIB_SYS
	&&	InstallOpenLibSys
	&&	UninstallOpenLibSys
#endif
	&&	InitializeDll
	&&	DeinitializeDll
	&&	IsCpuid
	&&	IsMsr
	&&	IsTsc
	&&	Hlt
	&&	HltEx
	&&	Rdmsr
	&&	RdmsrEx
	&&	Wrmsr
	&&	WrmsrEx
	&&	Rdpmc
	&&	RdpmcEx
	&&	Cpuid
	&&	CpuidEx
	&&	Rdtsc
	&&	RdtscEx
	&&	ReadIoPortByte
	&&	ReadIoPortWord
	&&	ReadIoPortDword
	&&	WriteIoPortByte
	&&	WriteIoPortWord
	&&	WriteIoPortDword
	&&	ReadPhysicalMemory
	&&	WritePhysicalMemory
	&&	SetPciMaxBusIndex
	&&	ReadPciConfigByte
	&&	ReadPciConfigWord
	&&	ReadPciConfigDword
	&&	WritePciConfigByte
	&&	WritePciConfigWord 
	&&	WritePciConfigDword
	&&	FindPciDeviceById
	&&	FindPciDeviceByClass
	))
	{
		return FALSE;
	}

	InitializeDll();

	return TRUE;
}

//-----------------------------------------------------------------------------
//
// Deinitialize
//
//-----------------------------------------------------------------------------

BOOL DeinitOpenLibSys(HMODULE *hModule)
{
	BOOL result = FALSE;

	if(*hModule == NULL)
	{
		return TRUE;
	}
	else
	{
		DeinitializeDll();
		result = FreeLibrary(*hModule);
		*hModule = NULL;

		return result;
	}
}
