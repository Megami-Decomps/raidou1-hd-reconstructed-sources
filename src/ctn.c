#include "types.h"
#include "atlfieldaccessor.h"
#include "ctn.h"
#include "dds3vrf.h"
#include "fld.h"
#include "sdf_vu0.h"
#include "sdfquat.h"
#include "sdfrand.h"
#include "sdfvu0.h"

typedef struct ctnBlock_t ctnBlock_t;
typedef struct ctnCitizenData_t ctnCitizenData_t;
typedef struct ctnCitizen_t ctnCitizen_t;
typedef struct ctnExit_t ctnExit_t;
typedef struct ctnGrid_t ctnGrid_t;
typedef struct ctnInput_t ctnInput_t;
typedef struct ctnObject_t ctnObject_t;
typedef struct ctnTargetInfo_t ctnTargetInfo_t;
typedef struct ctnWork_t ctnWork_t;

struct ctnCitizenData_t {
    sdfVector4_t rotateQuat;
    s32 fExist;
    f32 x;
    f32 y;
    f32 vx;
    f32 vy;
    f32 targetVx;
    f32 targetVy;
    f32 vleng;
    f32 dirX;
    f32 dirY;
    f32 normalX;
    f32 normalY;
    f32 offCenter;
    f32 leftWallDist;
    f32 rightWallDist;
    s32 index;
    s32 sliceIndex;
    s32 attr;
    f32 oldX;
    f32 oldY;
    s32 friendIndex[4];
    s32 playerEvadeArray[7];
    s32 resv0;
    s32 objectEvadeArray[7];
    s32 objectDir;
    s32 aheadEvadeArray[7];
    s32 spdType;
    s32 dir;
    f32 angle;
    u8 exitIndex;
    s8 pathPref;
    u8 classType;
    s8 followType;
    u8 friendNum;
    u8 blockIndex;
    u8 belongIndex;
    CTN_EVADE evadeType;
};

ctnWork_t *Work;
s32 gMap03_CntN;
s32 gMap03_CntS;
static ctnCitizenData_t *citizenData;

static void LoadDataSub(char *filename, char *assetname);
static void InitWork(void);
static void InitFromFile(s32 id, s32 floor);
static void SetCitizenAttr(ctnCitizen_t *pCitizen, s32 attr);
static void RemoveCitizenAttr(ctnCitizen_t *pCitizen, s32 attr);
static void RotateVec(f32 *vx, f32 *vy, f32 rad);
static f32 DotProduct(f32 x1, f32 y1, f32 x2, f32 y2);
static f32 CrossProduct(f32 x1, f32 y1, f32 x2, f32 y2);
static void LeaveBlock(ctnCitizen_t *pCitizen);
static ctnCitizen_t *AddCitizen(void);
static void UpdateCitizenPos(ctnCitizen_t *pCitizen);
static void UpdateCitizenRotate(ctnCitizen_t *pCitizen);
static void LeaveGrid(ctnCitizen_t *pCitizen, ctnGrid_t *pGrid);
static void EnterGrid(ctnCitizen_t *pCitizen, ctnGrid_t *pGrid);
static void SetPositionInfo(ctnCitizen_t *pCitizen);
static void UpdateCitizenVelocity(ctnCitizen_t *pCitizen);
static void UpdateTargetVelocity(ctnCitizen_t *pCitizen);
static void SetWallInfo(ctnCitizen_t *pCitizen);
static void SetPlayerWallDist(ctnCitizen_t *pCitizen, f32 *leftWallDist, f32 *rightWallDist);
static void SetObjectWallDist(ctnCitizen_t *pCitizen, ctnObject_t *pObject, f32 *leftWallDist, f32 *rightWallDist);
static void SetCitizenWallDist(ctnCitizen_t *pCitizen, ctnCitizen_t *pOther, f32 *leftWallDist, f32 *rightWallDist);
static ctnBlock_t *GetBlock(ctnCitizen_t *pCitizen);
static ctnTargetInfo_t *ChooseTarget(ctnCitizen_t *pCitizen, s32 prevBlockIndex);
static void EvadePlayerAhead(ctnCitizen_t *pCitizen);
static void EvadePlayer(ctnCitizen_t *pCitizen);
static void EvadeObject(ctnCitizen_t *pCitizen);
static void EvadeAheadSub(ctnCitizen_t *pCitizen, ctnCitizen_t *pOther);
static void SetPref(ctnCitizen_t *pCitizen);
static s32 GetPref(f32 leftWallDist, f32 h);
static s32 ComparePref(f32 leftWallDist, f32 h, s32 pathPref);
static bool CheckWait(ctnCitizen_t *pCitizen);
static void KillCitizenFriend(ctnCitizen_t *pCitizen);
static void KillCitizen(ctnCitizen_t *pCitizen);
static ctnCitizen_t *FindAheadList(ctnCitizen_t *pCitizen, f32 maxDist, s32 citizenNum, ctnCitizen_t *ctnList);
static ctnCitizen_t *FindAhead(ctnCitizen_t *pCitizen, f32 maxDist);
static ctnCitizen_t *FindHeadOn(ctnCitizen_t *pCitizen, f32 maxDist, s32 citizenNum, ctnCitizen_t *ctnList);
static void SetHeadOn(ctnCitizen_t *pCitizen, s32 maxDist);
static void SimulateSetFlags(void);
static ctnGrid_t *FreeGridBeside(f32 ox, f32 oy, ctnCitizen_t *pCitizen);
static void EvadeHeadOn(ctnCitizen_t *pCitizen);
static void MoveFollower(ctnCitizen_t *pCitizen);
static void EvadeObjectSub(ctnCitizen_t *pCitizen, ctnObject_t *pObject);
static void EnterBlock(ctnCitizen_t *pCitizen, ctnGrid_t *pGrid);
static f32 GetClassVelocity(ctnCitizen_t *pCitizen);
static void ShootCitizen(ctnExit_t *pExit);
static void SetOffCenter(ctnCitizen_t *pCitizen);
static s32 CheckExit(ctnCitizen_t *pCitizen);
static bool ChkNg_Grid(s32 ix, s32 iy);
static void OW_ObjectPos(s32 i, f32 *_fx, f32 *_fy, f32 *_radius);
static void ChkNg_MovePos1(ctnCitizen_t *ctn);
static void ChkNg_MovePos2(ctnCitizen_t *ctn, f32 *_fx, f32 *_fy);

// 0x18db4d0
static void LoadDataSub(char *filename, char *assetname) {
  void *Asset;
  sdfBinary *v10;
  s32 S32;
  sdfBinary *New;
  s32 v13;
  s32 v14;
  ctnWork_t *v17;
  ctnWork_t *v18;
  ctnWork_t *v19;
  ctnWork_t *v20;
  s32 v21;
  ctnWork_t *v22;
  s32 v23;
  ctnWork_t *v26;
  ctnBlock_t *v27;
  s64 v28;
  ctnBlock_t *v30;
  s32 *v32;
  s64 v33;
  s64 v34;
  Il2CppObject *v35;
  Il2CppClass *v36;
  void *v37;
  s64 v38;
  s64 v39;
  s64 v40;
  s64 v41;
  s32 v42;
  s64 v43;
  s64 v44;
  f32 Float;
  s64 v46;
  s64 v47;
  f32 v48;
  s64 v49;
  s64 v50;
  f32 v51;
  s64 v52;
  s64 v53;
  f32 v54;
  s64 v55;
  s64 v56;
  s32 v57;
  s64 v58;
  s64 v59;
  s32 v60;
  s64 v61;
  s64 v62;
  s64 v63;
  s64 v64;
  s64 v65;
  s64 v66;
  s64 v67;
  s64 v68;
  s64 v69;
  s64 v70;
  s64 v71;
  s64 v72;
  s64 v73;
  s64 v74;
  s64 v75;
  s64 v76;
  s64 v77;
  s64 v78;
  s64 v79;
  s64 v80;
  s64 v81;
  s64 v82;
  s64 v83;
  s64 v84;
  s64 v85;
  s64 v86;
  s64 v87;
  s64 v88;
  s64 v89;
  s64 v90;
  s64 v91;
  s64 v92;
  s64 v93;
  f32 v94;
  s64 v95;
  s64 v96;
  f32 v97;
  s64 v98;
  s64 v99;
  f32 v100;
  s64 v101;
  s64 v102;
  f32 v103;
  s64 v104;
  s64 v105;
  f32 v106;
  s64 v107;
  s64 v108;
  f32 v109;
  s64 v110;
  s64 v111;
  f32 v112;
  s64 v113;
  s64 v114;
  f32 v115;
  s64 v116;
  s64 v117;
  f32 v118;
  s64 v119;
  s64 v120;
  f32 v121;
  s64 v122;
  s64 v123;
  f32 v124;
  s64 v125;
  s64 v126;
  f32 v127;
  s64 v128;
  s64 v129;
  f32 v130;
  s64 v131;
  s64 v132;
  f32 v133;
  s64 v134;
  s64 v135;
  f32 v136;
  s64 v137;
  s64 v138;
  f32 v139;
  s64 v140;
  s64 v141;
  ctnBlock_t *blockArray;
  Il2CppClass **v144;
  s64 v145;
  s64 v146;
  ctnWork_t *v147;
  ctnExit_t *v148;
  f32 **vertex;
  f32 *v151;
  f32 v152;
  f32 **v153;
  f32 *v154;
  f32 v155;
  f32 **v156;
  f32 *v157;
  f32 v158;
  f32 **v159;
  f32 *v160;
  f32 *dir;
  f32 *v162;
  s32 v163;
  ctnExit_t *exitArray;
  ctnGrid_t *v166;
  s32 i;
  s32 v169;
  ctnWork_t *v170;
  s32 xMax;
  ctnGrid_t *pGrid;
  Il2CppObject *v173;
  void *v174;
  void *v175;
  Il2CppClass **v176;
  s32 v177;
  ctnGrid_t *v178;
  u8 *signalIndex;
  u8 *v181;
  u8 *v182;
  u8 *v183;
  u8 *v184;
  u8 U8;
  u8 v186;
  ctnBlock_t *v188;
  ctnWork_t *v190;
  s32 y;
  s32 x;
  ctnGrid_t *v193;
  s32 v194;
  s64 v195;
  s64 v196;
  s64 v197;
  ctnObject_t *v198;
  void *v199;
  s64 v200;
  s64 v201;
  s64 v202;
  ctnWork_t *v204;
  ctnObject_t *objectArray;
  sdfBinary *v210;
  sdfBinary *v211;
  sdfBinary *v212;
  s64 v213;

  InitWork();
  if (IsLoad(Dependent, assetname, 0))
  {
    goto LABEL_6;
  }
  Load(Dependent, assetname, assetname);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
LABEL_6:
  Asset = LoadAsset(_Ctrl_k__BackingField, assetname, filename, 0);
  v10 = Allocate(sdfBinary);
  _ctor(v10, Asset, 0);
  S32 = ReadS32(v10, 0);
  New = GetNew(v10, 0, S32, 0);
  v13 = ReadS32(v10, 0);
  v212 = GetNew(v10, 0, v13, 0);
  v14 = ReadS32(v10, 0);
  v211 = GetNew(v10, 0, v14, 0);
  Work->xMax = ReadU8(v10, 0);
  v17 = Work;
  v17->yMax = ReadU8(v10, 0);
  v18 = Work;
  v18->blockNum = ReadU8(v10, 0);
  v19 = Work;
  v19->exitNum = ReadU8(v10, 0);
  v20 = Work;
  v20->gridNum = ReadU16(v10, 0);
  ReadU16(v10, 0);
  v21 = ReadS32(v10, 0);
  v210 = GetNew(v10, 0, v21, 0);
  v22 = Work;
  v23 = ReadS32(v10, 0);
  v22->objectNum = v23;
  v26 = Work;
  v27 = NewSpecific(ctnBlock_t, Work->blockNum);
  v26->blockArray = v27;
  v28 = 0;
  while (v28 < Work->blockNum)
  {
    v30 = Allocate(ctnBlock_t);
    _ctor(v30);
    v32 = v30->targetInfo;
    if (v32[6] >= 1)
    {
      v213 = v28;
      v33 = 0;
      v34 = 8;
      do
      {
        v35 = Allocate(ctnTargetInfo_t);
        v36 = NewSpecific(f32, 2u);
        v35[1].klass = v36;
        v37 = NewSpecific(f32, 2u);
        v35[1].monitor = v37;
        _ctor(v35, 0);
        if (!QueryInterface(v35, *(void **)(*(u64 *)v32 + 64)))
          goto LABEL_100;
        *(u64 *)&v32[v34] = v35;
        v32 = v30->targetInfo;
        ++v33;
        v38 = *(u64 *)&v32[v34];
        v34 += 2;
        *(u32 *)(v38 + 32) = 255;
        v39 = *((u64 *)v32 + 3);
      }
      while (v33 < (s32)v39);
      v28 = v213;
      if ((s32)v39 >= 1)
      {
        v40 = 4;
        do
        {
          v41 = *(u64 *)&v32[2 * v40];
          v42 = ReadS32(New, 0);
          v43 = v30->targetInfo;
          *(u32 *)(v41 + 32) = v42;
          v44 = *(u64 *)(*(u64 *)(v43 + 8 * v40) + 16);
          Float = ReadFloat(New, 0);
          v46 = v30->targetInfo;
          *(f32 *)(v44 + 32) = Float;
          v47 = *(u64 *)(*(u64 *)(v46 + 8 * v40) + 16);
          v48 = ReadFloat(New, 0);
          v49 = v30->targetInfo;
          *(f32 *)(v47 + 36) = v48;
          v50 = *(u64 *)(*(u64 *)(v49 + 8 * v40) + 24);
          v51 = ReadFloat(New, 0);
          v52 = v30->targetInfo;
          *(f32 *)(v50 + 32) = v51;
          v53 = *(u64 *)(*(u64 *)(v52 + 8 * v40) + 24);
          v54 = ReadFloat(New, 0);
          v55 = v30->targetInfo;
          *(f32 *)(v53 + 36) = v54;
          v56 = *(u64 *)(v55 + 8 * v40);
          v57 = ReadS32(New, 0);
          v58 = v30->targetInfo;
          *(u32 *)(v56 + 36) = v57;
          v59 = *(u64 *)(v58 + 8 * v40);
          v60 = ReadS32(New, 0);
          v32 = v30->targetInfo;
          v61 = v40 - 3;
          ++v40;
          *(u32 *)(v59 + 40) = v60;
        }
        while (v61 < v32[6]);
      }
    }
    v62 = v30->fExit;
    *(u32 *)(v62 + 32) = ReadS32(New, 0);
    v63 = v30->fExit;
    *(u32 *)(v63 + 36) = ReadS32(New, 0);
    v64 = v30->fExit;
    *(u32 *)(v64 + 40) = ReadS32(New, 0);
    v65 = v30->fExit;
    *(u32 *)(v65 + 44) = ReadS32(New, 0);
    v66 = v30->fExit;
    *(u32 *)(v66 + 48) = ReadS32(New, 0);
    v67 = v30->fExit;
    *(u32 *)(v67 + 52) = ReadS32(New, 0);
    v68 = v30->fExit;
    *(u32 *)(v68 + 56) = ReadS32(New, 0);
    v69 = v30->fExit;
    *(u32 *)(v69 + 60) = ReadS32(New, 0);
    v70 = v30->fExit;
    *(u32 *)(v70 + 64) = ReadS32(New, 0);
    v71 = v30->fExit;
    *(u32 *)(v71 + 68) = ReadS32(New, 0);
    v72 = v30->fExit;
    *(u32 *)(v72 + 72) = ReadS32(New, 0);
    v73 = v30->fExit;
    *(u32 *)(v73 + 76) = ReadS32(New, 0);
    v74 = v30->fExit;
    *(u32 *)(v74 + 80) = ReadS32(New, 0);
    v75 = v30->fExit;
    *(u32 *)(v75 + 84) = ReadS32(New, 0);
    v76 = v30->fExit;
    *(u32 *)(v76 + 88) = ReadS32(New, 0);
    v77 = v30->fExit;
    *(u32 *)(v77 + 92) = ReadS32(New, 0);
    v78 = v30->dist;
    *(f32 *)(v78 + 32) = ReadFloat(New, 0);
    v79 = v30->dist;
    *(f32 *)(v79 + 36) = ReadFloat(New, 0);
    v80 = v30->dist;
    *(f32 *)(v80 + 40) = ReadFloat(New, 0);
    v81 = v30->dist;
    *(f32 *)(v81 + 44) = ReadFloat(New, 0);
    v82 = v30->dist;
    *(f32 *)(v82 + 48) = ReadFloat(New, 0);
    v83 = v30->dist;
    *(f32 *)(v83 + 52) = ReadFloat(New, 0);
    v84 = v30->dist;
    *(f32 *)(v84 + 56) = ReadFloat(New, 0);
    v85 = v30->dist;
    *(f32 *)(v85 + 60) = ReadFloat(New, 0);
    v86 = v30->dist;
    *(f32 *)(v86 + 64) = ReadFloat(New, 0);
    v87 = v30->dist;
    *(f32 *)(v87 + 68) = ReadFloat(New, 0);
    v88 = v30->dist;
    *(f32 *)(v88 + 72) = ReadFloat(New, 0);
    v89 = v30->dist;
    *(f32 *)(v89 + 76) = ReadFloat(New, 0);
    v90 = v30->dist;
    *(f32 *)(v90 + 80) = ReadFloat(New, 0);
    v91 = v30->dist;
    *(f32 *)(v91 + 84) = ReadFloat(New, 0);
    v92 = v30->dist;
    *(f32 *)(v92 + 88) = ReadFloat(New, 0);
    v93 = v30->dist;
    v94 = ReadFloat(New, 0);
    v95 = v30->vertex;
    *(f32 *)(v93 + 92) = v94;
    v96 = *(u64 *)(v95 + 32);
    v97 = ReadFloat(New, 0);
    v98 = v30->vertex;
    *(f32 *)(v96 + 32) = v97;
    v99 = *(u64 *)(v98 + 32);
    v100 = ReadFloat(New, 0);
    v101 = v30->vertex;
    *(f32 *)(v99 + 36) = v100;
    v102 = *(u64 *)(v101 + 40);
    v103 = ReadFloat(New, 0);
    v104 = v30->vertex;
    *(f32 *)(v102 + 32) = v103;
    v105 = *(u64 *)(v104 + 40);
    v106 = ReadFloat(New, 0);
    v107 = v30->vertex;
    *(f32 *)(v105 + 36) = v106;
    v108 = *(u64 *)(v107 + 48);
    v109 = ReadFloat(New, 0);
    v110 = v30->vertex;
    *(f32 *)(v108 + 32) = v109;
    v111 = *(u64 *)(v110 + 48);
    v112 = ReadFloat(New, 0);
    v113 = v30->vertex;
    *(f32 *)(v111 + 36) = v112;
    v114 = *(u64 *)(v113 + 56);
    v115 = ReadFloat(New, 0);
    v116 = v30->vertex;
    *(f32 *)(v114 + 32) = v115;
    v117 = *(u64 *)(v116 + 56);
    v118 = ReadFloat(New, 0);
    v119 = v30->normal;
    *(f32 *)(v117 + 36) = v118;
    v120 = *(u64 *)(v119 + 32);
    v121 = ReadFloat(New, 0);
    v122 = v30->normal;
    *(f32 *)(v120 + 32) = v121;
    v123 = *(u64 *)(v122 + 32);
    v124 = ReadFloat(New, 0);
    v125 = v30->normal;
    *(f32 *)(v123 + 36) = v124;
    v126 = *(u64 *)(v125 + 40);
    v127 = ReadFloat(New, 0);
    v128 = v30->normal;
    *(f32 *)(v126 + 32) = v127;
    v129 = *(u64 *)(v128 + 40);
    v130 = ReadFloat(New, 0);
    v131 = v30->normal;
    *(f32 *)(v129 + 36) = v130;
    v132 = *(u64 *)(v131 + 48);
    v133 = ReadFloat(New, 0);
    v134 = v30->normal;
    *(f32 *)(v132 + 32) = v133;
    v135 = *(u64 *)(v134 + 48);
    v136 = ReadFloat(New, 0);
    v137 = v30->normal;
    *(f32 *)(v135 + 36) = v136;
    v138 = *(u64 *)(v137 + 56);
    v139 = ReadFloat(New, 0);
    v140 = v30->normal;
    *(f32 *)(v138 + 32) = v139;
    v141 = *(u64 *)(v140 + 56);
    *(f32 *)(v141 + 36) = ReadFloat(New, 0);
    v30->index = v28;
    *(u32 *)&v30->crowd = 0;
    v30->citizenNum = 0;
    v30->area = ReadFloat(New, 0);
    v30->type = ReadS32(New, 0);
    v30->connectNum = ReadS32(New, 0);
    ReadS32(New, 0);
    blockArray = Work->blockArray;
    {
LABEL_100:
    }
    v144 = &blockArray->obj.klass + v28;
    v144[4] = v30;
    ++v28;
  }
  v145 = 0;
  v146 = 32;
  while (1)
  {
    v147 = Work;
    if (v145 >= v147->exitNum)
      break;
    v148 = Allocate(ctnExit_t);
    _ctor(v148);
    vertex = v148->vertex;
    v148->index = v145;
    v151 = vertex[0];
    v152 = ReadFloat(v212, 0);
    v153 = v148->vertex;
    v151[0] = v152;
    v154 = v153[0];
    v155 = ReadFloat(v212, 0);
    v156 = v148->vertex;
    v154[1] = v155;
    v157 = v156[1];
    v158 = ReadFloat(v212, 0);
    v159 = v148->vertex;
    v157[0] = v158;
    v160 = v159[1];
    v160[1] = ReadFloat(v212, 0);
    dir = v148->dir;
    dir[0] = ReadFloat(v212, 0);
    v162 = v148->dir;
    v162[1] = ReadFloat(v212, 0);
    v148->leng = ReadS32(v212, 0);
    v163 = ReadS32(v212, 0);
    v148->originalInterval = 60 * v163;
    v148->interval = 60 * v163;
    v148->blockIndex = ReadS32(v212, 0);
    v148->group = ReadS32(v212, 0);
    v148->popularity = ReadS32(v212, 0);
    ReadS32(v212, 0);
    v148->curCnt = 0;
    exitArray = Work->exitArray;
    *(Il2CppClass **)((char *)&exitArray->obj.klass + v146) = v148;
    ++v145;
    v146 += 8;
  }
  v147 = Work;
  v166 = NewSpecific(ctnGrid_t, v147->xMax * v147->yMax);
  v147->pGrid = v166;
  for (i = 0; ; ++i)
  {
    if (i >= Work->yMax)
      break;
    v169 = 0;
    while (1)
    {
      v170 = Work;
      xMax = v170->xMax;
      if (v169 >= xMax)
        break;
      v170 = Work;
      xMax = v170->xMax;
      pGrid = v170->pGrid;
      v173 = Allocate(ctnGrid_t);
      v174 = NewSpecific(byte, 5u);
      v173[2].monitor = v174;
      v175 = NewSpecific(s32, 3u);
      v173[3].monitor = v175;
      _ctor(v173, 0);
      v176 = &pGrid->obj.klass + v169 + i * xMax;
      v176[4] = v173;
      ++v169;
    }
  }
  v177 = 0;
  while (v177 < Work->gridNum)
  {
    v178 = Allocate(ctnGrid_t);
    _ctor(v178);
    v178->x = ReadS32(v211, 0);
    v178->y = ReadS32(v211, 0);
    ReadU8(v211, 0);
    signalIndex = v178->signalIndex;
    signalIndex[0] = ReadU8(v211, 0);
    v181 = v178->signalIndex;
    v181[1] = ReadU8(v211, 0);
    v182 = v178->signalIndex;
    v182[2] = ReadU8(v211, 0);
    v183 = v178->signalIndex;
    v183[3] = ReadU8(v211, 0);
    v184 = v178->signalIndex;
    v184[4] = ReadU8(v211, 0);
    v178->attr = ReadU8(v211, 0);
    U8 = ReadU8(v211, 0);
    if (U8 == 0xFF)
    {
      v178->pBlock = 0;
      v178->citizenNum = 0;
      goto LABEL_60;
    }
    else
    {
      v186 = U8;
      v188 = Work->blockArray[v186];
      v178->pBlock = v188;
      v178->citizenNum = 0;
      goto LABEL_60;
    }
LABEL_60:
    v190 = Work;
    x = v178->x;
    y = v178->y;
    v193 = v190->pGrid;
    v194 = v190->xMax;
    v195 = (s64)v193 + 8 * x + 8 * v194 * y;
    *(u64 *)(v195 + 32) = v178;
    ++v177;
  }
  v196 = 0;
  v197 = 32;
  goto LABEL_67;
  while (2)
  {
LABEL_67:
    if (v196 < Work->objectNum)
    {
      v198 = Allocate(ctnObject_t);
      v199 = NewSpecific(f32, 2u);
      v198->center = v199;
      _ctor(v198, 0);
      v200 = v198->center;
      *(f32 *)(v200 + 32) = ReadFloat(v210, 0);
      v201 = v198->center;
      *(f32 *)(v201 + 36) = ReadFloat(v210, 0);
      v198->radius = ReadFloat(v210, 0);
      v198->resv = ReadS32(v210, 0);
      v202 = v198->center;
      goto LABEL_72;
LABEL_73:
      v204 = Work;
      if (v204->mapID != 1)
        goto LABEL_83;
      goto LABEL_9000;
LABEL_72:
      goto LABEL_73;
      if (v204->mapID != 1)
      {
LABEL_83:
        objectArray = Work->objectArray;
        *(Il2CppClass **)((char *)&objectArray->obj.klass + v197) = v198;
        ++v196;
        v197 += 8;
        goto LABEL_67;
      }
LABEL_9000:
      v204 = Work;
      if (v197 == 104 && !v204->floorID)
      {
        *(u64 *)(v202 + 32) = 0x4238000042020000LL;
        *(u32 *)&v198->radius = 1061997773;
      }
      goto LABEL_83;
    }
    break;
  }
}

