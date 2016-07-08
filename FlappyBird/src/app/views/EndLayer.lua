local EndLayer = class("EndLayer", function ()
    return cc.Layer:create()
end)

local visibleSize = cc.Director:getInstance():getVisibleSize()

function EndLayer:ctor( ... )
    local black = cc.LayerColor:create(cc.c4b(0, 0, 0, 255)):addTo(self)
    black:runAction(cc.Sequence:create(
        cc.DelayTime:create(0.05), 
        cc.RemoveSelf:create(false)
    ))

    local btn = require("app.models.ButtonSprite"):create("button_ok.png", "button_ok.png", function()
        local customEvent = cc.EventCustom:new("GAME_LAUNCH_EVENT")
        self:getEventDispatcher():dispatchEvent(customEvent)
    end):addTo(self)
    btn:setPosition(cc.p(visibleSize.width/2, visibleSize.height/2))
end

return EndLayer