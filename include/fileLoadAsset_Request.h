#pragma once
#include "types.h"

typedef struct fileLoadAsset_Request fileLoadAsset_Request;

struct fileLoadAsset_Request {
    bool isDone;
    char *key;
    char *path;
};
