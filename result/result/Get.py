# -*- coding: GBK -*-
# @Time     : 2017/1/15 15:16
# @Author   : woodenrobot


# import os
# import re
# import time
# import requests
# from datetime import datetime, timedelta
# from bs4 import BeautifulSoup
# import sys
# reload(sys)
# sys.setdefaultencoding('utf8')
import os
import re
import time
import requests
from datetime import datetime, timedelta
from bs4 import BeautifulSoup
import sys,importlib
importlib.reload(sys)

headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit'
                      '/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safar'
                      'i/537.36',
    }


def numtozh(num):
    num_dict = {1: 'һ', 2: '��', 3: '��', 4: '��', 5: '��', 6: '��', 7: '��',
                8: '��', 9: '��', 0: '��'}
    num = int(num)
    if 100 <= num < 1000:
        b_num = num // 100
        s_num = (num-b_num*100) // 10
        g_num = (num-b_num*100) % 10
        if g_num == 0 and s_num == 0:
            num = '%s��' % (num_dict[b_num])
        elif s_num == 0:
            num = '%s��%s%s' % (num_dict[b_num], num_dict.get(s_num, ''), num_dict.get(g_num, ''))
        elif g_num == 0:
            num = '%s��%sʮ' % (num_dict[b_num], num_dict.get(s_num, ''))
        else:
            num = '%s��%sʮ%s' % (num_dict[b_num], num_dict.get(s_num, ''), num_dict.get(g_num, ''))
    elif 10 <= num < 100:
        s_num = num // 10
        g_num = (num-s_num*10) % 10
        if g_num == 0:
            g_num = ''
        num = '%sʮ%s' % (num_dict[s_num], num_dict.get(g_num, ''))
    elif 0 <= num < 10:
        g_num = num
        num = '%s' % (num_dict[g_num])
    elif -10 < num < 0:
        g_num = -num
        num = '����%s' % (num_dict[g_num])
    elif -100 < num <= -10:
        num = -num
        s_num = num // 10
        g_num = (num-s_num*10) % 10
        if g_num == 0:
            g_num = ''
        num = '����%sʮ%s' % (num_dict[s_num], num_dict.get(g_num, ''))
    return num


def get_weather():
    # ����ī��������ҳԴ��
    res = requests.get('http://tianqi.moji.com/', headers=headers)
    # ��BeautifulSoup��ȡ������Ϣ
    soup = BeautifulSoup(res.text, "html.parser")
    temp = soup.find('div', attrs={'class': 'wea_weather clearfix'}).em.getText()
    temp = numtozh(int(temp))
    weather = soup.find('div', attrs={'class': 'wea_weather clearfix'}).b.getText()
    sd = soup.find('div', attrs={'class': 'wea_about clearfix'}).span.getText()
    sd_num = re.search(r'\d+', sd).group()
    sd_num_zh = numtozh(int(sd_num))
    sd = sd.replace(sd_num, sd_num_zh)
    wind = soup.find('div', attrs={'class': 'wea_about clearfix'}).em.getText()
    aqi = soup.find('div', attrs={'class': 'wea_alert clearfix'}).em.getText()
    aqi_num = re.search(r'\d+', aqi).group()
    aqi_num_zh = numtozh(int(aqi_num))
    aqi = aqi.replace(aqi_num, aqi_num_zh).replace(' ', ',��������')
    info = soup.find('div', attrs={'class': 'wea_tips clearfix'}).em.getText()
    sd = sd.replace(' ', '�ٷ�֮').replace('%', '')
    aqi = 'ʵʱ��������ָ��' + aqi
    info = info.replace('��', ',')
    # ��ȡ���������
    today = datetime.now().strftime('%p %Y��%m��%d�� %I��%M��%S��')
    today = today.replace('PM', '����ã�������').replace('AM', '����ã�������')
    # ����ȡ����Ϣƴ�ӳ�һ�仰
    text = '%s, ʵʱ������%s, �¶�%s ���϶� ,%s ,%s ,%s ,%s' % \
           (today, weather, temp, sd, wind, aqi, info)
    return text


def text2voice(text):
    url = 'http://tts.baidu.com/text2audio?idx=1&tex={0}&cuid=baidu_speech_' \
          'demo&cod=2&lan=zh&ctp=1&pdt=1&spd=4&per=4&vol=5&pit=5'.format(text)
    # ֱ�Ӳ�������
    # os.system('mplayer "%s"' % url)


def WeatherInfo():
    # ��ȡ��Ҫת������������
    text = str(get_weather())
    return text
    # ��ȡ�����ļ����Ե�ַ
    #mp3path2 = os.path.join(os.path.dirname(__file__), '2.mp3')
    #print("We have get the file_path of media.:"+mp3path2)
    # �Ȳ���һ������������
    # os.system('mplayer %s' % mp3path2)
    # ������������
    text2voice(text)

# if __name__ == '__main__':
#     main()
