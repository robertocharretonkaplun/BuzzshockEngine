#include "buResourceManager.h"
namespace buEngineSDK {

buResourceManager& g_resourceManager() {
	return buResourceManager::instance();
}
}
