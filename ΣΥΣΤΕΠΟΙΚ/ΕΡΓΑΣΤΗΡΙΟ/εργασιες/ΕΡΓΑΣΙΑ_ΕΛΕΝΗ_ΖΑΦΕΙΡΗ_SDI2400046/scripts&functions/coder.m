function codes = coder(y, L)
R = ceil(log2(L));
A = 4;
d = (2*A)/L;

% Ορισμός των θεωρητικών σταθμών βάσει τύπου κβαντιστή
if mod(L,2) ~= 0 % Mid-tread
    levels = (-(L-1)/2 : (L-1)/2) * d;
else % Mid-rise
    levels = (-(L/2 - 0.5) : (L/2 - 0.5)) * d;
end

codes = strings(length(y), 1);
for i = 1:length(y)
    % Εύρεση του δείκτη της πλησιέστερης θεωρητικής στάθμης
    [~, idx] = min(abs(levels - y(i)));
    % Μετατροπή σε binary (ο δείκτης ξεκινά από 0 για το dec2bin)
    codes(i) = dec2bin(idx-1, R);
end
end
