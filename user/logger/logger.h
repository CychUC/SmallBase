#pragma once
#include <common.h>

namespace Small {
	class Logger;
	inline Logger* logger{};

	class Logger {
	public:
		explicit Logger() {
			if (!(console_exists_ = AttachConsole(GetCurrentProcessId())))
				AllocConsole();
			if ((console_handle_ = GetStdHandle(STD_OUTPUT_HANDLE)) != nullptr) {
				SetConsoleTitleA("SmallBase");
				SetConsoleOutputCP(CP_UTF8);

				console_out_.open("CONOUT$", std::ios_base::out | std::ios_base::app);
				logger = this;
			}
		}

		~Logger() {
			if (!console_exists_) FreeConsole();
			logger = nullptr;
		}

	public:
		void LogInfo(std::string_view info) {
			SetConsoleTextAttribute(console_handle_, static_cast<std::uint16_t>(FOREGROUND_BLUE | FOREGROUND_INTENSITY));
			console_out_ << "[INFO] " << info << std::endl;
		}

		void LogWarning(std::string_view info) {
			SetConsoleTextAttribute(console_handle_, static_cast<std::uint16_t>(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
			console_out_ << "[WARN] " << info << std::endl;
		}

		void LogError(std::string_view info) {
			SetConsoleTextAttribute(console_handle_, static_cast<std::uint16_t>(FOREGROUND_RED | FOREGROUND_INTENSITY));
			console_out_ << "[ERRO] " << info << std::endl;
		}

	private:
		bool console_exists_{};
		HANDLE console_handle_{};
		std::ofstream console_out_;
	};
}