  __int64 v5; // x1
  int32_t i; // w20

  if ( (byte_3F5AAEE & 1) == 0 )
  {
    il2cpp::InitializeMethodMetadata(0x58E4u);
    byte_3F5AAEE = 1;
  }
  if ( (SoundManager_TypeInfo->_2.bitflags2 & 2) != 0 && !SoundManager_TypeInfo->_2.cctor_finished )
  {
    il2cpp::TypeInitializer(SoundManager_TypeInfo, p);
    if ( SoundManager__p2sdStatusSE_Dead(0) )
      return;
  }
  else if ( SoundManager__p2sdStatusSE_Dead(0) )
  {
    return;
  }
  if ( ((*k)->fields.data->fields.flag & 1) == 0 && (*p)->fields.type == 36 )
  {
    i = (*p)->fields.data1->fields.i;
    if ( (SoundManager_TypeInfo->_2.bitflags2 & 2) != 0 && !SoundManager_TypeInfo->_2.cctor_finished )
      il2cpp::TypeInitializer(SoundManager_TypeInfo, v5);
    SoundManager__p2sdPlaySE_Dead(i, 0);
    (*k)->fields.data->fields.flag |= 1u;
  }
