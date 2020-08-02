# VideoFromPhoto
Console app that takes use of ffmpeg to create videos from photos.
## Platform Support
This app can currently be launched on linux with ffmpeg and ljsoncpp library, I will add auto installation in the future.
## "Installing" and running the app
### Linux
If you want to compile the software yourself, run the following commands:
```
sudo chmod ugo+rwx installVfP.swp
./installVfP.swp
```
If not just run the software with:
```
./VfP.swp <options>
```
### Windows
Currently not supported

## Options
```
-help
```
displays help for the software.
```
-cconf
```
creates a simple json config file, which can be modified with an ordinary text editor.
```
-custom
```
walks you through each settings used to create your video.
```
-json config.json
```
opens file called `config.json` and continues with values configured in it.

### config.json sample
```
{
"fps":10,
"StartingNumber":1234,
"ImageName":"<name>",
"ImageFileExtension":"<extension>",
"NameOfVideoFile":"<name>"
}
```

> - Fps is the number of frames per second of the video.
> - Starting number is the number of the first photo from your folder which you are converting.
> - Image name is the name before the number (e.g. IMG_).
> - ImageFileExtension is the extension af the images (eg. JPG), **without the dot!**.
> - NameOfVideoFile is the name of the video before .mp4.
> - **If you change anything other than the values on the right side of the config, it might throw an error**, the program also tells you the values before starting to make the video.

