//----- (0000000001B3AD70) ----------------------------------------------------
int32_t __fastcall Project_fclMisc__DestroyMessage(const MethodInfo *method)
{
  Project_fclMisc_c *v1; // x0
  int32_t gMsgID; // w19
  Project_itf_c *v3; // x0
  struct Project_fclMisc_StaticFields *static_fields; // x8

  if ( (byte_5756C92 & 1) != 0 )
  {
    v1 = Project_fclMisc_TypeInfo;
    if ( Project_fclMisc_TypeInfo->_2.cctor_finished )
      goto LABEL_3;
  }
  else
  {
    il2cpp::InitializeMethodMetadata(&Project_fclMisc_TypeInfo);
    il2cpp::InitializeMethodMetadata(&Project_itf_TypeInfo);
    byte_5756C92 = 1;
    v1 = Project_fclMisc_TypeInfo;
    if ( Project_fclMisc_TypeInfo->_2.cctor_finished )
    {
LABEL_3:
      gMsgID = v1->static_fields->gMsgID;
      if ( (gMsgID & 0x80000000) == 0 )
        goto LABEL_4;
      return 0;
    }
  }
  il2cpp::TypeInitializer(v1);
  v1 = Project_fclMisc_TypeInfo;
  gMsgID = Project_fclMisc_TypeInfo->static_fields->gMsgID;
  if ( (gMsgID & 0x80000000) == 0 )
  {
LABEL_4:
    if ( v1->_2.cctor_finished )
    {
      v3 = Project_itf_TypeInfo;
      if ( Project_itf_TypeInfo->_2.cctor_finished )
      {
LABEL_6:
        Project_itf__MesMngRelease(gMsgID, nullptr);
        static_fields = Project_fclMisc_TypeInfo->static_fields;
        static_fields->gMsgID = -1;
        *(_WORD *)&static_fields->gMsgFlag = 0;
        return 1;
      }
    }
    else
    {
      il2cpp::TypeInitializer(v1);
      gMsgID = Project_fclMisc_TypeInfo->static_fields->gMsgID;
      v3 = Project_itf_TypeInfo;
      if ( Project_itf_TypeInfo->_2.cctor_finished )
        goto LABEL_6;
    }
    il2cpp::TypeInitializer(v3);
    goto LABEL_6;
  }
  return 0;
}
// 5756C92: using guessed type char byte_5756C92;