// 0x18dc6c0
static void InitWork(void) {
  ctnWork_t *v1;
  ctnWork_t *Work_local;
  ctnWork_t *v5;
  ctnWork_t *v6;
  s32 v8;
  s64 v9;
  ctnWork_t *v10;
  s64 v11;
  ctnCitizen_t *citizenArray;
  ctnCitizen_t *v13;
  s64 i;
  ctnObject_t *objectArray;
  Il2CppObject *v19;
  Il2CppClass *v20;
  ctnWork_t *v22;
  s32 *timeSliceNum;

  v1 = Allocate(ctnWork_t);
  _ctor(v1);
  Work = v1;
  Work_local = Work;
  Work_local->blockArray = 0;
  Work_local = ((char *)Work_local + 32);
  Work_local->citizenArray = 0;
  LODWORD(Work_local->objectArray) = 0;
  v5 = Work;
  v5->pGrid = 0;
  v5 = ((char *)v5 + 16);
  HIDWORD(v5->timeSliceNum) = 0;
  v6 = Work;
  v6->gridData = 0;
  v6 = ((char *)v6 + 24);
  LODWORD(v6->pGrid) = 0;
  v8 = 0;
  v9 = 32;
  v10 = Work;
  v10->citizenNum = 0;
  *(u64 *)&v10->playerY = 0;
  *(u64 *)&v10->playerOldY = 0;
  *(u64 *)&v10->fPlayer = 0;
  v10->playerVy = 0.0;
  do
  {
    citizenArray = Work->citizenArray;
    v13 = Allocate(ctnCitizen_t);
    _ctor(v13);
    *(Il2CppClass **)((char *)&citizenArray->obj.klass + v9) = v13;
    v11 = *(s64 *)((char *)&Work->citizenArray->obj.klass + v9);
    v9 += 8;
    *(u32 *)(v11 + 92) = v8++;
    *(u32 *)(v11 + 32) = 0;
  }
  while (v9 != 2080);
  for (i = 32; i != 544; i += 8)
  {
    objectArray = Work->objectArray;
    v19 = Allocate(ctnObject_t);
    v20 = NewSpecific(f32, 2u);
    v19[1].klass = v20;
    _ctor(v19, 0);
    *(Il2CppClass **)((char *)&objectArray->obj.klass + i) = v19;
  }
  v22 = Work;
  timeSliceNum = v22->timeSliceNum;
  timeSliceNum[0] = 0;
  timeSliceNum[1] = 0;
  timeSliceNum[2] = 0;
  timeSliceNum[3] = 0;
  timeSliceNum[4] = 0;
  timeSliceNum[5] = 0;
  v22->sliceIndex = 0;
}

// 0x18dcb90
static void InitFromFile(s32 id, s32 floor) {
  u16 *v5;
  char *String_54864672;
  char *v7;
  char **v8;
  char *v9;
  char *v10;
  char *v11;
  void *Asset;
  sdfBinary *v16;
  s32 S32;
  sdfBinary *New;
  s64 v21;
  s64 v22;
  s64 v23;
  s64 v24;
  s64 v28;
  ctnCitizenData_t *v29;
  s64 v30;
  s64 v31;
  s64 v32;
  ctnCitizenData_t *v34;
  s32 v38;
  s32 v39;
  ctnWork_t *v41;
  ctnCitizenData_t *v42;
  s32 v44;
  s32 *friendIndex;
  s32 *v46;
  s32 *v47;
  s32 *v48;
  s32 *playerEvadeArray;
  s32 *v50;
  s32 *v51;
  s32 *v52;
  s32 *v53;
  s32 *v54;
  s32 *v55;
  s32 v56;
  s32 *objectEvadeArray;
  s32 *v58;
  s32 *v59;
  s32 *v60;
  s32 *v61;
  s32 *v62;
  s32 *v63;
  s32 v64;
  s32 *aheadEvadeArray;
  s32 *v66;
  s32 *v67;
  s32 *v68;
  s32 *v69;
  s32 *v70;
  s32 *v71;
  f32 v72;
  u32 *v;
  u32 v76;
  s32 v77;
  u32 v78;
  s32 v79;
  s32 v80;
  s64 exitIndex;
  s32 v82;
  s32 *v83;
  s64 v84;
  s64 v85;
  ctnWork_t *v86;
  s64 v87;
  s32 v88;
  __int128 v89;
  ctnCitizen_t *v90;
  u8 v91;
  u8 v93;
  s64 v94;
  s64 v95;
  u64 v96;
  s32 v97;
  ctnWork_t *v98;
  ctnCitizen_t *pFriends;
  ctnCitizen_t *v100;
  u32 *v101;
  s32 *v102;
  u32 *v103;
  s32 *v104;
  u32 *v105;
  s32 *v106;
  s64 v107;
  s64 v108;
  s64 v109;
  void *v110;
  f32 spd;
  ctnCitizen_t *citizenArray;
  Il2CppClass **v114;
  s64 v115;
  s64 v116;
  f32 v117;
  f32 v118;
  s32 v119;
  s32 v120;
  ctnGrid_t *Grid;
  s32 index;
  s64 i;
  s64 v127;
  s64 v128;
  s64 v129;
  s32 MaxMobCount;
  s32 OneRouteMaxMobCount;
  s64 v132;
  bool IsValidNewMobSystem;
  s32 v134;

  v134 = id;
  v5 = NewSpecific(char, 0x80u);
  String_54864672 = CreateString_54864672(0, v5, 0);
  if (id == 3)
  {
    if (floor == 1)
    {
      v8 = &"MAP03_01.CTZ";
    }
    else
    {
      v7 = String_54864672;
      if (floor)
        goto LABEL_10;
      v8 = &"MAP03_00.CTZ";
    }
    v7 = *v8;
  }
  else
  {
    v9 = ToString_55996800((s32)&v134, "d2", 0);
    v7 = Concat_54831728("MAP", v9, ".CTZ", 0);
  }
LABEL_10:
  v10 = ToString_55996800((s32)&v134, "d2", 0);
  v11 = Concat_54766928("fld_", v10, 0);
  if (IsLoad(Dependent, v11, 0))
  {
    goto LABEL_14;
  }
  Load(Dependent, v11, v11);
  LoadSyncAll(_Ctrl_k__BackingField, 0);
LABEL_14:
  Asset = LoadAsset(_Ctrl_k__BackingField, v11, v7, 0);
  v16 = Allocate(sdfBinary);
  _ctor(v16, Asset, 0);
  Work->citizenNum = ReadS32(v16, 0);
  S32 = ReadS32(v16, 0);
  New = GetNew(v16, 1, S32, 0);
  IsValidNewMobSystem = IsValidNewMobSystem();
  if (IsValidNewMobSystem)
  {
    v21 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldMobManager__get_Instance__ + 4);
    if ((*(u16 *)(v21 + 309) & 1) == 0)
      v21 = sub_42269C(v21);
    v22 = *(u64 *)(*(u64 *)(v21 + 192) + 16);
    if ((*(u16 *)(v22 + 309) & 1) == 0)
      v22 = sub_42269C(v22);
    OneRouteMaxMobCount = GetOneRouteMaxMobCount(**(void ***)(v22 + 184), 0);
    v23 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldMobManager__get_Instance__ + 4);
    if ((*(u16 *)(v23 + 309) & 1) == 0)
      v23 = sub_42269C(v23);
    v24 = *(u64 *)(*(u64 *)(v23 + 192) + 16);
    if ((*(u16 *)(v24 + 309) & 1) == 0)
      v24 = sub_42269C(v24);
    MaxMobCount = GetMaxMobCount(**(void ***)(v24 + 184), 0);
  }
  else
  {
    MaxMobCount = 256;
    OneRouteMaxMobCount = 256;
  }
  v132 = NewSpecific(s32, Work->exitNum);
  v28 = NewSpecific(ctnCitizenData_t, Work->citizenNum);
  v29 = (v28 + 32);
  v30 = v28;
  v31 = 0;
  v32 = v28 + 32;
  while (1)
  {
    if (v31 >= Work->citizenNum)
      break;
    v34 = Allocate(ctnCitizenData_t);
    _ctor(v34);
    if (v34 && !QueryInterface(v34, *(void **)(*(u64 *)v30 + 64)))
    {
LABEL_46:
    }
    v29 = v34;
    ++v31;
    ++v29;
  }
  ReadS32(New, 0);
  ReadS32(New, 0);
  v38 = 0;
  v39 = 0;
  while (1)
  {
    v41 = Work;
    if (v38 >= v41->citizenNum)
      break;
    v42 = Allocate(ctnCitizenData_t);
    _ctor(v42);
    v42->rotateQuat = ReadVector4(New, 0);
    v42->fExist = ReadS32(New, 0);
    v42->x = ReadFloat(New, 0);
    v42->y = ReadFloat(New, 0);
    v42->vx = ReadFloat(New, 0);
    v42->vy = ReadFloat(New, 0);
    v42->targetVx = ReadFloat(New, 0);
    v42->targetVy = ReadFloat(New, 0);
    v42->vleng = ReadFloat(New, 0);
    v42->dirX = ReadFloat(New, 0);
    v42->dirY = ReadFloat(New, 0);
    v42->normalX = ReadFloat(New, 0);
    v42->normalY = ReadFloat(New, 0);
    v42->offCenter = ReadFloat(New, 0);
    v42->leftWallDist = ReadFloat(New, 0);
    v42->rightWallDist = ReadFloat(New, 0);
    v42->index = ReadS32(New, 0);
    v42->sliceIndex = ReadS32(New, 0);
    v42->attr = ReadS32(New, 0);
    v42->oldX = (f32)ReadS32(New, 0);
    v44 = ReadS32(New, 0);
    friendIndex = v42->friendIndex;
    v42->oldY = (f32)v44;
    friendIndex[0] = ReadS32(New, 0);
    v46 = v42->friendIndex;
    v46[1] = ReadS32(New, 0);
    v47 = v42->friendIndex;
    v47[2] = ReadS32(New, 0);
    v48 = v42->friendIndex;
    v48[3] = ReadS32(New, 0);
    playerEvadeArray = v42->playerEvadeArray;
    playerEvadeArray[0] = ReadS32(New, 0);
    v50 = v42->playerEvadeArray;
    v50[1] = ReadS32(New, 0);
    v51 = v42->playerEvadeArray;
    v51[2] = ReadS32(New, 0);
    v52 = v42->playerEvadeArray;
    v52[3] = ReadS32(New, 0);
    v53 = v42->playerEvadeArray;
    v53[4] = ReadS32(New, 0);
    v54 = v42->playerEvadeArray;
    v54[5] = ReadS32(New, 0);
    v55 = v42->playerEvadeArray;
    v55[6] = ReadS32(New, 0);
    v56 = ReadS32(New, 0);
    objectEvadeArray = v42->objectEvadeArray;
    v42->resv0 = v56;
    objectEvadeArray[0] = ReadS32(New, 0);
    v58 = v42->objectEvadeArray;
    v58[1] = ReadS32(New, 0);
    v59 = v42->objectEvadeArray;
    v59[2] = ReadS32(New, 0);
    v60 = v42->objectEvadeArray;
    v60[3] = ReadS32(New, 0);
    v61 = v42->objectEvadeArray;
    v61[4] = ReadS32(New, 0);
    v62 = v42->objectEvadeArray;
    v62[5] = ReadS32(New, 0);
    v63 = v42->objectEvadeArray;
    v63[6] = ReadS32(New, 0);
    v64 = ReadS32(New, 0);
    aheadEvadeArray = v42->aheadEvadeArray;
    v42->objectDir = v64;
    aheadEvadeArray[0] = ReadS32(New, 0);
    v66 = v42->aheadEvadeArray;
    v66[1] = ReadS32(New, 0);
    v67 = v42->aheadEvadeArray;
    v67[2] = ReadS32(New, 0);
    v68 = v42->aheadEvadeArray;
    v68[3] = ReadS32(New, 0);
    v69 = v42->aheadEvadeArray;
    v69[4] = ReadS32(New, 0);
    v70 = v42->aheadEvadeArray;
    v70[5] = ReadS32(New, 0);
    v71 = v42->aheadEvadeArray;
    v71[6] = ReadS32(New, 0);
    v42->spdType = ReadS32(New, 0);
    v42->dir = ReadS32(New, 0);
    v42->angle = ReadFloat(New, 0);
    v42->exitIndex = ReadU8(New, 0);
    v42->pathPref = ReadS8(New, 0);
    v42->classType = ReadU8(New, 0);
    v42->followType = ReadS8(New, 0);
    v42->friendNum = ReadU8(New, 0);
    v42->blockIndex = ReadU8(New, 0);
    v42->evadeType = ReadS8(New, 0);
    ReadS8(New, 0);
    if (v42->spdType)
      v72 = 1.45;
    else
      v72 = 1.0;
    v = sdfDefaultRandCB->v;
    v76 = v[0];
    v77 = *(u64 *)v >> 30;
    v78 = v[2];
    v79 = *(u64 *)&v[2] >> 31;
    v[2] = v[1];
    v[3] = v78;
    v80 = v79 ^ v77;
    v[0] = v80;
    v[1] = v76;
    v42->vleng = (f32)((f32)(v72 * (f32)(v80 % 50 + 990)) / 1000.0) / 60.0;
    if (IsValidNewMobSystem)
    {
      if (!v42->fExist)
        goto LABEL_48;
      exitIndex = v42->exitIndex;
      v82 = *(u32 *)(v132 + 4 * exitIndex + 32);
      if (v82 >= OneRouteMaxMobCount || v39 > MaxMobCount)
        goto LABEL_48;
      *(u32 *)(v132 + 32 + 4 * exitIndex) = v82 + 1;
      v83 = v42->friendIndex;
      if ((s32)v83->max_length >= 1)
        sub_188E3B0(v83, 255, 4 * (u32)v83->max_length);
      v42->friendNum = 0;
    }
    if (!QueryInterface(v42, *(void **)(*(u64 *)v30 + 64)))
      goto LABEL_46;
    v84 = 8 * v39;
    *(u64 *)(v30 + v84 + 32) = v42;
    ++v39;
LABEL_48:
    ++v38;
  }
  if (IsValidNewMobSystem)
  {
    v41 = Work;
    v41->citizenNum = v39;
  }
  v85 = 0;
  while (2)
  {
    v86 = Work;
    if (v85 < v86->citizenNum)
    {
      v87 = *(u64 *)(v30 + 8 * v85 + 32);
      v88 = *(u32 *)(v87 + 32);
      if (!v88)
        goto LABEL_77;
      goto LABEL_9001;
      if (!v88)
      {
LABEL_77:
        ++v85;
        continue;
      }
LABEL_9001:
      v89 = *(_OWORD *)(v87 + 36);
      v90 = v86->citizenArray[v85];
      v90->fExist = v88;
      *(_OWORD *)&v90->x = v89;
      *(_OWORD *)&v90->targetVx = *(_OWORD *)(v87 + 52);
      *(_OWORD *)&v90->dirY = *(_OWORD *)(v87 + 68);
      *(u64 *)&v90->index = *(u64 *)(v87 + 92);
      *(u64 *)&v89 = *(u64 *)(v87 + 84);
      v90->attr = *(u32 *)(v87 + 100);
      *(u64 *)&v90->leftWallDist = v89;
      *(u32 *)&v90->exitIndex = *(u32 *)(v87 + 172);
      v91 = *(u8 *)(v87 + 176);
      v90->pTargetInfo = 0;
      v90->friendNum = v91;
      v90->evadeType = *(u32 *)(v87 + 180);
      v90->blockIndex = -1;
      v90->pAhead = 0;
      v90->pBehind = 0;
      v90->pHeadOn = 0;
      if (!*(u8 *)(v87 + 176))
      {
        v93 = 0;
LABEL_100:
        v101 = *(u32 **)(v87 + 120);
        v90->friendNum = v93;
        v102 = v90->playerEvadeArray;
        v90->angle = *(f32 *)(v87 + 168);
        v102[0] = v101[8];
        v102[1] = v101[9];
        v102[2] = v101[10];
        v102[3] = v101[11];
        v102[4] = v101[12];
        v102[5] = v101[13];
        v103 = *(u32 **)(v87 + 136);
        v102[6] = v101[14];
        v90->resv0 = 0;
        v104 = v90->objectEvadeArray;
        v104[0] = v103[8];
        v104[1] = v103[9];
        v104[2] = v103[10];
        v104[3] = v103[11];
        v104[4] = v103[12];
        v104[5] = v103[13];
        v104[6] = v103[14];
        v105 = *(u32 **)(v87 + 152);
        v90->objectDir = *(u32 *)(v87 + 144);
        v106 = v90->aheadEvadeArray;
        v106[0] = v105[8];
        v106[1] = v105[9];
        v106[2] = v105[10];
        v106[3] = v105[11];
        v106[4] = v105[12];
        v106[5] = v105[13];
        v106[6] = v105[14];
        v107 = *(u64 *)(v87 + 160);
        v90->newModelID = -1;
        *(u64 *)&v90->spdType = v107;
        *(u64 *)&v90->oldX = *(u64 *)(v87 + 104);
        if (IsValidNewMobSystem)
        {
          v108 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldMobManager__get_Instance__ + 4);
          if ((*(u16 *)(v108 + 309) & 1) == 0)
            v108 = sub_42269C(v108);
          v109 = *(u64 *)(*(u64 *)(v108 + 192) + 16);
          if ((*(u16 *)(v109 + 309) & 1) == 0)
            v109 = sub_42269C(v109);
          v110 = ChoiceChara(**(void ***)(v109 + 184), 0);
          spd = v110->_spd;
          v90->newModelID = v110->_mdl_id;
          v90->vleng = CalcMobSpeed(spd, 0);
        }
        citizenArray = Work->citizenArray;
        v114 = &citizenArray->obj.klass + v85;
        v114[4] = v90;
        goto LABEL_77;
      }
      v93 = 0;
      v94 = 8;
      while (2)
      {
        v97 = *(u32 *)(*(u64 *)(v87 + 112) + 4 * v94);
        v98 = Work;
        if (v97 < v98->citizenNum)
        {
          pFriends = v90->pFriends;
          v100 = v98->citizenArray[*(s32 *)(*(u64 *)(v87 + 112) + 4 * v94)];
          if (!v100)
          v95 = (s64)pFriends + 8 * v93;
          *(u64 *)(v95 + 32) = v100;
          ++v93;
        }
        v96 = v94 - 7;
        ++v94;
        if (v96 >= *(u8 *)(v87 + 176))
          goto LABEL_100;
        continue;
      }
    }
    break;
  }
  v115 = 32;
  while (2)
  {
    v116 = *(s64 *)((char *)&Work->citizenArray->obj.klass + v115);
    if (*(u32 *)(v116 + 32) == 1 && (!*(u8 *)(v116 + 108) || (*(u8 *)(v116 + 100) & 0x10) != 0))
    {
      v118 = *(f32 *)(v116 + 36);
      v117 = *(f32 *)(v116 + 40);
      if (v118 == INFINITY)
        v119 = 0x80000000;
      else
        v119 = v118;
      if (v117 == INFINITY)
        v120 = 0x80000000;
      else
        v120 = v117;
      Grid = ctnGetGrid(v119, v120);
      index = Grid->pBlock->index;
      ++Grid->citizenNum;
      if (index != *(u8 *)(v116 + 109))
      {
        LeaveBlock(v116);
        EnterBlock(v116, Grid);
      }
      SetWallInfo(v116);
      *(f32 *)(v116 + 80) = *(f32 *)(v116 + 84) - *(f32 *)(v116 + 88);
    }
    v115 += 8;
    if (v115 != 2080)
      continue;
    break;
  }
  if (IsValidNewMobSystem())
  {
    for (i = 32; i != 2080; i += 8)
    {
      v127 = *(s64 *)((char *)&Work->citizenArray->obj.klass + i);
      if (*(u32 *)(v127 + 32) == 1)
      {
        v128 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldMobManager__get_Instance__ + 4);
        if ((*(u16 *)(v128 + 309) & 1) == 0)
          v128 = sub_42269C(v128);
        v129 = *(u64 *)(*(u64 *)(v128 + 192) + 16);
        if ((*(u16 *)(v129 + 309) & 1) == 0)
          v129 = sub_42269C(v129);
        AddMobCount(**(void ***)(v129 + 184), *(u8 *)(v127 + 104), 0);
      }
    }
  }
}

// 0x18ddef0
static void SetCitizenAttr(ctnCitizen_t *pCitizen, s32 attr) {
  pCitizen->attr |= attr;
}

// 0x18ddf00
static void RemoveCitizenAttr(ctnCitizen_t *pCitizen, s32 attr) {
  pCitizen->attr &= ~attr;
}

// 0x18ddf10
static void RotateVec(f32 *vx, f32 *vy, f32 rad) {
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;

  v7 = sub_188E3C0(vx, vy);
  v8 = sub_188E3D0(rad);
  v9 = (f32)(v7 * *vx) - (f32)(v8 * *vy);
  v10 = (f32)(v8 * *vx) + (f32)(v7 * *vy);
  *vx = v9;
  *vy = v10;
}

// 0x18ddf80
static f32 DotProduct(f32 x1, f32 y1, f32 x2, f32 y2) {
  return (f32)(x1 * x2) + (f32)(y1 * y2);
}

// 0x18ddf90
static f32 CrossProduct(f32 x1, f32 y1, f32 x2, f32 y2) {
  return (f32)(x1 * y2) - (f32)(y1 * x2);
}

// 0x18ddfa0
static void LeaveBlock(ctnCitizen_t *pCitizen) {
  s32 blockIndex;
  s64 belongIndex;
  ctnBlock_t *v6;
  s32 v7;
  ctnCitizen_t *v8;
  s64 v9;
  s64 v10;
  char v11;
  s64 v12;
  s64 v13;
  Il2CppClass *v14;

  blockIndex = pCitizen->blockIndex;
  if (blockIndex != 255)
  {
    blockIndex = pCitizen->blockIndex;
    belongIndex = pCitizen->belongIndex;
    v6 = Work->blockArray[blockIndex];
    v7 = v6->citizenNum - 1;
    if (v7 > (s32)belongIndex)
    {
      v8 = v6->pCitizen;
      v9 = belongIndex + 5;
      v10 = 8 * belongIndex + 32;
      do
      {
        v14 = *(&v8->obj.klass + v9);
        *(Il2CppClass **)((char *)&v8->obj.klass + v10) = v14;
        v11 = v9 - 5;
        v8 = v6->pCitizen;
        v12 = v9 - 4;
        ++v9;
        v7 = v6->citizenNum - 1;
        v13 = *(s64 *)((char *)&v8->obj.klass + v10);
        v10 += 8;
        *(u8 *)(v13 + 110) = v11;
      }
      while (v12 < v7);
    }
    v6->citizenNum = v7;
    v6->crowd = (f32)v7 / v6->area;
  }
}

