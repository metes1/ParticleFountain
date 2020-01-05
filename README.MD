By: Seda Mete

Description
-----------------
Assignment 3 of Computer Graphics course. Uses C++ and OpenGL to create a 3D particle fountain.

How to Run Program
--------------------
The program is run using the makefile located in the directory. Type "make" to run the program.

Controls
------------
- Left-Arrow   => Rotate scene left on y-axis
- Right-Arrow  => Rotate scene right on y-axis
- Up-Arrow Key => Rotate scene on x-axis
- Down-Arrow   => Rotate scene on x-axis
- F            => Toggle friction mode
- L            => Toggle lightning
- E            => Add explosive particle
- O            => Add objects to the scene
- R            => Reset particle system
- SPACE        => Stop/Start continuous particle addition
- q/ESC        => Quit program

Additional Features
----------------------
1) Explosive Particles: When the 'E' key is pressed a very large explosive particle is added to the fountain. Once this particle collides with the floor, it immediately explodes into 40 tiny particles. Explosive particles can be added whenever, even when the regular fountain flow is paused.

2) Two objects added in the scene: When the 'O' key is pressed two rectangular prisms are added to the scene. Surface normals for each vertex were calculated so the lighting affects it correctly

References
------------
1) http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html

I used this website for some of my material values.