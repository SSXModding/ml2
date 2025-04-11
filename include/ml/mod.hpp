#ifndef ML_MOD_HPP
#define ML_MOD_HPP

/// Metadata
struct mlModMeta {
    const char* pszAuthor;
    const char* pszModName;
};

/// A mod
struct mlMod {
    mlMod() {
        pNextMod = 0;
    }
    virtual ~mlMod() {}

    // metadata
    virtual const mlModMeta& getMeta() const = 0;
    virtual const char* getId() const = 0;

    // Enable/disable mods.
    virtual void enable() = 0;

    virtual void disable() = 0;

    mlMod* pNextMod;
};

void mlRegisterMod(mlMod* pMod);
void mlModForEach(bool (*pcbCallback)(mlMod* pMod, void* context), void* context);
mlMod* mlFindMod(const char* pszName);

template<class T>
struct mlModAutoRegister {
    mlModAutoRegister(T* pMod) {
        mlRegisterMod((mlMod*)pMod);
    }
};

// Register a mod.
#define ML_REGISTER_MOD(T) \
    static T __modInstance_##T; \
    static mlModAutoRegister<T> __modRegister_##T(&__modInstance_##T);

#endif