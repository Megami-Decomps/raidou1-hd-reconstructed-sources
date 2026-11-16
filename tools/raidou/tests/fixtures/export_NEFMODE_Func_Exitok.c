//----- (000000000191DEB0) ----------------------------------------------------
bool __fastcall Project_sbattle__NEFMODE_Func_Exitok(const MethodInfo *method)
{
  Project_sbattle_c *v1; // x0
  struct Project_SBDEBUG_CSRWORK_o *nef_exitokcsr; // x20
  int v3; // w8
  int32_t point; // w8
  int32_t v6; // w8
  Project_sbattle_c *v7; // x0
  uint32_t cctor_finished; // w8
  struct Project_SBTLDEBUG_WORK_o *sbtldbwk; // x8
  Project_sBtl_c *v10; // x0
  int64_t status; // x11

  if ( (byte_5756022 & 1) == 0 )
  {
    il2cpp::InitializeMethodMetadata(&Project_sBtl_TypeInfo);
    il2cpp::InitializeMethodMetadata(&Project_sbattle_TypeInfo);
    byte_5756022 = 1;
  }
  v1 = Project_sbattle_TypeInfo;
  if ( !Project_sbattle_TypeInfo->_2.cctor_finished )
  {
    il2cpp::TypeInitializer(Project_sbattle_TypeInfo);
    v1 = Project_sbattle_TypeInfo;
  }
  nef_exitokcsr = v1->static_fields->sbtldbwk->fields.nef_exitokcsr;
  if ( !Project_Kernel_DDS3_PAD__CHECK_REP2(4100, nullptr) )
  {
    if ( Project_Kernel_DDS3_PAD__CHECK_REP2(4101, nullptr) )
    {
      point = nef_exitokcsr->fields.point;
      if ( point + 1 < nef_exitokcsr->fields.maxp )
        v6 = point + 1;
      else
        v6 = 0;
      nef_exitokcsr->fields.point = v6;
      return 1;
    }
    if ( Project_Kernel_DDS3_PAD__CHECK_TRIG(4097, 1, nullptr) )
    {
      v7 = Project_sbattle_TypeInfo;
      if ( !Project_sbattle_TypeInfo->_2.cctor_finished )
      {
LABEL_15:
        il2cpp::TypeInitializer(v7);
        v7 = Project_sbattle_TypeInfo;
      }
    }
    else
    {
      if ( !Project_Kernel_DDS3_PAD__CHECK_TRIG2(4096, nullptr) )
        return 1;
      v7 = Project_sbattle_TypeInfo;
      cctor_finished = Project_sbattle_TypeInfo->_2.cctor_finished;
      if ( nef_exitokcsr->fields.point )
      {
        if ( !cctor_finished )
        {
          il2cpp::TypeInitializer(Project_sbattle_TypeInfo);
          v7 = Project_sbattle_TypeInfo;
        }
        sbtldbwk = v7->static_fields->sbtldbwk;
        v10 = Project_sBtl_TypeInfo;
        status = sbtldbwk->fields.status;
        sbtldbwk->fields.mode = 10;
        sbtldbwk->fields.nef_mode = 0;
        sbtldbwk->fields.status = status & 0xFFFFFFFFFFFFF7FFLL;
        if ( !v10->_2.cctor_finished )
          il2cpp::TypeInitializer(v10);
        Project_sBtl__RestartBattle(nullptr);
        return 1;
      }
      if ( !cctor_finished )
        goto LABEL_15;
    }
    v7->static_fields->sbtldbwk->fields.nef_mode = v7->static_fields->sbtldbwk->fields.nef_modebk;
    return 1;
  }
  v3 = nef_exitokcsr->fields.point - 1;
  nef_exitokcsr->fields.point = v3;
  if ( v3 >= 0 )
    return 1;
  nef_exitokcsr->fields.point = nef_exitokcsr->fields.maxp - 1;
  return 1;
}
// 5756022: using guessed type char byte_5756022;

