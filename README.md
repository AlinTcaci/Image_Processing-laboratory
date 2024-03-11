# UTCN Image Processing Starter for :apple: MacOS

## Setting up your dev env

This guide will go through the process of setting up a basic development environment for the Image Processing labs. This guide should work for both ARM / Apple Silicon and Intel based processors as well.

The guide goes through setting up the following components

- HomeBrew package manager along with the necessary packages
- Visual Studio Code with the recommended plugins

### Install HomeBrew and req'd packages

In order to simplify installing the necessary software libraries and corresponding dependencies, it's advisable to use a package manager. For :apple: MacOS, one of the most popular ones is HomeBrew.

1. First download HomeBrew from the its website at [brew.sh](https://brew.sh)
2. Afterwards, just like the instruction dictates on the site, copy and paste the necessary command into a terminal of your choosing (such as MacOS's built-in terminal called _Terminal_)

```shell
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

3. Once you've successfully installed homebrew, restart your terminal and install the necessary packages for development. You can find a short description of each package in the table below:

| Package Name | Short Description         |
| ------------ | ------------------------- |
| clang-format | Formatter for clang       |
| cmake        | C++ build process manager |
| git          | Version Control System    |
| llvm         | C / C++ compiler back-end |
| ninja        | C / C++ build system      |
| opencv       | IP / CV framework         |

```shell
brew install clang-format cmake git llvm ninja opencv
```

### Install VS Code and extensions

Next, you'll want to install Visual Studio code from the official site [https://code.visualstudio.com](https://code.visualstudio.com)

It is recommended to install the following extensions for C / C++ development:

- [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack) (contains four extensions) by Microsoft
- [Better C++ Syntax](https://marketplace.visualstudio.com/items?itemName=jeff-hykin.better-cpp-syntax) by Jeff Hykin
- [CodeLLDB](https://marketplace.visualstudio.com/items?itemName=vadimcn.vscode-lldb) by Vadim Chugunov

Once you have successfully installed the necessary extensions, you're ready to begin developing

## Clone the project and try to run it

Next you'll want to clone the starter project  
Open your terminal and enter the following

```shell
git clone --recurse-submodules https://github.com/UTCN-AC-CS-DMP/ip-starter-macos.git
```
