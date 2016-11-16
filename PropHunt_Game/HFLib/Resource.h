#pragma once
#include "HifireLibrary.h"

class Resource : public Component {
public:
	//1- arvore 2-pedra
	int type;
	int stage = 0;
	//"destruir" quando chegar a 0
	float total;
	float amount;
	Renderer* renderer;

	void Set(float p_total, int p_type) {
		total = p_total;
		amount = total;
		type = p_type;
	}

	float Hit(float p_amount) {
		if (type != 4) {
			// caso n seja comida pois comida é infinito
			amount -= p_amount;
			if (amount < 0)
				p_amount += amount;
			if (stage == 0) {
				if (amount / total < 0.6f) {
					stage = 1;
					renderer->SetTileCoordinates(1, 0);
				}
			}
			if (stage == 1) {
				if (amount / total < 0.3f) {
					stage = 2;
					renderer->SetTileCoordinates(2, 0);
				}
			}

			if (stage == 2) {
				if (amount / total < 0.0f) {
					stage = 3;
					renderer->SetTileCoordinates(3, 0);
				}
			}
		}
		return p_amount;
	}
};
