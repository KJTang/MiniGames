local MenuLayer = class("MenuLayer", function ()
    return cc.Layer:create()
end)

local visibleSize = cc.Director:getInstance():getVisibleSize()

function MenuLayer:ctor( ... )
    local btnPause = require("app.models.ButtonSprite"):create("button_pause.png", "button_pause.png", function()
        cc.utils:captureScreen(handler(self, self.pauseGame), "test.png")
        -- self:pauseGame()
    end):addTo(self)
    btnPause:setPosition(cc.p(visibleSize.width/2, visibleSize.height/2))
end

function MenuLayer:pauseGame(succeed, outputFile)
    print("pause")
    -- local rt = cc.RenderTexture:create(visibleSize.width, visibleSize.height)
    -- rt:beginWithClear()
    -- self:getParent:visit()
    -- rt:end()

    --首先将之前截图显示的图片remove掉
    -- cc.Director:getInstance():getTextureCache():removeTextureForKey(fileName)

    local pauseScene = cc.Scene:create()
    cc.Director:getInstance():pushScene(pauseScene)
    local test = cc.Sprite:create("button_ok.png"):addTo(pauseScene)

    local btnResume = require("app.models.ButtonSprite"):create("button_resume.png", "button_pausresume", function()
        cc.Director:getInstance():popScene()
    end):addTo(pauseScene)
    -- btnResume:setPosition(cc.p(visibleSize.width/2, visibleSize.height/2))
    --captureScreen()会传出两个参数跟回调方法，succeed：表示截屏是否成功，outputFile传出文件名 —— 在onCapture中，已经定义了文件名
    -- if succeed then
    --     --成功，则用截图创建Sprite，显示出来
    --     local sp = cc.Sprite:create(outputFile):addTo(self)
    --     sp:setPosition(visibleSize.width/2, visibleSize.height/2)
    --     --当然不显示原图了，免得遮住了屏幕上的其他内容，所有缩放一下。
    --     sp:setScale(0.5)
    --     --将文件名传给fileName，在下次截图的onCapture方法中，你需要删除它
    --     fileName = outputFile

    --     -- cc.Director:getInstance():pushScene(pauseScene)
    -- else
    --     --截屏失败，给外界提示
    --     print("Capture screen failed.")
    -- end
end

function MenuLayer:resumeGame( ... )
    print("resume")
end

return MenuLayer