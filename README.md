# XStudio

## Build on windows

### Needed

- Qt 5.13.2
- Virtual Studio 2017
- Qt VS Tool Addin

### Set environment variables

[Downloads 3rdparty archive on <http://pan.baidu.com>](http://pan.baidu.com/s/1dFaSlpB) (password is `0taa`). This includes compiled [OSG](https://github.com/openscenegraph/OpenSceneGraph) and [LAPACK](http://www.netlib.org/lapack/).

To compile the solution, the two libraries are necessary. You may create the three variables to system environment as following:

```sh
LAPACK = {Your Local Path}\3rdparty\windows\LAPACK
OSG_INCLUDE = {Your Local Path}\3rdparty\windows\OSG\include
OSG_LIB = {Your Local Path}\3rdparty\windows\OSG\lib
```

To access the two libraries from any location you may have to add the directory where they are located to the Path variables. such as following:

```sh
PATH += {Your Path}\3rdparty\windows\LAPACK\bin
PATH += {Your Path}\3rdparty\windows\OSG\bin
```

### Open Visual Studio

Set Platforms to `x64`.

QT5(Addin) -> Qt Options -> Add Qt's path: such as `C:\Qt\Qt5.13.2\5.13.2\msvc2017_64`

Build Solution..
