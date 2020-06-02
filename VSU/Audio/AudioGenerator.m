%% 
clc
clear
close all

%%
% sine
fs = 2048;
dt = 1/fs;
Time = 1000;% Time Second 
L = Time/dt;
t = 0:dt:(L-1)*dt;
A = 100;% amplitude
f = 150;% freq
data = A*sin(2*pi*f*t);
acc = data;
% figure
% plot(t, acc), title('sine acc')

%%
% creat sine wav
disint=acc;
filename = '.\sine2.wav';
audiowrite(filename,disint,fs);
clear disint fs  