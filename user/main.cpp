// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "il2cpp-appdata.h"
#include "helpers.h"

#include <common.h>
#include <hooking/hooking.h>

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

// Custom injected code entry point
void Run()
{
    il2cpp_thread_attach(il2cpp_domain_get());

    using namespace Small;

    auto logger_inst = std::make_unique<Small::Logger>();
    auto renderer_inst = std::make_unique<Renderer>();
    auto hooking_inst = std::make_unique<Hooking>();

    hooking->original_present_ = renderer->GetPresent();

    hooking->AddHook(&(PVOID&)hooking->original_present_, Hooks::HookPresent, "SwapchainPresent");
    hooking->ApplyHooks();

    logger->LogInfo("Hello, world!");

    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    } while (!GetAsyncKeyState(VK_DELETE) & 1 && global_running_);

    hooking->RemoveHooks();

    hooking_inst.reset();
    renderer_inst.reset();
    logger_inst.reset();

    CloseHandle(Small::main_thread_);
    FreeLibraryAndExitThread(Small::global_module_, 0);
}