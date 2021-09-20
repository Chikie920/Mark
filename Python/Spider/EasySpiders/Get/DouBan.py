import requests

header = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
}

url = 'https://movie.douban.com/j/chart/top_list'
param = {
    'type': 5,
    'interval_id': '100:90',
    'action': '',
    'start': 0,
    'limit': 20,
}
response = requests.get(url, params=param, headers=header)
print(response.json())