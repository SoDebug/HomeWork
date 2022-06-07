# coding=utf-8
import ConfigParser

# 树莓派的ubuntu系统里面如果要使用计划任务，则必须写成绝对路径，意味着这里需要加前缀
# RASPBERRY_PI_PATH_ROOT = '/root/C/'
# RASPBERRY_PI_PATH_PROJECT = 'QX_SHS/'

# Windows调试不需要加绝对路径
RASPBERRY_PI_PATH_ROOT = ''
RASPBERRY_PI_PATH_PROJECT = ''

RASPBERRY_PI_PATH_PLUS = RASPBERRY_PI_PATH_ROOT + RASPBERRY_PI_PATH_PROJECT

HEADERS = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit'
                  '/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safar'
                  'i/537.36',
}

# get configuration
config = ConfigParser.ConfigParser()
config.readfp(open(RASPBERRY_PI_PATH_PLUS + 'qx_shs.ini'))

# 获取System
OWNER = config.get('System', 'OWNER')

# 获取Text
ATTACK_ALERT_TEXT = config.get('Text', 'ATTACK_ALERT_TEXT')
ALERT_TXT_MORNING = config.get('Text', 'ALERT_TXT_MORNING')
ALERT_TXT_NOON = config.get('Text', 'ALERT_TXT_NOON')
ALERT_TXT_AFTERNOON = config.get('Text', 'ALERT_TXT_AFTERNOON')
ALERT_TXT_NIGHT = config.get('Text', 'ALERT_TXT_NIGHT')
ALERT_TXT_OFF_WORK = config.get('Text', 'ALERT_TXT_OFF_WORK')
ALERT_TXT_HELLO = config.get('Text', 'ALERT_TXT_HELLO')

# 获取闹钟时间参数
CLOCK_MORNING_AWAKE = config.get('ClockTime', 'CLOCK_MORNING_AWAKE')
CLOCK_MORNING_GO = config.get('ClockTime', 'CLOCK_MORNING_GO')
CLOCK_NOON = config.get('ClockTime', 'CLOCK_NOON')
CLOCK_AFTERNOON = config.get('ClockTime', 'CLOCK_AFTERNOON')
CLOCK_EVENING = config.get('ClockTime', 'CLOCK_EVENING')

# 获取CameraRecognition参数
IMAGE_SIMILARITY = config.get('CameraRecognition', 'IMAGE_SIMILARITY')
SAMPLE_IMAGES_NAME = config.get('CameraRecognition', 'SAMPLE_IMAGES_NAME')

# 获取路径
MP3_ALERT = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_ALERT')
MP3_START = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_START')
MP3_NORMAL = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_NORMAL')
MP3_WEATHER = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_WEATHER')
MP3_MORNING_AWAKE = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_MORNING_AWAKE')
MP3_MORNING_GO = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_MORNING_GO')
MP3_NOON = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_NOON')
MP3_AFTERNOON = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_AFTERNOON')
MP3_EVENING = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_EVENING')
MP3_HALF_HOUR = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_HALF_HOUR')
MP3_HOUR = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_HOUR')
MP3_BACKGROUND = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'MP3_BACKGROUND')

CLASSIFIER_PATH = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'CLASSIFIER_PATH')
SAMPLE_IMAGES_SAVE_PATH = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'SAMPLE_IMAGES_SAVE_PATH')
CAMERA_MONITORING_FILES_PATH = RASPBERRY_PI_PATH_PLUS + config.get('Path', 'CAMERA_MONITORING_FILES_PATH')