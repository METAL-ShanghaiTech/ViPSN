<<<<<<< HEAD
 
=======
>>>>>>> 1246ff24a81c31105d0000fb2080dbef75ad56ef
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
<<<<<<< HEAD
A = 500;% amplitude
f = 300;% freq
=======
A = 100;% amplitude
f = 150;% freq
>>>>>>> 1246ff24a81c31105d0000fb2080dbef75ad56ef
data = A*sin(2*pi*f*t);
acc = data;
% figure
% plot(t, acc), title('sine acc')

%%
% creat sine wav
disint=acc;
<<<<<<< HEAD
filename = '.\sine3.wav';
=======
filename = '.\sine2.wav';
>>>>>>> 1246ff24a81c31105d0000fb2080dbef75ad56ef
audiowrite(filename,disint,fs);
clear disint fs  