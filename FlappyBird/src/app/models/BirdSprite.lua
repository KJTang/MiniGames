
local BirdSprite = class("BirdSprite", function()
    return cc.Sprite:create()
end)

local visibleSize = cc.Director:getInstance():getVisibleSize()
local landHeight = 112
local jumpHeight = 100

function BirdSprite:ctor()
    self:setPosition(display.center)

    self.bird_ = display.newSprite()
    self.bird_:addTo(self)

    display.loadSpriteFrames("bird.plist", "bird.png")
    local frames = display.newFrames("bird1_%d.png", 0, 3)
    local animation = display.newAnimation(frames, 0.1)
    -- display.setAnimationCache("bird1", animation)
    -- self.bird_:playAnimationForever(display.getAnimationCache("bird1"))
    self.bird_:playAnimationForever(animation)

    -- react to touch event
    local function onTouchBegan( ... )
        self:stopAllActions()
        -- action when touch screen
        local up = cc.EaseIn:create(
            cc.Spawn:create(
                cc.RotateTo:create(0.2, -30), 
                cc.MoveBy:create(0.3, cc.p(0, jumpHeight))
            ), 
            0.5
        )
        local down = cc.EaseOut:create(
            cc.Spawn:create(
                cc.RotateTo:create(
                    self:getPositionY()/visibleSize.height*1.5, 
                    90
                ), 
                cc.MoveTo:create(
                    self:getPositionY()/visibleSize.height*1.5, 
                    cc.p(visibleSize.width/2, landHeight)
                )
            ), 
            0.5 
        )
        self:runAction(cc.Sequence:create(
            up, 
            down
        ))
        return true
    end
    local function onTouchEnded( ... )
        return true
    end
    self.touchListener = cc.EventListenerTouchOneByOne:create()
    self.touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
    self.touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
    self:getEventDispatcher():addEventListenerWithSceneGraphPriority(self.touchListener, self)
end

function BirdSprite:start()
    -- 
end

function BirdSprite:stop()
    self:stopAllActions()
    self.bird_:stopAllActions()
    self.touchListener:setEnabled(false)
    transition.execute(self, cc.EaseOut:create(
        cc.Spawn:create(
            cc.RotateTo:create(
                self:getPositionY()/visibleSize.height*0.75, 
                90
            ), 
            cc.MoveTo:create(
                self:getPositionY()/visibleSize.height*0.75, 
                cc.p(visibleSize.width/2, landHeight)
            )
        ), 
        0.5 
    ), {
    onComplete = function()
    end
    })
end

return BirdSprite
