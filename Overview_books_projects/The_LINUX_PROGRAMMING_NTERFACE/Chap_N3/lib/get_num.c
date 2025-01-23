#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "get_num.h"

static void gnFail(const char *fname, const char *msg, const char *arg, const char *name)
{
    fprintf(stderr, "%s error", fname);
    if (name != NULL)
        fprintf(stderr, " (in %s)", name);
    fprintf(stderr, ": %s\n", msg);
    if (arg != NULL && *arg != '\0')
        fprintf(stderr, "        offending text: %s\n", arg);
    exit(EXIT_FAILURE);
}

static long getNum(const char *fname, const char *arg, int flags, const char *name)
{
    long res;
    char *endptr;
    int base;

    // Check for null or empty string
    if (arg == NULL || *arg == '\0')
        gnFail(fname, "null or empty string", arg, name);

    // Determine the base for conversion
    base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8 :
           (flags & GN_BASE_16) ? 16 : 10;

    // Convert the string to a long integer
    errno = 0;
    res = strtol(arg, &endptr, base);

    // Check for errors in strtol()
    if (errno != 0)
        gnFail(fname, "strtol() failed", arg, name);

    // Check for non-numeric characters
    if (*endptr != '\0')
        gnFail(fname, "nonnumeric characters", arg, name);

    // Check for negative values (if GN_NONNEG flag is set)
    if ((flags & GN_NONNEG) && res < 0)
        gnFail(fname, "negative value not allowed", arg, name);

    // Check for values greater than 0 (if GN_GT_0 flag is set)
    if ((flags & GN_GT_0) && res <= 0)
        gnFail(fname, "value must be > 0", arg, name);

    return res;
}

long getLong(const char *arg, int flags, const char *name)
{
    return getNum("getLong", arg, flags, name);
}

int getInt(const char *arg, int flags, const char *name)
{
    long res;

    // Convert the string to a long integer
    res = getNum("getInt", arg, flags, name);

    // Check if the result is within the range of an int
    if (res > INT_MAX || res < INT_MIN)
        gnFail("getInt", "integer out of range", arg, name);

    return (int)res;
}