#include "types.h"
#include "enemypath.h"

typedef struct SBTLENMY_ACTDATA SBTLENMY_ACTDATA;
typedef struct SBTLENMY_PATHDATA SBTLENMY_PATHDATA;

s16 tbldatacnt[4];
SBTLENMY_PATHDATA *pathdata;
SBTLENMY_ACTDATA **data;
static SBTLENMY_ACTDATA *enemypath_data_000;
static SBTLENMY_ACTDATA *enemypath_data_001;
static SBTLENMY_ACTDATA *enemypath_data_002;
