require "extern"   --导入模板，作用调用其class函数

MySprite = class("MySprite",
    function(fileName)
        return CCSprite:create(fileName) 
    end
)
 
MySprite.__index = MySprite   -- 用于访问
 
MySprite.type = 0    -- 自定义属性
MySprite.m_ball = "aaaa"
 
function MySprite:createMS(fileName,_type)      --自定义构造函数
    local mySprite = MySprite.new(fileName)
    mySprite:myInit(_type)
    return mySprite
end
 
function MySprite:myInit(_type)    --自定义函数
    self.type =_type
  CCMessageBox("create HSprite success", "Himi_Lua");
end