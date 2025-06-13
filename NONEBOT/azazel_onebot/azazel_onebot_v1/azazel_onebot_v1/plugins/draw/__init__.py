from nonebot import get_plugin_config
from nonebot.plugin import PluginMetadata

from .config import Config

##############################
from nonebot import on_command
##############################

__plugin_meta__ = PluginMetadata(
    name="draw",
    description="",
    usage="",
    config=Config,
)

config = get_plugin_config(Config)


import random
from nonebot.adapters.onebot.v11 import Message








# Tarot card pool (Major Arcana only for elegance)
tarot_cards = [
    ("The Fool", "A soul at the edge of the world, free of burden, ready to leap. Trust the winds, for they know the path."),
    ("The Magician", "Thy will shapes the ether — above and below. All lies within thy grasp."),
    ("The High Priestess", "She guardeth the moonlit veil of secrets. What is hidden shall be revealed in due time."),
    ("The Empress", "O mother of earth, thou bringest forth beauty, bounty, and tender grace."),
    ("The Emperor", "The throne is firm, the law unyielding. Power tempered by wisdom, or folly born of pride?"),
    ("The Hierophant", "2 prayers from the lost"),
    ("The Lovers", "Two souls entwined, mirrored in heart and fate. Choose not lightly, for love is ever a double-edged blade."),
    ("The Chariot", "Steady thy reins, noble rider. Victory cometh to the bold who master both beast and self."),
    ("Strength", "Not by fang nor claw, but by heart and grace doth the lion kneel."),
    ("The Hermit", "In solitude, the lantern burns. Seek not the world, but thine own truth."),
    ("Wheel of Fortune", "Fortune turneth evermore — in thy favor, or against thee. None know which spoke they ride."),
    ("Justice", "The blade is swift, the scales are true. What hath been sown shall be reaped."),
    ("The Hanged Man", "Suspend thyself in twilight thought. Surrender brings forth strange wisdom."),
    ("Death", "The hourglass empties — not of doom, but of change. Endings beget beginnings."),
    ("Temperance", "Blend the flame and the flood. Balance, dear one, is thy salvation."),
    ("The Devil", "Chains forged of thy own desire. Break them, or dance deeper into the night."),
    ("The Tower", "Lightning split the sky — and thee. What crumbles may clear the path."),
    ("The Star", "Soft glimmers on the darkened sea. Hope endureth, silent and bright."),
    ("The Moon", "Dreams walk in silver shadow. Not all is as it seemeth."),
    ("The Sun", "see, face, heal"),
    ("Judgement", "Awaken! The trumpet soundeth. Rise and reckon with thy past."),
    ("The World", "A circle complete. Thou art all and none, the dance and the stillness.")
]


planetary_cards= [
    ("Sun",     "Radiant victory"),
    ("Mercury",  "打开所有的门。"),
    ("Venus",   "you feel pretty"),
    ("Mars",    "粉碎! 粉碎! 粉碎!"),
    ("Jupiter", "很肥很肥。"),
    ("Saturn",  "伤害身边的人，伤害自己。"),
    ("Uranus",  "冻结! 冻结! 冻结!"),
    ("Neptune", "Open the floodgates..."),
    ("Pluto",   "逃脱"),
    ("Moon",    "The moon's blessing shines upon you"),  
    ("Earth",   "暴力行为和雄性无毛大猩猩。")  
]

# Draw a tarot
draw_tarot = on_command("draw card", 
                     aliases={"card", "draw_card", "tarot", "draw"},  # 别名，可以使用`/weather`来触发
                     priority=5,  # 优先级，数字越大优先级越高
                     block=True)  # 阻塞模式，阻塞其他事件直到处理完毕

@draw_tarot.handle()
async def handle_draw_tarot():
    tarot, tarot_meaning = random.choice(tarot_cards)
    response = f"🃏抽1张牌: *{tarot}*\n📜 {tarot_meaning}"
    await draw_tarot.finish(Message(response)) 




# Draw a card
draw_planetary = on_command("draw_planetary", 
                     aliases={"star", "stars", "planetary", "draw_star"},  # 别名，可以使用`/weather`来触发
                     priority=5,  # 优先级，数字越大优先级越高
                     block=True)  # 阻塞模式，阻塞其他事件直到处理完毕

@draw_planetary.handle()
async def handle_draw_planetary():
    planetary, planetary_meaning = random.choice(planetary_cards)
    response = f"🌗: *{planetary}*\n📜 {planetary_meaning}"
    await draw_planetary.finish(Message(response)) 

