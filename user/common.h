#pragma once

#include <Windows.h>

#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include "logger/logger.h"
#include "renderer/renderer.h"

namespace Small {
	inline HMODULE global_module_{};
	inline HANDLE main_thread_{};
	inline DWORD main_thread_id_{};
	inline bool global_running_{ true };
}