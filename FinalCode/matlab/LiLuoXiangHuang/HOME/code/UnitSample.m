function s = UnitSample(duration, fs, f)
%UnitSample生成单位样值串
%   duration: 信号持续时间
%   fs: 采样频率
%   f: 单位样值串频率

s = zeros(round(fs * duration), 1);
NS = round(duration * f);
N = round(fs / f);
ni = 0:NS - 1;
s(ni * N + 1) = 1;
end

