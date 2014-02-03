#Tower Defense
*TODO: think of an epic name*

##The Game
TowerDefense (internal working title) will be a simple tower defense game with everything you love about existing flash games but without shitty Flash. It's written in modern C++ and OpenGL, so you can enjoy the beautiful graphics in fullscreen (without browser chrome and blinking ads), without burning your CPU for nothing and without the need to create an account on a random gaming site to be able to save your progress. 

##The Intention
I'm not just writing it to obtain a game of my likes, the main reason is to improve my skills in C++11 and OpenGL core profile. Therefore I try to use as few 3rd party libs as possible and especially do all the rendering on my own. 

##The Toolkit
Since using only OpenGL core profile is a little bit more complex I'm encapsulating the OpenGL objects in C++ classes. These classes are not intendet to form a higher level API of any kind but to make handling of said objects more convenient and to add helping mechanisms like loading data from image files for textures. Also creating this deepens my understanding of them ;)
I'm targetting compatibility with core OpenGL 3.3, but I will use up to 4.4 where it isn't crucial. 
Another part of the toolkit targets portability. To be more platform independent I use GLFW for the window and context creation, but since it's written in plain C I also created classes to easily handle multiple windows and their inputs at once. 
This toolkit remains merged in the code of this game because I create it on demand and don't need it anywhere else. If I will use it again in another project chances are high I will fork the then more matured toolkit as an extra project, but until then you have to extract it on your own if you plan to use it. (This shouldn't be a problem, all the classes are in extra files. But it's highly uncommented so you might have trouble extending it.)

##The first attempt
Actually this is my second attempt. The first one died because of my old hardware. I planned to use mostly core profile and emulate stuff my grafics adapter wasn't capable of, but since I learned that my hardware only supported up to OpenGL 1.4 (Jup, old laptop...) I burried my dreams. 
Back then I also used SFML for window and context creation because it is written in C++ and therefore was easier to integrate, but I learned that it's too bloated with its own rendering mechanisms that completely don't fit my likes. 
Thanks to a new device capable of OpenGL 4.4 I decided to start again from scratch using GLFW, but most OpenGL encapsulations can be kept. 
