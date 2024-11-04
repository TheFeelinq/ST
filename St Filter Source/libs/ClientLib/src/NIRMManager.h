#pragma once

#include <string>
#include "NIFWnd.h"

#define g_pCNIRMManager (*(CNIRMManager**)0x115dd40)
class CNIFWnd;

/// Loader for resui/*.2dt files
/// thats for the newinterface only....
class CNIRMManager {
public:
    CNIRMManager();

    /// Load a reui file from the PK2
    /// \param filename Path and filename in Media.pk2 to load. Example: "reui/file.txt"
    void LoadFromFile(const char *filename, CObj *base, int a3);

    /// Get a pointer to a control identified by the Id
    /// \param id The Id of the control as stated in the res ui file or set on creation
    /// \returns Pointer to the control, NULL if Id was not found.
    CNIFWnd *GetResObj(int id);

    /// its close maybe.
    void RemoveObj_MAYBE(int id);

    /// Get a pointer to a control identified by the Id
    /// \tparam T Expected type of the control. The type is never validated.
    /// \param id The Id of the control as stated in the resinfo file or set on creation
    /// \param a2 Completely unknown, is always 1
    /// \returns Pointer to the control, NULL if Id was not found.
    template<typename T>
    T *GetResObj(int id) {
        return reinterpret_cast<T *(__thiscall *)(CNIRMManager *, int)>(0x0046e060)(this, id);
    }

private:
//char pad_unk[0x30];
};