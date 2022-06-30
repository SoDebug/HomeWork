# If you use it for the first time, you should install package:’wave‘
# For example: pip install wave
import os
import wave

def wav2pcm(input_dir, out_dir) :
    with open(input_dir, 'rb') as wavfile:
        ori_data = wavfile.read() ## 读出来是裸流bytes数据
        wavfile.close()
    with open(out_dir, 'wb') as pcmfile:
        pcmfile.write(ori_data)
        pcmfile.close()

if __name__ == '__main__':
    wav2pcm(os.path.join(r"input.wav"), 
            r"../output_files/output_files.pcm")