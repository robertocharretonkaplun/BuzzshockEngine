/**
* @file buSceneGraph.h
* @version 01Nov2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
* @brief
* Ref: Game Programming Patterns: Object Pool (page 305)
*/
#pragma once
#include <buPrerequisitesCore.h>
#include <buGameObject.h>
#include <buResourceManager.h>
#include <buCommons.h>

namespace buEngineSDK {
	class buSceneGraph	{
	public:
		/**
		 * @brief Default constructor
		 */
		buSceneGraph() = default;

		/**
		 * @brief Default destructor
		 */
		~buSceneGraph() = default;

		/**
		 * @brief Method in charge of updating the objects.
		 */
		void
		update(buVector3F _pos, buVector3F _rot,
           buVector3F _scal, float _angle);

		/**
		 * @brief Method in charge of rendering the objects.
		 */
		void 
		render(TopologyType::E _typology);

		/**
		 * @brief Method in charge of destroying the objects.
		 */
		void 
		destroy();

		/**
		 * @brief Method in charge of manage the used objects in the scene.
		 */
		void
		poolOfObjects();

		/**
		 * @brief Method in charge of adding an object to the game object vec.
		 */
		void
		addGameObject(String _filepath);

		/**
		 * @brief Method in charge of setting a selected object.
		 */
		void 
		setSelectedGO(int32 _index);

		/**
		 * @brief Method in charge of getting the selectef game object.
		 */
		buGameObject
		getSelectedGO();

		/**
		 * @brief Method in charge of adding a texture to the selected object.
		 */
		void
		addTexToSelectedObj(SPtr<buCoreTexture2D> tmpTex);

	public:
		Vector<buGameObject> m_gameObjects;
		uint32 m_amountOfGameObjects = 20;
		int32 m_selectedGO = 0;
	private:
		Vector<buGameObject> m_inUseGameObjects;
		Vector<buGameObject> m_notInUseGameObjects;
	};
}
