
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

local visibleSize = cc.Director:getInstance():getVisibleSize()

function MainScene:onCreate()
    self:initTouchEvent()
    self:initGameEvent()

    self:onGameLaunch()
end

function MainScene:onGameLaunch( ... )
    -- print("game launch")
    self:removeAllChildren(false)
    self.background = require("app.views.BackgroundLayer"):create():addTo(self)
    self.pipeLayer = require("app.views.PipeLayer"):create():addTo(self)
    self.bird = require("app.models.BirdSprite"):create():addTo(self)
    self.scoreLayer = require("app.views.ScoreLayer"):create():addTo(self)
    -- self.menuLayer = require("app.views.MenuLayer"):create():addTo(self)
    self.background:start()
    self.scoreLayer:start()
    -- event listener
    self.touchListener:setEnabled(true)
    -- pause game button
    local captureFile = "test.png"
    local btnPause = require("app.models.ButtonSprite"):create("button_pause.png", "button_pause.png", function()
        cc.utils:captureScreen(function(succeed, captureFile)
            if succeed then
                local pauseScene = cc.Scene:create()
                local background = cc.Sprite:create(captureFile):addTo(pauseScene):setPosition(display.center)
                local btnResume = require("app.models.ButtonSprite"):create("button_resume.png", "button_resume.png", function()
                    cc.Director:getInstance():getTextureCache():removeTextureForKey(captureFile)
                    cc.Director:getInstance():popScene()
                end):addTo(pauseScene)
                btnResume:setPosition(cc.p(15, 490))
                cc.Director:getInstance():pushScene(pauseScene)
            else
                print("Capture screen failed.")
            end
        end, captureFile)
    end):addTo(self)
    btnPause:setPosition(cc.p(15, 490))
end

function MainScene:onGameStart( ... )
    -- print("game start")
    self.pipeLayer:start()
    -- event listener
    self.touchListener:setEnabled(false)
    self.gameEndListener:setEnabled(true)
    -- collision detect
    self:scheduleUpdate(handler(self, self.update))
end

function MainScene:onGameEnd( ... )
    -- print("game end")
    self.bird:stop()
    self.background:stop()
    self.pipeLayer:stop()
    self.endLayer = require("app.views.EndLayer"):create():addTo(self)
    -- event listener
    self.gameEndListener:setEnabled(false)
    -- collision detect
    self:unscheduleUpdate()
end

function MainScene:initTouchEvent( ... )
    local function onTouchBegan( ... )
        local customEvent = cc.EventCustom:new("GAME_START_EVENT")
        self:getEventDispatcher():dispatchEvent(customEvent)
        return true
    end
    local function onTouchEnded( ... )
        return true
    end
    self.touchListener = cc.EventListenerTouchOneByOne:create()
    self.touchListener:setSwallowTouches(false)
    self.touchListener:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
    self.touchListener:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
    self:getEventDispatcher():addEventListenerWithSceneGraphPriority(self.touchListener, self)
end

function MainScene:initGameEvent( ... )
    self.gameLaunchListener = cc.EventListenerCustom:create("GAME_LAUNCH_EVENT", handler(self, self.onGameLaunch))
    self:getEventDispatcher():addEventListenerWithSceneGraphPriority(self.gameLaunchListener, self)

    self.gameStartListener = cc.EventListenerCustom:create("GAME_START_EVENT", handler(self, self.onGameStart))
    self:getEventDispatcher():addEventListenerWithSceneGraphPriority(self.gameStartListener, self)

    self.gameEndListener = cc.EventListenerCustom:create("GAME_END_EVENT", handler(self, self.onGameEnd))
    self:getEventDispatcher():addEventListenerWithSceneGraphPriority(self.gameEndListener, self)
end

function MainScene:update( ... )
    if self.bird:getPositionY() <= 112 or self.bird:getPositionY() >= visibleSize.height then -- 112 is land's height
        local customEvent = cc.EventCustom:new("GAME_END_EVENT")
        self:getEventDispatcher():dispatchEvent(customEvent)
        return
    end
    local birdRect = self.bird:getBoundingBox()
    for i, pipe in ipairs(self.pipeLayer:getChildren()) do
        local upRect = pipe:getUpBox()
        local downRect = pipe:getDownBox()
        if cc.rectIntersectsRect(birdRect, upRect) or cc.rectIntersectsRect(birdRect, downRect) then
            local customEvent = cc.EventCustom:new("GAME_END_EVENT")
            self:getEventDispatcher():dispatchEvent(customEvent)
            return
        end
    end
end

return MainScene
