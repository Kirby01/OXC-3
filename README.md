# OXC-3
Dynamic Leveling Amplifier based on

a=(1-(0.004+abs(a-b)/(a+b)))*b+(0.004+abs(a-b)/(a+b))*abs(drive*(l/2+r/2)^2)/a;

b=(1-(0.001+abs(a-b)/(a+b)))*a + abs(a-b)/(1+abs(a-b))+(0.001+abs(a-b)/(a+b))*b^(1-abs(a-b)/(a+b));

l/b;
r/b;
