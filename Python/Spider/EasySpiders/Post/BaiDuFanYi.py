import requests, json

header = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
}

url = 'https://fanyi.baidu.com/sug'

print('请输入要翻译的英文: ')
word = input()

data = {
    'kw': word
}

response = requests.post(url, data=data, headers=header)
print(response.json())