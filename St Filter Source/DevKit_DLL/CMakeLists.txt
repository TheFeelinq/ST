set(SOURCE_FILES
        src/DllMain.cpp
        src/hooks/Hooks.cpp src/hooks/Hooks.h
        src/hooks/GFXVideo3d_Hook.cpp src/hooks/GFXVideo3d_Hook.h
        src/hooks/WndProc_Hook.cpp src/hooks/WndProc_Hook.h
        src/hooks/CGame_Hook.cpp src/hooks/CGame_Hook.h
        src/imgui_windows/ImGui_Windows.cpp src/imgui_windows/ImGui_Windows.h
        src/imgui_windows/InterfaceDebugger.cpp src/imgui_windows/InterfaceDebugger.h
        src/imgui_windows/SoundTool.cpp src/imgui_windows/SoundTool.h
        src/imgui_windows/NavMeshTool.cpp src/imgui_windows/NavMeshTool.h
        src/imgui_windows/EntityExplorer.cpp src/imgui_windows/EntityExplorer.h
        src/imgui_windows/NotificationTool.cpp src/imgui_windows/NotificationTool.h
        src/imgui_windows/About.cpp src/imgui_windows/About.h
        src/imgui_windows/SystemMessage.cpp src/imgui_windows/SystemMessage.h
        src/imgui_windows/ErrorMessageTool.h src/imgui_windows/ErrorMessageTool.cpp
        src/Util.cpp src/Util.h
        src/QuickStart.cpp src/QuickStart.h
        src/MathUtil.cpp src/MathUtil.h src/imgui_windows/ErrorMessageTool.cpp src/imgui_windows/ErrorMessageTool.h src/NameGenerator.cpp src/NameGenerator.h src/imgui_windows/InterfaceTree.cpp src/imgui_windows/InterfaceTree.h src/MinHook/buffer.cpp src/MinHook/buffer.h src/MinHook/hde32.cpp src/MinHook/hde32.h src/MinHook/hde64.cpp src/MinHook/hde64.h src/MinHook/hook.h src/MinHook/hook.cpp src/MinHook/MinHook.cpp src/MinHook/MinHook.h src/MinHook/pstdint.cpp src/MinHook/pstdint.h src/MinHook/table32.h src/MinHook/table64.cpp src/MinHook/table64.h src/MinHook/trampoline.cpp src/MinHook/trampoline.h src/imgui_windows/ProcessViewer.cpp src/imgui_windows/ProcessViewer.h src/imgui_windows/PartyInfo.cpp src/imgui_windows/PartyInfo.h src/imgui_windows/CharacterData.cpp src/imgui_windows/CharacterData.h src/imgui_windows/Inventory.cpp src/imgui_windows/Inventory.h src/imgui_windows/ColorPicker.cpp src/imgui_windows/ColorPicker.h src/imgui_windows/ItemData.cpp src/imgui_windows/ItemData.h src/imgui_windows/PetFilter.cpp src/imgui_windows/PetFilter.h src/imgui_windows/FPSViewer.cpp src/imgui_windows/FPSViewer.h src/imgui_windows/CircleDrawTool.cpp src/imgui_windows/CircleDrawTool.h)

add_library(DevKit_DLL SHARED ${SOURCE_FILES})
target_link_libraries(DevKit_DLL detours BSLib ClientLib MathHelpers memory winmm DiscordRichPresence)

set_target_properties(DevKit_DLL
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/BinOut/${CMAKE_BUILD_TYPE}/"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/BinOut/${CMAKE_BUILD_TYPE}/"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/BinOut/${CMAKE_BUILD_TYPE}/"
        )
