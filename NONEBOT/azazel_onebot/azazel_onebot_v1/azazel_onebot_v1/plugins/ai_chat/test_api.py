import httpx
# 这是用来写异步程序的工具包. 可以让你的程序一边等网络响应一边干别的.
import asyncio

# 替换成你自己的 API Key, 格式为"Bearer sk-xxxxxx"
API_KEY = "Bearer sk-rwtawlthdlsoufjwluymoshmnnhidmgvvavivehqihvpjchy"
MODEL = "Qwen/Qwen-7B"  # 可换为你截图里列出的任意模型
API_URL = "https://api.siliconflow.cn/v1/chat/completions"  # 注意看你的文档是 .cn 还是 .com

async def main():
    headers = {
        "Authorization": API_KEY,
        "Content-Type": "application/json"
    }

    payload = {
        "model": MODEL,
        "messages": [
            {"role": "user", "content": "Tell me a poetic description of the Moon in old English style."}
        ]
    }

    try:
        async with httpx.AsyncClient(timeout=20) as client:
            response = await client.post(API_URL, headers=headers, json=payload)
            response.raise_for_status()
            data = response.json()
            print("✅ AI 回复内容：")
            print(data["choices"][0]["message"]["content"])
    except Exception as e:
        print("❌ 请求失败：", e)

# 启动主函数
asyncio.run(main())
