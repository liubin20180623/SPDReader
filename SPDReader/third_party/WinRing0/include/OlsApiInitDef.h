//-----------------------------------------------------------------------------
//     Author : hiyohiyo
//       Mail : hiyohiyo@crystalmark.info
//        Web : http://openlibsys.org/
//    License : The modified BSD license
//
//                          Copyright 2007 OpenLibSys.org. All rights reserved.
//-----------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------
//
// Type Defines
//
//-----------------------------------------------------------------------------

// DLL
typedef DWORD (WINAPI *_GetDllStatus) ();
typedef DWORD (WINAPI *_GetDllVersion) (PBYTE major, PBYTE minor, PBYTE revision, PBYTE release);
typedef DWORD (WINAPI *_GetDriverVersion) (PBYTE major, PBYTE minor, PBYTE revision, PBYTE release);
typedef DWORD (WINAPI *_GetDriverType) ();

#ifdef _OPEN_LIB_SYS
typedef BOOL (WINAPI *_InstallOpenLibSys) ();
typedef BOOL (WINAPI *_UninstallOpenLibSys) ();
#endif

typedef VOID (WINAPI *_InitializeDll) ();
typedef VOID (WINAPI *_DeinitializeDll) ();

// CPU
typedef BOOL (WINAPI *_IsCpuid) ();
typedef BOOL (WINAPI *_IsMsr) ();
typedef BOOL (WINAPI *_IsTsc) ();

typedef BOOL (WINAPI *_Hlt) ();
typedef DWORD (WINAPI *_Rdmsr) (DWORD index, PDWORD eax, PDWORD edx);
typedef DWORD (WINAPI *_Wrmsr) (DWORD index, DWORD eax, DWORD edx);
typedef DWORD (WINAPI *_Rdpmc) (DWORD index, PDWORD eax, PDWORD edx);
typedef DWORD (WINAPI *_Cpuid) (DWORD index, PDWORD eax, PDWORD ebx, PDWORD ecx, PDWORD edx);
typedef DWORD (WINAPI *_Rdtsc) (PDWORD eax, PDWORD edx);

typedef BOOL (WINAPI *_HltEx) (DWORD_PTR affinityMask);
typedef DWORD (WINAPI *_RdmsrEx) (DWORD index, PDWORD eax, PDWORD edx, DWORD_PTR affinityMask);
typedef DWORD (WINAPI *_WrmsrEx) (DWORD index, DWORD eax, DWORD edx, DWORD_PTR affinityMask);
typedef DWORD (WINAPI *_RdpmcEx) (DWORD index, PDWORD eax, PDWORD edx, DWORD_PTR affinityMask);
typedef DWORD (WINAPI *_CpuidEx) (DWORD index, PDWORD eax, PDWORD ebx, PDWORD ecx, PDWORD edx, DWORD_PTR affinityMask);
typedef DWORD (WINAPI *_RdtscEx) (PDWORD eax, PDWORD edx, DWORD_PTR affinityMask);

// IO
typedef BYTE (WINAPI *_ReadIoPortByte) (WORD address);
typedef WORD (WINAPI *_ReadIoPortWord) (WORD address);
typedef DWORD (WINAPI *_ReadIoPortDword) (WORD address);

typedef VOID (WINAPI *_WriteIoPortByte) (WORD address, BYTE value);
typedef VOID (WINAPI *_WriteIoPortWord) (WORD address, WORD value);
typedef VOID (WINAPI *_WriteIoPortDword) (WORD address, DWORD value);

// Memory
typedef DWORD (WINAPI *_ReadPhysicalMemory) (DWORD_PTR address, PBYTE buffer, DWORD count, DWORD unitSize);
typedef DWORD (WINAPI *_WritePhysicalMemory) (DWORD_PTR address, PBYTE buffer, DWORD count, DWORD unitSize);

// PCI
typedef VOID (WINAPI *_SetPciMaxBusIndex) (BYTE max);

typedef BYTE (WINAPI *_ReadPciConfigByte) (DWORD pciAddress, BYTE regAddress);
typedef WORD (WINAPI *_ReadPciConfigWord) (DWORD pciAddress, BYTE regAddress);
typedef DWORD (WINAPI *_ReadPciConfigDword) (DWORD pciAddress, BYTE regAddress);

typedef VOID (WINAPI *_WritePciConfigByte) (DWORD pciAddress, BYTE regAddress, BYTE value);
typedef VOID (WINAPI *_WritePciConfigWord) (DWORD pciAddress, BYTE regAddress, WORD value);
typedef VOID (WINAPI *_WritePciConfigDword) (DWORD pciAddress, BYTE regAddress, DWORD value);

typedef DWORD (WINAPI *_FindPciDeviceById) (WORD vendorId, WORD deviceId, BYTE index);
typedef DWORD (WINAPI *_FindPciDeviceByClass) (BYTE baseClass, BYTE subClass, BYTE programIf, BYTE index);