//----- (0000000002284290) ----------------------------------------------------
Project_Kernel_dds3ProcessID_t_o *__fastcall Project_Kernel_dds3KernelCore__StartProcess(
        System_String_o *namestr,
        int32_t priority,
        int32_t starttimer,
        int32_t shutdowntimer,
        Project_Kernel_dds3ProcessFunc_t_o *processfunc,
        Project_Kernel_shutdownfuncDelegate_o *shutdownfunc,
        Il2CppObject *data,
        const MethodInfo *method)
{
  __int64 v15; // x19
  int v16; // w0
  const MethodInfo *v17; // x1
  const MethodInfo *v18; // x1
  const MethodInfo *v19; // x1
  Project_Kernel_dds3KernelCore_c *v20; // x0
  const MethodInfo *v21; // x1

  if ( (byte_575950A & 1) == 0 )
  {
    il2cpp::InitializeMethodMetadata(&Project_Kernel_dds3KernelCore_TypeInfo);
    il2cpp::InitializeMethodMetadata(&Project_Kernel_dds3ProcessID_t_TypeInfo);
    byte_575950A = 1;
  }
  v15 = j_il2cpp::Allocate(Project_Kernel_dds3ProcessID_t_TypeInfo);
  System_Object___ctor((Il2CppObject *)v15, nullptr);
  if ( v15 )
  {
    *(_QWORD *)(v15 + 16) = namestr;
    il2cpp::WriteBarrier((void *)(v15 + 16), namestr);
    v16 = ((__int64 (__fastcall *)(System_String_o *, const MethodInfo *))namestr->klass->vtable._2_GetHashCode.methodPtr)(
            namestr,
            namestr->klass->vtable._2_GetHashCode.method);
    *(_DWORD *)(v15 + 36) = 0;
    *(_DWORD *)(v15 + 40) = 0;
    *(_DWORD *)(v15 + 32) = priority;
    *(_DWORD *)(v15 + 24) = v16;
    *(_DWORD *)(v15 + 28) = 1;
    *(_DWORD *)(v15 + 44) = (*(__int64 (__fastcall **)(__int64, _QWORD))(*(_QWORD *)v15 + 344LL))(
                              v15,
                              *(_QWORD *)(*(_QWORD *)v15 + 352LL));
    *(_DWORD *)(v15 + 48) = starttimer;
    *(_QWORD *)(v15 + 56) = processfunc;
    *(_DWORD *)(v15 + 52) = shutdowntimer;
    il2cpp::WriteBarrier((void *)(v15 + 56), processfunc);
    *(_QWORD *)(v15 + 64) = shutdownfunc;
    il2cpp::WriteBarrier((void *)(v15 + 64), shutdownfunc);
    *(_QWORD *)(v15 + 72) = data;
    il2cpp::WriteBarrier((void *)(v15 + 72), data);
    *(_QWORD *)(v15 + 80) = 0;
    il2cpp::WriteBarrier((void *)(v15 + 80), nullptr);
    *(_QWORD *)(v15 + 88) = 0;
    il2cpp::WriteBarrier((void *)(v15 + 88), nullptr);
    *(_QWORD *)(v15 + 96) = 0;
    il2cpp::WriteBarrier((void *)(v15 + 96), nullptr);
    *(_QWORD *)(v15 + 104) = 0;
    il2cpp::WriteBarrier((void *)(v15 + 104), nullptr);
    *(_QWORD *)(v15 + 112) = 0;
    il2cpp::WriteBarrier((void *)(v15 + 112), nullptr);
    if ( Project_Kernel_dds3KernelCore_TypeInfo->_2.cctor_finished )
    {
      Project_Kernel_dds3KernelCore__AddProcessList((Project_Kernel_dds3ProcessID_t_o *)v15, v17);
      if ( !*(_DWORD *)(v15 + 48) )
      {
LABEL_8:
        if ( Project_Kernel_dds3KernelCore_TypeInfo->_2.cctor_finished )
        {
          if ( (byte_5759506 & 1) != 0 )
            goto LABEL_10;
        }
        else
        {
          il2cpp::TypeInitializer(Project_Kernel_dds3KernelCore_TypeInfo);
          if ( (byte_5759506 & 1) != 0 )
          {
LABEL_10:
            v20 = Project_Kernel_dds3KernelCore_TypeInfo;
            if ( Project_Kernel_dds3KernelCore_TypeInfo->_2.cctor_finished )
            {
LABEL_11:
              Project_Kernel_dds3KernelCore__DeleteProcessList((Project_Kernel_dds3ProcessID_t_o *)v15, v18);
              *(_DWORD *)(v15 + 28) = *(_DWORD *)(v15 + 28) & 0xFFFFFFF0 | 2;
              Project_Kernel_dds3KernelCore__AddProcessList((Project_Kernel_dds3ProcessID_t_o *)v15, v21);
              *(_DWORD *)(v15 + 36) = 0;
              *(_DWORD *)(v15 + 40) = 0;
              return (Project_Kernel_dds3ProcessID_t_o *)v15;
            }
LABEL_15:
            il2cpp::TypeInitializer(v20);
            goto LABEL_11;
          }
        }
        il2cpp::InitializeMethodMetadata(&Project_Kernel_dds3KernelCore_TypeInfo);
        byte_5759506 = 1;
        v20 = Project_Kernel_dds3KernelCore_TypeInfo;
        if ( Project_Kernel_dds3KernelCore_TypeInfo->_2.cctor_finished )
          goto LABEL_11;
        goto LABEL_15;
      }
    }
    else
    {
      il2cpp::TypeInitializer(Project_Kernel_dds3KernelCore_TypeInfo);
      Project_Kernel_dds3KernelCore__AddProcessList((Project_Kernel_dds3ProcessID_t_o *)v15, v19);
      if ( !*(_DWORD *)(v15 + 48) )
        goto LABEL_8;
    }
  }
  return (Project_Kernel_dds3ProcessID_t_o *)v15;
}
// 22843F8: variable 'v17' is possibly undefined
// 2284410: variable 'v19' is possibly undefined
// 2284444: variable 'v18' is possibly undefined
// 228445C: variable 'v21' is possibly undefined
// 5759506: using guessed type char byte_5759506;
// 575950A: using guessed type char byte_575950A;

