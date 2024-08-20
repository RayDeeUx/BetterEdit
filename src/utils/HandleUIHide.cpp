/*
 as of aug 20 2024 US eastern daylight time,
 the following problems and/or missing bindings prevent this file
 from being ported to macos:
 // LevelEditorLayer class apparently being incomplete
 // GameManager class apparently being incomplete
 // CCMenuItemSpriteExtra class apparently being incomplete
 // no matching constructor for initialization of 'UIShowEvent'
 // no member named 'post' in 'UIShowEvent'
 // out-of-line definition of 'UIShowEvent' does not match any declaration in 'UIShowEvent'
 // out-of-line definition of 'UIShowFilter' does not match any declaration in 'UIShowFilter'
 // out-of-line definition of 'handle' does not match any declaration in 'UIShowFilter'
*/
/*
#include "HandleUIHide.hpp"
#include <Geode/modify/EditorUI.hpp>
#include <Geode/binding/LevelEditorLayer.hpp>
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>

class $modify(HideUI, EditorUI) {
    $override
    void showUI(bool show) {
        if (m_editorLayer->m_playbackMode == PlaybackMode::Playing) {
            // Playtest no ui option
            show = !GameManager::sharedState()->getGameVariable("0046");
        }

        EditorUI::showUI(show);
        UIShowEvent(this, show).post();

        m_currentLayerLabel->setVisible(show);

        auto lockBtn = static_cast<CCMenuItemSpriteExtra*>(
            this->getChildByID("layer-menu")->getChildByID("lock-layer"_spr)
        );
        if (lockBtn) {
            lockBtn->setVisible(show);
        }
        m_tabsMenu->setVisible(show && m_selectedMode == 2);
    }
};

UIShowEvent::UIShowEvent(EditorUI* ui, bool show) : ui(ui), show(show) {}

UIShowFilter::UIShowFilter(EditorUI* ui) : m_ui(ui) {}
ListenerResult UIShowFilter::handle(MiniFunction<Callback> fn, UIShowEvent* ev) {
    if (m_ui == ev->ui) {
        fn(ev);
    }
    return ListenerResult::Propagate;
}
*/