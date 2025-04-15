#ifndef ML_VTHOOK_GENERATED_HPP
#define ML_VTHOOK_GENERATED_HPP

// This file was generated. Do not edit it, changes will be lost the next time it is regenerated.

/// VtHook Manager for 0 Arguments
template<class ClassType, class RetType>
struct mlVtHookMan0 {
    typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType*);
#ifdef ML_VTHOOK_USE_VEC // TODO
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

/// VtHook Manager for 1 Arguments
template<class ClassType, class RetType, typename TArg1>
struct mlVtHookMan1 {
    typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType*, TArg1 arg1);
#ifdef ML_VTHOOK_USE_VEC // TODO
	typedef mlVec<PfnHook> ListType;
#else
	typedef mlList<PfnHook> ListType;
#endif

	ResultType Call(ClassType* pThat, TArg1 arg1) {
		u32 listLength = hookList.Size();
		ResultType lastResult;
		for(u32 i = 0; i < listLength; ++i) {
			lastResult = hookList[i](pThat, arg1);
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

/// VtHook Manager for 2 Arguments
template<class ClassType, class RetType, typename TArg1, typename TArg2>
struct mlVtHookMan2 {
    typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType*, TArg1 arg1, TArg2 arg2);
#ifdef ML_VTHOOK_USE_VEC // TODO
	typedef mlVec<PfnHook> ListType;
#else
	typedef mlList<PfnHook> ListType;
#endif

	ResultType Call(ClassType* pThat, TArg1 arg1, TArg2 arg2) {
		u32 listLength = hookList.Size();
		ResultType lastResult;
		for(u32 i = 0; i < listLength; ++i) {
			lastResult = hookList[i](pThat, arg1, arg2);
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

/// VtHook Manager for 3 Arguments
template<class ClassType, class RetType, typename TArg1, typename TArg2, typename TArg3>
struct mlVtHookMan3 {
    typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType*, TArg1 arg1, TArg2 arg2, TArg3 arg3);
#ifdef ML_VTHOOK_USE_VEC // TODO
	typedef mlVec<PfnHook> ListType;
#else
	typedef mlList<PfnHook> ListType;
#endif

	ResultType Call(ClassType* pThat, TArg1 arg1, TArg2 arg2, TArg3 arg3) {
		u32 listLength = hookList.Size();
		ResultType lastResult;
		for(u32 i = 0; i < listLength; ++i) {
			lastResult = hookList[i](pThat, arg1, arg2, arg3);
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

/// VtHook Manager for 4 Arguments
template<class ClassType, class RetType, typename TArg1, typename TArg2, typename TArg3, typename TArg4>
struct mlVtHookMan4 {
    typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType*, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4);
#ifdef ML_VTHOOK_USE_VEC // TODO
	typedef mlVec<PfnHook> ListType;
#else
	typedef mlList<PfnHook> ListType;
#endif

	ResultType Call(ClassType* pThat, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4) {
		u32 listLength = hookList.Size();
		ResultType lastResult;
		for(u32 i = 0; i < listLength; ++i) {
			lastResult = hookList[i](pThat, arg1, arg2, arg3, arg4);
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

/// VtHook Manager for 5 Arguments
template<class ClassType, class RetType, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
struct mlVtHookMan5 {
    typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType*, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5);
#ifdef ML_VTHOOK_USE_VEC // TODO
	typedef mlVec<PfnHook> ListType;
#else
	typedef mlList<PfnHook> ListType;
#endif

	ResultType Call(ClassType* pThat, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5) {
		u32 listLength = hookList.Size();
		ResultType lastResult;
		for(u32 i = 0; i < listLength; ++i) {
			lastResult = hookList[i](pThat, arg1, arg2, arg3, arg4, arg5);
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

/// VtHook Manager for 6 Arguments
template<class ClassType, class RetType, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
struct mlVtHookMan6 {
    typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType*, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6);
#ifdef ML_VTHOOK_USE_VEC // TODO
	typedef mlVec<PfnHook> ListType;
#else
	typedef mlList<PfnHook> ListType;
#endif

	ResultType Call(ClassType* pThat, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6) {
		u32 listLength = hookList.Size();
		ResultType lastResult;
		for(u32 i = 0; i < listLength; ++i) {
			lastResult = hookList[i](pThat, arg1, arg2, arg3, arg4, arg5, arg6);
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

/// VtHook Manager for 7 Arguments
template<class ClassType, class RetType, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7>
struct mlVtHookMan7 {
    typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType*, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7);
#ifdef ML_VTHOOK_USE_VEC // TODO
	typedef mlVec<PfnHook> ListType;
#else
	typedef mlList<PfnHook> ListType;
#endif

	ResultType Call(ClassType* pThat, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7) {
		u32 listLength = hookList.Size();
		ResultType lastResult;
		for(u32 i = 0; i < listLength; ++i) {
			lastResult = hookList[i](pThat, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
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

/// VtHook Manager for 8 Arguments
template<class ClassType, class RetType, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8>
struct mlVtHookMan8 {
    typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType*, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8);
#ifdef ML_VTHOOK_USE_VEC // TODO
	typedef mlVec<PfnHook> ListType;
#else
	typedef mlList<PfnHook> ListType;
#endif

	ResultType Call(ClassType* pThat, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8) {
		u32 listLength = hookList.Size();
		ResultType lastResult;
		for(u32 i = 0; i < listLength; ++i) {
			lastResult = hookList[i](pThat, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
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

/// VtHook Manager for 9 Arguments
template<class ClassType, class RetType, typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6, typename TArg7, typename TArg8, typename TArg9>
struct mlVtHookMan9 {
    typedef mlVtHookResult<RetType> ResultType;
	typedef ResultType (*PfnHook)(ClassType*, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9);
#ifdef ML_VTHOOK_USE_VEC // TODO
	typedef mlVec<PfnHook> ListType;
#else
	typedef mlList<PfnHook> ListType;
#endif

	ResultType Call(ClassType* pThat, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4, TArg5 arg5, TArg6 arg6, TArg7 arg7, TArg8 arg8, TArg9 arg9) {
		u32 listLength = hookList.Size();
		ResultType lastResult;
		for(u32 i = 0; i < listLength; ++i) {
			lastResult = hookList[i](pThat, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
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