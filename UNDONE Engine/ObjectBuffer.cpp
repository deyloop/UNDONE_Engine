/******************************************************************************
File	:	ObjectBuffer..cpp
Author	:	Anurup Dey
******************************************************************************/
///////////////////////////////////////////////////////////////////////////////
#include "ObjectBuffer.h"
/*/////////////////////////////////////////////////////////////////////////////
							WARNING! EDIT AT YOUR OWN RISK!
/////////////////////////////////////////////////////////////////////////////*/

//Prototypes of templates used.
template<typename storagetype>
bool Reallocating(vector<storagetype>& vec_to_check);
template<typename storagetype>
void Reallocate_vector(vector<storagetype>& storageVector,
					   list<storagetype*>& storageList);
template<typename storagetype>
storagetype** CreateNew(vector<storagetype>& storageVector,
						list<storagetype*>& storageList);

/*-----------------------------------------------------------------------------
Default Constructor.
-----------------------------------------------------------------------------*/
ObjectBuffer::ObjectBuffer(){

}
/*-----------------------------------------------------------------------------
Template function for checking if a container vector is about to relocate or
not.
Parameters:
[IN] storagetype	-	the type of objects that are stored
[IN] vec_to_check	-	the vector to check.
Returns:
true if about to resize, false otherwise.
-----------------------------------------------------------------------------*/
template<typename storagetype>
bool Reallocating(vector<storagetype>& vec_to_check) {
	if (!vec_to_check.empty( )) {
		if (vec_to_check.size( )==vec_to_check.capacity( )) {
			//things gonna change
			return true;
		}
	}
	return false;
}

/*-----------------------------------------------------------------------------
Called when a vector reallocates to update the corresponding linked list.
Parameters:
[IN] storagetype	-	the type of objects that are stored.
[IN] storageVector	-	the vector (which is reallocating)
[IN] storageList	-	the linked list which will be updated.
-----------------------------------------------------------------------------*/
template<typename storagetype>
void Reallocate_vector(vector<storagetype>& storageVector,
					   list<storagetype*>& storageList) {
	int i = 0;
	for (auto& ref_in_list:storageList) {
		ref_in_list = &storageVector[i];
		i++;
	}
	//NOTE: this doesn't yet allow for rearrangement of objects in the 
	//vector, so don't try that yet.
}

/*-----------------------------------------------------------------------------
Template function that adds an object to the buffer by creating an instance fir
-st and the returns a pointer-to-pointer to that object created.
Para meters:
[IN] storagetype	-	the type of objects that are stored.
[IN] storageVector	-	the vector (which is reallocating)
[IN] storageList	-	the linked list.
-----------------------------------------------------------------------------*/
template<typename storagetype>
storagetype** CreateNew(vector<storagetype>& storageVector,
						list<storagetype*>& storageList) {
	bool reallocate_list = Reallocating<storagetype>(storageVector);

	storagetype object;
	storageVector.push_back(object);

	if (reallocate_list) {
		Reallocate_vector<storagetype>(storageVector, storageList);
	}

	storageList.push_back(&storageVector.back( ));
	return &storageList.back( );
}

/*-----------------------------------------------------------------------------
Creates a new 3d Graphics object, Adds it to the buffer and returns a pointer 
to the reference to it.
-----------------------------------------------------------------------------*/
_3DGraphic** ObjectBuffer::CreateNew3DGraphic(){
	_3DGraphic** object = CreateNew<_3DGraphic>(m_3DGraphics, m_3DGraphicList);
	//Then since 3d graphics are graphical objects as well, 
	//Add this to the list of graphical objects.
	AddGraphicalObject((GraphicalObject*)&m_3DGraphics.back());

	return &m_3DGraphicList.back(); 
	//and thats the end of all the wierd vector juggling...
}

/*-----------------------------------------------------------------------------
Creates an new shader and adds it to the buffer. Then returns a referance to 
that shader. This shader can then be used in any number of programs.
-----------------------------------------------------------------------------*/
Shader** ObjectBuffer::CreateNewShader(){
	return CreateNew<Shader>(m_Shaders, m_ShaderList);
}

/*-----------------------------------------------------------------------------
Creates a ShaderProgram, adds it to the buffer, and returns a referance to it.
-----------------------------------------------------------------------------*/
ShaderProgram** ObjectBuffer::CreateNewShaderProgram(){
	return CreateNew<ShaderProgram>(m_ShaderPrograms, m_ShaderProgramList);
}

/*-----------------------------------------------------------------------------
Adds a pointer to a graphical object so that the list of all graphical objects 
can be retrieved later.
Parameters:
[IN]	obj	-	 the object to be added.
-----------------------------------------------------------------------------*/
void ObjectBuffer::AddGraphicalObject(GraphicalObject* obj){
	for (auto object : m_GraphicalObjects)
	{
		if (object == obj) return;
	}
	//NOTE: Graphical objects are also simple objects...
	m_GraphicalObjects.push_back(obj);

	AddSimpleObject((SimpleObject*)obj);
}

