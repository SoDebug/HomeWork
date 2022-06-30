function s = VariedUnitSample(duration, fs)
%VariedUnitSample���ɵ�λ��ֵ��
%   duration: �źų���ʱ��
%   fs: ����Ƶ��

s_len = round(fs * duration);
s = zeros(s_len, 1);
seg = round(0.01 * fs);

% ͨ��ѭ���������ź�
pos = 1;
while pos <= s_len
    s(pos) = 1;
    m = ceil(pos / seg);
    PT = 80 + 5 * mod(m, 50);
    pos = pos + PT;
end
end
