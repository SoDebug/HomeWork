# 使用说明
## 使用条件：
- 使用的录音中间开端、末端应当空白，中间无停顿
- 源文件应当是`pcm`格式
- 音频的采样率需要转为`8000Hz(8kHz)`
## 如果不符合以上条件需要采取一下措施
### 先决条件
- 存在`python`环境，推荐环境为`python 3.7`
- 安装`wave`:`pip install wave`
#### 格式转换为`pcm`格式
- 进入目录`HOME\code\lib\`下，运行`recorder.m`开始录音（默认为8秒）
- 将本目录下生成的`input.wav`拷贝至`HOME\code\lib\FfmpegManager\bin\`下，并打开终端，输入命令`.\ffmpeg -i input.wav -ac 1 -ar 8000 -y temp.wav`，完成`8000`采样率转换。
- 将上一步生成的`input.wav`拷贝至`HOME\code\lib`目录下。该目录存在`1.p`y脚本，在此处打开终端，输入`python 1.py`，完成`pcm`转换。
- 生成的文件在`HOME\code\output_files\`目录下。
- ！！如果文件大小非常大，你需要对文件的大小进行处理，可以采取剪辑等方式，直至为能正常运行为止！！
## 运行`Matlab`脚本检验效果
- 在`speechproc.m`里运行即可。
- 所有生成的过程性`pcm`保存在`HOME\code\save_files\`下。


#### NOTICE 
- 以往程序音频都已放到`pre_input(audio)`和`pre_output(audio)`目录下
- 目前的测试音频内容为：重庆理工大学 电气与电子工程学院

最后修改时间：2022/05/31