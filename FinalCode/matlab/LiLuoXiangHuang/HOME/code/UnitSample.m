function s = UnitSample(duration, fs, f)
%UnitSample���ɵ�λ��ֵ��
%   duration: �źų���ʱ��
%   fs: ����Ƶ��
%   f: ��λ��ֵ��Ƶ��

s = zeros(round(fs * duration), 1);
NS = round(duration * f);
N = round(fs / f);
ni = 0:NS - 1;
s(ni * N + 1) = 1;
end

