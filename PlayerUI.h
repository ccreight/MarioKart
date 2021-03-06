#pragma once
#include "Math.h"
#include "UIComponent.h"
#include <vector>

class PlayerUI : public UIComponent
{
public:
	enum RaceState
	{
		Active,
		Won,
		Lost
	};
	PlayerUI(class Actor* owner);
	
	void Update(float deltaTime) override;
	
	void Draw(class Shader* shader);
	
	void OnLapChange(int lapNum);
	void SetRaceState(RaceState rs) { mRaceState = rs; }

protected:
	bool IsPlayerInFirst() const;
	std::vector<class Texture*> mLapTextures;
	class Texture* mGoTexture;
	class Texture* mReadyTexture;
	class Texture* mFirstTexture;
	class Texture* mSecondTexture;
	int mLapIndex = 0;
	float mLapDisplayTimer = 0.0f;
	float mGoDisplayTimer = 2.0f; // TODO: Change to 2.0f when done
	RaceState mRaceState = Active;
};
