clc;clear;close all;


% sine
fs = 2048;
dt = 1/fs;
Time = 60;% Time Second 
L = Time/dt;
t = 0:dt:(L-1)*dt;

A = 100;% amplitude
f = 150;% freq

data = A*sin(2*pi*f*t);
acc = data;

% figure
% plot(t, acc), title('sine acc')

% creat sine wav
disint=acc;
filename = '.\Example\sine.wav';% Audio Filename 
audiowrite(filename,disint,fs);
