#pragma once
#include "types.h"

typedef struct MILKHEADERCLASS MILKHEADERCLASS;
typedef struct MILKITEMLISTCLASS MILKITEMLISTCLASS;
typedef struct MilkHallMenuBar MilkHallMenuBar;
typedef struct Money Money;
typedef struct shp_UI_manager_ScrollBar shp_UI_manager_ScrollBar;
typedef struct shp_UI_manager_TextSet shp_UI_manager_TextSet;

struct MilkHallMenuBar {
    shp_UI_manager_TextSet *price;
    shp_UI_manager_TextSet *yen;
    shp_UI_manager_TextSet *name;
};

struct MILKHEADERCLASS {
    shp_UI_manager_TextSet *text_soda;
    shp_UI_manager_TextSet *text_nedan;
};

struct MILKITEMLISTCLASS {
    Money *posse_money;
    Money *pay_money;
    MILKHEADERCLASS *header;
    shp_UI_manager_ScrollBar *scrollbar;
    MilkHallMenuBar *menubar[6];
};
