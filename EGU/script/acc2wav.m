clc;clear;close all;
load AccelerometerData\SuspensionBridge_Location_01 %Load FileName

%% Read time and 3 axis acc
time = SuspensionBridge_Location_01(:,1);
% xACC = 1.*SuspensionBridge_Location_01(:,5);
% yACC = 1.*SuspensionBridge_Location_01(:,6);
zACC = 1.*SuspensionBridge_Location_01(:,7);

%% plot 3 axis acc with time
% subplot(3,1,1);
% plot(time,xACC);
% subplot(3,1,2);
% plot(time,yACC);
% subplot(3,1,3);
% plot(time,zACC);

%% compute frequency 
tem = size(time);
timelen = tem(:,1);
endtime = time(end,:);
fs = round(timelen / endtime);

A = 1000;% Amplitude

%% generate audio file
disint=A.*zACC;
filename = '.\Example\SuspensionBridge_Location_01.wav';% Audio Filename 
audiowrite(filename,disint,fs);