// 0x18de0d0
static ctnCitizen_t *AddCitizen(void) {
  s64 i;
  ctnCitizen_t *v3;
  s64 v7;
  s32 v8;
  ctnCitizen_t *pFriends;
  s32 attr;
  u32 v14;
  s32 v15;
  s32 v16;
  u32 v17;
  s32 v18;
  s32 v19;
  u32 v20;
  ctnWork_t *Work_local;
  s64 v23;
  u32 v24;

  for (i = 0; i != 256; ++i)
  {
    if (Work->citizenArray[i]->fExist)
      continue;
    v7 = ctn_linkflag[i];
    if ((u32)v7 != 0xFFFF)
    {
      v8 = mdl_fadeflag[v7];
      if (v8 == 1)
        continue;
      if (v8 == 2)
        continue;
    }
    v3 = Work->citizenArray[i];
    if (v3->NgCount < 1)
      goto LABEL_25;
  }
  v3 = 0;
LABEL_25:
  pFriends = v3->pFriends;
  v3->fExist = 1;
  pFriends[0] = 0;
  *(u64 *)&v3->targetVx = 0;
  *(u64 *)&v3->vx = 0;
  attr = 0;
  v3->attr = 0;
  attr = v3->attr;
  v3->attr = attr | 0x80;
  v3->pAhead = 0;
  v3->pBehind = 0;
  v3->pHeadOn = 0;
  v3->evadeType = 0;
  *(u16 *)&v3->friendNum = -256;
  v3->vleng = 0.0;
  if (v14)
  {
    v15 = Work->timeSliceNum[0];
    if (v15 > 256)
      goto LABEL_29;
LABEL_32:
    v15 = Work->timeSliceNum[0];
LABEL_33:
    v16 = Work->timeSliceNum[1];
    if (v16 > v15)
      goto LABEL_34;
    v17 = 1;
    v15 = v16;
    goto LABEL_41;
  }
  else
  {
    v15 = Work->timeSliceNum[0];
    if (v15 <= 256)
      goto LABEL_32;
LABEL_29:
    v15 = 256;
    goto LABEL_33;
LABEL_34:
    v17 = 0;
  }
LABEL_41:
  if (Work->timeSliceNum[2] <= v15)
  {
    v17 = 2;
    v15 = Work->timeSliceNum[2];
LABEL_43:
    v18 = Work->timeSliceNum[3];
    if (v18 > v15)
      goto LABEL_44;
    v17 = 3;
    v15 = v18;
LABEL_45:
    v19 = Work->timeSliceNum[4];
    if (v19 > v15)
      goto LABEL_46;
    v17 = 4;
    v15 = v19;
LABEL_47:
    if (Work->timeSliceNum[5] > v15)
      goto LABEL_48;
    v17 = 5;
    v3->sliceIndex = 5;
    if (v24)
      goto LABEL_49;
LABEL_66:
    goto LABEL_49;
  }
  goto LABEL_43;
LABEL_44:
  goto LABEL_45;
LABEL_46:
  goto LABEL_47;
LABEL_48:
  v3->sliceIndex = v17;
  if (!v20)
    goto LABEL_66;
LABEL_49:
  Work_local = Work;
  v23 = (s64)Work_local->timeSliceNum + 4 * v17;
  ++*(u32 *)(v23 + 32);
  ++Work_local->citizenNum;
  return v3;
}

// 0x18de630
static void UpdateCitizenPos(ctnCitizen_t *pCitizen) {
  ctnCitizen_t *v6;
  f32 v7;
  f32 x;
  f32 y;
  s32 v12;
  s32 v13;
  ctnGrid_t *Grid;
  f32 v16;
  f32 v17;
  ctnGrid_t *v18;
  s32 v19;
  s32 v20;
  ctnGrid_t *v22;
  s32 index;
  f32 fy;
  f32 fx;

  *(u64 *)&pCitizen->oldX = *(u64 *)&pCitizen->x;
  ChkNg_MovePos1(pCitizen);
  if (pCitizen->friendNum)
  {
    if ((pCitizen->attr & 0x10) == 0)
    {
      v6 = pCitizen->pFriends[0];
      *(float32x2_t *)&pCitizen->x = vadd_f32(*(float32x2_t *)&pCitizen->x, *(float32x2_t *)&pCitizen->vx);
      *(u64 *)&pCitizen->dirX = *(u64 *)&v6->dirX;
      return;
    }
  }
  v7 = pCitizen->x + pCitizen->vx;
  fy = pCitizen->y + pCitizen->vy;
  fx = v7;
  ChkNg_MovePos2(pCitizen, &fx, &fy);
  x = pCitizen->x;
  y = pCitizen->y;
  if (x == INFINITY)
    v12 = 0x80000000;
  else
    v12 = x;
  if (y == INFINITY)
    v13 = 0x80000000;
  else
    v13 = y;
  Grid = ctnGetGrid(v12, v13);
  v17 = fy;
  v16 = fx;
  v18 = Grid;
  if (fx == INFINITY)
    v19 = 0x80000000;
  else
    v19 = fx;
  if (fy == INFINITY)
    v20 = 0x80000000;
  else
    v20 = fy;
  v22 = ctnGetGrid(v19, v20);
  if (!ctnCheckClose(fldGb->fieldID, fldGb->cut_idx, pCitizen) && v22 && v22->pBlock && ((pCitizen->attr & 0x20) != 0 || pCitizen->x != v16 || pCitizen->y != v17))
  {
    pCitizen->x = v16;
    pCitizen->y = v17;
    if (v18 != v22)
    {
      --v18->citizenNum;
      index = v22->pBlock->index;
      ++v22->citizenNum;
      if (index != pCitizen->blockIndex)
      {
        LeaveBlock(pCitizen);
        EnterBlock(pCitizen, v22);
      }
    }
    SetWallInfo(pCitizen);
    pCitizen->offCenter = pCitizen->leftWallDist - pCitizen->rightWallDist;
    return;
  }
  KillCitizen(pCitizen);
}

// 0x18df8c0
static void UpdateCitizenRotate(ctnCitizen_t *pCitizen) {
  f32 vx;
  f32 vy;
  bool v5;
  bool v6;
  long f64 v7;
  f32 v8;
  s64 v9;
  long f64 v10;
  s32 attr;
  _OWORD *p_m00;
  __int128 v14;
  __int128 v15;
  __int128 v16;
  ctnCitizen_t *p_fields;
  f32 v20;
  f32 v21;
  f32 angle;
  f32 i;
  f32 v25;
  sdfMatrix4_t v26;
  sdfVector4_t Row;

  vx = pCitizen->vx;
  if (vx >= 0.000005 || ((vy = pCitizen->vy, vy > -0.000005) ? (v5 = vx <= -0.000005) : (v5 = 1), !v5 ? (v6 = vy < 0.000005) : (v6 = 0), !v6))
  {
    if ((pCitizen->attr & 0x20) == 0)
    {
      v7 = sub_18E6660(0);
      v8 = *(f32 *)&v7;
      v10 = sub_18E6660(0, v9);
      attr = pCitizen->attr;
      if ((attr & 0x40) != 0)
      {
        if ((attr & 0x80) != 0)
          goto LABEL_14;
      }
      else
      {
        v20 = v8 - *(f32 *)&v10;
        v21 = v8 + *(f32 *)&v10;
        if (v20 < -3.1415927 || v20 > 3.1415927)
          v21 = v21 + -6.2831855;
        v8 = v21 * 0.5;
        if ((attr & 0x80) != 0)
        {
LABEL_14:
          pCitizen->angle = v8;
          goto LABEL_15;
        }
      }
      angle = pCitizen->angle;
      for (i = angle - v8; i < -3.1415927; i = i + 6.2831855)
        ;
      for (; i > 3.1415927; i = i + -6.2831855)
        ;
      v25 = 0.015707964;
      if (i <= 0.015707964)
      {
        v25 = i;
        if (i < -0.015707964)
          v25 = -0.015707964;
      }
      v8 = angle - v25;
      pCitizen->angle = angle - v25;
LABEL_15:
      p_m00 = &IdentityMatrix.m00;
      v14 = p_m00[2];
      v15 = p_m00[3];
      v16 = p_m00[1];
      *(_OWORD *)&v26.m00 = *p_m00;
      *(_OWORD *)&v26.m01 = v16;
      *(_OWORD *)&v26.m02 = v14;
      *(_OWORD *)&v26.m03 = v15;
      Row = GetRow(&v26, 1, 0);
      vct_A = Row;
      FromRotation(v8);
      p_fields = &pCitizen->fields;
      p_fields->rotateQuat = vct_A;
      return;
    }
  }
}

// 0x18df8b0
static void LeaveGrid(ctnCitizen_t *pCitizen, ctnGrid_t *pGrid) {
  --pGrid->citizenNum;
}

// 0x18ddde0
static void EnterGrid(ctnCitizen_t *pCitizen, ctnGrid_t *pGrid) {
  s32 index;

  index = pGrid->pBlock->index;
  ++pGrid->citizenNum;
  if (index != pCitizen->blockIndex)
  {
    LeaveBlock(pCitizen);
    EnterBlock(pCitizen, pGrid);
  }
}

// 0x18dde80
static void SetPositionInfo(ctnCitizen_t *pCitizen) {
  SetWallInfo(pCitizen);
  pCitizen->offCenter = pCitizen->leftWallDist - pCitizen->rightWallDist;
}

// 0x18e0020
static void UpdateCitizenVelocity(ctnCitizen_t *pCitizen) {
  f32 v3;
  f32 v4;
  f32 v5;
  f32 v8;
  f32 vy;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v14;

  v3 = pCitizen->targetVy - pCitizen->vy;
  v4 = pCitizen->targetVx - pCitizen->vx;
  v5 = sqrtf((f32)(v4 * v4) + (f32)(v3 * v3));
  if ((pCitizen->attr & 8) == 0)
    goto LABEL_10;
  if (Work->playerX != Work->playerOldX)
    goto LABEL_12;
  if (Work->playerY == Work->playerOldY)
  {
LABEL_10:
    v8 = pCitizen->vleng / 60.0;
    goto LABEL_13;
  }
LABEL_12:
  v8 = (f32)(pCitizen->vleng / 60.0) * 4.0;
LABEL_13:
  if (Equal(v5, 0.0, 0.00001, 0))
    return;
  if (IsValidNewMobSystem())
  {
    v8 = 3.4028235e+38;
  }
  else if (v8 < 0.0001)
  {
    return;
  }
  if (v5 <= v8)
  {
    v11 = pCitizen->targetVx * 1.3;
    v12 = pCitizen->targetVy * 1.3;
    if (VRF >= 3.0)
    {
      v14 = v11 + v11;
      v10 = v12 + v12;
    }
    else
    {
      v14 = v11 * VRF;
      v10 = v12 * VRF;
    }
    pCitizen->vx = v14;
  }
  else
  {
    vy = pCitizen->vy;
    pCitizen->vx = (f32)((f32)(v4 * v8) / v5) + pCitizen->vx;
    v10 = (f32)((f32)(v3 * v8) / v5) + vy;
  }
  pCitizen->vy = v10;
}

// 0x18e0220
static void UpdateTargetVelocity(ctnCitizen_t *pCitizen) {
  s32 attr;
  float32x2_t v6;
  s32 v9;
  s32 v10;
  s32 v11;
  ctnCitizen_t *pHeadOn;
  ctnCitizen_t *pAhead;
  s32 v14;
  float32x2_t v17;
  ctnExit_t *v18;
  float32x2_t v19;
  float32x2_t v20;
  int32x2_t v21;
  float32x2_t v22;
  int32x2_t v23;
  float32x2_t v24;
  f32 v25;
  float32x2_t v26;
  ctnExit_t *v27;
  f32 **vertex;
  float32x2_t v29;
  float32x2_t v30;
  float32x2_t v31;
  float32x2_t v32;
  float32x2_t v33;
  f32 v34;
  float32x2_t v35;
  int32x2_t v36;
  float32x2_t v37;
  float32x2_t v38;
  int32x2_t v39;
  s32 evadeType;
  s64 v43;
  ctnWork_t *v45;
  s32 v46;
  f32 v47;
  f32 leftWallDist;
  f32 v50;
  f32 rightWallDist;
  f32 v52;
  float32x2_t v53;
  float32x2_t v54;
  ctnCitizen_t *v55;
  float32x2_t v56;
  float32x2_t v57;
  float32x2_t v58;
  f32 v59;
  int32x2_t v60;
  int32x2_t v61;
  float32x2_t v62;
  float32x2_t v64;
  float32x2_t v65;
  float32x2_t v66;
  int32x2_t v67;
  float32x2_t v68;
  int32x2_t v69;
  f32 x;
  f32 y;
  ctnGrid_t *v72;
  s32 v73;
  float32x2_t v74;
  int32x2_t v75;
  f32 v76;
  s32 v77;
  int32x2_t v78;
  s32 pathPref;
  f32 v81;
  f32 v82;
  f32 v83;
  f32 v84;
  f32 v85;
  f32 v87;
  u64 v89;
  int32x2_t v90;
  u64 v91;
  f32 vleng;

  attr = pCitizen->attr;
  if ((attr & 1) == 0)
  {
    attr = pCitizen->attr;
    pCitizen->attr = attr & 0xFFFFFFDF;
    vleng = pCitizen->vleng;
    if (pCitizen->friendNum && (attr & 0x10) == 0)
    {
      MoveFollower(pCitizen);
      return;
    }
    v6.n64_u64[0] = *(u64 *)&pCitizen->dirX;
    if (!pCitizen->pTargetInfo)
      goto LABEL_29;
    if (Work->mapID != 2)
      goto LABEL_29;
    if ((u32)pCitizen->blockIndex - 1 <= 1 && pCitizen->pTargetInfo->blockIndex == 18)
    {
      if (Work->waitFlag == 1)
      {
        v9 = pCitizen->attr;
        pCitizen->targetVx = 0.0;
        pCitizen->targetVy = 0.0;
        v10 = v9 | 0x21;
        goto LABEL_113;
      }
    }
LABEL_29:
    v11 = pCitizen->attr;
    if ((v11 & 0x40) != 0)
    {
      if ((v11 & 0x20000000) != 0)
      {
        v27 = Work->exitArray[pCitizen->exitIndex];
        vertex = v27->vertex;
        v29.n64_u64[0] = *(u64 *)vertex[0];
        v30.n64_u64[0] = *(u64 *)vertex[1];
        v31.n64_u64[0] = vsub_f32(v29, v30).n64_u64[0];
        v32.n64_u64[0] = vmul_f32(v31, v31).n64_u64[0];
        if (vaddv_f32(v32) >= 5.0)
        {
          v33.n64_u64[0] = *(u64 *)v27->dir;
        }
        else
        {
          v32.n64_u32[1] = 1056964608;
          v33.n64_u64[0] = vsub_f32(vmul_f32(vadd_f32(v29, v30), (float32x2_t)0x3F0000003F000000LL), *(float32x2_t *)&pCitizen->x).n64_u64[0];
        }
        v32.n64_f32[0] = sqrtf(vaddv_f32(vmul_f32(v33, v33)));
        v89 = v32.n64_u64[0];
        v32.n64_u64[0] = v89;
        v34 = vleng;
        v35.n64_u64[0] = vdiv_f32(v33, vdup_lane_s32(v32, 0)).n64_u64[0];
        if (v32.n64_f32[0] < vleng)
          v34 = v32.n64_f32[0];
        v26.n64_u64[0] = vmul_n_f32(v35, v34).n64_u64[0];
        vleng = v34;
      }
      else
      {
        v17.n64_u64[0] = *(u64 *)&pCitizen->x;
        v18 = Work->exitArray[pCitizen->exitIndex];
        v19.n64_u64[0] = vmul_f32(vadd_f32(*(float32x2_t *)v18->vertex[0], *(float32x2_t *)v18->vertex[1]), (float32x2_t)0x3F0000003F000000LL).n64_u64[0];
        v20.n64_u64[0] = *(u64 *)v18->dir;
        v21.n64_u64[0] = vmul_f32(vsub_f32(v17, v19), v20).n64_u64[0];
        v22.n64_u64[0] = vsub_f32(vadd_f32(v19, vmul_n_f32(v20, vadd_f32(v21, vdup_lane_s32(v21, 1)).n64_f32[0])), v17).n64_u64[0];
        v23.n64_u64[0] = vmul_f32(v22, v22).n64_u64[0];
        v23.n64_f32[0] = sqrtf(vaddv_f32(v23));
        v24.n64_u64[0] = vdiv_f32(v22, vdup_lane_s32(v23, 0)).n64_u64[0];
        v25 = vleng;
        if (v23.n64_f32[0] < vleng)
          v25 = v23.n64_f32[0];
        v26.n64_u64[0] = vmul_n_f32(v24, v25).n64_u64[0];
        vleng = v25;
      }
      goto LABEL_81;
    }
    pHeadOn = pCitizen->pHeadOn;
    if (pHeadOn)
    {
      pAhead = pCitizen->pAhead;
      if (pAhead && pAhead->pHeadOn == pHeadOn)
      {
        evadeType = pAhead->evadeType;
      }
      else
      {
        v14 = pHeadOn->evadeType;
        if ((v14 | 2) == 3)
        {
          pCitizen->evadeType = v14;
          goto LABEL_63;
        }
        v36.n64_u64[0] = vrev64_s32(*(int32x2_t *)&pCitizen->dirX).n64_u64[0];
        v37.n64_u64[0] = *(u64 *)&pHeadOn->x;
        v38.n64_u64[0] = *(u64 *)&pCitizen->x;
        v39.n64_u64[0] = vmul_f32(vsub_f32(v37, v38), v36).n64_u64[0];
        if (vsub_f32(v39, vdup_lane_s32(v39, 1)).n64_f32[0] <= 0.0)
          evadeType = 1;
        else
          evadeType = 3;
      }
      pCitizen->evadeType = evadeType;
LABEL_63:
      EvadeObject(pCitizen);
      EvadePlayer(pCitizen);
      SetPref(pCitizen);
      if ((pCitizen->attr & 8) == 0)
        goto LABEL_70;
      v45 = Work;
      if (v45->playerX != v45->playerOldX)
        goto LABEL_71;
      v45 = Work;
      if (v45->playerY == v45->playerOldY)
LABEL_70:
        *(f32 *)&v46 = 0.12;
      else
LABEL_71:
        *(f32 *)&v46 = 0.33;
      v26.n64_u64[0] = vmul_n_f32(v6, vleng).n64_u64[0];
      v47 = *(f32 *)&v46;
      leftWallDist = pCitizen->leftWallDist;
      v90.n64_u64[0] = v26.n64_u64[0];
      if (leftWallDist < 0.35)
      {
LABEL_73:
        v50 = 3.1415927;
LABEL_80:
        v52 = v47 * v50;
        v87 = sub_188E3C0(ctn, v43);
        v53.n64_u64[0] = vmul_n_f32(vrev64_s32(v90), sub_188E3D0(v52)).n64_u64[0];
        v54.n64_u64[0] = vmul_n_f32(v90, v87).n64_u64[0];
        v26.n64_u32[0] = vsub_f32(v54, v53).n64_u32[0];
        v26.n64_u32[1] = vadd_f32(v54, v53).n64_u32[1];
        goto LABEL_81;
      }
      rightWallDist = pCitizen->rightWallDist;
      if (rightWallDist < 0.35)
      {
LABEL_77:
        v50 = -3.1415927;
        goto LABEL_80;
      }
      pathPref = pCitizen->pathPref;
      v26.n64_u64[0] = v90.n64_u64[0];
      v81 = (f32)((f32)(vleng * 6.0) + 0.5) + 0.2;
      v82 = leftWallDist + rightWallDist;
      switch (pathPref)
      {
        case 0:
          v83 = v82 / 6.0;
          v84 = 0.0;
          goto LABEL_127;
        case 1:
          v84 = v82 / 6.0;
          v85 = v84 + v84;
          goto LABEL_128;
        case 2:
          v84 = v82 / 3.0;
          goto LABEL_123;
        case 3:
          v84 = (f32)(v82 * 5.0) / 12.0;
          goto LABEL_126;
        case 4:
          v84 = v82 * 0.5;
LABEL_123:
          v85 = v84 + (f32)(v82 / 6.0);
          goto LABEL_128;
        case 5:
          v84 = (f32)(v82 / 6.0) + (f32)(v82 * 0.5);
          v85 = (f32)(v82 / 6.0) + v84;
          goto LABEL_128;
        case 6:
          v84 = (f32)(v82 / 3.0) + (f32)(v82 * 0.5);
LABEL_126:
          v83 = v82 / 6.0;
LABEL_127:
          v85 = v83 + v84;
LABEL_128:
          if (v85 >= leftWallDist && v84 <= leftWallDist)
            break;
          if (v84 > leftWallDist)
          {
LABEL_136:
            if (pCitizen->rightWallDist > v81)
              goto LABEL_73;
          }
          else if (pCitizen->leftWallDist > v81)
          {
            goto LABEL_77;
          }
          break;
        default:
          goto LABEL_136;
      }
LABEL_81:
      v55 = pCitizen->pAhead;
      if (!v55)
      {
LABEL_105:
        v76 = v26.n64_f32[1];
        v77 = pCitizen->attr;
        if ((v77 & 0x40) == 0)
        {
          v78.n64_u64[0] = vcltz_f32(vmul_f32(v26, *(float32x2_t *)&pCitizen->dirX)).n64_u64[0];
          if ((v78.n64_u8[0] & 1) != 0)
            v26.n64_f32[0] = 0.0;
          if ((v78.n64_u8[4] & 1) != 0)
            v76 = 0.0;
        }
        LODWORD(pCitizen->targetVx) = v26.n64_u32[0];
        pCitizen->targetVy = v76;
        v77 = pCitizen->attr;
        v10 = v77 | 1;
LABEL_113:
        pCitizen->attr = v10;
        return;
      }
      v56.n64_u64[0] = vsub_f32(*(float32x2_t *)&v55->x, *(float32x2_t *)&pCitizen->x).n64_u64[0];
      v57.n64_u64[0] = *(u64 *)&v55->targetVx;
      v91 = v26.n64_u64[0];
      v58.n64_u64[0] = vmul_f32(v56, v56).n64_u64[0];
      v59 = vaddv_f32(v58);
      if ((v55->attr & 0x20) == 0)
      {
        if (v59 < 4.0)
        {
          v60.n64_u64[0] = vmul_f32(v26, v56).n64_u64[0];
          v61.n64_u64[0] = vmul_f32(v56, v57).n64_u64[0];
          v62.n64_u64[0] = vadd_f32(vzip1_s32(v60, v61), vzip2_s32(v60, v61)).n64_u64[0];
          if (v62.n64_f32[1] > 0.0 && v62.n64_f32[0] > v62.n64_f32[1])
          {
            v64.n64_u64[0] = *(u64 *)&pCitizen->dirX;
            v65.n64_u64[0] = v64.n64_u64[0];
            v66.n64_u64[0] = *(u64 *)&v55->vx;
            v26.n64_u64[0] = v91;
            v65.n64_u64[0] = *(u64 *)&pCitizen->dirX;
            v67.n64_u64[0] = vmul_f32(v66, v64).n64_u64[0];
            v68.n64_u64[0] = *(u64 *)&pCitizen->normalX;
            v69.n64_u64[0] = vmul_f32(v26, v68).n64_u64[0];
            v26.n64_u64[0] = vadd_f32(vmul_n_f32(v65, vadd_f32(v67, vdup_lane_s32(v67, 1)).n64_f32[0]), vmul_n_f32(v68, vadd_f32(v69, vdup_lane_s32(v69, 1)).n64_f32[0])).n64_u64[0];
          }
        }
        goto LABEL_105;
      }
      x = v55->x;
      y = v55->y;
      v72 = FreeGridBeside(x, y, pCitizen);
      if (!v72 || pCitizen->friendNum || (v73 = pCitizen->attr, (v73 & 8) != 0))
      {
        v26.n64_u64[0] = v91;
        if (v59 <= 3.0)
        {
          v26.n64_u64[0] = 0;
          pCitizen->attr |= 0x20u;
        }
      }
      else
      {
        v74.n64_u64[0] = vadd_f32(vsub_f32(vcvt_f32_s32(*(int32x2_t *)&v72->x), *(float32x2_t *)&pCitizen->x), (float32x2_t)0x3F0000003F000000LL).n64_u64[0];
        v73 = pCitizen->attr;
        v75.n64_u64[0] = vmul_f32(v74, v74).n64_u64[0];
        pCitizen->attr = v73 | 4;
        v75.n64_f32[0] = sqrtf(vaddv_f32(v75));
        v26.n64_u64[0] = vmul_n_f32(vdiv_f32(v74, vdup_lane_s32(v75, 0)), vleng).n64_u64[0];
      }
      goto LABEL_105;
    }
    pCitizen->evadeType = 0;
    goto LABEL_63;
  }
}

