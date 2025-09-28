# Self-Hosted Runner for Execution Test

The CMSIS-Toolbox implements and [Run and Debug Configuration](https://open-cmsis-pack.github.io/cmsis-toolbox/build-overview/#run-and-debug-configuration) for command line usage with pyOCD. pyOCD is a debug connector used in [Keil Studio] that offers also command-line operation for Continuous Integration (CI).

This section explains how to setup a Linux box that runs a GitHub self-hosted runner for programming and execution of an application. The [build workflow](../.github/workflows/Build_T2G_Release.yaml) is executed on a GitHub hosted runner that stores the build output as an artifact.

![CI and HiL Test](CI_HIL.png "CI and HiL Test")

## Setup of a Linux System

This example uses an Raspberry Pi5 with Ubuntu ARM.

The following development tools and software packs are installed:

- [CMSIS-Toolbox](https://open-cmsis-pack.github.io/cmsis-toolbox) for download of Software packs.
- [pyOCD](https://pyocd.io/) for program download and execution.
- [pack: Infineon::T2G-B-H_DFP](https://www.keil.arm.com/packs/t2g-b-h_dfp-infineon) for access to flash programming algorithms.

### Install CMSIS-Toolbox

ToDo on Raspberry Pi

```
     # Set the path to vcpkg
     $ export PATH=$PATH:/home/devadmin/vcpkg
```

### Install pyOCD

ToDo on Raspberry Pi

```
     # Download pyOCD
     $ wget --no-check-certificate -P Downloads/ https://github.com/pyocd/pyOCD/releases/download/v0.39.0/pyocd-linux-arm64-0.39.0.zip

     # Install pyOCD 
     $ unzip pyocd-linux-arm64-0.39.0.zip -d /home/devadmin/.local/bin/
```

### Donwload and install the Infineon.T2G-B-H_DFP.1.2.1.pack DFP

ToDo on Raspberry Pi

```
     # Dowload the Infineon DFP
     $ wget --no-check-certificate -P Downloads/ https://itools.infineon.com/cmsis_packs/T2G-B-H/Infineon.T2G-B-H_DFP.1.2.1.pack

     # Add pack to PACK list
     $ cpackget add -a Infineon::T2G-B-H_DFP@^1.2.1
```


## Setup Runner on Raspberry Pi5

You need a GitHub account with access to the repository/org where you want the runner.

Run these commands on the Raspberry Pi. They’ll look something like this:

ToDo on Raspberry Pi

```
     # Create a folder dedicated for your repository. i.e.
     $ mkdir runner-safety-ifx-t2g && cd runner-safety-ifx-t2g

     # Download the latest runner package
     $ curl -o actions-runner-linux-arm64-2.328.0.tar.gz -L https://github.com/actions/runner/releases/download/v2.328.0/actions-runner-linux-arm64-2.328.0.tar.gz

     # Optional: Validate the hash
     $ echo "b801b9809c4d9301932bccadf57ca13533073b2aa9fa9b8e625a8db905b5d8eb  actions-runner-linux-arm64-2.328.0.tar.gz" | shasum -a 256 -c

     # Extract the installer
     $ tar xzf ./actions-runner-linux-arm64-2.328.0.tar.gz

     # Configure the self-hosted runner
     $ ./config.sh --url https://github.com/<user_name>/cmsis-mlek-examples --token <token_string>
	 
```

## Workflow

Build first the artifacts by executing the [Build_T2G_Release.yaml](/.github/workflows/Build_T2G_Release.yaml) workflow.

Start the download, flashing, and execution operations on the self-hosted runner.

Actions on Raspberry Pi

```
     # Start the listener on the Raspberry Pi
     $ ./run.sh
```

Start the [Run_T2G_Release.yaml](/.github/workflows/Run_T2G_Release.yaml) workflow.
