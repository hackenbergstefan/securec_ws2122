# Secure implementations on microcontrollers (WS 21/22)

In this repository the materials for the course "Sichere Implementierungen auf Mikrocontrollern" teached at Hochschule Augsburg in WS 2021/2022 can be found.


## How to install

### Requirements

* [ChipWhisperer v5 release](https://github.com/newaetech/chipwhisperer/releases). Either Virtual Machine or source code.
* ChipWhisperer Lite XMEGA (CW1173)

### 1. Install using ChipWhisperer Virtual Machine

1. Log in to Jupyter.
2. Create a new Notebook in the root folder.
3. Type in the first cell and execute:

```jupyter
! git clone https://gitlab.elektrotechnik.hs-augsburg.de/hackenbs/securec-ws2122.git
```
4. In the second cell:

```jupyter
pip install -e securec-ws2122
```

5. That's it. Now you can use the lecture notebooks.

#### Update

1. Log in to Jupyter.
2. Create a new Notebook in the root folder.
3. Type in the first cell and execute:

```jupyter
! cd securec-ws2122 && git pull
```


### 2. Install using ChipWhisperer source

1. Clone this repository inside (or in parallel) to the chipwhisperer repository.
2. Execute `pip install -e .` inside the clone of this repository.
5. That's it. Now you can use the lecture notebooks.

#### Update

1. Goto the clone and execute `git pull`.
