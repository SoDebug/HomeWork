# If you use it for the first time, you should run the command "pip install baidu-aip" in the Terminals.
from aip import AipSpeech
import datetime
""" Let's set some suitable configs for yourself """
APP_ID = '26337680'
API_KEY = 'AmrxDwbiVPt8j8xnoGovlBof'
SECRET_KEY = 'eNdsRM5kavGtgK4jveZTodNzz0AyxfOQ'
client = AipSpeech(APP_ID, API_KEY, SECRET_KEY)
content=input('Input the sentence wish to get.\n[Input]:')
try:
    result = client.synthesis(content, 'zh', 1, {
        'vol': 5,   # 音量参数传递
        'spd': 9,   # 语速参数传递
    })
    now_time = datetime.datetime.now().strftime('%m-%d-%H-%M-%S')
    filepath='./save_files/'+content[0:3]+'_'+now_time+'.mp3'
    try:
        if not isinstance(result, dict):
            with open(filepath, 'wb') as f:
                f.write(result)
        print('Okay!')
    except:
        print('[ERROR]:When we try to create an audio file, some errors occur.')
except:
    print('[ERROR]:Some terrible things occur in the process when we send the quest to Baidu Server. You had better '
          'check '
          'your settings on API.')

