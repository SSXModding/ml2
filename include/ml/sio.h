#ifndef ML_SIO_H
#define ML_SIO_H

/* This header declares utilities for using the EE SIO periphial directly. */

#ifdef __cplusplus
extern "C" {
#endif

    void sioPutc(char c);

    void sioPuts(const char* pszIn);

#ifdef __cplusplus
};
#endif

#endif