Last updated 7-September-2018

# Introduction


(From https://www.heynow.com/redweasel)

Red Weasel, one of our family of weasel apps, lets you easily change the RGB values on a set of images. We created it for a friend who wanted to correct for the red loss in his underwater photos. (Even water at 5ft depth will have a noticeable loss of red.) Our resulting app corrects the red balance, and for good measure green and blue too, making it useful for a wider audience while still keeping the overall simplicity of the weasel apps.


# How To Build

Red Weasel is both a macOS and Windows application. It is built using the JUCE (htttp://www.juce.com) application framework. 

We use rake for generating the project files and building from the command line. Have a look at the output of this on macOS:
```
cd {git-root}/ReadWeasel/mac
rake -T
```
and on for Windows:
```
cd {git-root}/RedWeasel/win
rake -T
``` 
to see what all the build tasks are. Read the contents of the rakefile to learn about command line options such as "sign" and "rev".

Once a full build has been made, the Xcode and VisualStudio projects will exist. You can then use one or both of the following IDEs to do editing and debugging of the application:

## macOS build prerequisites

You'll need XCode 8 or later to build on macOS.

Download the .zip of JUCE v5.3.2 from https://github.com/WeAreROLI/JUCE/releases/tag/5.3.2. Unpack the zip and place it at `~/JUCE`

## Windows build prerequisites

You'll need Virtual Studio 2017 to build on Windows.

Download the .zip of JUCE v5.3.2 from https://github.com/WeAreROLI/JUCE/releases/tag/5.3.2. Unpack the zip and place it at `C:\JUCE`
