# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/qmk)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the Clueboard product line.

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [VitePress](https://vitepress.dev/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls).

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.

***

## LowBrain Section

### 前提OS・ソフトウェア
- Windows10 Pro 20H2
- WLS2 Ubuntu-20.04
- Docker Desktop 20.10.5

### コンパイル環境セットアップ手順
1. `WLS2 Ubuntu-20.04`のコンソールにて以下コマンドを実行  
（以下ユーザホームディレクトリを作業場所とした例）  
    ```sh
    cd ~/
    git clone --recurse-submodules https://github.com/lowbrain/qmk_firmware.git
    ```

### QMK Custom Keymaps コンパイル手順

1. `WLS2 Ubuntu-20.04`のコンソールにて以下コマンドを実行  
（以下ユーザホームディレクトリを作業場所とした例）

    * ymd75/rev2:custom_jp  
        source:~/qmk_firmware/keyboards/ymd75/keymaps/custom_jp
        ```sh
        cd ~/qmk_firmware
        util/docker_build.sh ymd75/rev2:custom_jp
        ```

    * xiudi/xd60/rev3:custom_jp  
        source:~/qmk_firmware/keyboards/xiudi/xd60/keymaps/custom_jp
        ```sh
        cd ~/qmk_firmware
        util/docker_build.sh xiudi/xd60/rev3:custom_jp
        ```

    * xiudi/xd87:custom_jp  
        source:~/qmk_firmware/keyboards/xiudi/xd87/keymaps/custom_jp
        ```sh
        cd ~/qmk_firmware
        util/docker_build.sh xiudi/xd87:custom_jp
        ```

    * id80:custom_jp  
        source:~/qmk_firmware/keyboards/id80/ansi/keymaps/custom_jp
        ```sh
        cd ~/qmk_firmware
        util/docker_build.sh id80/ansi:custom_jp
        ```

2. `~/qmk_firmware`にファームウェアとしてのファイル`*.hex`が出力されるのでそのファイルを対象キーボードにフラッシュする。
フラッシュの方法については、キーボードの仕様によるので省略する。