% https://www.mathworks.com/help/signal/ref/butter.html
% Design a 6th-order lowpass Butterworth filter with a cutoff frequency 
% of 300 Hz, which, for data sampled at 1000 Hz
pkg load signal;

order = 40;
fc = 500;
fs = 20000;

[a,b] = butter(order,fc/(fs/2));


f = fopen('coeficientes_iir','w');
fprintf(f,'%d\n',order);
fprintf(f,'%d\n',fs);
fprintf(f,'%f\n',b);
fprintf(f,'%f\n',a);
