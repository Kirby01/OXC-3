# OXC-3
Dynamic Leveling Amplifier
OXC-3 Core

a = (1 - (0.004 + abs(a - b) / (a + b))) x b + (0.004 + abs(a - b) / (a + b)) x abs(3 x (l/2 + r/2)^2) / a

b = (1 - (0.001 + abs(a - b) / (a + b))) x a + abs(a - b) / (1 + abs(a - b)) + (0.001 + abs(a - b) / (a + b)) x b^(1 - abs(a - b) / (a + b))

output:
L = l / b

R = r / b


OXC-3 uses adaptive distance-based timing between two recursive states
(a and b). As the states separate, timing accelerates automatically,
while a bounded difference term stabilizes the gain-control behavior.
The result is a fast but smooth dynamic leveling effect with strong
self-correcting behavior and low waveform distortion. Developed with math plugin by Socalabs.
