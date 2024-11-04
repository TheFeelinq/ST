#include <Windows.h>

#pragma once
#define MEMUTIL_READ_BY_PTR_OFFSET(ptr, offset, type) \
	*(type*)(((uintptr_t)ptr) + offset)

#define MEMUTIL_WRITE_VALUE(type, offset, value) \
	Write<type>(offset, value)

template<typename T>
int addr_from_this(T funptr) {
	union  {
		int addr;
		T ptr;
	} myu;

	myu.ptr = funptr;
	return myu.addr;
}

template<typename T>
static bool Write(uintptr_t offset, T& value)
{
	LPVOID lpOffset = reinterpret_cast<LPVOID>(offset);

	DWORD dwOldProtect = 0;
	if (!VirtualProtect(lpOffset, sizeof(T), PAGE_READWRITE, &dwOldProtect))
		return false;

	*(T*)(offset) = value;

	return VirtualProtect(lpOffset, sizeof(T), dwOldProtect, &dwOldProtect);
}

template<typename T>
void placeHook(int trampoline_location, T& target_location)
{
	placeHook(trampoline_location, reinterpret_cast<int>(&target_location));
}

void placeHook(int trampoline_location, int target_location);

void replaceOffset(int trampoline_location, int target_location);

void replaceAddr(int addr, int value);

void vftableHook(unsigned int vftable_addr, int offset, int target_func);

bool Write(uintptr_t offset, const void* data, int length);
bool RenderNop(void* addr, int count);
bool CopyBytes(int dst, const void* src, size_t size);
bool CopyBytes(void* dst, const void* src, size_t size);
void RenderJMPInstruction(int address, int jumpto, char* buf);
void JMPFunction(int address, int jumpto);
void RenderCALLInstruction(int address, int jumpto, char* buf);
void CALLFunction(int address, int jumpto);