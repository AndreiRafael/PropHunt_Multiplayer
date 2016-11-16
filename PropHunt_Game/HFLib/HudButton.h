#pragma once
#include "Component.h"
#include "BoxCollider.h"
#include "Input.h"

class HudButton : public Component {
private:
	BoxCollider* collider;
	void(*function)() = nullptr;
	int m_w, m_h;
	int hh, hw;
	void Awake() {
		
	}

	void Start() {

	}

	void Update() {

	}
public:
	bool isClicked() {
		int x, y;
		HF_INPUT->GetMouseScreenPosition(&x, &y);
		if (HF_INPUT->GetMouseButtonDown(SDL_BUTTON_LEFT)) {
			if (x > gameObject->position.x - hw &&
				x < gameObject->position.x + hw &&
				y > gameObject->position.y - hh &&
				y < gameObject->position.y + hh) {
				if (function != nullptr)
					function();
				return true;
			}
		}
		return false;
	}

	void SetSize(int w, int h) {
		m_w = w;
		m_h = h;
		hh = h / 2;
		hw = w / 2;
	}

	void SetFunctionCall(void(*func)()) {
		function = func;
	}
};