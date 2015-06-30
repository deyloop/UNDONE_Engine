#ifndef _AUTO_MACRO_GENERATION_
#define _AUTO_MACRO_GENERATION_
#define GENERATE_FUNCTIONS_WITH_DEF(type) \
	 void DeleteAll_ ## type (OwnerShip ownership = 0);\
	 DPointer<type> CreateNew_ ## type (OwnerShip ownership = 0);\
	 DPointer<type> Get_ ## type ## _ByName (const char* name, OwnerShip ownership = 0);
#define GENERATE_FUNCTION_DEFINITIONS(x)\
	void DObjectBuffer::DeleteAll_ ## x (OwnerShip ownership){\
		DeleteAll<x>(ownership);\
		}\
	DPointer<x> DObjectBuffer::CreateNew_ ## x (OwnerShip ownership){\
		return CreateNew<x>(ownership);\
		}\
	DPointer<x> DObjectBuffer::Get_ ## x ## _ByName (const char* name, OwnerShip ownership){\
		return GetComponentByNameOfType<x>(name, ownership);\
		}
#define GENERATE_FUNCTIONS(type) \
	virtual void DeleteAll_ ## type (OwnerShip ownership = 0) = 0;\
	virtual DPointer<type> CreateNew_ ## type (OwnerShip ownership = 0) = 0;\
	virtual DPointer<type> Get_ ## type ## _ByName (const char* name, OwnerShip ownership = 0) = 0;
#endif

#define GENERATE_DEFINITON_MACROS(GEN)(\
	# ## ifdef _PASTE_DECLARATIONS_FOR_DOBJECTBUFFER_\
		GENERATE_FUNCTIONS_WITH_DEF(GEN)\
	# ## endif )


#ifdef _PASTE_DECLARATIONS_FOR_DOBJECTBUFFER_
	GENERATE_FUNCTIONS_WITH_DEF(GameObject)
	GENERATE_FUNCTIONS_WITH_DEF(WorldTransform)
	GENERATE_FUNCTIONS_WITH_DEF(Mesh)
	GENERATE_FUNCTIONS_WITH_DEF(GraphicMaterial)
	GENERATE_FUNCTIONS_WITH_DEF(_3DGraphic)
	GENERATE_FUNCTIONS_WITH_DEF(_2DGraphic)
	GENERATE_FUNCTIONS_WITH_DEF(Texture)
	GENERATE_FUNCTIONS_WITH_DEF(Shader)
	GENERATE_FUNCTIONS_WITH_DEF(ShaderProgram)
#endif

#ifdef _PASTE_DEFINITIONS_FOR_DOBJECTBUFFER_
	GENERATE_FUNCTION_DEFINITIONS(GameObject);
	GENERATE_FUNCTION_DEFINITIONS(WorldTransform);
	GENERATE_FUNCTION_DEFINITIONS(Mesh);
	GENERATE_FUNCTION_DEFINITIONS(GraphicMaterial);
	GENERATE_FUNCTION_DEFINITIONS(_3DGraphic);
	GENERATE_FUNCTION_DEFINITIONS(_2DGraphic);
	GENERATE_FUNCTION_DEFINITIONS(Texture);
	GENERATE_FUNCTION_DEFINITIONS(Shader);
	GENERATE_FUNCTION_DEFINITIONS(ShaderProgram);
#endif
