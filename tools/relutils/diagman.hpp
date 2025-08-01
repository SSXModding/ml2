#pragma once
#include <cstdio>
#include <string_view>

namespace rel {

    /// Abstracts the emission of diagnostic messages.
	class cDiagnosticMan {
    public:
        cDiagnosticMan(std::string_view programName);

		void emitNotice(const std::string_view notice);

		/// Emit a warning.
		void emitWarning(const std::string_view warning);

		/// Emit an error. This also exits the process with an error code.
		[[noreturn]] void emitError(const std::string_view error);
		[[noreturn]] void emitFatalError(const std::string_view error);

		template <class... Args>
		void emitNotice(const char* format, Args... args) {
			char buf[256] {};
			auto written = snprintf(&buf[0], sizeof(buf) - 1, format, args...);
			emitNotice(std::string_view(buf, written));
		}

		template <class... Args>
		void emitWarning(const char* format, Args... args) {
			char buf[256] {};
			auto written = snprintf(&buf[0], sizeof(buf) - 1, format, args...);
			emitWarning(std::string_view(buf, written));
		}

		template <class... Args>
		[[noreturn]] void emitError(const char* format, Args... args) {
			char buf[256] {};
			auto written = snprintf(&buf[0], sizeof(buf) - 1, format, args...);
			emitError(std::string_view(buf, written));
		}

		template <class... Args>
		[[noreturn]] void emitFatalError(const char* format, Args... args) {
			char buf[256] {};
			auto written = snprintf(&buf[0], sizeof(buf) - 1, format, args...);
			emitFatalError(std::string_view(buf, written));
		}
	};

} // namespace rel