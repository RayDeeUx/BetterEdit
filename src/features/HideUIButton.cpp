#include <Geode/modify/EditorUI.hpp>
#include <Geode/binding/CCMenuItemToggler.hpp>
#include <Geode/binding/LevelEditorLayer.hpp>
#include <Geode/ui/BasedButtonSprite.hpp>
#include <Geode/utils/cocos.hpp>
#include <utils/HandleUIHide.hpp>

using namespace geode::prelude;

class $modify(HideButtonUI, EditorUI) {
    struct Fields {
        CCMenuItemToggler* hideToggle = nullptr;
    };
    
    $override
    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel))
            return false;
        
        if (auto menu = this->getChildByID("undo-menu")) {
            auto unhideSpr = CircleButtonSprite::createWithSpriteFrameName(
                "eye-off.png"_spr, 1.f, CircleBaseColor::Gray, CircleBaseSize::Tiny
            );
            unhideSpr->setOpacity(105);
            static_cast<CCSprite*>(unhideSpr->getTopNode())->setOpacity(105);
            auto hideSpr   = CircleButtonSprite::createWithSpriteFrameName(
                "eye-on.png"_spr, 1.f, CircleBaseColor::Green, CircleBaseSize::Tiny
            );

            m_fields->hideToggle = CCMenuItemToggler::create(
                hideSpr, unhideSpr, this, menu_selector(HideButtonUI::onHide)
            );
            m_fields->hideToggle->setID("hide-ui-toggle"_spr);
            m_fields->hideToggle->m_notClickable = true;
            menu->addChild(m_fields->hideToggle);
            menu->updateLayout();

            // attempted
            /*
            auto tmpToggle = CCMenuItemToggler::create(
                hideSpr, unhideSpr, this, menu_selector(HideButtonUI::onHide)
            );
            tmpToggle->setID("hide-ui-toggle-temp"_spr);
            tmpToggle->m_notClickable = true;
            menu->addChild(tmpToggle);
            menu->updateLayout();
            auto newPosition = tmpToggle->convertToWorldSpace(tmpToggle->getPosition());
            tmpToggle->removeMeAndCleanup();
            auto newMenu = CCMenu::create();
            m_fields->hideToggle = CCMenuItemToggler::create(
                hideSpr, unhideSpr, lel, menu_selector(HideButtonUI::onHide)
            );
            m_fields->hideToggle->setID("hide-ui-toggle"_spr);
            m_fields->hideToggle->setPosition(newPosition);
            newMenu->addChild(m_fields->hideToggle);
            newMenu->setPosition(0, 0);
            newMenu->updateLayout();
            lel->addChild(newMenu, 1);
            lel->updateLayout();
            */
        }

        return true;
    }

    $override
    void showUI(bool show) {
        EditorUI::showUI(show);
    }

    void onHide(CCObject*) {
        EditorUI::setVisible(m_fields->hideToggle->isToggled());
        if (m_fields->hideToggle) {
            m_fields->hideToggle->toggle(!EditorUI::isVisible());
            m_fields->hideToggle->setVisible(m_editorLayer->m_playbackMode != PlaybackMode::Playing);
        }
    }
};
