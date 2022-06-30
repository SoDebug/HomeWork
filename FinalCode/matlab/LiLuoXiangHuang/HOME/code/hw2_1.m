clear all;
close all;
% 定义参数
a1 = 1.3789;
a2 = -0.9506;
b = 1;
a = [1, -a1, -a2];

% 求共振峰频率
T = 0.000125;
p = roots(a);
omega = abs(angle(p(1)));
f = omega/2/pi/T;
fprintf("共振峰频率f: %.4f\n", f);

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
% 用filter绘制单位样值响应
figure;
n = [0:399]';
x = n * 0;
x(1) = 1;
y = filter(b, a, x);
stem(n, y);
title("filter绘制单位样值响应");
xlabel("n(samples)");
ylabel("Amplitude");