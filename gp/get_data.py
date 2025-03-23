import requests
import json

ST_price = 0.0
GZ = 0.0311034768

def get_GLOD_price():
    global ST_price, GZ
    url = 'https://quote.alltick.io/quote-b-api/trade-tick'
    token = '5166cf9d3515ab54471eb33354d9fd3e-c-app'
    query = {
        "trace": "edd5d390-df7f-4acf-8f67-68fd2f0c6426",
        "data": {
            "symbol_list": [
                {
                    "code": "GOLD"
                },
                {
                    "code": "USDCNH"
                }
            ]
        }
    }
    params = {
        'token': token,
        'query': json.dumps(query)
    }
    # 发送get请求
    
    # 发送GET请求
    response = requests.get(url, params=params)
    
    # # 显示响应状态码
    # print(f"状态码: {response.status_code}")
    
    # # 显示响应头
    # print("\n响应头:")
    # for key, value in response.headers.items():
    #     print(f"{key}: {value}")
    
    # # 显示响应内容
    # print("\n响应内容:")
    try:
        # 尝试解析JSON响应
        response_json = response.json()
        lists = response_json['data']['tick_list']
        # print(json.dumps(response_json, indent=4, ensure_ascii=False))
        price = 0.0
        USCNY = 0.0
        for l in lists:
            if l['code'] == 'GOLD':
                price = float(response_json['data']['tick_list'][0]['price'])
            elif l['code'] == 'USDCNH':
                USCNY = float(response_json['data']['tick_list'][1]['price'])
        # print(f"当前金价: {price}")
        # print(f"当前金价(美元/KG): {price/gg}")
        # print(f"当前金价(美元/g): {price/gg/1000.0}")
        # print(f"当前金价: {price/gg/1000.0 * USCNY} 人民币/克")
        return price / GZ / 1000.0 * USCNY
    except json.JSONDecodeError:
        # 如果不是JSON格式，显示原始内容
        # print(response.text)
        return ST_price
    pass

if __name__ == '__main__':
    # sol()
    print(get_GLOD_price())