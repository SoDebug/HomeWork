function s = VariedUnitSample(duration, fs)
%VariedUnitSample生成单位样值串
%   duration: 信号持续时间
%   fs: 采样频率

s_len = round(fs * duration);
s = zeros(s_len, 1);
seg = round(0.01 * fs);

% 通过循环来生成信号
pos = 1;
while pos <= s_len
    s(pos) = 1;
    m = ceil(pos / seg);
    PT = 80 + 5 * mod(m, 50);
    pos = pos + PT;
end
end
