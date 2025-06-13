# api_client.py
import requests

API_URL = "https://api.siliconflow.cn/v1/chat/completions"
API_KEY = "sk-rwtawlthdlsoufjwluymoshmnnhidmgvvavivehqihvpjchy"

def call_siliconflow_api1(user_message: str) -> str:
    payload = {
        "model": "deepseek-ai/DeepSeek-R1-0528-Qwen3-8B",
        "messages": [{"role": "user", "content": user_message}],
        "stream": False,
        "max_tokens": 80,
        "temperature": 0.7,
        "top_p": 0.7,
        "top_k": 50,
        "frequency_penalty": 0.5,
        "n": 1,
        "response_format": {"type": "text"},
    }

def call_siliconflow_api2(user_message: str) -> str:
    payload = {
        "model": "deepseek-ai/DeepSeek-R1",
        "messages": [{"role": "user", "content": user_message}],
        "stream": False,
        "max_tokens": 80,
        "temperature": 0.7,
        "top_p": 0.7,
        "top_k": 80,
        "frequency_penalty": 0.5,
        "n": 1,
        "response_format": {"type": "text"},
    }


    headers = {
        "Authorization": f"Bearer {API_KEY}",
        "Content-Type": "application/json"
    }

    try:
        response = requests.post(API_URL, json=payload, headers=headers)
        response.raise_for_status() # 检测服务器有没有返回错误.如果返回状态码HTTP200, 这一行什麽都不会发生. 否则抛出异常, 程序跳到except里执行.
        data = response.json()  #.json方法将json字符串自动转成python中的dict格式.

        # 加强健壮性
        content = data.get("choices", [{}])[0].get("message", {}).get("content")
        if not content:
            content = "啥都不是 :("
        return content


        #return data["choices"][0]["message"]["content"]
    except Exception as e:
        return f"调用失败了喵: {str(e)}"
