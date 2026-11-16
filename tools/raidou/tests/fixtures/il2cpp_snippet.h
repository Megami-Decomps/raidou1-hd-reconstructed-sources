struct Project_fld_Save_t_Fields {
	struct System_Byte_array* takara;
	int16_t tmnltype;
	int16_t tmnlid;
	int32_t AnahoriCnt;
	struct System_Int32_array* pub;
	struct System_Byte_array_array* automapmask;
	struct System_Byte_array* kiretsu;
	bool kiretsuClr;
};
struct Project_fld_Fields {
};
struct Project_fld_StaticFields {
	struct UnityEngine_Vector4_o g_targetPos;
	struct UnityEngine_Vector4_o g_cameraPos;
	int32_t CamTableIdx;
	float CamKakudoY;
	float DefaultCamDir;
	struct Project_cam_t_array* gCamTable;
	struct Project_camCustom_t_o* gCamTypeB;
	struct Project_camCustom_t_o* gCamTypeC;
	struct Project_camCustom_t_o* gCamTypeD;
	struct Project_camCustom_t_o* gCamTypeP;
	int32_t NowCamType;
	float defaultDir;
	float CameraLengNow;
	int32_t CameraLengWait;
};
struct Project_libsdf_sdfGrPacketHeader_t_Fields {
	struct Project_libsdf_sdfGrPacketHeader_t_o* next;
	int32_t ctxt;
};
struct Project_SKIL176_Fields {
};
struct Project_libsdf_sdf3DViewportPacket_t_Fields : Project_libsdf_sdfGrPacketHeader_t_Fields {
	struct Project_libsdf_sdfCamera_o* cameraObject;
	struct Project_libsdf_sdf3DViewportPacket_t_o* traceSrc;
};
struct Project_Kernel_dds3KernelCore_Fields {
};
struct Project_Kernel_dds3KernelCore_StaticFields {
	struct Project_Kernel_dds3ProcessID_t_o* startinglistf;
	struct Project_Kernel_dds3ProcessID_t_o* startinglistl;
	int32_t startinglistcnt;
	struct Project_Kernel_dds3ProcessID_t_o* endinglistf;
	struct Project_Kernel_dds3ProcessID_t_o* endinglistl;
	int32_t endinglistcnt;
	struct Project_Kernel_dds3ProcessID_t_o* runninglistf;
	struct Project_Kernel_dds3ProcessID_t_o* runninglistl;
	int32_t runninglistcnt;
	struct Project_Kernel_dds3ProcessID_t_o* runprocess;
	int32_t uua_count;
	int32_t un_scene_max;
	struct UnityEngine_AsyncOperation_array* unSceneOp;
};
struct Project_Kernel_dds3ProcessFunc_t_Fields : System_MulticastDelegate_Fields {
};
struct Project_Kernel_shutdownfuncDelegate_Fields : System_MulticastDelegate_Fields {
};
struct Project_Kernel_dds3ProcessID_t_Fields {
	struct System_String_o* name;
	int32_t nameHash;
	uint32_t flag;
	int32_t priority;
	uint32_t starttime;
	uint32_t runtime;
	int32_t id;
	int32_t starttimer;
	int32_t shutdowntimer;
	struct Project_Kernel_dds3ProcessFunc_t_o* processfunc;
	struct Project_Kernel_shutdownfuncDelegate_o* shutdownfunc;
	Il2CppObject* workdata;
	struct Project_Kernel_dds3ProcessID_t_o* next;
	struct Project_Kernel_dds3ProcessID_t_o* prev;
};
struct Project_Kernel_DDS3_PRIORITY_Fields {
	int32_t value__;
};
