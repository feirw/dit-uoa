function [d, y, e] = quantizer(x, L)
A = 4; % Μέγιστο πλάτος σήματος
d = (2*A)/L; % Βήμα κβάντισης

if mod(L,2) ~= 0 % Mid-tread (Περιττό L)
    y = d * round(x/d);
    max_level = ((L-1)/2)*d;
else % Mid-rise (Άρτιο L)
    y = d * (floor(x/d) + 0.5);
    max_level = (L/2 - 0.5)*d;
end

% Clipping (Περιορισμός στα όρια των σταθμών)
y(y > max_level) = max_level;
y(y < -max_level) = -max_level;

% Σφάλμα
e = y - x;
end
