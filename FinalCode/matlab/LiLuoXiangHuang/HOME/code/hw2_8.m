clear all;
close all;
fs = 8000;
duration = 1;

s = VariedUnitSample(duration, fs);

sound(s, fs);
t = [0:7999]' / 8000;
figure;
plot(t, s);
