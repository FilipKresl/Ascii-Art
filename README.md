### About

This C++ application was developed as a semester assignment for the BI-PA2 course at the Czech Technical University in Prague, Faculty of Information Technology.
It can take images in several basic formats and convert them into ASCII art. 
Users have the option to customize their ASCII palette or use a pre-designed one. 
When multiple images are uploaded, the application can emulate a video sequence. 
Additionally, it offers features such as lightening, darkening, various resizing options, color inversion, ... 

----
### Examples
<img width="1120" alt="Screenshot 2024-05-09 at 10 06 47" src="https://github.com/FilipKresl/Ascii-Art/assets/45666363/6150a9b3-5410-42df-85d4-50696fc82037">

<img width="732" alt="Screenshot 2024-05-09 at 10 23 26" src="https://github.com/FilipKresl/Ascii-Art/assets/45666363/95a75d73-04a7-4881-9142-395dcd310006">

<img width="1415" alt="Screenshot 2024-05-09 at 10 26 17" src="https://github.com/FilipKresl/Ascii-Art/assets/45666363/bc5a76d0-9f98-4872-8bf0-dc0c00a0a43a">

----
### HELP

#### Commands:
  - h for help
  - p for play
  - l for inserting own pallete in a file (write the name of the file before the images)
  - n for natural look - initial stretching disabled
  - r for output in round Ascii (e.g. o80@) (default)
  - s for output in sharp Ascii (e.g. -/I#)

#### Run examples:
  - ./kreslfil assets/img/johnny.bmp
  - ./kreslfil assets/img/albert.tga
  - ./kreslfil -l assets/palleteNumbers.txt assets/img/cat2.bmp assets/img/cat.bmp
  - ./kreslfil -l assets/palletePerfect.txt assets/img/cat2.bmp assets/img/cat.bmp
  - ./kreslfil -s -p assets/img/img*.bmp

#### Editing:
  - Z,X,C,V for different types of RESIZING
  - N,M     for SWITCHING between images
  - B       for RELOADING the image with initial setting
  - K,L     for increasing/decreasing LIGHT for the current image
  - W,A,S,D for MOVING the current image
  - F       for DELETING the image
  - G,H     for SWAPPING the image with previous/next one

  - I       for INVERTING the colors
  - O,P     for changing the PALLETE
  - U       for PLAY/STOP
  - Y       for changing the Direction of playing
----
