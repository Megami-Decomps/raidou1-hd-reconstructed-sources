//----- (0000000002286EA0) ----------------------------------------------------
Project_Kernel_dds3ProcessID_t_o *__fastcall Project_Kernel_dds3KernelCore__SearchProcessPriority(
        int32_t priority,
        const MethodInfo *method)
{
  Project_Kernel_dds3KernelCore_c *v3; // x0
  Project_Kernel_dds3ProcessID_t_o *result; // x0

  if ( (byte_575949A & 1) != 0 )
  {
    v3 = Project_Kernel_dds3KernelCore_TypeInfo;
    if ( Project_Kernel_dds3KernelCore_TypeInfo->_2.cctor_finished )
      goto LABEL_3;
  }
  else
  {
    il2cpp::InitializeMethodMetadata(&Project_Kernel_dds3KernelCore_TypeInfo);
    byte_575949A = 1;
    v3 = Project_Kernel_dds3KernelCore_TypeInfo;
    if ( Project_Kernel_dds3KernelCore_TypeInfo->_2.cctor_finished )
    {
LABEL_3:
      result = v3->static_fields->startinglistf;
      if ( result )
        goto LABEL_4;
      goto LABEL_6;
    }
  }
  il2cpp::TypeInitializer(v3);
  result = Project_Kernel_dds3KernelCore_TypeInfo->static_fields->startinglistf;
  if ( result )
  {
LABEL_4:
    while ( result->fields.priority != priority )
    {
      result = result->fields.next;
      if ( !result )
        goto LABEL_6;
    }
    return result;
  }
LABEL_6:
  if ( Project_Kernel_dds3KernelCore_TypeInfo->_2.cctor_finished )
  {
    result = Project_Kernel_dds3KernelCore_TypeInfo->static_fields->runninglistf;
    if ( result )
      goto LABEL_8;
  }
  else
  {
    il2cpp::TypeInitializer(Project_Kernel_dds3KernelCore_TypeInfo);
    result = Project_Kernel_dds3KernelCore_TypeInfo->static_fields->runninglistf;
    if ( result )
    {
LABEL_8:
      while ( result->fields.priority != priority )
      {
        result = result->fields.next;
        if ( !result )
          goto LABEL_10;
      }
      return result;
    }
  }
LABEL_10:
  if ( Project_Kernel_dds3KernelCore_TypeInfo->_2.cctor_finished )
  {
    result = Project_Kernel_dds3KernelCore_TypeInfo->static_fields->endinglistf;
    if ( !result )
      return result;
  }
  else
  {
    il2cpp::TypeInitializer(Project_Kernel_dds3KernelCore_TypeInfo);
    result = Project_Kernel_dds3KernelCore_TypeInfo->static_fields->endinglistf;
    if ( !result )
      return result;
  }
  do
  {
    if ( result->fields.priority == priority )
      break;
    result = result->fields.next;
  }
  while ( result );
  return result;
}
// 575949A: using guessed type char byte_575949A;

