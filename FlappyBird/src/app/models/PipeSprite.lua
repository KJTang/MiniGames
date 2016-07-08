
local PipeSprite = class("PipeSprite", function()
    return cc.Sprite:create()
end)

local pipeMoveSpeed = 6

local visibleSize = cc.Director:getInstance():getVisibleSize()

function PipeSprite:ctor()
    self.pipeUp = cc.Sprite:create("pipe_up.png"):addTo(self)
    self.pipeDown = cc.Sprite:create("pipe_down.png"):addTo(self)
    self.pipeUp:setPositionY(-225)
    self.pipeDown:setPositionY(225)
    -- increase score
    self:scheduleUpdate(handler(self, self.update))
end

function PipeSprite:start()
    transition.execute(self, cc.Spawn:create(
        cc.MoveBy:create(pipeMoveSpeed, cc.p(-visibleSize.width*2, 0)), 
        cc.Sequence:create(
            cc.DelayTime:create(pipeMoveSpeed), 
            cc.RemoveSelf:create(false)
        )
    ), {})
end

function PipeSprite:stop( ... )
    self:stopAllActions()
end

function PipeSprite:update( ... )
    if self:getPositionX()+self.pipeUp:getContentSize().width/2 < visibleSize.width/2 then
        local customEvent = cc.EventCustom:new("SCORE_INCREASE_EVENT")
        self:getEventDispatcher():dispatchEvent(customEvent)
        self:unscheduleUpdate()
    end
end

function PipeSprite:getUpBox( ... )
    local size = self.pipeUp:getContentSize()
    local rect = cc.rect(
        self.pipeUp:getPositionX()+self:getPositionX()-size.width/2, 
        self.pipeUp:getPositionY()+self:getPositionY()-size.height/2, 
        size.width, 
        size.height
    )
    return rect
end

function PipeSprite:getDownBox( ... )
    local size = self.pipeDown:getContentSize()
    local rect = cc.rect(
        self.pipeDown:getPositionX()+self:getPositionX()-size.width/2, 
        self.pipeDown:getPositionY()+self:getPositionY()-size.height/2, 
        size.width, 
        size.height
    )
    return rect
end

return PipeSprite
