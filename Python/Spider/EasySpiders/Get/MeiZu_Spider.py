from functools import wraps
from os import write
from types import resolve_bases
import requests, bs4, re

header = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
}

url = 'https://bbs.meizu.cn/forum-22-1.html'
response = requests.get(url, headers=header)
soup = bs4.BeautifulSoup(response.text, 'html.parser')
web_data = open('MeiZu.txt', 'a')
for term in soup.select('.maincont_list a'):
    web_data.write('%s\n' % term)

'''
以下为文本处理
'''
target = re.compile('.*?id="(.*?)".*?title="(.*?)">')
data = open('MeiZu.txt', 'r')
lines = data.readlines()
data = open('MeiZu.txt', 'a')
for line in lines:
    result = target.findall(line)
    data.write('%ss\n' % result)
data.close()