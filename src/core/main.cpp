
extern "C" {
    void sioPuts(const char* pszIn);
}

// Called to initalize the ml core.
void mlStart() {
    sioPuts("it's alive.. maybe? perhapsibly? who knows");
}