
from nonebot import on_regex
from nonebot.typing import T_State
from nonebot.adapters.onebot.v11 import GroupMessageEvent, Bot, Message
import os


HELP_FILE_PATH = os.path.join(os.path.dirname(__file__), "help.txt")
help_cmd = on_regex(pattern=r'^/help$',priority=1)









@help_cmd.handle()
async def Test_send(bot: Bot, event: GroupMessageEvent, state: T_State):#GroupMessageEvent只回复群聊消息哦
    msg = "Bot启动正常"
    try:
        with open(HELP_FILE_PATH, "r", encoding="utf-8") as f:
            help_text = f.read()
        await help_cmd.finish(Message(help_text))
    except Exception:
        await help_cmd.finish("读取选项卡失败喵 >_<")
