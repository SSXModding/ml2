#include "diagman.hpp"

#include <cstdio>
#include <cstdlib>

namespace rel {

/// helper which makes printing a std::string_view using the "%.*s" format
/// a bit less of a annoying chore
#define STAR_FORMAT_SV(sv) static_cast<int>(sv.size()), sv.data()

	namespace {
		std::string_view gCurrentProgram;

		void emitShared(const std::string_view type, const std::string_view message, FILE* fp = stdout) {
			std::fprintf(fp, "%.*s %.*s: %.*s\n", STAR_FORMAT_SV(gCurrentProgram), STAR_FORMAT_SV(type), STAR_FORMAT_SV(message));
		}
	} // namespace

	cDiagnosticMan::cDiagnosticMan(std::string_view programName) {
		gCurrentProgram = programName;
	}

	void cDiagnosticMan::emitNotice(const std::string_view notice) {
		emitShared("notice", notice);
	}

	void cDiagnosticMan::emitWarning(const std::string_view warning) {
		emitShared("warning", warning);
	}

	void cDiagnosticMan::emitError(const std::string_view error) {
		emitShared("error", error, stderr);
		std::quick_exit(1);
	}

	void cDiagnosticMan::emitFatalError(const std::string_view error) {
		emitShared("fatal error", error, stderr);
		std::quick_exit(1);
	}
} // namespace rel