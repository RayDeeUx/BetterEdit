/*
 as of aug 20 2024 US eastern daylight time,
 the following change(s) w(as/ere) made to allow this file
 to be ported to macos:
 // added new include directive: //#include <Geode/utils/cocos.hpp>//
*/
#include "Editor.hpp"
#include <Geode/utils/cocos.hpp>

std::vector<GameObject*> getSelectedObjects(EditorUI* ui) {
    if (ui->m_selectedObject) {
        return std::vector<GameObject*>({ ui->m_selectedObject });
    }
    else {
        return ccArrayToVector<GameObject*>(ui->m_selectedObjects);
    }
}
