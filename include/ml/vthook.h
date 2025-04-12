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

template <class ClassType, class RetType>
struct mlVTHookMan0 {
	typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType* pThat);
#ifdef USE_VEC
    typedef mlVec<PfnHook> ListType;
#else
    typedef mlList<PfnHook> ListType;
#endif

	ResultType Call(ClassType* pThat) {
		u32 listLength = hookList.Size();
		ResultType lastResult;
		for(u32 i = 0; i < listLength; ++i) {
			lastResult = hookList[i](pThat);
			if(lastResult.code == kVtHook_Abort)
				break;
		}

		return lastResult;
	}

	void RegisterHook(PfnHook hook) {
		hookList.pushBack(hook);
	}

   private:
	ListType hookList;
};

#endif