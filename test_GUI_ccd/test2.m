% Fs = 70;  % Sampling Frequency
% 
% N     = 6;   % Order
% Fpass = 1;   % Passband Frequency
% Fstop = 10;  % Stopband Frequency
% Wpass = 4;   % Passband Weight
% Wstop = 80;   % Stopband Weight
% dens  = 20;  % Density Factor
% 
% % Calculate the coefficients using the FIRPM function.
% b  = firpm(N, [0 Fpass Fstop Fs/2]/(Fs/2), [1 1 0 0], [Wpass Wstop], ...
%            {dens});
% Hd = dfilt.dffir(b);
% 
% [y,zf] = filter(b,1,loc-sum(loc)/size(loc,2));
% 
% plot(1:200,loc-sum(loc)/size(loc,2),1:200,y)


A=[ 0.18,1; 0.05,1];
B=[0;-5];
inv(A)*B