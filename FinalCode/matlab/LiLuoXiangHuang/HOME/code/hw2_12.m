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

% 检验共振峰频率
T = 0.000125;
p = roots(a);
omega = abs(angle(p(1)));
f = omega/2/pi/T;
fprintf("共振峰频率f: %.4f Hz\n", f);

% 用zplane绘制零极点图
figure;
zplane(b, a);
title("零极点图");
% 用freqz绘制频率响应
figure;
freqz(b, a);
title("频率响应");
% 用impz绘制单位样值响应
figure;
impz(b, a, 400);
title("impz绘制单位样值响应");
