
from nonebot import on_regex
from nonebot.typing import T_State
from nonebot.adapters.onebot.v11 import GroupMessageEvent, Bot, Message

Test = on_regex(pattern=r'^(测试|test)$',priority=1)
@Test.handle()
async def Test_send(bot: Bot, event: GroupMessageEvent, state: T_State):#GroupMessageEvent只回复群聊消息哦
    msg = "everythings fine ๑>ᴗO๑"
    await Test.finish(message=Message(msg))

Test = on_regex(pattern=r'^(/去自杀)$',priority=1)
@Test.handle()
async def Test_send(bot: Bot, event: GroupMessageEvent, state: T_State):#GroupMessageEvent只回复群聊消息哦
    msg = "真的吗"
    await Test.finish(message=Message(msg))

Test = on_regex(pattern=r'^(/关机)$',priority=1)
@Test.handle()
async def Test_send(bot: Bot, event: GroupMessageEvent, state: T_State):#GroupMessageEvent只回复群聊消息哦
    msg = "不要"
    await Test.finish(message=Message(msg))

Test = on_regex(pattern=r'^(/假的)$',priority=1)
@Test.handle()
async def Test_send(bot: Bot, event: GroupMessageEvent, state: T_State):#GroupMessageEvent只回复群聊消息哦
    msg = "๑>ᴗO๑"
    await Test.finish(message=Message(msg))



Test = on_regex(pattern=r'^(/我喜欢你)$',priority=1)
@Test.handle()
async def Test_send(bot: Bot, event: GroupMessageEvent, state: T_State):#GroupMessageEvent只回复群聊消息哦
    msg = "移情模组未响应..."
    await Test.finish(message=Message(msg))

Test = on_regex(pattern=r'^(/真的)$',priority=1)
@Test.handle()
async def Test_send(bot: Bot, event: GroupMessageEvent, state: T_State):#GroupMessageEvent只回复群聊消息哦
    msg = "上一步指令不存在。"
    await Test.finish(message=Message(msg))

Test = on_regex(pattern=r'^(/gpt_plus)$',priority=1)
@Test.handle()
async def Test_send(bot: Bot, event: GroupMessageEvent, state: T_State):#GroupMessageEvent只回复群聊消息哦
    msg = "no permission"
    await Test.finish(message=Message(msg))







