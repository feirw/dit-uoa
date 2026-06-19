% =========================================================================
% MAIN SCRIPT - ΚΒΑΝΤΙΣΗ ΚΑΙ ΚΩΔΙΚΟΠΟΙΗΣΗ
% =========================================================================


% =========================================================================
% Σήμα εισόδου
% =========================================================================
Ts = 0.01;
t = 0:Ts:1;

x = 4*cos(2*pi*t);

% =========================================================================
% ΠΕΡΙΠΤΩΣΗ 1 : L = 7  (Mid-tread)
% =========================================================================
L7 = 7;

[d7, y7, e7] = quantizer(x, L7);

codes7 = coder(y7, L7);

mse7_prac = mean(e7.^2);
mse7_theor = (d7^2)/12;

figure;

subplot(2,1,1);

plot(t,x,'b','LineWidth',1.2);
hold on;

stairs(t,y7,'r','LineWidth',1.5);

title(['Mid-tread Quantizer (L = 7), \Delta = ', num2str(d7)]);
xlabel('Time (s)');
ylabel('Amplitude');

legend('Original Signal','Quantized Signal');

grid on;

subplot(2,1,2);

plot(t,e7,'k','LineWidth',1.2);


xlabel('Time (s)');
ylabel('Error');

grid on;

disp('=================================================');
disp('L = 7 (Mid-tread)');
disp('Encoded Values:');
disp(codes7);

% =========================================================================
% ΠΕΡΙΠΤΩΣΗ 2 : L = 8  (Mid-rise)
% =========================================================================
L8 = 8;

[d8, y8, e8] = quantizer(x, L8);

codes8 = coder(y8, L8);

mse8_prac = mean(e8.^2);
mse8_theor = (d8^2)/12;

figure;

subplot(2,1,1);

plot(t,x,'b','LineWidth',1.2);
hold on;

stairs(t,y8,'r','LineWidth',1.5);

title(['Mid-rise Quantizer (L = 8), \Delta = ', num2str(d8)]);
xlabel('Time (s)');
ylabel('Amplitude');

legend('Original Signal','Quantized Signal');

grid on;

subplot(2,1,2);

plot(t,e8,'k','LineWidth',1.2);

xlabel('Time (s)');
ylabel('Error');

grid on;

disp('=================================================');
disp('L = 8 (Mid-rise)');
disp('Encoded Values:');
disp(codes8);
