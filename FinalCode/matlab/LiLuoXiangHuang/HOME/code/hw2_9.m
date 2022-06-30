clear all;
close all;
fs = 8000;
duration = 2;
% ����e(n)
en = VariedUnitSample(duration, fs);

a1 = 1.3789;
a2 = -0.9506;
b = 1;
a = [1, -a1, -a2];
% ����s(n)
sn = filter(b, a, en);
% �������ź�
sound([en; sn/max(abs(sn))], fs);

% ����ʱ����
figure;
subplot(2, 1, 1);
plot(en);
ylabel("e(n)");
subplot(2, 1, 2);
plot(sn);
ylabel("s(n)");
% ����Ƶ����
L = length(en);
fft_freq = fs * (0 : (L / 2))' / L;
figure;
subplot(2, 1, 1);
EN = abs(fft(en) / L);
EN = EN(1 : L / 2 + 1);
EN(2 : end - 1) = 2 * EN(2 : end - 1);
plot(fft_freq, EN);
ylabel('e(n)����Ƶ��');
subplot(2, 1, 2);
SN = abs(fft(sn) / L);
SN = SN(1 : L / 2 + 1);
SN(2 : end - 1) = 2 * SN(2 : end - 1);
plot(fft_freq, SN);
ylabel('s(n)����Ƶ��');