// 0x18dfe70
static void SetWallInfo(ctnCitizen_t *pCitizen) {
  f32 *v3;
  f32 *v4;
  s64 v6;
  f32 y;
  f32 x;
  s32 v9;
  s32 v10;
  ctnBlock_t *pBlock;
  ctnTargetInfo_t *pTargetInfo;
  f32 v13;
  f32 v14;
  s64 leftWallIndex;
  f32 **vertex;
  f32 **normal;
  f32 *v19;
  f32 *v20;
  f32 v21;
  f32 v22;
  f32 v23;
  f32 v24;
  s64 rightWallIndex;
  f32 *v26;
  f32 *v27;
  f32 v28;
  f32 v29;

  v3 = NewSpecific(f32, 2u);
  v4 = NewSpecific(f32, 2u);
  if (pCitizen->pTargetInfo)
  {
    v6 = v4;
    x = pCitizen->x;
    y = pCitizen->y;
    if (x == INFINITY)
      v9 = 0x80000000;
    else
      v9 = x;
    if (y == INFINITY)
      v10 = 0x80000000;
    else
      v10 = y;
    pBlock = ctnGetGrid(v9, v10)->pBlock;
    if (pBlock)
    {
      pTargetInfo = pCitizen->pTargetInfo;
      v14 = pCitizen->x;
      v13 = pCitizen->y;
      leftWallIndex = pTargetInfo->leftWallIndex;
      vertex = pBlock->vertex;
      normal = pBlock->normal;
      v19 = vertex[leftWallIndex];
      v20 = normal[leftWallIndex];
      v21 = v19[0] - v14;
      v3[0] = v21;
      v22 = v19[1] - v13;
      v3[1] = v22;
      v24 = v20[0];
      v23 = v20[1];
      pTargetInfo = pCitizen->pTargetInfo;
      vertex = pBlock->vertex;
      normal = pBlock->normal;
      rightWallIndex = pTargetInfo->rightWallIndex;
      v26 = vertex[rightWallIndex];
      v27 = normal[rightWallIndex];
      pCitizen->leftWallDist = -(f32)((f32)(v21 * v24) + (f32)(v22 * v23));
      v28 = v26[0] - v14;
      *(f32 *)(v6 + 32) = v28;
      v29 = v26[1] - v13;
      *(f32 *)(v6 + 36) = v29;
      pCitizen->rightWallDist = -(f32)((f32)(v28 * v27[0]) + (f32)(v29 * v27[1]));
    }
  }
}

// 0x18e2110
static void SetPlayerWallDist(ctnCitizen_t *pCitizen, f32 *leftWallDist, f32 *rightWallDist) {
  f32 v8;

  v8 = vaddv_f32(vmul_f32(vsub_f32(*(float32x2_t *)&Work->playerX, *(float32x2_t *)&pCitizen->x), *(float32x2_t *)&pCitizen->normalX));
  *leftWallDist = pCitizen->leftWallDist + v8;
  *rightWallDist = pCitizen->rightWallDist - v8;
}

// 0x18e21c0
static void SetObjectWallDist(ctnCitizen_t *pCitizen, ctnObject_t *pObject, f32 *leftWallDist, f32 *rightWallDist) {
  float32x2_t v9;
  float32x2_t v10;
  float32x2_t v11;
  f32 v12;

  v9.n64_u64[0] = *(u64 *)&pCitizen->x;
  v10.n64_u64[0] = *(u64 *)&pCitizen->normalX;
  v11.n64_u64[0] = *(u64 *)pObject->center;
  v12 = vaddv_f32(vmul_f32(vsub_f32(v11, v9), v10));
  *leftWallDist = v12 + pCitizen->leftWallDist;
  *rightWallDist = pCitizen->rightWallDist - v12;
}

// 0x18e2280
static void SetCitizenWallDist(ctnCitizen_t *pCitizen, ctnCitizen_t *pOther, f32 *leftWallDist, f32 *rightWallDist) {
  float32x2_t v9;
  float32x2_t v10;
  float32x2_t v11;
  f32 v12;

  v9.n64_u64[0] = *(u64 *)&pOther->x;
  v10.n64_u64[0] = *(u64 *)&pCitizen->x;
  v11.n64_u64[0] = *(u64 *)&pCitizen->normalX;
  v12 = vaddv_f32(vmul_f32(vsub_f32(v9, v10), v11));
  *leftWallDist = v12 + pCitizen->leftWallDist;
  *rightWallDist = pCitizen->rightWallDist - v12;
}

// 0x18e2330
static ctnBlock_t *GetBlock(ctnCitizen_t *pCitizen) {
  s32 blockIndex;

  blockIndex = pCitizen->blockIndex;
  if (blockIndex == 255)
    return 0;
  blockIndex = pCitizen->blockIndex;
  return Work->blockArray[blockIndex];
}

// 0x18e23c0
static ctnTargetInfo_t *ChooseTarget(ctnCitizen_t *pCitizen, s32 prevBlockIndex) {
  ctnBlock_t *v6;
  s64 connectNum;
  ctnTargetInfo_t *v9;
  s64 m_Items;
  f32 crowd;
  ctnBlock_t *v12;

  v6 = Work->blockArray[pCitizen->blockIndex];
  connectNum = (u32)v6->connectNum;
  if ((s32)connectNum < 1)
    return 0;
  v9 = 0;
  m_Items = v6->targetInfo;
  crowd = 100000.0;
  do
  {
    v12 = Work->blockArray[*(s32 *)(*(u64 *)m_Items + 32)];
    if (v12->dist[pCitizen->exitIndex] < v6->dist[pCitizen->exitIndex] && v12->crowd < crowd)
    {
      crowd = v12->crowd;
      v9 = *(ctnTargetInfo_t *)m_Items;
    }
    m_Items += 8;
    --connectNum;
  }
  while (connectNum);
  return v9;
}

// 0x18e25f0
static void EvadePlayerAhead(ctnCitizen_t *pCitizen) {
  f32 v5;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;
  f32 v11;
  bool v12;
  bool v13;
  f32 v14;
  bool v15;
  bool v16;
  f32 v17;
  f32 v20;
  bool v21;
  bool v22;
  f32 v23;
  bool v24;
  f32 v25;
  bool v26;
  bool v27;
  f32 v28;
  f32 v29;
  bool v32;
  bool v33;
  f32 v34;
  bool v35;
  bool v36;
  f32 v37;
  f32 v40;
  bool v41;
  bool v42;

  v5 = vaddv_f32(vmul_f32(vsub_f32(*(float32x2_t *)&Work->playerX, *(float32x2_t *)&pCitizen->x), *(float32x2_t *)&pCitizen->normalX));
  v6 = pCitizen->leftWallDist + v5;
  v7 = v6 + (f32)(pCitizen->rightWallDist - v5);
  v8 = v6 + -0.5;
  v9 = v6 + 0.5;
  v10 = v7 / 6.0;
  if (v8 <= 0.0 && v9 >= 0.0 || ((v11 = v10 + 0.0, v8 <= (f32)(v10 + 0.0)) ? (v12 = v9 < v11) : (v12 = 1), !v12 || v8 >= 0.0 && v9 <= v11))
  {
    pCitizen->playerEvadeArray[0] = 0;
  }
  v13 = v8 > v10 || v9 < v10;
  if (v13 && ((v14 = v10 + v10, v8 <= (f32)(v10 + v10)) ? (v15 = v9 < v14) : (v15 = 1), v15 && (v8 >= v10 ? (v16 = v9 > v14) : (v16 = 1), v16)))
  {
    v17 = v7 / 3.0;
    if (v8 <= (f32)(v7 / 3.0) && v9 >= v17)
      goto LABEL_49;
  }
  else
  {
    pCitizen->playerEvadeArray[1] = 0;
    v17 = v7 / 3.0;
    if (v8 <= (f32)(v7 / 3.0) && v9 >= v17)
      goto LABEL_49;
  }
  v20 = v17 + v10;
  v21 = v8 > (f32)(v17 + v10) || v9 < v20;
  if (!v21 || (v8 >= v17 ? (v22 = v9 > v20) : (v22 = 1), !v22))
LABEL_49:
    pCitizen->playerEvadeArray[2] = 0;
  v23 = (f32)(v7 * 5.0) / 12.0;
  v24 = v8 > v23 || v9 < v23;
  if (v24 && ((v25 = v10 + v23, v8 <= (f32)(v10 + v23)) ? (v26 = v9 < v25) : (v26 = 1), v26 && (v8 >= v23 ? (v27 = v9 > v25) : (v27 = 1), v27)))
  {
    v28 = v7 * 0.5;
    v29 = v28 + v10;
    if (v8 <= v28 && v9 >= v28)
      goto LABEL_82;
  }
  else
  {
    pCitizen->playerEvadeArray[3] = 0;
    v28 = v7 * 0.5;
    v29 = v28 + v10;
    if (v8 <= v28 && v9 >= v28)
      goto LABEL_82;
  }
  v32 = v8 > v29 || v9 < v29;
  if (!v32 || v8 >= v28 && v9 <= v29)
LABEL_82:
    pCitizen->playerEvadeArray[4] = 0;
  v33 = v8 > v29 || v9 < v29;
  if (v33 && ((v34 = v10 + v29, v8 <= (f32)(v10 + v29)) ? (v35 = v9 < v34) : (v35 = 1), v35 && (v8 >= v29 ? (v36 = v9 > v34) : (v36 = 1), v36)))
  {
    v37 = v17 + v28;
    if (v8 <= v37 && v9 >= v37)
      goto LABEL_117;
  }
  else
  {
    pCitizen->playerEvadeArray[5] = 0;
    v37 = v17 + v28;
    if (v8 <= v37 && v9 >= v37)
      goto LABEL_117;
  }
  v40 = v10 + v37;
  v41 = v8 > v40 || v9 < v40;
  if (!v41 || (v8 >= v37 ? (v42 = v9 > v40) : (v42 = 1), !v42))
LABEL_117:
    pCitizen->playerEvadeArray[6] = 0;
}

// 0x18e1280
static void EvadePlayer(ctnCitizen_t *pCitizen) {
  s32 *playerEvadeArray;
  __int128 v4;
  ctnWork_t *v7;
  float32x2_t v8;
  float32x2_t v9;
  float32x2_t v10;
  int32x2_t v11;

  playerEvadeArray = pCitizen->playerEvadeArray;
  *(u64 *)&v4 = 0x100000001LL;
  *((u64 *)&v4 + 1) = 0x100000001LL;
  playerEvadeArray[6] = 1;
  *(_OWORD *)playerEvadeArray = v4;
  *(u64 *)&playerEvadeArray[4] = 0x100000001LL;
  pCitizen->attr &= ~8u;
  if (Work->mapID == 3)
  {
    if (!Work->floorID)
      return;
  }
  v7 = Work;
  if (!v7->fPlayer)
    return;
  v7 = Work;
  v8.n64_u64[0] = vsub_f32(*(float32x2_t *)&pCitizen->x, *(float32x2_t *)&v7->playerX).n64_u64[0];
  v9.n64_u64[0] = vmul_f32(v8, v8).n64_u64[0];
  if (vaddv_f32(v9) < 25.0)
  {
    v10.n64_u64[0] = vsub_f32(*(float32x2_t *)&pCitizen->oldX, *(float32x2_t *)&v7->playerOldX).n64_u64[0];
    v11.n64_u64[0] = vmul_f32(v10, v10).n64_u64[0];
    if ((vmvn_s8(vcge_f32(vadd_f32(v11, vdup_lane_s32(v11, 1)), vadd_f32(v9, vdup_lane_s32(v9, 1)))).n64_u8[0] & 1) == 0)
    {
      pCitizen->attr |= 8u;
      EvadePlayerAhead(pCitizen);
    }
  }
}

// 0x18e10a0
static void EvadeObject(ctnCitizen_t *pCitizen) {
  s32 *objectEvadeArray;
  __int128 v5;
  s64 i;
  ctnWork_t *v9;
  ctnObject_t *v10;
  f32 *center;
  f32 v12;
  f32 v13;
  f32 dirX;
  f32 dirY;

  objectEvadeArray = pCitizen->objectEvadeArray;
  *(u64 *)&v5 = 0x100000001LL;
  *((u64 *)&v5 + 1) = 0x100000001LL;
  objectEvadeArray[6] = 1;
  *(_OWORD *)objectEvadeArray = v5;
  *(u64 *)&objectEvadeArray[4] = 0x100000001LL;
  pCitizen->attr &= ~0x100u;
  if (Work->mapID != 3)
    goto LABEL_10;
  if (!Work->floorID)
    return;
  goto LABEL_10;
  if (Work->floorID)
  {
LABEL_10:
    for (i = 0; ; ++i)
    {
      v9 = Work;
      if (i >= v9->objectNum)
        return;
      v9 = Work;
      v10 = v9->objectArray[i];
      center = v10->center;
      v12 = center[1] - pCitizen->y;
      v13 = center[0] - pCitizen->x;
      if ((f32)((f32)(v13 * v13) + (f32)(v12 * v12)) < (f32)((f32)(v10->radius + 7.0) * (f32)(v10->radius + 7.0)))
      {
        dirX = pCitizen->dirX;
        dirY = pCitizen->dirY;
        if ((f32)((f32)(v13 * dirX) + (f32)(v12 * dirY)) <= 0.0)
          continue;
        EvadeObjectSub(pCitizen, v10);
        pCitizen->attr |= 0x100u;
      }
    }
  }
}

// 0x18e2bd0
static void EvadeAheadSub(ctnCitizen_t *pCitizen, ctnCitizen_t *pOther) {
  float32x2_t v7;
  float32x2_t v8;
  float32x2_t v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  bool v17;
  bool v18;
  f32 v19;
  bool v20;
  bool v21;
  f32 v22;
  f32 v25;
  bool v26;
  bool v27;
  f32 v28;
  bool v29;
  f32 v30;
  bool v31;
  bool v32;
  f32 v33;
  f32 v34;
  bool v35;
  bool v36;
  f32 v37;
  bool v38;
  bool v39;
  f32 v40;
  f32 v43;
  bool v44;
  bool v45;

  v7.n64_u64[0] = *(u64 *)&pOther->x;
  v8.n64_u64[0] = *(u64 *)&pCitizen->x;
  v9.n64_u64[0] = *(u64 *)&pCitizen->normalX;
  v10 = vaddv_f32(vmul_f32(vsub_f32(v7, v8), v9));
  v11 = v10 + pCitizen->leftWallDist;
  v12 = v11 + (f32)(pCitizen->rightWallDist - v10);
  v13 = v11 + -0.5;
  v14 = v11 + 0.5;
  v15 = v12 / 6.0;
  if (v13 <= 0.0 && v14 >= 0.0 || ((v16 = v15 + 0.0, v13 <= (f32)(v15 + 0.0)) ? (v17 = v14 < v16) : (v17 = 1), !v17 || v13 >= 0.0 && v14 <= v16))
  {
    pCitizen->aheadEvadeArray[0] = 0;
  }
  v18 = v13 > v15 || v14 < v15;
  if (v18 && ((v19 = v15 + v15, v13 <= (f32)(v15 + v15)) ? (v20 = v14 < v19) : (v20 = 1), v20 && (v13 >= v15 ? (v21 = v14 > v19) : (v21 = 1), v21)))
  {
    v22 = v12 / 3.0;
    if (v13 <= (f32)(v12 / 3.0) && v14 >= v22)
      goto LABEL_49;
  }
  else
  {
    pCitizen->aheadEvadeArray[1] = 0;
    v22 = v12 / 3.0;
    if (v13 <= (f32)(v12 / 3.0) && v14 >= v22)
      goto LABEL_49;
  }
  v25 = v22 + v15;
  v26 = v13 > (f32)(v22 + v15) || v14 < v25;
  if (!v26 || (v13 >= v22 ? (v27 = v14 > v25) : (v27 = 1), !v27))
LABEL_49:
    pCitizen->aheadEvadeArray[2] = 0;
  v28 = (f32)(v12 * 5.0) / 12.0;
  v29 = v13 > v28 || v14 < v28;
  if (!v29 || ((v30 = v15 + v28, v13 <= (f32)(v15 + v28)) ? (v31 = v14 < v30) : (v31 = 1), !v31 || (v13 >= v28 ? (v32 = v14 > v30) : (v32 = 1), !v32)))
  {
    pCitizen->aheadEvadeArray[3] = 0;
  }
  v33 = v12 * 0.5;
  v34 = v33 + v15;
  if (v13 <= v33 && v14 >= v33 || (v13 <= v34 ? (v35 = v14 < v34) : (v35 = 1), !v35 || v13 >= v33 && v14 <= v34))
    pCitizen->aheadEvadeArray[4] = 0;
  v36 = v13 > v34 || v14 < v34;
  if (v36 && ((v37 = v15 + v34, v13 <= (f32)(v15 + v34)) ? (v38 = v14 < v37) : (v38 = 1), v38 && (v13 >= v34 ? (v39 = v14 > v37) : (v39 = 1), v39)))
  {
    v40 = v22 + v33;
    if (v13 <= v40 && v14 >= v40)
      goto LABEL_109;
  }
  else
  {
    pCitizen->aheadEvadeArray[5] = 0;
    v40 = v22 + v33;
    if (v13 <= v40 && v14 >= v40)
      goto LABEL_109;
  }
  v43 = v15 + v40;
  v44 = v13 > v43 || v14 < v43;
  if (!v44 || (v13 >= v40 ? (v45 = v14 > v43) : (v45 = 1), !v45))
LABEL_109:
    pCitizen->aheadEvadeArray[6] = 0;
}

