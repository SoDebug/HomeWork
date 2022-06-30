clear all;
close all;
a1 = 1.3789;
a2 = -0.9506;
b = 1;
a = [1, -a1, -a2];

[z, p, k] = tf2zpk(b, a);
p = p .* exp(1i * sign(imag(p)) * 150 * 2 * pi / 8000);
[b, a] = zp2tf(z, p, k);

fprintf("a1=%d, a2=%d\n", a(2), a(3));

% ���鹲���Ƶ��
T = 0.000125;
p = roots(a);
omega = abs(angle(p(1)));
f = omega/2/pi/T;
fprintf("�����Ƶ��f: %.4f Hz\n", f);

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
