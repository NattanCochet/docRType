# Known issues

## No audio on linux version

Sometimes Linux doesn't provide the required dependencies for SFML's audio libraries so please download the following packages

**Fedora command**
```sh
sudo dnf install alsa-lib-devel pulseaudio-libs-devel
```

**Debian based distributions command**
```sh
sudo apt update
sudo apt install libasound2-dev libpulse-dev
```

**Arch based distributions command**
```sh
sudo pacman -S alsa-lib pulseaudio
```