#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_MSC_VER)
#include <io.h>
#define access _access
#define F_OK 0
#else
#include <unistd.h>
#endif
#include <volk/volk_prefs.h>

void volk_get_config_path(char* path, bool read)
{
    if (!path)
        return;
    const char* suffix = "/.volk/volk_config";
    const char* suffix2 = "/volk/volk_config"; // non-hidden
    char* home = NULL;

    // allows config redirection via env variable
    home = getenv("VOLK_CONFIGPATH");
    if (home != NULL) {
        strncpy(path, home, 512);
        strcat(path, suffix2);
        if (!read || access(path, F_OK) != -1) {
            return;
        }
    }

    // check for user-local config file
    home = getenv("HOME");
    if (home != NULL) {
        strncpy(path, home, 512);
        strcat(path, suffix);
        if (!read || (access(path, F_OK) != -1)) {
            return;
        }
    }

    // check for config file in APPDATA (Windows)
    home = getenv("APPDATA");
    if (home != NULL) {
        strncpy(path, home, 512);
        strcat(path, suffix);
        if (!read || (access(path, F_OK) != -1)) {
            return;
        }
    }

    // check for system-wide config file
    if (access("/etc/volk/volk_config", F_OK) != -1) {
        strncpy(path, "/etc", 512);
        strcat(path, suffix2);
        if (!read || (access(path, F_OK) != -1)) {
            return;
        }
    }

    // If still no path was found set path[0] to '0' and fall through
    path[0] = 0;
    return;
}

size_t volk_load_preferences(volk_arch_pref_t** prefs_res)
{
    return 0; //disable
}
