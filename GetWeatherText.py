# coding=utf-8

# RASPBERRY_PI_PATH_ROOT 执行Ubuntu计划任务必须声明绝对路径
RASPBERRY_PI_PATH_ROOT = '/root/C/'

import sys

sys.path.append(RASPBERRY_PI_PATH_ROOT)
import re
import requests
from bs4 import BeautifulSoup
from datetime import datetime
from Helper_DG.DateTimeHelper_DG import *
from QX_SHS.ConfigField import *

reload(sys)
sys.setdefaultencoding('utf8')


def numtozh(num):
    num_dict = {1: '一', 2: '二', 3: '三', 4: '四', 5: '五', 6: '六', 7: '七',
                8: '八', 9: '九', 0: '零'}
    num = int(num)
    if 100 <= num < 1000:
        b_num = num // 100
        s_num = (num - b_num * 100) // 10
        g_num = (num - b_num * 100) % 10
        if g_num == 0 and s_num == 0:
            num = '%s百' % (num_dict[b_num])
        elif s_num == 0:
            num = '%s百%s%s' % (num_dict[b_num], num_dict.get(s_num, ''), num_dict.get(g_num, ''))
        elif g_num == 0:
            num = '%s百%s十' % (num_dict[b_num], num_dict.get(s_num, ''))
        else:
            num = '%s百%s十%s' % (num_dict[b_num], num_dict.get(s_num, ''), num_dict.get(g_num, ''))
    elif 10 <= num < 100:
        s_num = num // 10
        g_num = (num - s_num * 10) % 10
        if g_num == 0:
            g_num = ''
        num = '%s十%s' % (num_dict[s_num], num_dict.get(g_num, ''))
    elif 0 <= num < 10:
        g_num = num
        num = '%s' % (num_dict[g_num])
    elif -10 < num < 0:
        g_num = -num
        num = '零下%s' % (num_dict[g_num])
    elif -100 < num <= -10:
        num = -num
        s_num = num // 10
        g_num = (num - s_num * 10) % 10
        if g_num == 0:
            g_num = ''
        num = '零下%s十%s' % (num_dict[s_num], num_dict.get(g_num, ''))
    return num


# timeRegion 时间区间 1=早上，2=中午，3=傍晚，4=夜晚,其他=现在
def get_weather(name, timeRegion):
    # 下载墨迹天气主页源码
    res = requests.get('http://tianqi.moji.com/', headers=HEADERS)
    # 用BeautifulSoup获取所需信息
    soup = BeautifulSoup(res.text, "html.parser")
    address = soup.find('div', attrs={'class': 'search_default'}).em.getText()
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
    aqi = aqi.replace(aqi_num, aqi_num_zh).replace(' ', ',空气质量')
    info = soup.find('div', attrs={'class': 'wea_tips clearfix'}).em.getText()
    sd = sd.replace(' ', '百分之').replace('%', '')
    aqi = 'aqi' + aqi
    info = info.replace('，', ',')
    # 获取今天的日期
    timeNow = datetime.datetime.now()

    # 将获取的信息拼接成一句话
    weatherText = ''
    if timeRegion == 1:
        weatherText = '早上好！%s ,今天是%s年,%s月,%s日,星期%s,现在的时间是%s点,%s分。您所在的地区是%s,天气%s,温度%s摄氏度,%s,%s,%s,%s 开始美好的一天吧，么么哒。' % \
                      (
                          name, timeNow.year, timeNow.month, timeNow.day, get_week_day_by_date(timeNow), timeNow.hour,
                          timeNow.minute, address,
                          weather, temp,
                          sd,
                          wind,
                          aqi, info)
    elif timeRegion == 2:
        weatherText = '中午好！%s ,今天是%s年,%s月,%s日,星期%s,现在的时间是%s点,%s分。您所在的地区是%s,天气%s,温度%s摄氏度,%s,%s,%s,%s 中午一定要记得休息哦，么么哒。' % \
                      (
                          name, timeNow.year, timeNow.month, timeNow.day, get_week_day_by_date(timeNow), timeNow.hour,
                          timeNow.minute, address,
                          weather, temp,
                          sd,
                          wind,
                          aqi, info)
    elif timeRegion == 3:
        weatherText = '下午好！%s ,今天是%s年,%s月,%s日,星期%s,现在的时间是%s点,%s分。您所在的地区是%s,天气%s,温度%s摄氏度,%s,%s,%s,%s 忙了一天，累了吧，么么哒。' % \
                      (
                          name, timeNow.year, timeNow.month, timeNow.day, get_week_day_by_date(timeNow), timeNow.hour,
                          timeNow.minute, address,
                          weather, temp,
                          sd,
                          wind,
                          aqi, info)
    elif timeRegion == 4:
        weatherText = '晚上好！%s ,今天是%s年,%s月,%s日,星期%s,现在的时间是%s点,%s分。您所在的地区是%s,天气%s,温度%s摄氏度,%s,%s,%s,%s 夜已深了，早点休息吧，么么哒。' % \
                      (
                          name, timeNow.year, timeNow.month, timeNow.day, get_week_day_by_date(timeNow), timeNow.hour,
                          timeNow.minute, address,
                          weather, temp,
                          sd,
                          wind,
                          aqi, info)
    elif timeRegion == 5:
        weatherText = '现在是,北京时间 %s年,%s月,%s日,星期%s,%s点,%s分。' % \
                      (
                          timeNow.year, timeNow.month, timeNow.day, get_week_day_by_date(timeNow), timeNow.hour,
                          timeNow.minute)
    else:
        weatherText = '您好！%s ,今天是%s年,%s月,%s日,星期%s,现在的时间是%s点,%s分。您所在的地区是%s,天气%s,温度%s摄氏度,%s,%s,%s,%s 么么哒。' % \
                      (
                          name, timeNow.year, timeNow.month, timeNow.day, get_week_day_by_date(timeNow), timeNow.hour,
                          timeNow.minute, address,
                          weather, temp,
                          sd,
                          wind,
                          aqi, info)

    return weatherText