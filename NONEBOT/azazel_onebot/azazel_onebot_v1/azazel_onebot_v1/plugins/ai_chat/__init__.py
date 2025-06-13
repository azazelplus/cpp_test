# __init__.py
from nonebot import on_command
from nonebot.adapters.onebot.v11 import MessageSegment, MessageEvent
from nonebot.params import CommandArg
from .api_client import call_siliconflow_api1
from .api_client import call_siliconflow_api2

ai_chat_api1 = on_command("ai", aliases={"chat", "gpt"})
ai_chat_api2 = on_command("ai_ds_r1", aliases={"chat_ds_r1", "gpt_ds_r1"})

# 这是可能用到的用户权限筛选列表
ALLOWED_USERS = {"2052119800", "1838427319"}  # 替换为你的 QQ 号，必须是字符串！

prompt1="请用不超过50字简洁回答问题。Please answer the question concisely in no more than 50 characters."



@ai_chat_api1.handle()
async def _(event: MessageEvent, args=CommandArg()):
    user_text = prompt1 + args.extract_plain_text().strip()

    if not user_text:
        await ai_chat_api1.finish("啊?")

    await ai_chat_api1.send("嗯...")

    reply = call_siliconflow_api1(user_text)

    await ai_chat_api1.finish(MessageSegment.text(reply))




@ai_chat_api2.handle()
async def _(event: MessageEvent, args=CommandArg()):

    user_id = event.get_user_id()  # 获取发送消息者的 QQ 号
    if user_id not in ALLOWED_USERS:
        await ai_chat_api2.finish("no permission :(")


    #拼接预设提示词和用户输入
    user_text = prompt1 + args.extract_plain_text().strip()
    if not user_text:
        await ai_chat_api2.finish("啊?")

    await ai_chat_api2.send("嗯...")

    reply = call_siliconflow_api2(user_text)

    await ai_chat_api2.finish(MessageSegment.text(reply))
