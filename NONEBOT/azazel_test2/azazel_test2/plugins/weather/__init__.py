from nonebot import get_plugin_config
from nonebot.plugin import PluginMetadata

from .config import Config

##############################
from nonebot import on_command

from nonebot.rule import to_me # 仅当消息是发给bot时才会触发
##############################

__plugin_meta__ = PluginMetadata(
    name="weather",
    description="",
    usage="",
    config=Config,
)

config = get_plugin_config(Config)

# 创建一个名为weather的事件响应器. 它会对`/天气`开头的消息进行响应!
weather = on_command("天气", 
                     rule=to_me(),  # 仅当消息是发给bot时才会触发
                     aliases={"weather", "查天气"},  # 别名，可以使用`/weather`来触发
                     priority=5,  # 优先级，数字越大优先级越高
                     block=True)  # 阻塞模式，阻塞其他事件直到处理完毕

@weather.handle()
async def handle_weather():
    await weather.finish("现在的天气是……晴！🌞") #.finish是mather类的一个方法, 回复一条消息然后结束这个事件处理流程, 等价于:`await weather.send("天气是☀️")    raise FinishedException  # 通知 NoneBot 这次处理结束了`