// 0x18e1410
static void SetPref(ctnCitizen_t *pCitizen) {
  f32 leftWallDist;
  f32 v4;
  f32 v6;
  f32 v7;
  u32 v8;
  f32 v10;
  int32x4_t *objectEvadeArray;
  s32 attr;
  s32 evadeType;
  s32 *aheadEvadeArray;
  s32 v15;
  s64 v16;
  int32x4_t *playerEvadeArray;
  int32x4_t v18;
  uint8x8_t v19;
  u32 v20;
  s32 v21;
  float32x2_t v23;
  s32 pathPref;
  f32 v25;
  int8x16_t v26;
  u32 v27;
  u32 v28;
  u32 v29;
  int32x4_t v30;
  uint8x8_t v31;
  u32 v32;
  s32 v33;
  int32x4_t v34;
  uint8x8_t v35;
  u32 v36;
  s32 v37;
  s64 v38;
  f32 v39;
  f32 v40;
  f32 v42;
  f32 v43;
  s32 v44;
  f32 v45;
  f32 v46;
  f32 v47;
  f32 v48;
  f32 v49;

  leftWallDist = pCitizen->leftWallDist;
  v4 = leftWallDist + pCitizen->rightWallDist;
  v6 = 6.0;
  v7 = v4 / 6.0;
  if (leftWallDist >= 0.0)
  {
    if ((f32)(v7 + 0.0) >= leftWallDist)
    {
      v8 = 0;
      goto LABEL_17;
    }
  }
  if (v7 > leftWallDist || (f32)(v7 + v7) < leftWallDist)
  {
    v10 = v4 / 3.0;
    if ((f32)(v4 / 3.0) > leftWallDist || (f32)(v10 + v7) < leftWallDist)
    {
      v25 = (f32)(v4 * 5.0) / 12.0;
      if (v25 > leftWallDist || (f32)(v7 + v25) < leftWallDist)
      {
        v39 = (f32)(v4 * 0.5) + v7;
        if ((f32)(v4 * 0.5) > leftWallDist || v39 < leftWallDist)
        {
          if (v39 > leftWallDist || (f32)(v7 + v39) < leftWallDist)
          {
            v40 = v10 + (f32)(v4 * 0.5);
            if ((f32)(v7 + v40) < leftWallDist || v40 > leftWallDist)
              v8 = 7;
            else
              v8 = 6;
          }
          else
          {
            v8 = 5;
          }
        }
        else
        {
          v8 = 4;
        }
      }
      else
      {
        v8 = 3;
      }
    }
    else
    {
      v8 = 2;
    }
  }
  else
  {
    v8 = 1;
  }
LABEL_17:
  objectEvadeArray = NewSpecific(s32, 7u);
  if (v4 < 1.2 || v8 == 7)
    return;
  attr = pCitizen->attr;
  pCitizen->pathPref = v8;
  if ((attr & 8) != 0)
  {
    playerEvadeArray = pCitizen->playerEvadeArray;
    if ((attr & 0x100) == 0)
    {
      objectEvadeArray = pCitizen->playerEvadeArray;
      v18 = vbicq_s8((int8x16_t)xmmword_3CFFD40, vceqzq_s32(playerEvadeArray[2]));
      v18.n128_u32[0] = vaddvq_s32(v18) & 0xF;
      v19.n64_u64[0] = vcnt_s8((int8x8_t)v18.n128_u64[0]).n64_u64[0];
      v19.n64_u16[0] = vaddlv_u8(v19);
      v20 = v19.n64_u32[0];
      if (playerEvadeArray[3].n128_u32[0])
        v20 = v19.n64_u32[0] + 1;
      if (playerEvadeArray[3].n128_u32[1])
        ++v20;
      if (playerEvadeArray[3].n128_u32[2])
        v21 = -1;
      else
        v21 = 0;
      if (v20 == v21)
      {
        v23.n64_u64[0] = *(u64 *)&pCitizen->normalX;
        pathPref = pCitizen->pathPref;
        if (vaddv_f32(vmul_f32(v23, vsub_f32(*(float32x2_t *)&Work->playerX, *(float32x2_t *)&pCitizen->x))) >= 0.0)
        {
          LOBYTE(v16) = pathPref - 1;
          if (pathPref < 1)
            return;
        }
        else
        {
          if (pathPref > 5)
            return;
          LOBYTE(v16) = pathPref + 1;
        }
        goto LABEL_130;
      }
      goto LABEL_84;
    }
    objectEvadeArray[2].n128_u32[0] = 1;
    if (!playerEvadeArray[2].n128_u32[0] || !pCitizen->objectEvadeArray[0])
      objectEvadeArray[2].n128_u32[0] = 0;
    objectEvadeArray[2].n128_u32[1] = 1;
    if (!playerEvadeArray[2].n128_u32[1] || !pCitizen->objectEvadeArray[1])
      objectEvadeArray[2].n128_u32[1] = 0;
    objectEvadeArray[2].n128_u32[2] = 1;
    if (!playerEvadeArray[2].n128_u32[2] || !pCitizen->objectEvadeArray[2])
      objectEvadeArray[2].n128_u32[2] = 0;
    objectEvadeArray[2].n128_u32[3] = 1;
    if (!playerEvadeArray[2].n128_u32[3] || !pCitizen->objectEvadeArray[3])
      objectEvadeArray[2].n128_u32[3] = 0;
    objectEvadeArray[3].n128_u32[0] = 1;
    if (!playerEvadeArray[3].n128_u32[0] || !pCitizen->objectEvadeArray[4])
      objectEvadeArray[3].n128_u32[0] = 0;
    objectEvadeArray[3].n128_u32[1] = 1;
    if (!playerEvadeArray[3].n128_u32[1] || !pCitizen->objectEvadeArray[5])
      objectEvadeArray[3].n128_u32[1] = 0;
    objectEvadeArray[3].n128_u32[2] = 1;
    if (!playerEvadeArray[3].n128_u32[2] || !pCitizen->objectEvadeArray[6])
      objectEvadeArray[3].n128_u32[2] = 0;
    v26 = vceqzq_s32(playerEvadeArray[2]);
    v27 = playerEvadeArray[3].n128_u32[0];
    v28 = playerEvadeArray[3].n128_u32[1];
    v29 = playerEvadeArray[3].n128_u32[2];
    v30 = vbicq_s8((int8x16_t)xmmword_3CFFD40, v26);
    v30.n128_u32[0] = vaddvq_s32(v30) & 0xF;
    v31.n64_u64[0] = vcnt_s8((int8x8_t)v30.n128_u64[0]).n64_u64[0];
    v31.n64_u16[0] = vaddlv_u8(v31);
    v32 = v31.n64_u32[0];
    if (v27)
      v32 = v31.n64_u32[0] + 1;
    if (v28)
      ++v32;
    if (v29)
      v33 = -1;
    else
      v33 = 0;
    if (v32 != v33)
      goto LABEL_84;
LABEL_73:
    objectEvadeArray = pCitizen->objectEvadeArray;
    v34 = vbicq_s8((int8x16_t)xmmword_3CFFD40, vceqzq_s32(objectEvadeArray[2]));
    v34.n128_u32[0] = vaddvq_s32(v34) & 0xF;
    v35.n64_u64[0] = vcnt_s8((int8x8_t)v34.n128_u64[0]).n64_u64[0];
    v35.n64_u16[0] = vaddlv_u8(v35);
    v36 = v35.n64_u32[0];
    if (objectEvadeArray[3].n128_u32[0])
      v36 = v35.n64_u32[0] + 1;
    if (objectEvadeArray[3].n128_u32[1])
      ++v36;
    if (objectEvadeArray[3].n128_u32[2])
      v37 = -1;
    else
      v37 = 0;
    if (v36 == v37)
    {
      if (pCitizen->objectDir < 0)
        goto LABEL_117;
LABEL_82:
      if (!(u8)v8)
        return;
      LOBYTE(v16) = v8 - 1;
      goto LABEL_130;
    }
LABEL_84:
    v38 = v8;
    if (pCitizen->evadeType == 1)
    {
      if (objectEvadeArray[2].n128_u32[v8])
        goto LABEL_129;
      if (v8)
      {
        LOBYTE(v16) = v8 - 1;
        if (objectEvadeArray[1].n128_u32[v8 + 3])
          goto LABEL_130;
        LODWORD(v16) = v8 - 2;
        if (v8 >= 2)
        {
          if (objectEvadeArray[2].n128_u32[(u32)v16])
            goto LABEL_130;
          LODWORD(v16) = v8 - 3;
          if (v8 >= 3)
          {
            if (objectEvadeArray[2].n128_u32[(u32)v16])
              goto LABEL_130;
            LODWORD(v16) = v8 - 4;
            if (v8 >= 4)
            {
              if (objectEvadeArray[2].n128_u32[(u32)v16])
                goto LABEL_130;
              LODWORD(v16) = v8 - 5;
              if (v8 >= 5)
              {
                if (objectEvadeArray[2].n128_u32[(u32)v16])
                  goto LABEL_130;
                LODWORD(v16) = v8 - 6;
                if (v8 >= 6)
                {
                  if (objectEvadeArray[2].n128_u32[(u32)v16])
                    goto LABEL_130;
                }
              }
            }
          }
        }
      }
      while (!objectEvadeArray[2].n128_u32[v38])
      {
        if (++v38 == 7)
          return;
      }
    }
    else
    {
      while (!objectEvadeArray[2].n128_u32[v38])
      {
        if (++v38 == 7)
        {
          if (objectEvadeArray[2].n128_u32[v8])
            goto LABEL_129;
          if (v8)
          {
            LOBYTE(v16) = v8 - 1;
            if (objectEvadeArray[1].n128_u32[v8 + 3])
              goto LABEL_130;
            LODWORD(v16) = v8 - 2;
            if (v8 >= 2)
            {
              if (objectEvadeArray[2].n128_u32[(u32)v16])
                goto LABEL_130;
              LODWORD(v16) = v8 - 3;
              if (v8 >= 3)
              {
                if (objectEvadeArray[2].n128_u32[(u32)v16])
                  goto LABEL_130;
                LODWORD(v16) = v8 - 4;
                if (v8 >= 4)
                {
                  if (objectEvadeArray[2].n128_u32[(u32)v16])
                    goto LABEL_130;
                  LODWORD(v16) = v8 - 5;
                  if (v8 >= 5)
                  {
                    if (objectEvadeArray[2].n128_u32[(u32)v16])
                      goto LABEL_130;
                    LODWORD(v16) = v8 - 6;
                    if (v8 >= 6)
                    {
                      if (objectEvadeArray[2].n128_u32[(u32)v16])
                        goto LABEL_130;
                    }
                  }
                }
              }
            }
          }
          return;
        }
      }
    }
    LOBYTE(v16) = v38;
    goto LABEL_130;
  }
  if ((attr & 0x100) != 0)
    goto LABEL_73;
  evadeType = pCitizen->evadeType;
  if (evadeType == 1)
    goto LABEL_82;
  if (evadeType)
  {
LABEL_117:
    if ((u8)v8 > 5u)
      return;
    LOBYTE(v16) = v8 + 1;
    goto LABEL_130;
  }
  aheadEvadeArray = pCitizen->aheadEvadeArray;
  v15 = aheadEvadeArray[v8];
  if (v8 <= 3)
  {
    if (v15 == 1)
    {
      LOBYTE(v16) = v8;
LABEL_130:
      pCitizen->pathPref = v16;
      return;
    }
    v16 = v8 + 1;
    if (v8 != 3)
    {
      if (aheadEvadeArray[v16] == 1)
        goto LABEL_130;
      v16 = v8 + 2;
      if (v8 != 2)
      {
        if (aheadEvadeArray[v16] == 1)
          goto LABEL_130;
        v16 = v8 + 3;
        if (v8 != 1 && aheadEvadeArray[v16] == 1)
          goto LABEL_130;
      }
    }
    goto LABEL_150;
  }
  if (v15 == 1)
  {
LABEL_129:
    LOBYTE(v16) = v8;
    goto LABEL_130;
  }
  LOBYTE(v16) = v8 - 1;
  if (aheadEvadeArray[v8 - 1] == 1)
    goto LABEL_130;
  if (v8 >= 5)
  {
    LOBYTE(v16) = v8 - 2;
    if (aheadEvadeArray[v8 - 2] == 1)
      goto LABEL_130;
    if (v8 >= 6)
    {
      LOBYTE(v16) = v8 - 3;
      if (*((u32 *)&aheadEvadeArray->bounds + v8 + 1) == 1)
        goto LABEL_130;
    }
  }
LABEL_150:
  v42 = v8;
  if (aheadEvadeArray[0] == 1 && (v43 = vabds_f32(0.0, v42), v43 < 100.0))
  {
    v44 = v43;
    pCitizen->pathPref = 0;
    if (v43 == INFINITY)
      v44 = 0x80000000;
  }
  else
  {
    v44 = 100;
  }
  if (aheadEvadeArray[1] == 1)
  {
    v45 = vabds_f32(1.0, v42);
    if (v45 < (f32)v44)
    {
      v44 = v45;
      if (v45 == INFINITY)
        v44 = 0x80000000;
      pCitizen->pathPref = 1;
    }
  }
  if (aheadEvadeArray[2] == 1)
  {
    v46 = vabds_f32(2.0, v42);
    if (v46 < (f32)v44)
    {
      v44 = v46;
      if (v46 == INFINITY)
        v44 = 0x80000000;
      pCitizen->pathPref = 2;
    }
  }
  if (aheadEvadeArray[3] == 1)
  {
    v47 = vabds_f32(3.0, v42);
    if (v47 < (f32)v44)
    {
      v44 = v47;
      if (v47 == INFINITY)
        v44 = 0x80000000;
      pCitizen->pathPref = 3;
    }
  }
  if (aheadEvadeArray[4] == 1)
  {
    v48 = vabds_f32(4.0, v42);
    if (v48 < (f32)v44)
    {
      v44 = v48;
      if (v48 == INFINITY)
        v44 = 0x80000000;
      pCitizen->pathPref = 4;
    }
  }
  if (aheadEvadeArray[5] == 1)
  {
    v49 = vabds_f32(5.0, v42);
    if (v49 < (f32)v44)
    {
      v44 = v49;
      if (v49 == INFINITY)
        v44 = 0x80000000;
      pCitizen->pathPref = 5;
    }
  }
  if (aheadEvadeArray[6] == 1 && vabds_f32(v6, v42) < (f32)v44)
  {
    LOBYTE(v16) = 6;
    goto LABEL_130;
  }
}

// 0x18e2ea0
static s32 GetPref(f32 leftWallDist, f32 h) {
  f32 v3;
  f32 v6;
  f32 v7;
  f32 v8;
  f32 v9;
  f32 v10;

  v3 = h / 6.0;
  if (leftWallDist >= 0.0 && (f32)(v3 + 0.0) >= leftWallDist)
    return 0;
  if (v3 <= leftWallDist && (f32)(v3 + v3) >= leftWallDist)
    return 1;
  v6 = h / 3.0;
  if ((f32)(h / 3.0) <= leftWallDist && (f32)(v6 + v3) >= leftWallDist)
    return 2;
  v7 = (f32)(h * 5.0) / 12.0;
  if (v7 <= leftWallDist && (f32)(v3 + v7) >= leftWallDist)
    return 3;
  v8 = h * 0.5;
  v9 = v8 + v3;
  if (v8 <= leftWallDist && v9 >= leftWallDist)
    return 4;
  if (v9 <= leftWallDist && (f32)(v3 + v9) >= leftWallDist)
    return 5;
  v10 = v6 + v8;
  if ((f32)(v3 + v10) < leftWallDist || v10 > leftWallDist)
    return 7;
  else
    return 6;
}

// 0x18e1d00
static s32 ComparePref(f32 leftWallDist, f32 h, s32 pathPref) {
  f32 v4;
  f32 v5;
  s32 result;
  f32 v7;

  switch (pathPref)
  {
    case 0:
      v4 = h / 6.0;
      v5 = 0.0;
      goto LABEL_12;
    case 1:
      v5 = h / 6.0;
      v7 = v5 + v5;
      goto LABEL_13;
    case 2:
      v5 = h / 3.0;
      goto LABEL_8;
    case 3:
      v5 = (f32)(h * 5.0) / 12.0;
      goto LABEL_11;
    case 4:
      v5 = h * 0.5;
LABEL_8:
      v7 = v5 + (f32)(h / 6.0);
      goto LABEL_13;
    case 5:
      v5 = (f32)(h / 6.0) + (f32)(h * 0.5);
      v7 = (f32)(h / 6.0) + v5;
      goto LABEL_13;
    case 6:
      v5 = (f32)(h / 3.0) + (f32)(h * 0.5);
LABEL_11:
      v4 = h / 6.0;
LABEL_12:
      v7 = v4 + v5;
LABEL_13:
      if (v7 < leftWallDist || v5 > leftWallDist)
      {
        if (v5 <= leftWallDist)
          result = 1;
        else
          result = -1;
      }
      else
      {
        result = 0;
      }
      break;
    default:
      result = -2;
      break;
  }
  return result;
}

// 0x18e0e40
static bool CheckWait(ctnCitizen_t *pCitizen) {
  if (!pCitizen->pTargetInfo)
    return 0;
  if (Work->mapID != 2)
    return 0;
  if ((u32)pCitizen->blockIndex - 1 > 1 || pCitizen->pTargetInfo->blockIndex != 18)
    return 0;
  if (Work->waitFlag == 1)
    return 1;
  return 0;
}

// 0x18e2f90
void ctnLoadDataIDFloor(s32 id, s32 floor) {
  char *v5;
  char *v6;
  char *v7;
  char *v9;
  s32 v10;
  s64 v12;
  s64 v13;
  s64 v14;
  f32 v15;
  s32 v16;
  ctnWork_t *v18;
  ctnObject_t *v19;
  s64 v20;
  s64 v21;
  s64 v22;
  f32 v23;
  s32 v24;
  ctnWork_t *v25;
  s64 v26;
  s64 v27;
  s64 v28;
  f32 v29;
  u32 v30;
  ctnWork_t *v31;
  s64 v32;
  s64 v33;
  s64 v34;
  f32 v35;
  u32 v36;
  ctnWork_t *v37;
  ctnWork_t *v38;
  s64 v40;
  s64 v41;
  s32 v42;
  s32 mapID;

  mapID = id;
  if (id == 3)
  {
    if (floor == 1)
    {
      v6 = "MAP03_01.CTN";
    }
    else if (floor)
    {
      v6 = 0;
    }
    else
    {
      v6 = "MAP03_00.CTN";
    }
  }
  else
  {
    v5 = ToString_55996800((s32)&mapID, "d2", 0);
    v6 = Concat_54831728("MAP", v5, ".CTN", 0);
  }
  v7 = ToString_55996800((s32)&mapID, "d2", 0);
  v9 = Concat_54766928("fld_", v7, 0);
  LoadDataSub(v6, v9);
  v10 = mapID;
  if (mapID == 2)
  {
    v12 = 0;
    while (1)
    {
      if (v12 >= Work->exitNum)
        break;
      v13 = (s64)Work->exitArray + 8 * v12++;
      v14 = *(u64 *)(v13 + 32);
      v15 = (f32)*(s32 *)(v14 + 44) + (f32)*(s32 *)(v14 + 44);
      v16 = v15;
      if (v15 == INFINITY)
        v16 = 0x80000000;
      *(u32 *)(v14 + 48) = v16;
    }
    v10 = mapID;
    goto LABEL_26;
  }
LABEL_26:
  if (!floor && v10 == 3)
  {
    v18 = Work;
    v18->objectNum = 1;
    v19 = v18->objectArray[0];
    *(u64 *)v19->center = 0x4100000041300000LL;
    v19->radius = 1.0;
    v20 = 0;
    while (1)
    {
      v25 = Work;
      if (v20 >= v25->exitNum)
        break;
      v25 = Work;
      v21 = (s64)v25->exitArray + 8 * v20++;
      v22 = *(u64 *)(v21 + 32);
      v23 = (f32)*(s32 *)(v22 + 44) * 1.5;
      v24 = v23;
      if (v23 == INFINITY)
        v24 = 0x80000000;
      *(u32 *)(v22 + 48) = v24;
    }
    v10 = mapID;
  }
  if (v10 == 4)
  {
    v26 = 0;
    while (1)
    {
      v31 = Work;
      if (v26 >= v31->exitNum)
        break;
      v31 = Work;
      v27 = (s64)v31->exitArray + 8 * v26++;
      v28 = *(u64 *)(v27 + 32);
      v29 = *(s32 *)(v28 + 44);
      v30 = vcvts_n_s32_f32(v29, 2u);
      if ((f32)(v29 * 4.0) == INFINITY)
        v30 = 0x80000000;
      *(u32 *)(v28 + 48) = v30;
    }
    v10 = mapID;
    goto LABEL_56;
  }
LABEL_56:
  if (v10 == 7)
  {
    v32 = 0;
    while (1)
    {
      v37 = Work;
      if (v32 >= v37->exitNum)
        break;
      v37 = Work;
      v33 = (s64)v37->exitArray + 8 * v32++;
      v34 = *(u64 *)(v33 + 32);
      v35 = *(s32 *)(v34 + 44);
      v36 = vcvts_n_s32_f32(v35, 4u);
      if ((f32)(v35 * 16.0) == INFINITY)
        v36 = 0x80000000;
      *(u32 *)(v34 + 48) = v36;
    }
  }
  v38 = Work;
  v38->mapID = mapID;
  v38->floorID = floor;
  if (IsNewMobSystem())
  {
    v40 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldMobManager__get_Instance__ + 4);
    if ((*(u16 *)(v40 + 309) & 1) == 0)
      v40 = sub_42269C(v40);
    v41 = *(u64 *)(*(u64 *)(v40 + 192) + 16);
    if ((*(u16 *)(v41 + 309) & 1) == 0)
      v41 = sub_42269C(v41);
    Load(**(void ***)(v41 + 184), mapID, floor);
  }
  v42 = mapID;
  InitFromFile(v42, floor);
}

// 0x18ddcc0
ctnGrid_t *ctnGetGrid(s32 x, s32 y) {
  ctnWork_t *Work_local;

  if (x < 0)
    return 0;
  if (y < 0)
    return 0;
  Work_local = Work;
  if (Work_local->xMax <= x)
    return 0;
  Work_local = Work;
  if (Work_local->yMax <= y)
    return 0;
  Work_local = Work;
  return *(&Work_local->pGrid[x] + Work_local->xMax * y);
}

// 0x18e3600
void ctnMemFree(void) {
  ctnWork_t *Work_local;
  ctnWork_t *v3;
  ctnWork_t *v4;

  Work_local = Work;
  if (!Work_local->blockArray)
  {
    goto LABEL_5;
  }
  Work_local = Work;
  Work_local->blockArray = 0;
LABEL_5:
  v3 = Work;
  if (!v3->gridData)
  {
    goto LABEL_7;
  }
  v3 = Work;
  v3->gridData = 0;
LABEL_7:
  v4 = Work;
  if (!v4->pGrid)
  {
    goto LABEL_9;
  }
  v4 = Work;
  v4->pGrid = 0;
LABEL_9:
  if (!Work)
    return;
  Work = 0;
}

// 0x18e37e0
static void KillCitizenFriend(ctnCitizen_t *pCitizen) {
  s64 v5;
  s64 v6;

  pCitizen->fExist = 0;
  --Work->citizenNum;
  pCitizen->NgCount = 2;
  if (IsValidNewMobSystem())
  {
    v5 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldMobManager__get_Instance__ + 4);
    if ((*(u16 *)(v5 + 309) & 1) == 0)
      v5 = sub_42269C(v5);
    v6 = *(u64 *)(*(u64 *)(v5 + 192) + 16);
    if ((*(u16 *)(v6 + 309) & 1) == 0)
      v6 = sub_42269C(v6);
    RemoveMobCount(**(void ***)(v6 + 184), pCitizen->exitIndex, 0);
  }
}

// 0x18df6f0
static void KillCitizen(ctnCitizen_t *pCitizen) {
  s32 friendNum;
  u64 v5;
  ctnCitizen_t *v6;
  u64 v7;
  ctnCitizen_t *m_Items;
  ctnCitizen_t *v9;
  f32 y;
  f32 x;
  s32 v12;
  s32 v13;
  ctnGrid_t *Grid;
  s64 v16;
  s64 v17;

  pCitizen->NgCount = 2;
  friendNum = pCitizen->friendNum;
  pCitizen->fExist = 0;
  if (friendNum)
  {
    if ((pCitizen->attr & 0x10) == 0)
      goto LABEL_10;
    v5 = 0;
    do
    {
      v6 = pCitizen->pFriends[v5];
      KillCitizenFriend(v6);
      ++v5;
    }
    while (v5 < pCitizen->friendNum);
    if (pCitizen->friendNum)
    {
LABEL_10:
      v7 = 0;
      m_Items = pCitizen->pFriends;
      do
      {
        v9 = m_Items[v7++];
        v9->friendNum = 0;
      }
      while (v7 < pCitizen->friendNum);
    }
  }
  x = pCitizen->x;
  y = pCitizen->y;
  if (x == INFINITY)
    v12 = 0x80000000;
  else
    v12 = x;
  if (y == INFINITY)
    v13 = 0x80000000;
  else
    v13 = y;
  Grid = ctnGetGrid(v12, v13);
  --Grid->citizenNum;
  LeaveBlock(pCitizen);
  --Work->citizenNum;
  if (IsValidNewMobSystem())
  {
    v16 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldMobManager__get_Instance__ + 4);
    if ((*(u16 *)(v16 + 309) & 1) == 0)
      v16 = sub_42269C(v16);
    v17 = *(u64 *)(*(u64 *)(v16 + 192) + 16);
    if ((*(u16 *)(v17 + 309) & 1) == 0)
      v17 = sub_42269C(v17);
    RemoveMobCount(**(void ***)(v17 + 184), pCitizen->exitIndex, 0);
  }
}

// 0x18e38d0
static ctnCitizen_t *FindAheadList(ctnCitizen_t *pCitizen, f32 maxDist, s32 citizenNum, ctnCitizen_t *ctnList) {
  f32 v9;
  s64 v10;
  f32 dirX;
  f32 dirY;
  ctnCitizen_t *v13;
  s64 v14;
  ctnCitizen_t *v15;
  s64 friendNum;
  ctnCitizen_t *m_Items;
  f32 v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  f32 v23;
  bool v24;
  f32 v25;
  char v26;
  f32 v28;

  if (citizenNum >= 1)
  {
    v9 = -1.0;
    v10 = 0;
    dirX = pCitizen->dirX;
    dirY = pCitizen->dirY;
    v13 = 0;
    v14 = citizenNum;
    v28 = 10000.0;
    while (1)
    {
      v15 = ctnList[v10];
      if (v15 != pCitizen)
      {
        friendNum = pCitizen->friendNum;
        if (pCitizen->friendNum)
        {
          m_Items = pCitizen->pFriends;
          while (v15 != m_Items)
          {
            ++m_Items;
            if (!--friendNum)
              goto LABEL_11;
          }
          goto LABEL_5;
        }
LABEL_11:
        v18 = v15->y - pCitizen->y;
        v19 = v15->x - pCitizen->x;
        v20 = sqrtf((f32)(v19 * v19) + (f32)(v18 * v18)) + v9;
        if (v20 <= maxDist)
        {
          v21 = v15->dirX;
          v22 = v15->dirY;
          if ((f32)((f32)(dirX * v21) + (f32)(dirY * v22)) < 0.8)
            goto LABEL_5;
          if ((f32)((f32)(dirX * v19) + (f32)(dirY * v18)) > 0.0)
          {
            EvadeAheadSub(pCitizen, v15);
            v9 = -1.0;
            v23 = pCitizen->leftWallDist - v15->rightWallDist;
            if (v23 >= -1.0)
            {
              v24 = v23 <= 1.0;
              v25 = v28;
              v26 = v24;
              if (((u8)v26 & (v20 < v28)) != 0)
              {
                v25 = v20;
                v13 = v15;
              }
              v28 = v25;
            }
          }
        }
      }
LABEL_5:
      if (++v10 == v14)
        return v13;
    }
  }
  return 0;
}

// 0x18e3b10
static ctnCitizen_t *FindAhead(ctnCitizen_t *pCitizen, f32 maxDist) {
  s32 *aheadEvadeArray;
  __int128 v7;
  f32 dirX;
  f32 dirY;
  f32 x;
  f32 y;
  ctnBlock_t *v13;
  ctnCitizen_t *result;
  s32 v16;
  s32 v17;
  s32 v18;
  ctnBlock_t *v20;
  f32 v21;
  s32 citizenNum;
  ctnCitizen_t *v23;

  aheadEvadeArray = pCitizen->aheadEvadeArray;
  *(u64 *)&v7 = 0x100000001LL;
  *((u64 *)&v7 + 1) = 0x100000001LL;
  aheadEvadeArray[6] = 1;
  *(_OWORD *)aheadEvadeArray = v7;
  dirX = pCitizen->dirX;
  dirY = pCitizen->dirY;
  x = pCitizen->x;
  y = pCitizen->y;
  *(u64 *)&aheadEvadeArray[4] = 0x100000001LL;
  v13 = Work->blockArray[pCitizen->blockIndex];
  result = FindAheadList(pCitizen, maxDist, v13->citizenNum, v13->pCitizen);
  if (!result)
  {
    if (maxDist <= 0.0)
    {
      return 0;
    }
    else
    {
      v16 = 1;
      while (1)
      {
        x = dirX + x;
        y = dirY + y;
        v17 = x == INFINITY ? 0x80000000 : (s32)x;
        v18 = y == INFINITY ? 0x80000000 : (s32)y;
        result = (ctnCitizen_t *)ctnGetGrid(v17, v18);
        if (!result)
          break;
        v20 = *(ctnBlock_t *)&result->rotateQuat.x;
        if (!v20)
          return 0;
        if (v13 != v20)
        {
          citizenNum = v20->citizenNum;
          v23 = v20->pCitizen;
          return FindAheadList(pCitizen, maxDist, citizenNum, v23);
        }
        v21 = (f32)v16++;
        if (v21 >= maxDist)
          return 0;
      }
    }
  }
  return result;
}

// 0x18e3cb0
static ctnCitizen_t *FindHeadOn(ctnCitizen_t *pCitizen, f32 maxDist, s32 citizenNum, ctnCitizen_t *ctnList) {
  s64 v7;
  f32 v9;
  f32 v10;
  ctnCitizen_t *v11;
  ctnCitizen_t *i;
  ctnCitizen_t *v13;
  float32x2_t v14;
  f32 v15;
  float32x2_t v16;
  float32x2_t v17;
  float32x2_t v18;
  float32x2_t v19;
  float32x2_t v20;
  f32 v21;

  LODWORD(v7) = citizenNum;
  if ((s32)v7 >= 1)
  {
    v9 = maxDist * maxDist;
    v10 = 10000.0;
    v11 = 0;
    v7 = (u32)v7;
    for (i = ctnList; ; ++i)
    {
      v13 = i;
      v14.n64_u64[0] = vsub_f32(*(float32x2_t *)&i->x, *(float32x2_t *)&pCitizen->x).n64_u64[0];
      v15 = vaddv_f32(vmul_f32(v14, v14));
      if (v15 > v9 || (v13->attr & 0x40) != 0)
        goto LABEL_5;
      v16.n64_u64[0] = *(u64 *)&pCitizen->dirX;
      v17.n64_u64[0] = *(u64 *)&v13->dirX;
      if (vaddv_f32(vmul_f32(v16, v17)) > -0.8)
        goto LABEL_5;
      v18.n64_u64[0] = *(u64 *)&v13->x;
      v19.n64_u64[0] = *(u64 *)&pCitizen->x;
      v20.n64_u64[0] = *(u64 *)&pCitizen->dirX;
      if (vaddv_f32(vmul_f32(vsub_f32(v18, v19), v20)) > 0.0)
      {
        v21 = pCitizen->leftWallDist - v13->rightWallDist;
        if (v21 >= -1.0 && v21 <= 1.0 && v15 < v10)
        {
          v10 = v15;
          v11 = v13;
        }
      }
LABEL_5:
      if (!--v7)
        return v11;
    }
  }
  return 0;
}

