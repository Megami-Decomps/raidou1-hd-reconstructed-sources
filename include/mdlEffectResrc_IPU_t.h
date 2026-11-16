#pragma once
#include "types.h"

typedef struct mdlEffectResrc_IPU_t mdlEffectResrc_IPU_t;
typedef struct pbResourceUnit_IPU pbResourceUnit_IPU;
typedef struct sdfPacStdBlockHeader_t sdfPacStdBlockHeader_t;

struct mdlEffectResrc_IPU_t {
    pbResourceUnit_IPU *data;
    bool busy;
    bool playing;
    void *decoder;
};

struct pbResourceUnit_IPU {
    sdfPacStdBlockHeader_t *header;
    void *extHeader;
    char *path;
    char *target;
};
