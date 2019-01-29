#ifndef SpriteCollectionManagerFile
#define SpriteCollectionManagerFile
#include "headers/SpriteData.h"
#include <vector>

class SpriteCollectionManager {
private:
	std::vector<SpriteData*> spriteData;
public:
	int CheckSpriteDataExistence(const std::string& name);
	SpriteData* GetSpriteByName(const std::string& name);
	void CreateTextures(SDL_Renderer* renderer);
	void PushBack(SpriteData* data);

	SpriteCollectionManager();
	~SpriteCollectionManager();
};
#endif