// 0x18e3e80
static void SetHeadOn(ctnCitizen_t *pCitizen, s32 maxDist) {
  float32x2_t v6;
  f32 v8;
  ctnBlock_t *v9;
  ctnCitizen_t *HeadOn;
  __int128 v12;
  bool v13;
  ctnCitizen_t *p_pHeadOn;
  ctnCitizen_t *v15;
  int8x8_t v16;
  __int128 v17;
  ctnGrid_t *Grid;
  ctnBlock_t *pBlock;
  s32 citizenNum;
  ctnCitizen_t *v22;
  __int128 v23;

  if ((pCitizen->attr & 0x40) != 0)
  {
    pCitizen->pHeadOn = 0;
    p_pHeadOn = &pCitizen->pHeadOn;
    v15 = 0;
LABEL_13:
  }
  else
  {
    v6.n64_u64[0] = *(u64 *)&pCitizen->dirX;
    v8 = maxDist;
    v9 = Work->blockArray[pCitizen->blockIndex];
    HeadOn = FindHeadOn(pCitizen, (f32)maxDist, v9->citizenNum, v9->pCitizen);
    pCitizen->pHeadOn = HeadOn;
    if (pCitizen->pHeadOn)
      v13 = 1;
    else
      v13 = maxDist < 1;
    if (!v13)
    {
      v16.n64_u64[0] = vbsl_s8(vceq_f32(v6, vdup_n_s32(0x7F800000u)), (int8x8_t)0x8000000080000000LL, vcvt_s32_f32(v6)).n64_u64[0];
      *(int8x8_t *)&v12 = vbsl_s8(vceq_f32(*(float32x2_t *)&pCitizen->x, vdup_n_s32(0x7F800000u)), (int8x8_t)0x8000000080000000LL, vcvt_s32_f32(*(float32x2_t *)&pCitizen->x));
      v23 = v12;
      do
      {
        *((u64 *)&v17 + 1) = *((u64 *)&v23 + 1);
        *(int32x2_t *)&v17 = vadd_s32(*(int32x2_t *)&v23, v16);
        v23 = v17;
        Grid = ctnGetGrid(v17, SDWORD1(v17));
        if (!Grid)
          break;
        pBlock = Grid->pBlock;
        if (!pBlock)
          break;
        if (v9 != pBlock)
        {
          citizenNum = pBlock->citizenNum;
          v22 = pBlock->pCitizen;
          v15 = FindHeadOn(pCitizen, v8, citizenNum, v22);
          pCitizen->pHeadOn = v15;
          p_pHeadOn = &pCitizen->pHeadOn;
          goto LABEL_13;
        }
        --maxDist;
      }
      while (maxDist);
    }
  }
}

// 0x18e4050
static void SimulateSetFlags(void) {
  bool IsValidNewMobSystem;
  s64 i;
  ctnCitizen_t *v7;
  s32 sliceIndex;
  f32 v10;
  ctnCitizen_t *Ahead;
  s64 v13;
  s64 v14;
  s64 v15;
  s64 v16;
  s32 v17;
  s64 v18;
  ctnWork_t *v19;
  ctnCitizen_t *v20;
  ctnExit_t *v21;
  f32 *dir;
  f32 **vertex;
  u32 friendNum;
  ctnCitizen_t *pFriends;
  s64 v26;
  s64 v27;
  s64 v30;
  ctnCitizen_t *v31;
  s64 v32;
  ctnCitizen_t *v33;
  ctnCitizen_t *v34;
  s64 v35;

  IsValidNewMobSystem = IsValidNewMobSystem();
  for (i = 0; i != 256; ++i)
  {
    while (1)
    {
      v7 = Work->citizenArray[i];
      if (!v7->fExist)
        break;
      if (IsValidNewMobSystem)
        goto LABEL_14;
      sliceIndex = v7->sliceIndex;
      if (sliceIndex == Work->sliceIndex)
        goto LABEL_14;
      goto LABEL_9000;
      if (sliceIndex == Work->sliceIndex)
      {
LABEL_14:
        if (!v7->friendNum || (v7->attr & 0x10) != 0)
        {
          v10 = 1.0;
          if (Work->blockArray[v7->blockIndex]->crowd >= 0.2)
            v10 = 3.0;
          Ahead = FindAhead(v7, v10);
          v7->pAhead = Ahead;
          if (Ahead)
          {
            Ahead->pBehind = v7;
          }
        }
        break;
      }
LABEL_9000:
      if (++i == 256)
        goto LABEL_40;
    }
  }
  if (IsValidNewMobSystem)
  {
    v13 = 32;
    while (1)
    {
      v14 = *(s64 *)((char *)&Work->citizenArray->obj.klass + v13);
      if (*(u32 *)(v14 + 32))
      {
        if (!*(u8 *)(v14 + 108) || (*(u8 *)(v14 + 100) & 0x10) != 0)
        {
          SetHeadOn(v14, 11);
        }
      }
      v13 += 8;
      if (v13 == 2080)
        goto LABEL_56;
    }
  }
LABEL_40:
  v15 = 32;
  while (2)
  {
    v16 = *(s64 *)((char *)&Work->citizenArray->obj.klass + v15);
    if (!*(u32 *)(v16 + 32))
      goto LABEL_44;
    v17 = *(u32 *)(v16 + 96);
    if (v17 != Work->sliceIndex)
      goto LABEL_44;
    if (!*(u8 *)(v16 + 108) || (*(u8 *)(v16 + 100) & 0x10) != 0)
    {
      SetHeadOn(v16, 11);
    }
LABEL_44:
    v15 += 8;
    if (v15 != 2080)
      continue;
    break;
  }
LABEL_56:
  v18 = 0;
  while (2)
  {
    v19 = Work;
    v20 = v19->citizenArray[v18];
    if (v20->fExist && (v20->attr & 0x40) != 0)
    {
      v19 = Work;
      v21 = v19->exitArray[v20->exitIndex];
      vertex = v21->vertex;
      dir = v21->dir;
      if ((f32)((f32)((f32)((f32)(v20->x - vertex[0][0]) * dir[1]) - (f32)((f32)(v20->y - vertex[0][1]) * dir[0])) * (f32)((f32)(dir[1] * (f32)(v20->x - vertex[1][0])) - (f32)(dir[0] * (f32)(v20->y - vertex[1][1])))) < 0.0)
      {
        v20->attr |= 0x20000000u;
        friendNum = v20->friendNum;
        if (!v20->friendNum)
          goto LABEL_57;
        pFriends = v20->pFriends;
        if (friendNum >= 4)
        {
          v30 = 0;
          v31 = &pFriends[3];
          do
          {
            v32 = *(v31 - 2);
            v30 -= 4;
            (*(v31 - 3))->attr |= 0x40u;
            *(u32 *)(v32 + 100) |= 0x40u;
            (*(v31 - 1))->attr |= 0x40u;
            v33 = v31;
            v31 += 4;
            v33->attr |= 0x40u;
          }
          while (-(s64)((u8)friendNum & 0xFC) != v30);
          v26 = -v30;
          v27 = friendNum & 3;
          if (v27)
            goto LABEL_80;
        }
        else
        {
          v26 = 0;
          v27 = friendNum & 3;
          if (!v27)
            goto LABEL_57;
LABEL_80:
          v34 = &pFriends[v26];
          do
          {
            v35 = (s64)*v34++;
            --v27;
            *(u32 *)(v35 + 100) |= 0x40u;
          }
          while (v27);
        }
      }
    }
LABEL_57:
    if (++v18 != 256)
      continue;
    break;
  }
}

// 0x18e1df0
static ctnGrid_t *FreeGridBeside(f32 ox, f32 oy, ctnCitizen_t *pCitizen) {
  f32 normalX;
  f32 normalY;
  s32 v10;
  s32 v11;
  ctnBlock_t *pBlock;
  f32 v13;
  f32 v14;
  f32 v15;
  ctnGrid_t *v17;
  f32 v18;
  ctnGrid_t *v19;
  s32 v20;
  s32 v21;
  ctnWork_t *Work_local;
  f32 v23;
  ctnGrid_t *v24;
  s32 v25;
  s32 v26;
  ctnWork_t *v27;

  normalX = pCitizen->normalX;
  normalY = pCitizen->normalY;
  if (ox == INFINITY)
    v10 = 0x80000000;
  else
    v10 = ox;
  if (oy == INFINITY)
    v11 = 0x80000000;
  else
    v11 = oy;
  pBlock = ctnGetGrid(v10, v11)->pBlock;
  v13 = 100000.0;
  v14 = oy;
  v15 = ox;
  v17 = 0;
LABEL_12:
  v18 = v13;
  v19 = v17;
  while (1)
  {
    v15 = v15 + normalX;
    v14 = v14 + normalY;
    if (v15 == INFINITY)
      v20 = 0x80000000;
    else
      v20 = v15;
    if (v14 == INFINITY)
      v21 = 0x80000000;
    else
      v21 = v14;
    if (v20 < 0)
      break;
    if (v21 < 0)
      break;
    Work_local = Work;
    if (Work_local->xMax <= v20)
      break;
    Work_local = Work;
    if (Work_local->yMax <= v21)
      break;
    Work_local = Work;
    v17 = *(&Work_local->pGrid[v20] + Work_local->xMax * v21);
    if (!v17 || v17->pBlock != pBlock)
      break;
    if (!v17->citizenNum)
    {
      v13 = (f32)((f32)(v15 - pCitizen->x) * (f32)(v15 - pCitizen->x))
          + (f32)((f32)(v14 - pCitizen->y) * (f32)(v14 - pCitizen->y));
      if (v13 < v18)
        goto LABEL_12;
    }
  }
LABEL_38:
  v23 = v18;
  v24 = v19;
  while (1)
  {
    ox = ox - normalX;
    oy = oy - normalY;
    if (ox == INFINITY)
      v25 = 0x80000000;
    else
      v25 = ox;
    if (oy == INFINITY)
      v26 = 0x80000000;
    else
      v26 = oy;
    if (v25 < 0)
      return v24;
    if (v26 < 0)
      return v24;
    v27 = Work;
    if (v27->xMax <= v25)
      return v24;
    v27 = Work;
    if (v27->yMax <= v26)
      return v24;
    v27 = Work;
    v19 = *(&v27->pGrid[v25] + v27->xMax * v26);
    if (!v19 || v19->pBlock != pBlock)
      return v24;
    if (!v19->citizenNum)
    {
      v18 = (f32)((f32)(ox - pCitizen->x) * (f32)(ox - pCitizen->x))
          + (f32)((f32)(oy - pCitizen->y) * (f32)(oy - pCitizen->y));
      if (v18 < v23)
        goto LABEL_38;
    }
  }
}

// 0x18e0f60
static void EvadeHeadOn(ctnCitizen_t *pCitizen) {
  ctnCitizen_t *pHeadOn;
  ctnCitizen_t *pAhead;
  s32 evadeType;
  float32x2_t v6;
  float32x2_t v7;
  int32x2_t v8;
  int32x2_t v9;

  pHeadOn = pCitizen->pHeadOn;
  if (!pHeadOn)
  {
    pCitizen->evadeType = 0;
    return;
  }
  pAhead = pCitizen->pAhead;
  if (pAhead && pAhead->pHeadOn == pHeadOn)
  {
    pCitizen->evadeType = pAhead->evadeType;
  }
  else
  {
    evadeType = pHeadOn->evadeType;
    if ((evadeType | 2) == 3)
    {
      pCitizen->evadeType = evadeType;
      return;
    }
    v6.n64_u64[0] = *(u64 *)&pHeadOn->x;
    v7.n64_u64[0] = *(u64 *)&pCitizen->x;
    v8.n64_u64[0] = vrev64_s32(*(int32x2_t *)&pCitizen->dirX).n64_u64[0];
    v9.n64_u64[0] = vmul_f32(vsub_f32(v6, v7), v8).n64_u64[0];
    if (vsub_f32(v9, vdup_lane_s32(v9, 1)).n64_f32[0] > 0.0)
    {
      pCitizen->evadeType = 3;
      return;
    }
    pCitizen->evadeType = 1;
  }
}

