
extern "C" {
    void sioPuts(const char* pszIn);
}

// Initalizes the ml core.
// This shoulc be called once by hooking an appropiate game function.
extern "C" void mlStart() {
    sioPuts("it's alive.. maybe? perhapsibly? who knows");
}