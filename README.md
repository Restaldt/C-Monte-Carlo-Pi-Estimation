# C-Monte-Carlo-Pi-Estimation
C programs that estimate pi via Monte Carlo


The "Monte Carlo Method" is a method of solving problems using statistics. Given the probability, P, that an event will occur in certain conditions, a computer can be used to generate those conditions repeatedly. The number of times the event occurs divided by the number of times the conditions are generated should be approximately equal to P.

How this program works:

If a circle of radius R is inscribed inside a square with side length 2R, then the area of the circle will be pi*R^2 and the area of the square will be (2R)^2. So the ratio of the area of the circle to the area of the square will be pi/4.

This means that, if you pick N points at random inside the square, approximately N*pi/4 of those points should fall inside the circle.

This program picks points at random inside the square. It then checks to see if the point is inside the circle (it knows it's inside the circle if x^2 + y^2 < R^2, where x and y are the coordinates of the point and R is the radius of the circle). The program keeps track of how many points it's picked so far (N) and how many of those points fell inside the circle (M).

Pi is then approximated as follows:

pi = (4*M)/ N
      
      
      