// 0x18e0a30
static void MoveFollower(ctnCitizen_t *pCitizen) {
  s64 friendNum;
  ctnCitizen_t *m_Items;
  ctnCitizen_t *v5;
  s32 attr;
  f32 v7;
  ctnCitizen_t *pHeadOn;
  s32 evadeType;
  int32x2_t v10;
  float32x2_t v12;
  int32x2_t v13;
  float32x2_t v14;
  f32 v15;
  u32 pathPref;
  u32 v18;
  f32 v20;
  f32 v21;
  float32x2_t v22;
  float32x2_t v23;
  u32 v24;
  float32x2_t v25;
  float32x2_t v26;
  u32 v27;
  float32x2_t v28;
  float32x2_t v29;
  u32 v36;
  u64 v37;
  u64 v38;
  u64 v39;
  u64 v40;
  f32 v41;
  f32 v42;
  f32 v43;
  f32 v44;

  friendNum = pCitizen->friendNum;
  if (pCitizen->friendNum)
  {
    m_Items = pCitizen->pFriends;
    while (1)
    {
      v5 = m_Items;
      if ((m_Items->attr & 0x10) != 0)
        break;
      ++m_Items;
      if (!--friendNum)
        goto LABEL_7;
    }
  }
  else
  {
LABEL_7:
    v5 = 0;
  }
  attr = v5->attr;
  if ((attr & 1) != 0 || (pCitizen->attr & 0x80) == 0)
  {
    v7 = sqrtf((f32)(v5->vx * v5->vx) + (f32)(v5->vy * v5->vy));
    if ((attr & 0x20) == 0)
      goto LABEL_18;
    goto LABEL_15;
  }
  UpdateTargetVelocity(v5);
  v7 = sqrtf((f32)(v5->targetVx * v5->targetVx) + (f32)(v5->targetVy * v5->targetVy));
  if ((v5->attr & 0x20) != 0)
  {
LABEL_15:
    pCitizen->attr |= 0x20u;
  }
LABEL_18:
  pHeadOn = v5->pHeadOn;
  evadeType = v5->evadeType;
  pCitizen->pHeadOn = pHeadOn;
  pCitizen->evadeType = evadeType;
  pCitizen->pathPref = v5->pathPref;
  if ((v5->attr & 8) != 0)
  {
    pCitizen->attr |= 8u;
    if ((v5->attr & 0x40) == 0)
      goto LABEL_29;
LABEL_21:
    v12.n64_u64[0] = *(u64 *)&v5->targetVx;
    v13.n64_u64[0] = vmul_f32(v12, v12).n64_u64[0];
    v13.n64_f32[0] = sqrtf(vaddv_f32(v13));
    v14.n64_u64[0] = vdiv_f32(v12, vdup_lane_s32(v13, 0)).n64_u64[0];
    v15 = v7 * 1.3;
    pathPref = v5->pathPref;
    if (pathPref < 3)
      goto LABEL_24;
LABEL_30:
    if (pathPref - 7 < 0xFFFFFFFD)
    {
      switch (pCitizen->followType)
      {
        case 0xFE:
          goto LABEL_48;
        case 0xFF:
          goto LABEL_42;
        case 1:
          goto LABEL_32;
        case 2:
          goto LABEL_35;
        default:
          goto LABEL_60;
      }
      goto LABEL_60;
    }
    if (v5->evadeType || (v5->attr & 8) != 0)
    {
      pCitizen->followType = -2;
LABEL_48:
      if ((v5->attr & 0x20) == 0)
      {
        if (!v24)
        {
          v39 = v14.n64_u64[0];
          v43 = v15;
          v14.n64_u64[0] = v39;
          v15 = v43;
        }
        v25.n64_u64[0] = vmul_f32(v14, (float32x2_t)0x3F3504F4BF3504F4LL).n64_u64[0];
        v26.n64_u64[0] = vrev64_s32(vmul_f32(v14, (float32x2_t)0x3F3504F2BF3504F2LL)).n64_u64[0];
        v14.n64_u32[0] = vadd_f32(v26, v25).n64_u32[0];
        v27 = vsub_f32(v26, v25).n64_u32[1];
        goto LABEL_59;
      }
      if (v24)
      {
LABEL_58:
        v28.n64_u64[0] = vrev64_s32(v14).n64_u64[0];
        v29.n64_u64[0] = vmul_f32(v14, vdup_n_s32(0x324CDE2Eu)).n64_u64[0];
        v14.n64_u32[0] = vadd_f32(v29, v28).n64_u32[0];
        v27 = vsub_f32(v29, v28).n64_u32[1];
LABEL_59:
        v14.n64_u32[1] = v27;
        goto LABEL_60;
      }
    }
    else
    {
      pCitizen->followType = -1;
LABEL_42:
      goto LABEL_58;
    }
    v40 = v14.n64_u64[0];
    v44 = v15;
    v14.n64_u64[0] = v40;
    v15 = v44;
    goto LABEL_58;
  }
  pCitizen->attr &= ~8u;
  if ((v5->attr & 0x40) == 0)
    goto LABEL_29;
  goto LABEL_21;
LABEL_29:
  v14.n64_u64[0] = *(u64 *)&v5->dirX;
  v15 = v7 * 1.3;
  pathPref = v5->pathPref;
  if (pathPref >= 3)
    goto LABEL_30;
LABEL_24:
  if (!v5->evadeType && (v5->attr & 8) == 0)
  {
    pCitizen->followType = 1;
LABEL_32:
    goto LABEL_46;
  }
  pCitizen->followType = 2;
LABEL_35:
  if ((v5->attr & 0x20) != 0)
  {
    if (v18)
    {
LABEL_46:
      v20 = -4.371139e-08 * v14.n64_f32[0];
      v21 = vmuls_lane_f32(4.371139e-08, v14, 1);
      v22.n64_u64[0] = vrev64_s32(v14).n64_u64[0];
      v23.n64_u32[1] = v22.n64_u32[1];
      v22.n64_f32[1] = v21;
      v23.n64_f32[0] = v20;
      v14.n64_u64[0] = vsub_f32(v23, v22).n64_u64[0];
      goto LABEL_60;
    }
    v38 = v14.n64_u64[0];
    v42 = v15;
    v14.n64_u64[0] = v38;
    v15 = v42;
    goto LABEL_46;
  }
  if (!v18)
  {
    v37 = v14.n64_u64[0];
    v41 = v15;
    v14.n64_u64[0] = v37;
    v15 = v41;
  }
  v10.n64_f32[0] = vmuls_lane_f32(0.70710677, v14, 1);
  v14.n64_u64[0] = vsub_f32(vmul_n_f32((float32x2_t)0x3F3504F3BF3504F3LL, v14.n64_f32[0]), vdup_lane_s32(v10, 0)).n64_u64[0];
LABEL_60:
  __asm { FMOV            V3.2S, #6.0 }
  *(float32x2_t *)&pCitizen->targetVx = vmul_n_f32(vsub_f32(vadd_f32(vmul_f32(v14, vdup_n_s32(0x3E99999Au)), vadd_f32(*(float32x2_t *)&v5->x, vmul_f32(*(float32x2_t *)&v5->vx, _D3))), *(float32x2_t *)&pCitizen->x), v15);
  if (!v36)
  pCitizen->attr |= 1u;
}

// 0x18e28c0
static void EvadeObjectSub(ctnCitizen_t *pCitizen, ctnObject_t *pObject) {
  f32 *center;
  f32 y;
  f32 x;
  f32 v9;
  f32 normalY;
  f32 normalX;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  f32 v17;
  f32 v18;
  f32 *v19;
  f32 radius;
  f32 v21;
  f32 v22;
  f32 v23;
  s32 v24;
  f32 v25;
  f32 v26;
  f32 v27;
  f32 v28;
  f32 v29;
  bool v30;
  bool v31;
  f32 v32;
  bool v33;
  bool v34;
  f32 v35;
  f32 v38;
  bool v39;
  bool v40;
  f32 v41;
  bool v42;
  f32 v43;
  bool v44;
  bool v45;
  f32 v46;
  f32 v47;
  bool v48;
  bool v49;
  f32 v50;
  bool v51;
  bool v52;
  f32 v53;
  f32 v56;
  bool v57;
  bool v58;

  center = pObject->center;
  x = pCitizen->x;
  y = pCitizen->y;
  v9 = y;
  normalX = pCitizen->normalX;
  normalY = pCitizen->normalY;
  v12 = normalY;
  v14 = center[0];
  v13 = center[1];
  v15 = x;
  v16 = normalX;
  v17 = v13;
  v18 = v14;
  v19 = pObject->center;
  v16 = pCitizen->normalX;
  v12 = pCitizen->normalY;
  v15 = pCitizen->x;
  v9 = pCitizen->y;
  v18 = v19[0];
  v17 = v19[1];
  radius = pObject->radius;
  v21 = (f32)((f32)(v14 - x) * normalX) + (f32)((f32)(v13 - y) * normalY);
  v22 = v21 + pCitizen->leftWallDist;
  v23 = pCitizen->rightWallDist - v21;
  if ((f32)((f32)(v16 * (f32)(v18 - v15)) + (f32)(v12 * (f32)(v17 - v9))) >= 0.0)
    v24 = 1;
  else
    v24 = -1;
  pCitizen->objectDir = v24;
  v25 = v22 + v23;
  v26 = v22 - radius;
  v27 = v22 + radius;
  v28 = v25 / 6.0;
  if (v26 <= 0.0 && v27 >= 0.0 || ((v29 = v28 + 0.0, v26 <= (f32)(v28 + 0.0)) ? (v30 = v27 < v29) : (v30 = 1), !v30 || v26 >= 0.0 && v27 <= v29))
  {
    pCitizen->objectEvadeArray[0] = 0;
  }
  v31 = v26 > v28 || v27 < v28;
  if (v31 && ((v32 = v28 + v28, v26 <= (f32)(v28 + v28)) ? (v33 = v27 < v32) : (v33 = 1), v33 && (v26 >= v28 ? (v34 = v27 > v32) : (v34 = 1), v34)))
  {
    v35 = v25 / 3.0;
    if (v26 <= (f32)(v25 / 3.0) && v27 >= v35)
      goto LABEL_54;
  }
  else
  {
    pCitizen->objectEvadeArray[1] = 0;
    v35 = v25 / 3.0;
    if (v26 <= (f32)(v25 / 3.0) && v27 >= v35)
      goto LABEL_54;
  }
  v38 = v35 + v28;
  v39 = v26 > (f32)(v35 + v28) || v27 < v38;
  if (!v39 || (v26 >= v35 ? (v40 = v27 > v38) : (v40 = 1), !v40))
LABEL_54:
    pCitizen->objectEvadeArray[2] = 0;
  v41 = (f32)(v25 * 5.0) / 12.0;
  v42 = v26 > v41 || v27 < v41;
  if (!v42 || ((v43 = v28 + v41, v26 <= (f32)(v28 + v41)) ? (v44 = v27 < v43) : (v44 = 1), !v44 || (v26 >= v41 ? (v45 = v27 > v43) : (v45 = 1), !v45)))
  {
    pCitizen->objectEvadeArray[3] = 0;
  }
  v46 = v25 * 0.5;
  v47 = v46 + v28;
  if (v26 <= v46 && v27 >= v46 || (v26 <= v47 ? (v48 = v27 < v47) : (v48 = 1), !v48 || v26 >= v46 && v27 <= v47))
    pCitizen->objectEvadeArray[4] = 0;
  v49 = v26 > v47 || v27 < v47;
  if (v49 && ((v50 = v28 + v47, v26 <= (f32)(v28 + v47)) ? (v51 = v27 < v50) : (v51 = 1), v51 && (v26 >= v47 ? (v52 = v27 > v50) : (v52 = 1), v52)))
  {
    v53 = v35 + v46;
    if (v26 <= v53 && v27 >= v53)
      goto LABEL_114;
  }
  else
  {
    pCitizen->objectEvadeArray[5] = 0;
    v53 = v35 + v46;
    if (v26 <= v53 && v27 >= v53)
      goto LABEL_114;
  }
  v56 = v28 + v53;
  v57 = v26 > v56 || v27 < v56;
  if (!v57 || (v26 >= v53 ? (v58 = v27 > v56) : (v58 = 1), !v58))
LABEL_114:
    pCitizen->objectEvadeArray[6] = 0;
}

// 0x18dfbf0
static void EnterBlock(ctnCitizen_t *pCitizen, ctnGrid_t *pGrid) {
  ctnBlock_t *pBlock;
  s64 citizenNum;
  u8 index;
  ctnCitizen_t *v8;
  Il2CppClass **v9;
  s32 v10;
  s64 exitIndex;
  s32 v14;
  s32 attr;
  f32 *dir;
  f32 v18;
  u32 friendNum;
  ctnCitizen_t *pFriends;
  s64 v21;
  ctnTargetInfo_t *v22;
  ctnTargetInfo_t *p_pTargetInfo;
  f32 *moveDir;
  f32 *moveNormal;
  Il2CppClass **v28;
  Il2CppClass *v29;
  Il2CppClass *v30;

  pBlock = pGrid->pBlock;
  citizenNum = pBlock->citizenNum;
  if ((u32)citizenNum == 63)
  {
    pCitizen->blockIndex = -1;
    KillCitizen(pCitizen);
  }
  else
  {
    index = pBlock->index;
    pCitizen->belongIndex = citizenNum;
    v8 = pBlock->pCitizen;
    pCitizen->blockIndex = index;
    pBlock->citizenNum = citizenNum + 1;
    v9 = &v8->obj.klass + citizenNum;
    v9[4] = pCitizen;
    exitIndex = pCitizen->exitIndex;
    v14 = pBlock->fExit[exitIndex];
    pBlock->crowd = (f32)pBlock->citizenNum / pBlock->area;
    if (v14)
    {
      exitIndex = pCitizen->exitIndex;
      attr = pCitizen->attr;
      dir = Work->exitArray[exitIndex]->dir;
      pCitizen->dirX = dir[0];
      v18 = dir[1];
      pCitizen->attr = attr | 0x40;
      friendNum = pCitizen->friendNum;
      pCitizen->dirY = v18;
      if (friendNum)
      {
        pFriends = pCitizen->pFriends;
        if (friendNum == 1)
        {
          v21 = 0;
        }
        else
        {
          v21 = 0;
          do
          {
            v28 = &pFriends->obj.klass + v21;
            v21 += 2;
            v30 = v28[4];
            v29 = v28[5];
            HIDWORD(v30->_1.generic_class) |= 0x40u;
            HIDWORD(v29->_1.generic_class) |= 0x40u;
          }
          while ((friendNum & 0xFE) != v21);
        }
        if ((friendNum & 1) != 0)
          pFriends[v21]->attr |= 0x40u;
      }
    }
    else
    {
      v22 = ChooseTarget(pCitizen, v10);
      pCitizen->pTargetInfo = v22;
      p_pTargetInfo = &pCitizen->pTargetInfo;
      moveDir = v22->moveDir;
      moveNormal = v22->moveNormal;
      *((u32 *)p_pTargetInfo - 14) = LODWORD(moveDir[0]);
      *((u32 *)p_pTargetInfo - 13) = LODWORD(moveDir[1]);
      *((u32 *)p_pTargetInfo - 12) = LODWORD(moveNormal[0]);
      *((u32 *)p_pTargetInfo - 11) = LODWORD(moveNormal[1]);
    }
  }
}

// 0x18e45a0
static f32 GetClassVelocity(ctnCitizen_t *pCitizen) {
  s32 spdType;
  f32 v5;
  u32 *v;
  u32 v7;
  s32 v8;
  u32 v9;
  s32 v10;
  s32 v11;

  spdType = pCitizen->spdType;
  v5 = 1.45;
  if (!spdType)
    v5 = 1.0;
  v = sdfDefaultRandCB->v;
  v7 = v[0];
  v8 = *(u64 *)v >> 30;
  v9 = v[2];
  v10 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v9;
  v11 = v10 ^ v8;
  v[0] = v11;
  v[1] = v7;
  return (f32)((f32)(v5 * (f32)(v11 % 200 + 900)) / 1000.0) / 60.0;
}

// 0x18e46f0
static void ShootCitizen(ctnExit_t *pExit) {
  ctnExitTable_t *v3;
  s64 v4;
  s64 v5;
  s64 v6;
  s64 v7;
  s64 v8;
  void *v9;
  s32 citizenNum;
  s32 curCnt;
  s64 v14;
  s32 v15;
  s32 v16;
  s32 *v17;
  s32 *v18;
  s32 popularity;
  u32 *v;
  u32 v25;
  s32 v26;
  u32 v27;
  s32 v28;
  u32 v29;
  s32 v30;
  s32 ExitIndex;
  s32 v32;
  ctnBlock_t *v34;
  s64 v35;
  ctnCitizen_t *pCitizen;
  s32 index_low;
  s64 v38;
  s32 v39;
  s32 v40;
  s32 v41;
  s32 v42;
  s32 v43;
  s32 v44;
  ctnCitizen_t *v45;
  s64 v46;
  s32 v47;
  ctnCitizen_t *v48;
  s32 v49;
  s32 v50;
  s32 v51;
  s64 v52;
  s64 v53;
  s64 v54;
  ctnCitizen_t *v55;
  s32 v56;
  ctnCitizen_t *v57;
  u32 *v62;
  u32 v63;
  s32 v64;
  u32 v65;
  s32 v66;
  u32 v67;
  f32 v68;
  s32 v69;
  s32 v70;
  ctnCitizen_t *v71;
  u32 *v78;
  u32 v79;
  u32 v80;
  s32 v81;
  s32 v82;
  u32 v83;
  s32 v84;
  char v85;
  bool v86;
  s32 v87;
  s32 v88;
  s32 v89;
  _BOOL4 v90;
  void *v91;
  f32 spd;
  u32 *v96;
  u32 v97;
  u32 v98;
  s32 v99;
  s32 v100;
  u32 v101;
  _BOOL4 v102;
  _BOOL4 IsValidNewMobSystem;
  bool v105;
  ctnCitizen_t *v108;
  u32 *v109;
  u32 v110;
  u32 v111;
  s32 v112;
  s32 v113;
  u32 v114;
  s32 v115;
  f32 **v116;
  s32 v117;
  s32 v118;
  bool v119;
  f32 *v120;
  f32 *v121;
  f32 v122;
  f32 v123;
  u32 *v128;
  u32 v129;
  u32 v130;
  s32 v131;
  s32 v132;
  u32 v133;
  s32 v134;
  ctnCitizen_t *v135;
  ctnCitizen_t *pFriends;
  ctnCitizen_t *v137;
  u8 classType;
  f32 v139;
  bool v140;
  f32 vleng;
  u8 v143;
  f32 **vertex;
  f32 v145;
  f32 v146;
  f32 *v147;
  f32 *v148;
  f32 *dir;
  f32 v151;
  ctnWork_t *v153;
  f32 v156;
  s32 v158;
  s32 v159;
  f32 v161;
  f32 y;
  f32 x;
  s32 v165;
  s32 v166;
  ctnGrid_t *Grid;
  s32 index;
  float32x2_t v173;
  f32 targetVy;
  f32 v175;
  char v176;
  f32 v177;
  f32 v178;
  f32 v179;
  f32 v180;
  f32 v181;
  s32 v182;
  s32 v183;
  s32 v184;
  s32 v185;
  s32 v186;
  s32 v187;
  s32 v188;
  s32 v189;
  s32 v190;
  s32 v191;

  v3 = NewSpecific(ctnExitTable_t, 0x10u);
  v4 = v3;
  if (*(s32 *)((char *)v3 + 24) >= 1)
  {
    v5 = 0;
    do
    {
      v6 = *(s32 *)((char *)v3 + 24);
      *(u64 *)((s64)&v3[0] + 8 * v5++) = 0;
    }
    while (v5 < v6);
  }
  v7 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldMobManager__get_Instance__ + 4);
  if ((*(u16 *)(v7 + 309) & 1) == 0)
  {
    v8 = *(u64 *)(*(u64 *)(sub_42269C(v7) + 192) + 16);
    if ((*(u16 *)(v8 + 309) & 1) != 0)
      goto LABEL_8;
LABEL_15:
    v9 = **(void ***)(sub_42269C(v8) + 184);
    if (IsValidNewMobSystem())
      goto LABEL_9;
    goto LABEL_16;
  }
  v8 = *(u64 *)(*(u64 *)(v7 + 192) + 16);
  if ((*(u16 *)(v8 + 309) & 1) == 0)
    goto LABEL_15;
LABEL_8:
  v9 = **(void ***)(v8 + 184);
  if (IsValidNewMobSystem())
  {
LABEL_9:
    citizenNum = Work->citizenNum;
    if (citizenNum >= GetMaxMobCount(v9, 0) || !CheckSpawnMob(v9, pExit, 0))
    {
      return;
    }
    goto LABEL_19;
  }
LABEL_16:
  curCnt = pExit->curCnt;
  if (curCnt)
  {
LABEL_71:
    pExit->curCnt = curCnt - 1;
    return;
  }
  if (Work->citizenNum < 253)
    goto LABEL_19;
  goto LABEL_70;
  if (Work->citizenNum >= 253)
  {
LABEL_70:
    curCnt = pExit->curCnt;
    goto LABEL_71;
  }
LABEL_19:
  v14 = 0;
  v15 = 0;
  v16 = 0;
  v17 = (v4 + 32);
  do
  {
    if (!Work->exitArray[v14])
      goto LABEL_21;
    if (pExit->group == -1)
    {
      if (Work->exitArray[v14]->group == -1)
        goto LABEL_21;
    }
    if (Work->mapID == 7)
    {
      if (Work->exitArray[v14]->group != pExit->group)
        goto LABEL_44;
      goto LABEL_21;
    }
    if (Work->exitArray[v14]->group == pExit->group)
      goto LABEL_44;
    if (Work->exitArray[v14]->group == -1 || pExit->group == -1)
    {
LABEL_44:
      if (Work->exitArray[v14]->blockIndex != pExit->blockIndex && v14 != pExit->index)
      {
        v18 = &v17[2 * v16++];
        popularity = Work->exitArray[v14]->popularity;
        v15 += popularity;
        *v18 = popularity;
        v18[1] = v14;
      }
    }
LABEL_21:
    ++v14;
  }
  while (v14 != 16);
  goto LABEL_52;
LABEL_53:
  goto LABEL_54;
LABEL_52:
  goto LABEL_53;
LABEL_54:
  v = sdfDefaultRandCB->v;
  v25 = v[0];
  v26 = *(u64 *)v >> 30;
  v27 = v[2];
  v28 = *(u64 *)&v[2] >> 31;
  v[2] = v[1];
  v[3] = v27;
  v29 = v28 ^ v26;
  v[0] = v29;
  v[1] = v25;
  v30 = (s32)(f32)v29 % v15;
  if (v30 >= *v17)
  {
    v32 = *(u32 *)(v4 + 40) + *v17;
    if (v30 >= v32)
    {
      v40 = *(u32 *)(v4 + 48) + v32;
      if (v30 >= v40)
      {
        v158 = *(u32 *)(v4 + 56) + v40;
        if (v30 >= v158)
        {
          v159 = *(u32 *)(v4 + 64) + v158;
          if (v30 >= v159)
          {
            v182 = *(u32 *)(v4 + 72) + v159;
            if (v30 >= v182)
            {
              v183 = *(u32 *)(v4 + 80) + v182;
              if (v30 >= v183)
              {
                v184 = *(u32 *)(v4 + 88) + v183;
                if (v30 >= v184)
                {
                  v185 = *(u32 *)(v4 + 96) + v184;
                  if (v30 >= v185)
                  {
                    v186 = *(u32 *)(v4 + 104) + v185;
                    if (v30 >= v186)
                    {
                      v187 = *(u32 *)(v4 + 112) + v186;
                      if (v30 >= v187)
                      {
                        v188 = *(u32 *)(v4 + 120) + v187;
                        if (v30 >= v188)
                        {
                          v189 = *(u32 *)(v4 + 128) + v188;
                          if (v30 >= v189)
                          {
                            v190 = *(u32 *)(v4 + 136) + v189;
                            if (v30 >= v190)
                            {
                              v191 = *(u32 *)(v4 + 144) + v190;
                              if (v30 >= v191)
                              {
                                if (v30 >= *(u32 *)(v4 + 152) + v191)
                                {
                                  ExitIndex = 0;
                                  if (!IsValidNewMobSystem())
                                    goto LABEL_60;
                                }
                                else
                                {
                                  ExitIndex = *(u8 *)(v4 + 156);
                                  if (!IsValidNewMobSystem())
                                    goto LABEL_60;
                                }
                              }
                              else
                              {
                                ExitIndex = *(u8 *)(v4 + 148);
                                if (!IsValidNewMobSystem())
                                  goto LABEL_60;
                              }
                            }
                            else
                            {
                              ExitIndex = *(u8 *)(v4 + 140);
                              if (!IsValidNewMobSystem())
                                goto LABEL_60;
                            }
                          }
                          else
                          {
                            ExitIndex = *(u8 *)(v4 + 132);
                            if (!IsValidNewMobSystem())
                              goto LABEL_60;
                          }
                        }
                        else
                        {
                          ExitIndex = *(u8 *)(v4 + 124);
                          if (!IsValidNewMobSystem())
                            goto LABEL_60;
                        }
                      }
                      else
                      {
                        ExitIndex = *(u8 *)(v4 + 116);
                        if (!IsValidNewMobSystem())
                          goto LABEL_60;
                      }
                    }
                    else
                    {
                      ExitIndex = *(u8 *)(v4 + 108);
                      if (!IsValidNewMobSystem())
                        goto LABEL_60;
                    }
                  }
                  else
                  {
                    ExitIndex = *(u8 *)(v4 + 100);
                    if (!IsValidNewMobSystem())
                      goto LABEL_60;
                  }
                }
                else
                {
                  ExitIndex = *(u8 *)(v4 + 92);
                  if (!IsValidNewMobSystem())
                    goto LABEL_60;
                }
              }
              else
              {
                ExitIndex = *(u8 *)(v4 + 84);
                if (!IsValidNewMobSystem())
                  goto LABEL_60;
              }
            }
            else
            {
              ExitIndex = *(u8 *)(v4 + 76);
              if (!IsValidNewMobSystem())
                goto LABEL_60;
            }
          }
          else
          {
            ExitIndex = *(u8 *)(v4 + 68);
            if (!IsValidNewMobSystem())
              goto LABEL_60;
          }
        }
        else
        {
          ExitIndex = *(u8 *)(v4 + 60);
          if (!IsValidNewMobSystem())
            goto LABEL_60;
        }
      }
      else
      {
        ExitIndex = *(u8 *)(v4 + 52);
        if (!IsValidNewMobSystem())
          goto LABEL_60;
      }
    }
    else
    {
      ExitIndex = *(u8 *)(v4 + 44);
      if (!IsValidNewMobSystem())
        goto LABEL_60;
    }
LABEL_56:
    ExitIndex = CalcNextExitIndex(v9, ExitIndex, 0);
    if ((ExitIndex & 0x80000000) == 0)
      goto LABEL_100;
    return;
  }
  ExitIndex = *(u8 *)(v4 + 36);
  if (IsValidNewMobSystem())
    goto LABEL_56;
LABEL_60:
  v34 = Work->blockArray[pExit->blockIndex];
  v35 = (u32)v34->citizenNum;
  if ((s32)v35 >= 1)
  {
    pCitizen = v34->pCitizen;
    index_low = LOBYTE(pExit->index);
    if ((u32)v35 < 4)
    {
      v38 = 0;
      v39 = 0;
      goto LABEL_87;
    }
    v38 = v35 & 0x7FFFFFFC;
    v41 = 0;
    v42 = 0;
    v43 = 0;
    v44 = 0;
    v45 = &pCitizen[3];
    v46 = (u32)v35 & 0xFFFFFFFC;
    do
    {
      v47 = (*(v45 - 3))->exitIndex;
      v48 = v45;
      v49 = (*(v45 - 2))->exitIndex;
      v50 = (*(v45 - 1))->exitIndex;
      v45 += 4;
      v51 = v48->exitIndex;
      if (v47 != index_low)
        ++v41;
      if (v49 != index_low)
        ++v42;
      if (v50 != index_low)
        ++v43;
      if (v51 != index_low)
        ++v44;
      v46 -= 4;
    }
    while (v46);
    v39 = v44 + v43 + v42 + v41;
    if (v38 != v35)
    {
LABEL_87:
      v52 = ~v38;
      if ((v35 & 1) != 0)
      {
        v53 = (s64)pCitizen + 8 * v38;
        v38 |= 1u;
        if (*(u8 *)(*(u64 *)(v53 + 32) + 104) != index_low)
          ++v39;
      }
      if (v52 + v35)
      {
        v54 = v35 - v38;
        v55 = &pCitizen[v38 + 1];
        do
        {
          if ((*(v55 - 1))->exitIndex == index_low)
            v56 = v39;
          else
            v56 = v39 + 1;
          v57 = v55;
          v55 += 2;
          if (v57->exitIndex == index_low)
            v39 = v56;
          else
            v39 = v56 + 1;
          v54 -= 2;
        }
        while (v54);
      }
    }
    if (v39 > 20)
      return;
  }
LABEL_100:
  goto LABEL_102;
LABEL_103:
  goto LABEL_104;
LABEL_102:
  goto LABEL_103;
LABEL_104:
  v62 = sdfDefaultRandCB->v;
  v63 = v62[0];
  v64 = *(u64 *)v62 >> 30;
  v65 = v62[2];
  v66 = *(u64 *)&v62[2] >> 31;
  v62[2] = v62[1];
  v62[3] = v65;
  v67 = v66 ^ v64;
  v62[0] = v67;
  v62[1] = v63;
  LODWORD(v62) = pExit->interval;
  v68 = (f32)(s32)v62 * 0.5;
  v69 = (s32)(f32)v67 % (s32)v62;
  v70 = v68;
  if (v68 == INFINITY)
    v70 = 0x80000000;
  pExit->curCnt = v70 + v69;
  v71 = AddCitizen();
  v71->exitIndex = ExitIndex;
  if (IsValidNewMobSystem())
    goto LABEL_108;
  goto LABEL_119;
LABEL_120:
  goto LABEL_121;
LABEL_108:
  AddMobCount(v9, ExitIndex, 0);
LABEL_119:
  goto LABEL_120;
LABEL_121:
  v78 = sdfDefaultRandCB->v;
  v79 = v78[0];
  v80 = v78[2];
  v81 = *(u64 *)v78 >> 30;
  v82 = *(u64 *)&v78[2] >> 31;
  v78[2] = v78[1];
  v78[3] = v80;
  v83 = v82 ^ v81;
  v78[0] = v83;
  v78[1] = v79;
  v84 = (f32)v83;
  v85 = v84 & 7;
  v87 = -v84;
  v86 = v87 < 0;
  v88 = v87 & 7;
  if (v86)
    LOBYTE(v89) = v85;
  else
    v89 = -v88;
  v71->classType = v89;
  v90 = (v89 & 0xFE) != 0 && (v89 & 0xFE) != 6;
  v71->spdType = v90;
  v71->vleng = GetClassVelocity(v71);
  if (IsValidNewMobSystem())
    goto LABEL_130;
  goto LABEL_137;
LABEL_138:
  goto LABEL_139;
LABEL_130:
  v91 = ChoiceChara(v9, 0);
  spd = v91->_spd;
  v71->newModelID = v91->_mdl_id;
  v71->vleng = CalcMobSpeed(spd, 0);
LABEL_137:
  goto LABEL_138;
LABEL_139:
  v96 = sdfDefaultRandCB->v;
  v97 = v96[0];
  v98 = v96[2];
  v99 = *(u64 *)v96 >> 30;
  v100 = *(u64 *)&v96[2] >> 31;
  v96[2] = v96[1];
  v96[3] = v98;
  v101 = v100 ^ v99;
  v96[0] = v101;
  v96[1] = v97;
  v102 = (s32)(f32)v101 % 100 > 19;
  IsValidNewMobSystem = IsValidNewMobSystem();
  v105 = IsValidNewMobSystem || v102;
  if (!IsValidNewMobSystem && !v102)
  {
    v128 = sdfDefaultRandCB->v;
    v129 = v128[0];
    v130 = v128[2];
    v131 = *(u64 *)v128 >> 30;
    v132 = *(u64 *)&v128[2] >> 31;
    v128[2] = v128[1];
    v128[3] = v130;
    v133 = v132 ^ v131;
    v128[0] = v133;
    v128[1] = v129;
    if ((s32)(f32)v133 >= 0)
      v134 = (s32)(f32)v133 & 1;
    else
      v134 = -((s32)(f32)v133 & 1);
    v135 = AddCitizen();
    if (IsValidNewMobSystem())
      v135->newModelID = ChoiceChara(v9, 0)->_mdl_id;
    pFriends = v71->pFriends;
    ++v135->friendNum;
    ++v71->friendNum;
    v135->exitIndex = v71->exitIndex;
    v137[0] = v71;
    classType = v71->classType;
    v139 = 0.9;
    v140 = (classType & 1) == 0;
    vleng = v71->vleng;
    if ((classType & 1) != 0)
      v143 = classType - 1;
    else
      v143 = classType + 1;
    if (v140)
      v108 = v135;
    else
      v108 = v71;
    if (!v140)
      v71 = v135;
    v135->classType = v143;
    if (v140)
      v139 = 1.1;
    v135->vleng = vleng * v139;
    v71->attr |= 0x10u;
    v108->attr &= ~0x10u;
    if ((v134 & 0x80000000) == 0)
      goto LABEL_174;
    goto LABEL_175;
  }
  goto LABEL_143;
LABEL_144:
  goto LABEL_145;
LABEL_143:
  goto LABEL_144;
LABEL_145:
  v108 = 0;
  v109 = sdfDefaultRandCB->v;
  v110 = v109[0];
  v111 = v109[2];
  v112 = *(u64 *)v109 >> 30;
  v113 = *(u64 *)&v109[2] >> 31;
  v109[2] = v109[1];
  v109[3] = v111;
  v114 = v113 ^ v112;
  v109[0] = v114;
  v109[1] = v110;
  v115 = (s32)(f32)v114 % 10;
  if (!v115)
  {
LABEL_175:
    v71->pathPref = 2;
    vertex = pExit->vertex;
    v145 = 0.2;
    v146 = 0.8;
    v118 = 0;
    v119 = !v105;
    v117 = 1;
    goto LABEL_176;
  }
  if (v115 != 1)
  {
    v108 = 0;
    v71->pathPref = 3;
    v116 = pExit->vertex;
    v117 = 0;
    v118 = 0;
    v119 = 0;
    v121 = v116[0];
    v120 = v116[1];
    v122 = (f32)(v121[0] + v120[0]) * 0.5;
    v71->x = v122;
    v123 = (f32)(v121[1] + v120[1]) * 0.5;
    goto LABEL_177;
  }
LABEL_174:
  v71->pathPref = 4;
  vertex = pExit->vertex;
  v145 = 0.8;
  v146 = 0.2;
  v117 = 0;
  v119 = !v105;
  v118 = 1;
LABEL_176:
  v148 = vertex[0];
  v147 = vertex[1];
  v122 = (f32)(v148[0] * v145) + (f32)(v147[0] * v146);
  v71->x = v122;
  v123 = (f32)(v148[1] * v145) + (f32)(v147[1] * v146);
LABEL_177:
  dir = pExit->dir;
  v71->y = v123;
  v71->x = v122 - (f32)(dir[0] * 0.1);
  v151 = dir[1];
  v71->y = v123 - (f32)(v151 * 0.1);
  v153 = Work;
  if (Work->mapID == 3)
  {
    v153 = Work;
    if (!v153->floorID)
    {
      if (v71->y >= 2.0)
      {
        v161 = 12.2;
        if (gMap03_CntS != 1)
          v161 = 13.0;
        if (gMap03_CntS == 2)
          v161 = 12.6;
        v71->x = v161;
        gMap03_CntS = (gMap03_CntS + 1) % 3;
      }
      else
      {
        v156 = 9.8;
        if (gMap03_CntN != 1)
          v156 = 9.0;
        if (gMap03_CntN == 2)
          v156 = 9.4;
        v71->x = v156;
        gMap03_CntN = (gMap03_CntN + 1) % 3;
      }
    }
  }
  x = v71->x;
  y = v71->y;
  v71->oldX = x;
  v71->oldY = y;
  if (x == INFINITY)
    v165 = 0x80000000;
  else
    v165 = x;
  if (y == INFINITY)
    v166 = 0x80000000;
  else
    v166 = y;
  Grid = ctnGetGrid(v165, v166);
  index = Grid->pBlock->index;
  ++Grid->citizenNum;
  if (index != v71->blockIndex)
  {
    LeaveBlock(v71);
    EnterBlock(v71, Grid);
LABEL_228:
    goto LABEL_229;
LABEL_236:
    v173.n64_u64[0] = vmul_f32(*(float32x2_t *)&v71->dirX, (float32x2_t)0x3F0000003F000000LL).n64_u64[0];
    v108->pathPref = v71->pathPref;
    *(float32x2_t *)&v108->targetVx = v173;
    if (v117)
    {
      targetVy = v173.n64_f32[1];
      v176 = 1;
      v177 = (f32)(v173.n64_f32[0] * -4.371139e-08) - targetVy;
      v175 = v173.n64_f32[0] + (f32)(targetVy * -4.371139e-08);
    }
    else
    {
      v175 = v173.n64_f32[1];
      if (!v118)
      {
LABEL_246:
        v178 = v71->x;
        v179 = v71->y;
        v108->targetVx = 0.0;
        v108->targetVy = 0.0;
        v180 = v179 + v175;
        v181 = v178 + v173.n64_f32[0];
        v108->x = v181;
        v108->y = v180;
        v108->oldX = v181;
        v108->oldY = v180;
        return;
      }
      v173.n64_u32[0] = LODWORD(v108->targetVx);
      v175 = v108->targetVy;
      v176 = -1;
      v177 = (f32)(v173.n64_f32[0] * 1.1924881e-08) + v175;
      v175 = (f32)(v175 * 1.1924881e-08) - v173.n64_f32[0];
    }
    v173.n64_f32[0] = v177;
    v108->targetVx = v177;
    v108->targetVy = v175;
    v108->followType = v176;
    goto LABEL_246;
  }
  goto LABEL_228;
LABEL_229:
  SetWallInfo(v71);
  v71->offCenter = v71->leftWallDist - v71->rightWallDist;
  if (v119)
    goto LABEL_236;
}

