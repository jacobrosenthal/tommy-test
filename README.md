# tommy-test

'Blink' sketch for the [WeLoop Tommy](http://welooptommy.com/) that vibrates the motor. Based on work by the [ossw](ossw.github.io) project.

Install [yotta](http://yottadocs.mbed.com/):
* `brew tap ARMmbed/homebrew-formulae`
* `brew install python cmake ninja arm-none-eabi-gcc`
* `pip install yotta`

Build
* `yt build`

Upload
* You need to have previously 'jailbroken' your watch with the ossw project.
* Then you can upload `build/weloop-gcc/source/tommy-test.zip`
