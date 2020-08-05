# Inverse & Forward Kinematics

Excecise in implemenation of inverse kinematics. 

In this exercise theres an arm object that can be manipulated using the mouse:

![Image of Yaktocat](https://github.com/rotba/Graphics_4/blob/master/orig.png)

The challenge and the interesting part is that the object is constituen from links that are has a certain topology and mutual constraints.
Here we can see the expected outcome of manipulating some internal link.

The way we implemented interaction between the links is by using forward kinematics techniqe to calculate the matrix of each object (translation and rotation).

![Image of Yaktocat](https://github.com/rotba/Graphics_4/blob/master/forward1.png)

![Image of Yaktocat](https://github.com/rotba/Graphics_4/blob/master/forward2.png)

The second task was to implement an algorithm to make the arm find the other box object in the scene, and to do so we used the inverse kinematics approach:

![Image of Yaktocat](https://github.com/rotba/Graphics_4/blob/master/inverse.png)

Here we can see the result of this algorithm (obtained by clicking the space button).

You can clone this repository to play with our arm! Just double click the inverse_kinematics.lnk.
