import Get
import time
import syn6288
Info=str(Get.WeatherInfo())
Info_split=Info.split("：")
print(Info)
syn = syn6288.SYN6288()
for character in Info_split:
    time.sleep(5)
    try:
        syn.play_text(character)
        while not syn.query_state():
            time.sleep(0.01)
        print(character)
    except:
        print("Failed on play...")
    time.sleep(1)