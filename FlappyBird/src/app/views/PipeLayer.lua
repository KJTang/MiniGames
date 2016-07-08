
local PipeLayer = class("PipeLayer", function()
    return cc.Layer:create()
end)

local visibleSize = cc.Director:getInstance():getVisibleSize()

function PipeLayer:ctor()
end

function PipeLayer:start()
    if self:getChildrenCount() ~= 0 then
        self:removeAllChildren(false)
    end

    local action = cc.RepeatForever:create(cc.Sequence:create(
        cc.CallFunc:create(function ()
            local newPipe = require("app.models.PipeSprite"):create():addTo(self)
            newPipe:setPosition(cc.p(visibleSize.width*1.5, 300 + math.random(-80, 80)))
            newPipe:start()
        end), 
        cc.DelayTime:create(3)
    ))
    self:runAction(action)
end

function PipeLayer:stop( ... )
    self:stopAllActions()
    local pipes = self:getChildren()
    for i, p in ipairs(pipes) do
        p:stop()
    end
end

return PipeLayer