

#include "UILoadingBarTest_Editor.h"


// UILoadingBarTest_Editor

UILoadingBarTest_Editor::UILoadingBarTest_Editor()
    : _count(0)
{
    
}

UILoadingBarTest_Editor::~UILoadingBarTest_Editor()
{
    
}

void UILoadingBarTest_Editor::switchLoadMethod(cocos2d::CCObject *pSender)
{
    CCMenuItemToggle *item = (CCMenuItemToggle*)pSender;
    if (item->getSelectedIndex() == 0){
        _layout->removeAllChildrenWithCleanup(true);
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILoadingBar_Editor/ui_loadingbar_editor_1.json"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
    }else{
        _layout->removeAllChildrenWithCleanup(true);
        _layout->removeFromParentAndCleanup(true);
        
        _layout = static_cast<Layout*>(GUIReader::getInstance()->widgetFromBinaryFile("cocosui/UIEditorTest/UILoadingBar_Editor/ui_loadingbar_editor_1.csb"));
        _touchGroup->addWidget(_layout);
        
        this->configureGUIScene();
    }
}

void UILoadingBarTest_Editor::configureGUIScene()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSize rootSize = _layout->getSize();
    _touchGroup->setPosition(CCPoint((screenSize.width - rootSize.width) / 2,
                                     (screenSize.height - rootSize.height) / 2));
    
    Layout* root = static_cast<Layout*>(_touchGroup->getWidgetByName("root_Panel"));
    
    ui::Label* back_label = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "back"));
    back_label->addTouchEventListener(this, toucheventselector(UIScene_Editor::toGUIEditorTestScene));
    
    _sceneTitle = static_cast<ui::Label*>(UIHelper::seekWidgetByName(root, "UItest"));
    
    LoadingBar* loadingBar_left_to_right = dynamic_cast<LoadingBar*>(UIHelper::seekWidgetByName(root, "LoadingBar_856"));
    loadingBar_left_to_right->setPercent(0);
    
    LoadingBar* loadingBar_right_to_left = dynamic_cast<LoadingBar*>(UIHelper::seekWidgetByName(root, "LoadingBar_857"));
    loadingBar_right_to_left->setPercent(0);
}

bool UILoadingBarTest_Editor::init()
{
    if (UIScene_Editor::init())
    {
        scheduleUpdate();
        
        _layout = static_cast<Layout*>(GUIReader::getInstance()->widgetFromJsonFile("cocosui/UIEditorTest/UILoadingBar_Editor/ui_loadingbar_editor_1.json"));
        _touchGroup->addWidget(_layout);
       
        this->configureGUIScene();
        return true;
    }
    
    return false;
}

void UILoadingBarTest_Editor::update(float delta)
{
    _count++;
    if (_count > 100)
    {
        _count = 0;
    }
    
    Layout* root = static_cast<Layout*>(_touchGroup->getWidgetByName("root_Panel"));
    
    LoadingBar* loadingBar_left_to_right = dynamic_cast<LoadingBar*>(UIHelper::seekWidgetByName(root, "LoadingBar_856"));
    loadingBar_left_to_right->setPercent(_count);
    
    LoadingBar* loadingBar_right_to_left = dynamic_cast<LoadingBar*>(UIHelper::seekWidgetByName(root, "LoadingBar_857"));
    loadingBar_right_to_left->setPercent(_count);
}

void UILoadingBarTest_Editor::toCocosGUITestScene(cocos2d::CCObject *sender, TouchEventType type)
{
    switch (type)
    {
        case TOUCH_EVENT_ENDED:
        {
            unscheduleUpdate();
            
            UIScene_Editor::toGUIEditorTestScene(sender, type);            
        }
            break;
            
        default:
            break;
    }
}