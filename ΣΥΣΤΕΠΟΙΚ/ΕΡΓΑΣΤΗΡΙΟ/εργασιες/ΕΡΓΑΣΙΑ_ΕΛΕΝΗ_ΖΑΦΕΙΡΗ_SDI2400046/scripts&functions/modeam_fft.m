% =========================================================
% 3.2 AM Διαμόρφωση και Μελέτη Φάσματος (FFT)
% =========================================================


fs = 50000;
T = 0.05;
t = 0:1/fs:T-1/fs;

f1 = 50;
f2 = 120;
fc = 1000;
Ac = 1;

m = cos(2*pi*f1*t) + 0.5*cos(2*pi*f2*t);

mu_values = [0.1 0.7 1.2];

N = length(t);
f_axis = (-N/2:N/2-1)*(fs/N);

figure;

for i = 1:length(mu_values)

    mu = mu_values(i);

    % AM signal
    s = Ac * (1 + mu * m) .* cos(2*pi*fc*t);

    % FFT
    S_fft = fftshift(fft(s));
    S_fft = abs(S_fft)/max(abs(S_fft));

    % =========================
    % TIME DOMAIN
    % =========================
    subplot(3,2,2*i-1);

    plot(t, s, 'LineWidth', 1.2);
    hold on;

    % envelope για να φαίνεται καθαρά η διαφορά :)
    env = Ac*(1 + mu*m);
    plot(t, env, 'r--', 'LineWidth', 1);

    plot(t, -env, 'r--', 'LineWidth', 1);

    title(['AM στο Χρόνο, \mu = ', num2str(mu)]);
    xlabel('Χρόνος (s)');
    ylabel('Πλάτος');
    grid on;
    xlim([0 0.05]);

    % =========================
    % FREQUENCY DOMAIN
    % =========================
    subplot(3,2,2*i);

    plot(f_axis, S_fft, 'LineWidth', 1.2);
    title(['Φάσμα AM, \mu = ', num2str(mu)]);
    xlabel('Συχνότητα (Hz)');

    grid on;
    xlim([-2000 2000]);

end
