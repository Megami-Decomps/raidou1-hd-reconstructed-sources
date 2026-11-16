#include "types.h"
#include "jmsmodeltables.h"

typedef struct JmsLight_t JmsLight_t;
typedef struct jmsModelTable_t jmsModelTable_t;
typedef struct sdf3DLight_t sdf3DLight_t;

struct JmsLight_t {
    sdf3DLight_t *light;
    sdfVector4_t ambient;
};

jmsModelTable_t *jmsModelTable[6];
