
local ScoreLayer = class("ScoreLayer", function()
    return cc.Layer:create()
end)

local visibleSize = cc.Director:getInstance():getVisibleSize()

function ScoreLayer:ctor()
    self.score = 0
    self.scoreListener = cc.EventListenerCustom:create("SCORE_INCREASE_EVENT", handler(self, self.onScoreIncrease))
    self:getEventDispatcher():addEventListenerWithSceneGraphPriority(self.scoreListener, self)

    cc.SpriteFrameCache:getInstance():addSpriteFrames("number.plist")
    self.sprite = require("app.models.ScoreSprite"):create(0):addTo(self)
    self.sprite:setPosition(cc.p(visibleSize.width/2, 400))
end

function ScoreLayer:start()
    self.score = 0
end

function ScoreLayer:stop( ... )

end

function ScoreLayer:onScoreIncrease( ... )
    self.score = self.score + 1
    -- print("current score:"..self.score)
    self.sprite:removeFromParent(false)
    self.sprite = require("app.models.ScoreSprite"):create(self.score):addTo(self)
    self.sprite:setPosition(cc.p(visibleSize.width/2, 400))
end

return ScoreLayer