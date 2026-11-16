//----- (000000000194A750) ----------------------------------------------------
void __fastcall Project_VISUALDATA_WORK___ctor(Project_VISUALDATA_WORK_o *this, const MethodInfo *method)
{
  struct Project_MOTIONDATA_WORK_array *v3; // x0

  if ( (byte_57560DB & 1) == 0 )
  {
    il2cpp::InitializeMethodMetadata(&Project_MOTIONDATA_WORK___TypeInfo);
    byte_57560DB = 1;
  }
  v3 = (struct Project_MOTIONDATA_WORK_array *)il2cpp::NewSpecific(Project_MOTIONDATA_WORK___TypeInfo, 0x30u);
  this->fields.mwk = v3;
  il2cpp::WriteBarrier(&this->fields.mwk, v3);
  System_Object___ctor((Il2CppObject *)this, nullptr);
}
// 57560DB: using guessed type char byte_57560DB;

