  __int64 v3; // x1
  nbCameraBoss_c *v4; // x0
  float BSARI_Cut1_Rate; // s8
  Project_nbCamera_t_o *v6; // x20
  Project_nbFormation_t_o *pFormation; // [xsp+8h] [xbp-18h] BYREF

  if ( (byte_3F58649 & 1) == 0 )
  {
    il2cpp::InitializeMethodMetadata(0x56E0u);
    byte_3F58649 = 1;
  }
  pFormation = 0;
  if ( (effBattle_TypeInfo->_2.bitflags2 & 2) != 0 && !effBattle_TypeInfo->_2.cctor_finished )
    il2cpp::TypeInitializer(effBattle_TypeInfo, method);
  pFormation = effBattle__effBTLSkillGetInvokeFormation(0, 0);
  v4 = nbCameraBoss_TypeInfo;
  if ( (nbCameraBoss_TypeInfo->_2.bitflags2 & 2) != 0 && !nbCameraBoss_TypeInfo->_2.cctor_finished )
  {
    il2cpp::TypeInitializer(nbCameraBoss_TypeInfo, v3);
    v4 = nbCameraBoss_TypeInfo;
  }
  v4->static_fields->BSARI_Cut1_Rate = v4->static_fields->BSARI_Cut1_Rate * 0.985;
  BSARI_Cut1_Rate = v4->static_fields->BSARI_Cut1_Rate;
  if ( (effBattleMisc_TypeInfo->_2.bitflags2 & 2) != 0 && !effBattleMisc_TypeInfo->_2.cctor_finished )
    il2cpp::TypeInitializer(effBattleMisc_TypeInfo, v3);
  effBattleMisc__effBTLModelGetMarkPosition2(&pFormation, 1u, 0);
  Project_SDF_VU0__STOREVECTOR(&(*pNbCamera)->fields.target, 0);
  Project_SDF_VU0__COPYVECTOR_A_TO_C(0);
  Project_SDF_VU0__LOADVECTOR_B(nbCameraBoss_TypeInfo->static_fields->BSARI_Cut1_Start, 0);
  Project_SDF_VU0__INTERPOLATE((BSARI_Cut1_Rate * 0.5) + 0.75, 0);
  Project_SDF_VU0__COPYVECTOR_A_TO_B(0);
  Project_SDF_VU0__COPYVECTOR_C_TO_A(0);
  Project_SDF_VU0__SUBVECTOR(0);
  v6 = *pNbCamera;
  v6->fields.distance = Project_SDF_VU0__GETLENGTH(0);
  Project_SDF_VU0__NORMALIZE(0);
  Project_SDF_VU0__STOREVECTOR(&(*pNbCamera)->fields.direction, 0);
  (*pNbCamera)->fields.fovy = 0.69813;
  return 1;
