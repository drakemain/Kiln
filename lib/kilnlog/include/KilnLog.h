#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// Level definitions
#define KLOG_CRI -2
#define KLOG_ERR -1
#define KLOG_INF 0
#define KLOG_WAR 1
#define KLOG_DEB 2

// Interface
typedef struct {
    void (*const put)(int level, const char* msg, ...);
    void (*const setLevel)(int level);
    void (*const setFile)(const char* file);
    void (*const setSilent)(const bool silent);
    void (*const flush)(void);
} kiln_log_interface;

extern kiln_log_interface const KLog;

#ifdef __cplusplus
}
#endif