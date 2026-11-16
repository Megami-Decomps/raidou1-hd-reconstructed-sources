#pragma once
#include "types.h"

typedef struct ItemListMenuBar ItemListMenuBar;
typedef struct KNYHEADERCLASS KNYHEADERCLASS;
typedef struct KNYITEMLISTCLASS KNYITEMLISTCLASS;
typedef struct Money Money;
typedef struct Quantity Quantity;
typedef struct shp_UI_manager_ScrollBar shp_UI_manager_ScrollBar;
typedef struct shp_UI_manager_TextSet shp_UI_manager_TextSet;

struct Quantity {
    shp_UI_manager_TextSet *num;
};

struct ItemListMenuBar {
    shp_UI_manager_TextSet *name;
    shp_UI_manager_TextSet *price;
    shp_UI_manager_TextSet *yen;
    shp_UI_manager_TextSet *posse;
    Quantity *quantity;
};

struct KNYHEADERCLASS {
    shp_UI_manager_TextSet *text_sinamono;
    shp_UI_manager_TextSet *text_nedan;
    shp_UI_manager_TextSet *text_syoji;
    shp_UI_manager_TextSet *text_baibai;
};

struct KNYITEMLISTCLASS {
    Money *posse_money;
    Money *pay_money;
    KNYHEADERCLASS *header;
    shp_UI_manager_ScrollBar *scrollbar;
    ItemListMenuBar *menubar[6];
};
