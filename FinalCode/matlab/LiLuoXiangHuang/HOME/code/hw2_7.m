clear all;
close all;
fs = 8000;
f1 = 200;
f2 = 300;
duration = 1;

s1 = UnitSample(duration, fs, f1);
s2 = UnitSample(duration, fs, f2);

sound([s1;s2], fs);
