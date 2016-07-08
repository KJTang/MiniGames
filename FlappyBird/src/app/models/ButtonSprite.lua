
local ButtonSprite = class("ButtonSprite", function()
    return cc.Sprite:create()
end)

local visibleSize = cc.Director:getInstance():getVisibleSize()

function ButtonSprite:ctor(releasedPic, pressedPic, callbackFunc)
    self.releasedPic = releasedPic
    self.pressedPic = pressedPic
    self.callbackFunc = callbackFunc

    local btnReleased = cc.Sprite:create(releasedPic):addTo(self)
    local btnPressed = cc.Sprite:create(pressedPic):addTo(self)

    local function onTouchBegan(touch, event)
        local target = event:getCurrentTarget()
        -- relative position
        local locationInNode = target:convertToNodeSpace(touch:getLocation())
        local rect = cc.rect(0, 0, target:getContentSize().width, target:getContentSize().height)
        if cc.rectContainsPoint(rect, locationInNode) then
            self.touchListener:setSwallowTouches(true)
            btnPressed:setVisible(true)
            btnReleased:setVisible(false)
            callbackFunc()
        end
        return true
    end
    local function onTouchEnded( ... )
        self.touchListener:setSwallowTouches(false)
        return true
    end
    self.touchListener = cc.EventListenerTouchOneByOne:create()
    self.touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
    self.touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
    self:getEventDispatcher():addEventListenerWithSceneGraphPriority(self.touchListener, btnReleased)
end

return ButtonSprite
