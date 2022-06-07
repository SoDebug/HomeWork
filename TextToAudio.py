# coding=utf-8

# RASPBERRY_PI_PATH_ROOT 执行Ubuntu计划任务必须声明绝对路径
RASPBERRY_PI_PATH_ROOT = '/root/C/'

import sys

sys.path.append(RASPBERRY_PI_PATH_ROOT)
import os
from FunctionCode.GetWeatherText import *
from FunctionCode.TextToAudio import *

# 播放器(totem)和音乐文件(The_Snow.mp3)需要用户指定,需要指定时间
def play_mp3_weather(time_index):
    # 通过不同的时间，获取不同时间的天气信息
    text = get_weather(str(OWNER), time_index)
    # 将文字信息转换成语音信息
    text2voice(text, MP3_WEATHER)
    os.system("mpg321 {0}".format(str(MP3_WEATHER)))


if __name__ == '__main__':

    timeNow = get_current_time()

    print('{0} -> welcome to use qixiao`s program .  starting ...'.format(timeNow))

    # os.system("mpg321 {0}".format(str(MP3_START)))
    # text = get_weather(str(OWNER), 0)
    # print(text)

    try:
        # 获取特定格式的当前时间
        timeNowStringFormat = str('{0}:{1}'.format(timeNow.hour, timeNow.minute))
        # 打印当前时间
        # print('time now -> {0}'.format(timeNow))
        # 进行时间判断,并在不同时间段进行对应的操作
        if timeNowStringFormat == CLOCK_MORNING_AWAKE:
            print('{0} >>> morning ! it`s time to awake ... '.format(str(CLOCK_MORNING_AWAKE)))
            play_mp3_weather(1)
            os.system("mpg321 {0}".format(str(MP3_MORNING_AWAKE)))
        if timeNowStringFormat == CLOCK_MORNING_GO:
            print('{0} >>> morning ! it`s time to go ... '.format(str(CLOCK_MORNING_GO)))
            play_mp3_weather(1)
            os.system("mpg321 {0}".format(str(MP3_MORNING_GO)))
        elif timeNowStringFormat == CLOCK_NOON:
            print('{0} >>> good noon have a good mood ... '.format(str(CLOCK_NOON)))
            play_mp3_weather(2)
            os.system("mpg321 {0}".format(str(MP3_NOON)))
        elif timeNowStringFormat == CLOCK_AFTERNOON:
            print('{0} >>> good afternoon it`s time to happy ... '.format(str(CLOCK_AFTERNOON)))
            play_mp3_weather(3)
            os.system("mpg321 {0}".format(str(MP3_AFTERNOON)))
        elif timeNowStringFormat == CLOCK_EVENING:
            print('{0} >>> good night it`s time to sleep ... '.format(str(CLOCK_EVENING)))
            play_mp3_weather(4)
            os.system("mpg321 {0}".format(str(MP3_EVENING)))
        # 整点报时功能 早7点以后，晚24点之前 除去13点午休时间
        elif timeNow.hour > 7 and timeNow.hour < 24 and timeNow.hour != 13 and timeNow.minute == 00:
            print('# >>> integral point. ... ')
            os.system("mpg321 {0}".format(str(MP3_HOUR)))
            play_mp3_weather(5)
        # 半点报时功能 早7点以后，晚24点之前 除去13点午休时间
        elif timeNow.hour >= 7 and timeNow.hour < 24 and timeNow.hour != 13 and timeNow.minute == 30:
            print('# >>> half an hour ... ')
            os.system("mpg321 {0}".format(str(MP3_HALF_HOUR)))
        else:
            pass

    except Exception:
        print(str(timeNow) + ' >>> ' + Exception)