// 0x18e0010
static void SetOffCenter(ctnCitizen_t *pCitizen) {
  pCitizen->offCenter = pCitizen->leftWallDist - pCitizen->rightWallDist;
}

// 0x18e5a50
static s32 CheckExit(ctnCitizen_t *pCitizen) {
  f32 *v3;
  ctnExit_t *v5;
  f32 **vertex;
  f32 *v7;
  f32 *v8;
  f32 v9;
  f32 v10;
  f32 v11;
  f32 v12;
  f32 *dir;
  f32 v14;
  f32 v15;

  v3 = NewSpecific(f32, 2u);
  if (pCitizen->friendNum && (pCitizen->attr & 0x10) == 0)
    return 0;
  v5 = Work->exitArray[pCitizen->exitIndex];
  vertex = v5->vertex;
  v8 = vertex[0];
  v7 = vertex[1];
  v9 = (f32)(v8[0] + v7[0]) * 0.5;
  v3[0] = v9;
  v10 = (f32)(v8[1] + v7[1]) * 0.5;
  v3[1] = v10;
  v11 = pCitizen->y - v10;
  v12 = pCitizen->x - v9;
  if ((f32)((f32)(v12 * v12) + (f32)(v11 * v11)) > 9.0)
    return 0;
  dir = v5->dir;
  v14 = dir[0];
  v15 = dir[1];
  return (f32)((f32)(v12 * v14) + (f32)(v11 * v15)) > 0.0;
}

// 0x18e5bb0
void ctnUpdate(ctnInput_t *pInput) {
  f32 playerX;
  f32 playerY;
  s32 v8;
  s32 v9;
  ctnGrid_t *Grid;
  __int128 v13;
  ctnWork_t *Work_local;
  float32x2_t v15;
  ctnWork_t *v17;
  s64 v18;
  s64 v19;
  void *v20;
  s64 v21;
  s64 v22;
  s64 i;
  ctnWork_t *v25;
  ctnCitizen_t *v26;
  s32 NgCount;
  bool v28;
  s32 v29;
  s32 sliceIndex;
  s64 j;
  ctnWork_t *v34;
  s64 v35;
  s64 v36;
  s32 v37;
  s64 v40;
  ctnWork_t *v43;
  ctnCitizen_t *v44;
  s32 attr;
  s32 v46;

  if (pInput)
  {
    playerX = pInput->playerX;
    playerY = pInput->playerY;
    Work->waitFlag = pInput->waitFlag;
    if (playerX == INFINITY)
      v8 = 0x80000000;
    else
      v8 = playerX;
    if (playerY == INFINITY)
      v9 = 0x80000000;
    else
      v9 = playerY;
    Grid = ctnGetGrid(v8, v9);
    if (Grid)
    {
      *(u64 *)&v13 = *(u64 *)&pInput->playerX;
      Work_local = Work;
      v15.n64_u64[0] = *(u64 *)&Work_local->playerX;
      Work_local->fPlayer = pInput->fPlayer;
      *((float32x2_t *)&v13 + 1) = v15;
      *(float32x2_t *)&Work_local->playerVx = vsub_f32(*(float32x2_t *)&v13, v15);
      *(_OWORD *)&Work_local->playerX = v13;
      if (!IsValidNewMobSystem())
        goto LABEL_36;
    }
    else
    {
      Work->fPlayer = 0;
      if (!IsValidNewMobSystem())
        goto LABEL_36;
    }
  }
  else
  {
    v17 = Work;
    v17->fPlayer = 0;
    v17->waitFlag = 0;
    if (!IsValidNewMobSystem())
      goto LABEL_36;
  }
  if (!Work->waitFlag)
  {
    v18 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldMobManager__get_Instance__ + 4);
    if ((*(u16 *)(v18 + 309) & 1) == 0)
      v18 = sub_42269C(v18);
    v19 = *(u64 *)(*(u64 *)(v18 + 192) + 16);
    if ((*(u16 *)(v19 + 309) & 1) == 0)
      v19 = sub_42269C(v19);
    v20 = **(void ***)(v19 + 184);
    v21 = *((u64 *)Method_AtlUtil_AtSingleton_AtlFieldManager__get_Instance__ + 4);
    if ((*(u16 *)(v21 + 309) & 1) != 0)
    {
      v22 = *(u64 *)(*(u64 *)(v21 + 192) + 16);
      if ((*(u16 *)(v22 + 309) & 1) != 0)
        goto LABEL_34;
    }
    else
    {
      v22 = *(u64 *)(*(u64 *)(sub_42269C(v21) + 192) + 16);
      if ((*(u16 *)(v22 + 309) & 1) != 0)
      {
LABEL_34:
LABEL_35:
        Update(v20, VRF_DeltaTime, 0);
        goto LABEL_36;
      }
    }
    sub_42269C(v22);
    goto LABEL_35;
  }
LABEL_36:
  for (i = 32; i != 2080; i += 8)
  {
    v25 = Work;
    v26 = *(ctnCitizen_t *)((char *)&v25->citizenArray->obj.klass + i);
    NgCount = v26->NgCount;
    v28 = __OFSUB__(NgCount, 1);
    v29 = NgCount - 1;
    if (v29 < 0 == v28)
      v26->NgCount = v29;
    if (v26->fExist)
    {
      sliceIndex = v26->sliceIndex;
      if (sliceIndex != v25->sliceIndex)
        continue;
      if (!CheckExit(v26))
        continue;
      KillCitizen(v26);
    }
  }
  for (j = 0; ; ++j)
  {
    v34 = Work;
    if (j >= v34->exitNum)
      break;
    v34 = Work;
    ShootCitizen(v34->exitArray[j]);
  }
  v35 = 32;
  while (2)
  {
    v36 = *(s64 *)((char *)&Work->citizenArray->obj.klass + v35);
    if (!*(u32 *)(v36 + 32))
      goto LABEL_63;
    v37 = *(u32 *)(v36 + 96);
    if (v37 != Work->sliceIndex)
      goto LABEL_63;
    *(u64 *)(v36 + 128) = 0;
    *(u64 *)(v36 + 136) = 0;
    *(u32 *)(v36 + 100) &= 0xFFFFFFFA;
LABEL_63:
    v35 += 8;
    if (v35 != 2080)
      continue;
    break;
  }
  SimulateSetFlags();
  v40 = 32;
  while (2)
  {
    v43 = Work;
    v44 = *(ctnCitizen_t *)((char *)&v43->citizenArray->obj.klass + v40);
    if (!v44->fExist)
      goto LABEL_78;
    attr = v44->attr;
    if ((attr & 0x80) != 0)
      goto LABEL_89;
    if ((attr & 1) == 0)
    {
      v46 = v44->sliceIndex;
      if (v46 != v43->sliceIndex)
        goto LABEL_92;
LABEL_89:
      UpdateTargetVelocity(v44);
      goto LABEL_92;
    }
LABEL_92:
    UpdateCitizenVelocity(v44);
    UpdateCitizenPos(v44);
    UpdateCitizenRotate(v44);
    v44->attr &= ~0x80u;
LABEL_78:
    v40 += 8;
    if (v40 != 2080)
      continue;
    break;
  }
  Work->sliceIndex = (Work->sliceIndex + 1) % 6;
}

// 0x18e3520
void ctnAdjustShoot(f32 ratio) {
  s64 v4;
  s64 v5;
  s64 v6;
  f32 v7;
  s32 v8;

  v4 = 0;
  while (1)
  {
    if (v4 >= Work->exitNum)
      break;
    v5 = (s64)Work->exitArray + 8 * v4++;
    v6 = *(u64 *)(v5 + 32);
    v7 = (f32)*(s32 *)(v6 + 44) * ratio;
    v8 = v7;
    if (v7 == INFINITY)
      v8 = 0x80000000;
    *(u32 *)(v6 + 48) = v8;
  }
}

// 0x18e0f30
void ctnNormalizeVec(f32 *vx, f32 *vy) {
  f32 v3;

  v3 = sqrtf((f32)(*vx * *vx) + (f32)(*vy * *vy));
  *vx = *vx / v3;
  *vy = *vy / v3;
}

// 0x18df4f0
bool ctnCheckClose(s32 map, s32 id, ctnCitizen_t *ctn) {
  bool result;
  f32 x;
  f32 v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 z;

  result = 0;
  if (((map | id) & 0x80000000) == 0 && ctn)
  {
    x = ctn->x;
    if (map != 1)
      return 0;
    v11 = (f32)(x * 100.0) + ctn_ofs_fx;
    v12 = ctn_ofs_fz - (f32)(ctn->y * 100.0);
    if (id == 20)
    {
      if (ctn->dirX != 0.0 || ctn->dirY <= 0.0)
        return 0;
      v15 = g_cameraPos.x;
      z = g_cameraPos.z;
      if ((f32)(sqrtf((f32)((f32)(v11 - v15) * (f32)(v11 - v15)) + (f32)((f32)(v12 - z) * (f32)(v12 - z))) / 100.0) >= 5.0)
        return 0;
    }
    else
    {
      if (id != 7 || ctn->dirX <= 0.0 || ctn->dirY != 0.0)
        return 0;
      v13 = g_cameraPos.x;
      v14 = g_cameraPos.z;
      if ((f32)(sqrtf((f32)((f32)(v11 - v13) * (f32)(v11 - v13)) + (f32)((f32)(v12 - v14) * (f32)(v12 - v14))) / 100.0) >= 2.0)
        return 0;
    }
    return 1;
  }
  return result;
}

// 0x18e61a0
f32 ctnCameraRelativeDistance(f32 camX, f32 camZ, f32 ctnX, f32 ctnZ) {
  return sqrtf((f32)((f32)(ctnX - camX) * (f32)(ctnX - camX)) + (f32)((f32)(ctnZ - camZ) * (f32)(ctnZ - camZ)));
}

// 0x18e61c0
static bool ChkNg_Grid(s32 ix, s32 iy) {
  ctnWork_t *v7;
  ctnWork_t *v8;
  ctnWork_t *v9;
  bool v10;
  bool result;
  s32 v12;
  bool v13;
  bool v14;
  u32 v15;
  bool v16;
  bool v17;
  bool v18;
  _BOOL4 v19;
  bool v20;
  _BOOL4 v21;
  bool v22;
  _BOOL4 v23;
  bool v24;

  goto LABEL_3;
LABEL_7:
  if (Work->floorID)
    goto LABEL_9;
  return ix == 40 && (u32)iy < 6
      || (u32)(ix - 41) >= 0xFFFFFFFE && iy == 29
      || ix == 25 && (u32)(iy - 45) > 0xFFFFFFFD
      || (u32)(ix - 27) >= 0xFFFFFFFE && (u32)(iy - 43) > 0xFFFFFFFA
      || (u32)(ix - 28) >= 0xFFFFFFFD && (u32)(iy - 41) > 0xFFFFFFF9
      || (u32)(ix - 68) >= 0xFFFFFFE0 && iy == 69
      || ix == 74 && (u32)iy <= 0x41;
LABEL_3:
  if (Work->mapID == 1)
    goto LABEL_7;
LABEL_9:
  v7 = Work;
  if (v7->mapID != 2)
  {
LABEL_15:
    v8 = Work;
    if (v8->mapID != 3)
    {
LABEL_21:
      v9 = Work;
      if (v9->mapID != 3)
        return 0;
      if (v9->floorID != 1)
        return 0;
      return (u32)(ix - 46) >= 0xFFFFFFE5 && iy == 30
          || (u32)(ix - 36) >= 0xFFFFFFEF && iy == 34
          || (u32)(ix - 47) >= 0xFFFFFFFE && (u32)(iy - 31) > 0xFFFFFFEA;
      if (Work->floorID == 1)
        return (u32)(ix - 46) >= 0xFFFFFFE5 && iy == 30
            || (u32)(ix - 36) >= 0xFFFFFFEF && iy == 34
            || (u32)(ix - 47) >= 0xFFFFFFFE && (u32)(iy - 31) > 0xFFFFFFEA;
      return 0;
    }
    if (v8->floorID)
      goto LABEL_21;
    return (u32)(ix - 12) >= 0xFFFFFFFE && (u32)(iy - 9) >= 0xFFFFFFFE;
  }
  if (v7->floorID)
    goto LABEL_15;
  if (ix == 68 && iy == 45)
    return 1;
  v10 = ix == 68 && iy == 64;
  result = 1;
  v12 = !v10;
  v13 = iy == 45 && ix == 85;
  if (!v13 && v12)
  {
    v14 = ix == 85 || ix == 68;
    if (!v14 || iy != 49)
    {
      v15 = ix - 85;
      v16 = ix == 85 || ix == 68;
      if ((!v16 || iy != 60) && (v15 < 0xFFFFFFF0 || iy != 49))
      {
        v17 = ix == 68 || ix == 85;
        v18 = v17 && (u32)(iy - 60) >= 0xFFFFFFF6;
        v19 = !v18;
        v20 = v15 >= 0xFFFFFFF0 && iy == 60;
        v21 = !v20;
        v22 = iy == 45 && v15 > 0xFFFFFFEF;
        if (!v22 && v21 && v19 && ((u32)(ix - 88) < 0xFFFFFFED || iy != 64))
        {
          v23 = (u32)(iy - 45) < 0xFFFFFFF6 || ix != 85;
          v24 = (u32)(iy - 45) > 0xFFFFFFF6 && ix == 68;
          if (!v24 && v23 && (ix != 68 || (u32)(iy - 100) < 0xFFFFFFDD))
            return 0;
        }
      }
    }
  }
  return result;
}

// 0x18dca90
static void OW_ObjectPos(s32 i, f32 *_fx, f32 *_fy, f32 *_radius) {
  if (Work->mapID != 1)
    return;
  if (i == 9 && !Work->floorID)
  {
    *fx = 32.5;
    *fy = 46.0;
    *radius = 0.8;
  }
}

// 0x18de940
static void ChkNg_MovePos1(ctnCitizen_t *ctn) {
  f32 x;
  f32 y;
  f32 vy;
  f32 vx;

  if (Work->mapID != 1)
    return;
  if (Work->floorID)
    return;
  x = ctn->x;
  if (x >= 38.0 && x <= 39.0)
  {
    y = ctn->y;
    if (y >= 28.0 && y <= 30.0 && ctn->dirX == 1.0)
    {
      vx = ctn->vx;
      vy = ctn->vy;
      ctn->vx = 0.0;
      ctn->vy = vy + vx;
    }
  }
}

// 0x18dea70
static void ChkNg_MovePos2(ctnCitizen_t *ctn, f32 *_fx, f32 *_fy) {
  ctnWork_t *v9;
  ctnWork_t *v10;
  ctnWork_t *v11;
  f32 v12;
  f32 v13;
  f32 v14;
  f32 v15;
  f32 v16;
  bool v17;
  bool v18;
  f32 v19;
  f32 v20;
  f32 v21;
  f32 v22;
  bool v23;
  bool v24;

  goto LABEL_3;
LABEL_7:
  if (Work->floorID)
    goto LABEL_9;
  v15 = *fx;
  if (*fx >= 39.4 && v15 <= 41.0 && *fy >= 0.0 && *fy <= 6.5)
  {
    if (ctn->dirY == 0.0)
      return;
    v16 = -0.002;
    goto LABEL_173;
  }
  if (v15 >= 38.4 && v15 <= 49.0)
  {
    v19 = *fy;
    if (*fy >= 29.0 && v19 <= 30.3)
      goto LABEL_60;
  }
  if (v15 >= 25.0)
  {
    if (v15 <= 26.0 && *fy >= 43.0 && *fy <= 45.5)
    {
      if (ctn->dirY == 0.0)
        return;
      v16 = 0.002;
      goto LABEL_173;
    }
    if (v15 <= 27.0 && *fy >= 35.0 && *fy <= 43.3 || v15 <= 28.0 && *fy >= 35.0 && *fy <= 41.6)
    {
      if (ctn->dirY == 0.0)
        return;
      v16 = 0.003;
LABEL_173:
      *fx = v15 + v16;
      return;
    }
  }
  if (v15 >= 35.2 && v15 <= 68.0)
  {
    v19 = *fy;
    if (*fy >= 68.8 && v19 <= 70.0)
      goto LABEL_144;
  }
  if (v15 < 74.0 || v15 > 75.0 || *fy < 0.0 || *fy > 65.0)
  {
    if (v15 < 32.0)
      return;
    if (v15 > 33.0)
      return;
    v19 = *fy;
    if (*fy < 45.5 || v19 > 46.5)
      return;
    if (ctn->dirY != 0.0)
      goto LABEL_138;
LABEL_139:
    v22 = 0.01;
LABEL_146:
    *fy = v19 + v22;
    return;
  }
  goto LABEL_171;
LABEL_3:
  if (Work->mapID == 1)
    goto LABEL_7;
LABEL_9:
  v9 = Work;
  if (v9->mapID != 2)
    goto LABEL_15;
  if (v9->floorID)
    goto LABEL_15;
  v15 = *fx;
  v17 = *fx < 67.7;
  if (*fx > 69.3)
    v17 = 1;
  if (!v17)
  {
    v19 = *fy;
    if (*fy >= 44.7 && v19 <= 46.3)
    {
LABEL_92:
      if (ctn->dirX == 0.0)
        goto LABEL_172;
      goto LABEL_139;
    }
  }
  v18 = v15 < 84.7;
  if (v15 > 86.3)
    v18 = 1;
  if (!v18)
  {
    v19 = *fy;
    if (*fy >= 44.7 && v19 <= 46.3)
      goto LABEL_137;
  }
  if (v15 >= 67.7 && v15 <= 69.3)
  {
    if ((v19 = *fy, *fy >= 63.7) && v19 <= 65.3 || (v19 = *fy, *fy >= 48.7) && v19 <= 50.3)
    {
      if (ctn->dirX == 0.0)
        goto LABEL_172;
      goto LABEL_145;
    }
  }
  if (!v18)
  {
    v19 = *fy;
    if (*fy >= 48.7 && v19 <= 50.3)
    {
      if (ctn->dirX != 0.0)
      {
LABEL_145:
        v22 = -0.01;
        goto LABEL_146;
      }
LABEL_138:
      v16 = 0.01;
      goto LABEL_173;
    }
  }
  if (!v17)
  {
    v19 = *fy;
    if (*fy >= 59.7 && v19 <= 61.3)
      goto LABEL_92;
  }
  if (!v18)
  {
    v19 = *fy;
    if (*fy >= 59.7 && v19 <= 61.3)
    {
LABEL_137:
      if (ctn->dirX == 0.0)
        goto LABEL_138;
      goto LABEL_139;
    }
  }
  if (v15 >= 69.0 && v15 <= 85.0)
  {
    v19 = *fy;
    if (*fy >= 49.0 && v19 <= 50.0)
    {
LABEL_144:
      if (ctn->dirX == 0.0)
        return;
      goto LABEL_145;
    }
  }
  v23 = v15 < 68.0;
  if (v15 > 69.0)
    v23 = 1;
  if (v23 || *fy < 50.0 || *fy > 60.0)
  {
    v24 = v15 < 85.0;
    if (v15 > 86.0)
      v24 = 1;
    if (!v24 && *fy >= 50.0 && *fy <= 60.0)
      goto LABEL_132;
    if (v15 < 69.0)
    {
LABEL_160:
      if (!v23 && *fy >= 36.0 && *fy <= 45.0)
        goto LABEL_171;
      if (v24 || *fy < 35.0 || *fy > 45.0)
      {
        if (v23 || *fy < 65.0 || *fy > 100.0)
          return;
        goto LABEL_171;
      }
LABEL_132:
      if (ctn->dirY != 0.0)
        goto LABEL_138;
      return;
    }
    if (v15 > 85.0 || ((v19 = *fy, *fy < 60.0) || v19 > 61.0) && ((v19 = *fy, *fy < 45.0) || v19 > 46.0))
    {
      if (v15 <= 88.0)
      {
        v19 = *fy;
        if (*fy >= 64.0 && v19 <= 65.0)
          goto LABEL_144;
      }
      goto LABEL_160;
    }
LABEL_60:
    if (ctn->dirX == 0.0)
      return;
    goto LABEL_139;
  }
LABEL_171:
  if (ctn->dirY == 0.0)
    return;
LABEL_172:
  v16 = -0.01;
  goto LABEL_173;
LABEL_15:
  v10 = Work;
  if (v10->mapID != 3)
    goto LABEL_21;
  goto LABEL_19;
  if (v10->mapID == 3)
  {
LABEL_19:
    if (v10->floorID)
      goto LABEL_21;
    v15 = *fx;
    if (*fx < 10.0 || v15 > 11.0 || *fy < 6.0 || *fy > 10.0)
    {
      if (v15 < 11.0 || v15 > 12.0 || *fy < 6.0 || *fy > 10.0)
        return;
      goto LABEL_132;
    }
    goto LABEL_171;
  }
LABEL_21:
  v11 = Work;
  if (v11->mapID != 3)
    return;
  v11 = Work;
  if (v11->floorID == 1)
  {
    v12 = *fx;
    if (*fx >= 19.0 && v12 <= 36.0)
    {
      v13 = *fy;
      if (*fy >= 30.0 && v13 <= 30.5)
      {
        if (ctn->dirX != 0.0)
        {
          v14 = 0.01;
LABEL_120:
          v20 = v13 + v14;
LABEL_127:
          *fy = v20;
          goto LABEL_128;
        }
        goto LABEL_128;
      }
      v13 = *fy;
      if (*fy >= 34.2 && v13 <= 35.0)
      {
        if (ctn->dirX != 0.0)
        {
          v14 = -0.01;
          goto LABEL_120;
        }
LABEL_128:
        v15 = *fx;
        if (*fx < 45.0 || v15 > 47.0 || *fy < 10.0 || *fy > 31.0)
          return;
        goto LABEL_132;
      }
    }
    if (v12 >= 36.0 && v12 <= 46.0)
    {
      v21 = *fy;
      if (*fy >= 30.0 && v21 <= 31.0 && ctn->dirX != 0.0)
      {
        v20 = v21 + 0.01;
        goto LABEL_127;
      }
    }
    goto LABEL_128;
  }
}
