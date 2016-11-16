#pragma once
#include "HifireLibrary.h"

class MapDrawer : public Component {
private:
	HudRenderer* renderer;
	bool show = false;
	void Awake() {
		gameObject->AddComponent<HudRenderer>();
		renderer = GetComponent<HudRenderer>();
		renderer->SetTexture("Assets/Hud/mapColors.png");
		renderer->DivideTiles(6, 1);
		renderer->SetEnabled(false);
	}

	void Update() {
		if (HF_INPUT->GetButtonDown(hfb_fire)) {
			show = !show;
			renderer->SetEnabled(show);
		}
	}
};