/*-----------------------------------------------------------------------------
Adds a pointer to a simple object so that the list of all simple objects
can be retrieved later.
Parameters:
[IN]	obj	-	 the object to be added.
-----------------------------------------------------------------------------*/
void ObjectBuffer::AddSimpleObject(SimpleObject* obj){
	for (auto object : m_SimpleObjects){
		if (object == obj) return;
	}

	m_SimpleObjects.push_back(obj);
}

/*-----------------------------------------------------------------------------
Summary:	Removes an object from the buffer.
Parameters:
[in]	*object	- pointer to the object to be removed.
------------------------------------------------------------------------------*/
void ObjectBuffer::RemoveObject(SimpleObject* object)
{
	//loop through the simple object buffer>
	for (unsigned int i = 0; i < m_SimpleObjects.size(); i++)
	{
		//find the object.
		if (m_SimpleObjects[i] == object)
		{
			//remove the object.
			m_SimpleObjects.erase(m_SimpleObjects.begin() + i);
			break;
		}
	}
}


void ObjectBuffer::RemoveObject(GraphicalObject* object){
	//loop through the graphical object buffer>
	for (unsigned int i = 0; i < m_GraphicalObjects.size(); i++)
	{
		//find the object.
		if (m_GraphicalObjects[i] == object)
		{
			//remove the object.
			m_GraphicalObjects.erase(m_GraphicalObjects.begin() + i);
			//Since graphical objects are also registered as simple objects,
			//We have to remove them from the simple object list as well.
			RemoveObject((SimpleObject*)object);
			break;
		}
	}
}

void ObjectBuffer::RemoveObject(_3DGraphic** obj){
	//Okay.. so this is pretty hard to do. the object in the vector is first
	//removed by first swiping it with the last element and the deleting the last
	//element by popping it out. Then the refference in the list has to be taken 
	//care of. After that, the references in the other vectors are removed,
	//like the GraphicalObject vector and the SimpleObject vector.					//somethings are so damn hard to get right.
	
	//So first we find the object to be removed										
	for (unsigned int i = 0; i < m_3DGraphics.size(); i++){
		if (*obj == &m_3DGraphics[i]){//really, who understands pointers so much?
			//luckily, we find the object..
			//so now we swipe it
			m_3DGraphics[i] = m_3DGraphics.back();	//Now there are two copies
													//of this last element.
			//Now lets make the pointer of the last object in the list
			//point to this place in the vector.
			obj = &m_3DGraphicList.back();

			//now it's time to remove the deleted object.
			//first from the list.
			m_3DGraphicList.remove(*obj);

			//and now the last element in the vector
			m_3DGraphics.pop_back();
			break; //phew!
		}
	}
}																			//They are so damn hard to figure out initially..
																					//...but when they are done, the just have a charm of thier own.
void ObjectBuffer::DeleteShader(Shader** shader){
	Shader* point = *shader;
	point->DeleteShader();

	//So first we find the object to be removed	
	for (unsigned int i = 0; i < m_Shaders.size(); i++){
		if (*shader == &m_Shaders[i]){//really, who understands pointers so much?
			//luckily, we find the object..
			//so now we swipe it
			m_Shaders[i] = m_Shaders.back();	//Now there are two copies
												//of this last element.
			//Now lets make the pointer of the last object in the list
			//point to this place in the vector.
			shader = &m_ShaderList.back();

			//now it's time to remove the deleted object.
			//first from the list.
			m_ShaderList.remove(*shader);

			//and now the last element in the vector
			m_Shaders.pop_back();
			break; //phew!
		}
	}
}

void ObjectBuffer::DeleteShaderProgram(ShaderProgram** prog){
	ShaderProgram* point = *prog;
	point-> DeleteProgram();

	//So first we find the object to be removed										
	for (unsigned int i = 0; i < m_ShaderPrograms.size(); i++){
		if (*prog == &m_ShaderPrograms[i]){//really, who understands pointers so much?
			//luckily, we find the object..
			//so now we swipe it
			m_ShaderPrograms[i] = m_ShaderPrograms.back();	//Now there are two copies
			//of this last element.
			//Now lets make the pointer of the last object in the list
			//point to this place in the vector.
			prog = &m_ShaderProgramList.back();

			//now it's time to remove the deleted object.
			//first from the list.
			m_ShaderProgramList.remove(*prog);

			//and now the last element in the vector
			m_ShaderPrograms.pop_back();
			break; //phew!
		}
	}
}

void ObjectBuffer::DeleteAllObjects(){
	m_ShaderList.clear();
	m_ShaderProgramList.clear();
	m_3DGraphicList.clear();
}