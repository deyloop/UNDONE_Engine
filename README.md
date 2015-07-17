# README #

This README documents whatever steps are necessary to get project up and running.

### What is this repository for? ###

This repository is contains the latest source code, along with some other stuff like timely screenshots, of the UNDONE Engine, which is primarily another game engine, but what the engine is for might change in the future. The engine is currently only compatible with the Windows operating system, but it is designed in a way so that all system specific code is nicely abstracted away under its own little place, and to port it into other operating systems is fairly easy to do.

####Implimented Features:####

* The engine is able to access the graphics hardware to use fully accelerated hardware.

* It can load 3d models of many supported and widely used formats such as 
  1. .obj 
  2. .collada 
  3. .blend 
  4. .3ds 
  5. .maya <br>
  and more!

* Can load up all majorly available image formats.

* Has a component based architecture which makes using the engine easy.

* A customized memory management module.


### How do I get set up? ###
   
To set up the project, it is prefered that you fork it and check for the following dependancies:
* [The Open Asset Import Library (AssImp)](http://assimp.sourceforge.net/).
* [FreeImage library.](http://freeimage.sourceforge.net/)
* [FreeType library.](http://www.freetype.org/)
* [OpenGL](https://www.opengl.org/)
* [The GL Extention Wrangler (GLEW)](http://glew.sourceforge.net/)
* [The GL Maths library headers (GLM)](http://glm.g-truc.net/)

The source code does not have a MakeFile or any project generation in it. It only has a Visual Studio Project file.

###How To Contribute###
In case you have something to contribute to the functionality of UNDONE, I would be more than pleased to know

There are several ways you can contribute to this repository. Any way you choose, you want to be **making a fork** of this repo and making changs there, and then sending me a **pull request** when done to get your contribution accepted and done on the source code.

##### Make Bug Fixes ####
* You can check the **Issues** page on the repository and serach for the Issues taged *Bug* to find known bugs in the engine.

##### Help Make New Features ####
* You can check the **Issues** Page regularly for new proposed features, and impliment them on your fork, and after complete testing, **create a pull request**.

##### Propose new features #####
Alternatively, if you have an idea but don't know how to impliment it, you can just *create a new issue* or *let me know through an email*. 

##### Report Bugs #####
You can similarly use the **Issues** page to notify of any undiscovered bugs. Please Tag that issue as a bug when you do so.

#### Credit for Contribution ####
You may name yourself as the author of any source files *you create*. **In case you modify any existing code, you are not allowed to place your name into the source file.**

### Who do I talk to? ###

* Repo owner or admin :  Anurup Dey
* E-mail: anu.rup.dey98@gmail.com

