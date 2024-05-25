#include <Geode/DefaultInclude.hpp>

// todo: CustomKeybinds on Mac
#ifdef GEODE_IS_WINDOWS

#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <utils/EditCommandExt.hpp>
#include <Geode/binding/EditButtonBar.hpp>

using namespace geode::prelude;
using namespace keybinds;

struct $modify(BEEditorUI, EditorUI) {
    $override
    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel))
            return false;

        this->defineKeybind("rotate-45-ccw"_spr, [this]() {
            this->transformObjectCall(EditCommand::RotateCCW45);
        });
        this->defineKeybind("rotate-45-cw"_spr, [this]() {
            this->transformObjectCall(EditCommand::RotateCW45);
        });
        this->defineKeybind("rotate-snap"_spr, [this]() {
            this->transformObjectCall(EditCommand::RotateSnap);
        });
        this->defineKeybind("show-scale"_spr, [this]() {
            if (auto scaleBtn = m_editButtonBar->m_buttonArray->objectAtIndex(m_editButtonBar->m_buttonArray->count() - 3)) {
                this->activateScaleControl(scaleBtn);
            }
        });
        this->defineKeybind("show-ui"_spr, [this]() {
            this->showUI(true);
        });
        this->defineKeybind("hide-ui"_spr, [this]() {
            this->showUI(false);
        });
        this->defineKeybind("select-all"_spr, [this]() {
            this->selectAll();
        });
        this->defineKeybind("select-all-left"_spr, [this]() {
            this->selectAllWithDirection(true);
        });
        this->defineKeybind("select-all-right"_spr, [this]() {
            this->selectAllWithDirection(false);
        });
        this->defineKeybind("move-obj-half-left"_spr, [this] {
            this->moveObjectCall(EditCommand::HalfLeft);
        });
        this->defineKeybind("move-obj-half-right"_spr, [this] {
            this->moveObjectCall(EditCommand::HalfRight);
        });
        this->defineKeybind("move-obj-half-up"_spr, [this] {
            this->moveObjectCall(EditCommand::HalfUp);
        });
        this->defineKeybind("move-obj-half-down"_spr, [this] {
            this->moveObjectCall(EditCommand::HalfDown);
        });
        this->defineKeybind("move-obj-quarter-left"_spr, [this] {
            this->moveObjectCall(EditCommandExt::QuarterLeft);
        });
        this->defineKeybind("move-obj-quarter-right"_spr, [this] {
            this->moveObjectCall(EditCommandExt::QuarterRight);
        });
        this->defineKeybind("move-obj-quarter-up"_spr, [this] {
            this->moveObjectCall(EditCommandExt::QuarterUp);
        });
        this->defineKeybind("move-obj-quarter-down"_spr, [this] {
            this->moveObjectCall(EditCommandExt::QuarterDown);
        });
        this->defineKeybind("move-obj-eighth-left"_spr, [this] {
            this->moveObjectCall(EditCommandExt::EighthLeft);
        });
        this->defineKeybind("move-obj-eighth-right"_spr, [this] {
            this->moveObjectCall(EditCommandExt::EighthRight);
        });
        this->defineKeybind("move-obj-eighth-up"_spr, [this] {
            this->moveObjectCall(EditCommandExt::EighthUp);
        });
        this->defineKeybind("move-obj-eighth-down"_spr, [this] {
            this->moveObjectCall(EditCommandExt::EighthDown);
        });
        this->defineKeybind("move-obj-big-left"_spr, [this] {
            this->moveObjectCall(EditCommand::BigLeft);
        });
        this->defineKeybind("move-obj-big-right"_spr, [this] {
            this->moveObjectCall(EditCommand::BigRight);
        });
        this->defineKeybind("move-obj-big-up"_spr, [this] {
            this->moveObjectCall(EditCommand::BigUp);
        });
        this->defineKeybind("move-obj-big-down"_spr, [this] {
            this->moveObjectCall(EditCommand::BigDown);
        });
        this->defineKeybind("save-editor-level"_spr, [this] {
            if (Mod::get()->template getSettingValue<bool>("no-save-confirmation")) {
                BEEditorUI::attemptToSaveLevel(1);
            } else {
                BEEditorUI::saveConfirmation("save this level", "Save", 1);
            }
        });
        this->defineKeybind("save-play-editor"_spr, [this] {
            if (Mod::get()->template getSettingValue<bool>("no-save-confirmation")) {
                BEEditorUI::attemptToSaveLevel(2);
            } else {
                BEEditorUI::saveConfirmation("save this level and playtest it", "Save", 2);
            }
        });
        this->defineKeybind("save-exit-editor"_spr, [this] {
            if (Mod::get()->template getSettingValue<bool>("no-save-confirmation")) {
                BEEditorUI::attemptToSaveLevel(3);
            } else {
                BEEditorUI::saveConfirmation("save this level and exit the editor", "Save and Exit", 3);
            }
        });
        
        return true;
    }

    void defineKeybind(const char* id, std::function<void()> callback) {
        this->template addEventListener<InvokeBindFilter>([=](InvokeBindEvent* event) {
            if (event->isDown()) {
                callback();
            }
            return ListenerResult::Propagate;
        }, id);
    }

    void saveConfirmation(std::string saveTypeForPopup, std::string saveTypeForButton, int mode) {
        createQuickPopup(
            "BetterEdit Level Saving",
            fmt::format("Are you sure you want to <cl>{}</c>?", saveTypeForPopup),
            "Cancel", fmt::format("{}", saveTypeForButton).c_str(),
            [](FLAlertLayer* alert, bool save) {
                if (save) {
                    BEEditorUI::attemptToSaveLevel(mode);
                }
            }
        );
    }

    void attemptToSaveLevel(int mode) {
        if (!(0 < mode && mode < 4)) { return; }
        if (auto editorPauseLayer = EditorPauseLayer::create(this->m_editorLayer)) {
            switch (mode) {
                default:
                    break;
                case 1:
                    editorPauseLayer->saveLevel();

                    FLAlertLayer::create(
                        "BetterEdit Level Saving",
                        "Your <cl>level</c> has been saved.",
                        "OK"
                    )->show();
                    break;
                case 2:
                    editorPauseLayer->onSaveAndPlay(nullptr); // may not work
                    break;
                case 3:
                    editorPauseLayer->onSaveAndExit(nullptr);
                    break;
            }
        } else {
            FLAlertLayer::create(
                "BetterEdit Level Saving Failed!",
                "Your <cl>level</c> <cr>could not </c> be saved. Please try again.",
                "OK"
            )->show();
        }
    }
};

