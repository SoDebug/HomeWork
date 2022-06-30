# If you use it for the first time, you should run the command "pip install baidu-aip" in the Terminals.
from aip import AipSpeech
""" Let's set some suitable configs for yourself """
APP_ID = '26337680'
API_KEY = 'AmrxDwbiVPt8j8xnoGovlBof'
SECRET_KEY = 'eNdsRM5kavGtgK4jveZTodNzz0AyxfOQ'
client = AipSpeech(APP_ID, API_KEY, SECRET_KEY)
content=input('Input the sentence wish to get.\n[Input]:')
try:
    result = client.synthesis(content, 'zh', 1, {
        'vol': 5,
    })
    try:
        if not isinstance(result, dict):
            with open('audio.mp3', 'wb') as f:
                f.write(result)
    except:
        print('[ERROR]:When we try to create an audio file, some errors occur.')
except:
    print('[ERROR]:Some terrible things occur in the process when we send the quest to Baidu Server. You had better '
          'check '
          'your settings on API.')

