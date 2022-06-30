clear all;
close all;
% �������
a1 = 1.3789;
a2 = -0.9506;
b = 1;
a = [1, -a1, -a2];

% �����Ƶ��
T = 0.000125;
p = roots(a);
omega = abs(angle(p(1)));
f = omega/2/pi/T;
fprintf("�����Ƶ��f: %.4f\n", f);

% ��zplane�����㼫��ͼ
figure;
zplane(b, a);
title("�㼫��ͼ");
% ��freqz����Ƶ����Ӧ
figure;
freqz(b, a);
title("Ƶ����Ӧ");
% ��impz���Ƶ�λ��ֵ��Ӧ
figure;
impz(b, a, 400);
title("impz���Ƶ�λ��ֵ��Ӧ");
% ��filter���Ƶ�λ��ֵ��Ӧ
figure;
n = [0:399]';
x = n * 0;
x(1) = 1;
y = filter(b, a, x);
stem(n, y);
title("filter���Ƶ�λ��ֵ��Ӧ");
xlabel("n(samples)");
ylabel("Amplitude");