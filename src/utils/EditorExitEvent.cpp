/*
 as of aug 20 2024 US eastern daylight time,
 the following problems and/or missing bindings prevent this file
 from being ported to macos:
 // LevelEditorLayer class apparently being incomplete
*/
/*
#include "EditorExitEvent.hpp"
#include <Geode/modify/GameManager.hpp>
#include <Geode/binding/LevelEditorLayer.hpp>

// run on editor exit
class $modify(GameManager) {
    void returnToLastScene(GJGameLevel* level) {
        auto editor = LevelEditorLayer::get();
        if (editor && m_sceneEnum == 3) {
            EditorExitEvent().post();
        }
        GameManager::returnToLastScene(level);
    }
};
*/