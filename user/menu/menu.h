#pragma once
#include <common.h>

namespace Small {
	class Menu {
	public:
		void Init();
		void Loop();
	public:
		bool initialized_;
		bool opened_;
	};
	inline Menu menu;
}