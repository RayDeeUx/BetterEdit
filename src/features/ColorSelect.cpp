/*
 as of aug 20 2024 US eastern daylight time,
 the following problems and/or missing bindings prevent this file
 from being ported to macos:
 GJSpecialColorSelect::init()
*/
/*
#include <Geode/modify/GJSpecialColorSelect.hpp>

using namespace geode::prelude;

class $modify(GJSpecialColorSelect) {
	bool init(int p0, GJSpecialColorSelectDelegate* p1, ColorSelectType p2){

		if(((int) p2) == 1){
			p2 = (ColorSelectType)0;
		}

		return GJSpecialColorSelect::init(p0, p1, p2);
	}
};
*/