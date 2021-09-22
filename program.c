#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

typedef struct
{
    const char *executable;
} configuration;

static int config_converter(void *user, const char *section, const char *name, const char *value);

int main(void)
{
    configuration config;

    if (ini_parse("aromlauncher.ini", config_converter, &config) < 0)
    {
        printf("Error loading configuration file.\n");
        return 1;
    }

    char launch[] = "AlphaROMdiE.exe ";
    strcat(launch, config.executable);

    system(launch);
    return 0;
}

static int config_converter(void *user, const char *section, const char *name, const char *value)
{
    configuration *p_config = (configuration *)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("Launch", "exe"))
    {
        p_config->executable = strdup(value);
    }
    else
    {
        // Unknown name error
        return 0;
    }

    return 1;
}