$execute {
    BindManager::get()->registerBindable(BindableAction(
        "save-editor-level"_spr,
        "Save Current Editor Level",
        "Save the level you're currently editing",
        { Keybind::create(KEY_S, Modifier::Control) },
        Category::EDITOR
        ));
    BindManager::get()->registerBindable({
        "save-play-editor"_spr,
        "Save and Play Editor Level",
        "Saves and playtests the level you're currently editing",
        { Keybind::create(KEY_S, Modifier::Shift | Modifier::Control | Modifier::Alt) },
        Category::EDITOR
    });
    BindManager::get()->registerBindable({
        "save-exit-editor"_spr,
        "Save and Exit Editor Level",
        "Saves and exits the level you're currently editing",
        { Keybind::create(KEY_S, Modifier::Shift | Modifier::Control) },
        Category::EDITOR
    });
    BindManager::get()->registerBindable(BindableAction(
        "rotate-45-ccw"_spr,
        "Rotate 45 CCW",
        "Rotate the Selected Object(s) 45 Degrees Counter-Clockwise",
        { Keybind::create(KEY_Q, Modifier::Shift) },
        Category::EDITOR_MODIFY
    ));
    BindManager::get()->registerBindable(BindableAction(
        "rotate-45-cw"_spr,
        "Rotate 45 CW",
        "Rotate the Selected Object(s) 45 Degrees Clockwise",
        { Keybind::create(KEY_E, Modifier::Shift) },
        Category::EDITOR_MODIFY
    ));
    BindManager::get()->registerBindable(BindableAction(
        "rotate-snap"_spr,
        "Rotate Snap",
        "Rotate the Selected Object(s) to Match Adjacent Slopes",
        {},
        Category::EDITOR_MODIFY
    ));

    BindManager::get()->registerBindable(BindableAction(
        "select-all"_spr,
        "Select All",
        "Select All Object(s)",
        {},
        Category::EDITOR_MODIFY
    ));
    BindManager::get()->registerBindable(BindableAction(
        "select-all-left"_spr,
        "Select All Left",
        "Select All Object(s) Left of the Screen",
        {},
        Category::EDITOR_MODIFY
    ));
    BindManager::get()->registerBindable(BindableAction(
        "select-all-right"_spr,
        "Select All Right",
        "Select All Object(s) Right of the Screen",
        {},
        Category::EDITOR_MODIFY
    ));

    BindManager::get()->registerBindable(BindableAction(
        "show-scale"_spr,
        "Show Scale Control",
        "Show the object scaling controls",
        {},
        Category::EDITOR_UI
    ));
    // todo: toggle UI
    BindManager::get()->registerBindable(BindableAction(
        "show-ui"_spr,
        "Show UI",
        "",
        {},
        Category::EDITOR_UI
    ));
    BindManager::get()->registerBindable(BindableAction(
        "hide-ui"_spr,
        "Hide UI",
        "",
        {},
        Category::EDITOR_UI
    ));
    BindManager::get()->registerBindable({
        "move-obj-half-left"_spr,
        "Move Object Half Left",
        "Move Selected Object(s) half of a Block left (15 Units)",
        { Keybind::create(KEY_A, Modifier::Control | Modifier::Alt) },
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-half-right"_spr,
        "Move Object Half Right",
        "Move Selected Object(s) half of a Block right (15 Units)",
        { Keybind::create(KEY_D, Modifier::Control | Modifier::Alt) },
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-half-up"_spr,
        "Move Object Half Up",
        "Move Selected Object(s) half of a Block up (15 Units)",
        { Keybind::create(KEY_W, Modifier::Control | Modifier::Alt) },
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-half-down"_spr,
        "Move Object Half Down",
        "Move Selected Object(s) half of a Block down (15 Units)",
        { Keybind::create(KEY_S, Modifier::Control | Modifier::Alt) },
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-quarter-left"_spr,
        "Move Object Quarter Left",
        "Move Selected Object(s) quarter of a Block left (7.5 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-quarter-right"_spr,
        "Move Object Quarter Right",
        "Move Selected Object(s) quarter of a Block right (7.5 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-quarter-up"_spr,
        "Move Object Quarter Up",
        "Move Selected Object(s) quarter of a Block up (7.5 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-quarter-down"_spr,
        "Move Object Quarter Down",
        "Move Selected Object(s) quarter of a Block down (7.5 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-eighth-left"_spr,
        "Move Object Eighth Left",
        "Move Selected Object(s) eighth of a Block left (3.75 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-eighth-right"_spr,
        "Move Object Eighth Right",
        "Move Selected Object(s) eighth of a Block right (3.75 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-eighth-up"_spr,
        "Move Object Eighth Up",
        "Move Selected Object(s) eighth of a Block up (3.75 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-eighth-down"_spr,
        "Move Object Eighth Down",
        "Move Selected Object(s) eighth of a Block down (3.75 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-big-left"_spr,
        "Move Object Big Left",
        "Move Selected Object(s) 5 Blocks left (150 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-big-right"_spr,
        "Move Object Big Right",
        "Move Selected Object(s) 5 Blocks right (150 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-big-up"_spr,
        "Move Object Big Up",
        "Move Selected Object(s) 5 Blocks up (150 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
    BindManager::get()->registerBindable({
        "move-obj-big-down"_spr,
        "Move Object Big Down",
        "Move Selected Object(s) 5 Blocks down (150 Units)",
        {},
        Category::EDITOR_MOVE, true
    });
}

#endif
