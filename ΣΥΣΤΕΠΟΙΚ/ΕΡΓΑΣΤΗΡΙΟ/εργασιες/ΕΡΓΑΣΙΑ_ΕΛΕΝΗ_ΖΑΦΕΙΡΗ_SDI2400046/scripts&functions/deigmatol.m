% =========================================================================
% 3.4 Δειγματοληψία (Sampling) και Θεώρημα Nyquist
% =========================================================================

% 1. Δημιουργία Αναλογικού Σήματος (ως Σημείο Αναφοράς)
fs_cont = 50000;
T = 0.05;
t_cont = 0:1/fs_cont:T;
f1 = 50; f2 = 120;
fc = 1000; Ac = 1; mu = 0.7;

m_cont = cos(2*pi*f1*t_cont) + 0.5*cos(2*pi*f2*t_cont);
s_cont = Ac * (1 + mu*m_cont) .* cos(2*pi*fc*t_cont);

% 2. Υπολογισμός Ορίου Nyquist
f_max = fc + f2;            % 1120 Hz
f_nyquist = 2 * f_max;      % 2240 Hz

fs_array = [10000, 2240, 1500];
titles = {'Υπερδειγματοληψία (f_s >> 2f_{max})', ...
    'Οριακή Δειγματοληψία (f_s = 2f_{max})', ...
    'Υποδειγματοληψία / Aliasing (f_s < 2f_{max})'};

% 3. Διαδικασία Δειγματοληψίας (Stem Plots)
figure('Position', [100, 100, 900, 700]);

for i = 1:3
    fs_samp = fs_array(i);
    t_samp = 0:1/fs_samp:T;

    m_samp = cos(2*pi*f1*t_samp) + 0.5*cos(2*pi*f2*t_samp);
    s_samp = Ac * (1 + mu*m_samp) .* cos(2*pi*fc*t_samp);

    subplot(3, 1, i);
    % Σχεδίαση αναλογικού σήματος με διακριτικό χρώμα
    plot(t_cont, s_cont, 'Color', [0.8 0.8 0.8]);
    hold on;
    % Σχεδίαση δειγμάτων
    stem(t_samp, s_samp, 'r', 'MarkerSize', 3, 'LineWidth', 0.5);

    title(titles{i}, 'Color', 'k');
    ylabel('Πλάτος');
    if i == 3, xlabel('Χρόνος (s)'); end

    xlim([0 0.01]); % Εστίαση για να φαίνονται οι "ακίδες"
    grid on;
end

sgtitle('Επίδραση της Συχνότητας Δειγματοληψίας στο AM Σήμα', 'FontSize', 14);
