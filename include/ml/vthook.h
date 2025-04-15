#ifndef ML_VTHOOK_H
#define ML_VTHOOK_H

#include <ml/cxx/vec.hpp>
#include <ml/cxx/list.hpp>

//#define USE_VEC

enum mlVtHookResultCode {
	kVtHook_Abort,
	kVtHook_RunOriginal
};

template <class RetType>
struct mlVtHookResult {
	mlVtHookResultCode code;
	RetType lastReturn;

	mlVtHookResult(RetType ret)
		: lastReturn(ret) {
		code = kVtHook_RunOriginal;
	}
	mlVtHookResult(mlVtHookResultCode code, RetType ret)
		: code(code), lastReturn(ret) {
	}
};

template <>
struct mlVtHookResult<void> {
	mlVtHookResultCode code;

	mlVtHookResult() {
		code = kVtHook_RunOriginal;
	}
	mlVtHookResult(mlVtHookResultCode code)
		: code(code) {
	}
};

// Include the generated managers
#include "vthook_generated.hpp"

// TODO: helper macros maybe

#endif