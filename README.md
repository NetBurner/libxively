# NetBurner Xively C library (libxively)

## Introduction

nb-libxively is a netburner implementation of libxively, the official Xively
C library. For more information about libxively, visit the 
[libxively github repository](https://github.com/xively/libxively)

## Get started

* Create a library folder in your local netburner repostitory (default c:\nburn)
* Open a cmd prompt and go to the default nburn directory
* `setenv.bat` to set your local environment to build NetBurner products
* `cd library` to enter the new library directory
* `git clone https://github.com/netburner/nb-libxively`
* `cd nb-libxively`
* `make` to build the library

Once the library has successfull built, you will be able to use the library by
including \nburn\lib\nb-libxively.a in your NBEclipse project. You will also need
to include the nb-libxively source folder to your project directory includes.
