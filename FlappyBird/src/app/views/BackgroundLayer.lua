
local BackgroundLayer = class("BackgroundLayer", function()
    return cc.Layer:create()
end)

local visibleSize = cc.Director:getInstance():getVisibleSize()
local landMoveSpeed = 3.5

function BackgroundLayer:ctor()
    local bg = cc.Sprite:create("bg_day.png"):addTo(self)
    bg:setPosition(cc.p(visibleSize.width/2, visibleSize.height/2))

    self.land1 = cc.Sprite:create("land.png"):addTo(self)
    self.land1:setAnchorPoint(cc.p(0, 0))
    self.land1:setPosition(cc.p(0, 0))

    self.land2 = cc.Sprite:create("land.png"):addTo(self)
    self.land2:setAnchorPoint(cc.p(0, 0))
    self.land2:setPosition(cc.p(visibleSize.width, 0))
end

function BackgroundLayer:start( ... )
    transition.execute(self.land1, cc.RepeatForever:create(cc.Sequence:create(
        cc.MoveBy:create(landMoveSpeed, cc.p(-visibleSize.width, 0)), 
        cc.CallFunc:create(function()
            self.land1:setPositionX(0)
        end)
    )), {})
    transition.execute(self.land2, cc.RepeatForever:create(cc.Sequence:create(
        cc.MoveBy:create(landMoveSpeed, cc.p(-visibleSize.width, 0)), 
        cc.CallFunc:create(function()
            self.land2:setPositionX(visibleSize.width)
        end)
    )), {})
end

function BackgroundLayer:stop( ... )
    self.land1:stopAllActions()
    self.land2:stopAllActions()
end

return BackgroundLayer