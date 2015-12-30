# ofxOrbbecAstra

openFrameworks addon for using the [Orbbec Astra SDK](https://orbbec3d.com/develop/). Mostly barebones support at the moment – PRs are welcome to help build this out!

## Setup

Clone this addon into your `openFrameworks/addons` folder.

```
cd path/to/openFrameworks/addons/
git clone https://github.com/mattfelsen/ofxOrbbecAstra.git
```

The Astra SDK is bundled in the `libs` folder and does not require a separate download or installation.

## Running the example project

Hopefully this should compile and run without any hiccups. Please open an issue if you run into trouble here.

## Using this addon in your project

If you're creating a new project, the easiest approach is to copy the example project, which is already set up with the correct header & linker paths, and has the dynamic libraries in the `bin` folder of the application.

If you're using the projectGenerator, either to create a new project or update an existing one, most things will be taken care of for you, but you will still need to set some things manually. Likewise, the Xcode OF plugin will probably do some, but not all, of the necessary things. Check that the following settings, which are also outlined  `addon_config.mk`, are set up correctly, or do so manually if needed:

- add to **Header Search Paths**:
  - `../../../addons/ofxOrbbecAstra/libs/astra/include/`
- add to **Other Linker Flags**:
  - `../../../addons/ofxOrbbecAstra/libs/astra/lib/osx/libAstra.dylib`
  - `../../../addons/ofxOrbbecAstra/libs/astra/lib/osx/libAstraAPI.dylib`
  - `../../../addons/ofxOrbbecAstra/libs/astra/lib/osx/libAstraUL.dylib`
- add to **Runpath Search Paths**:
  - `@executable_path/../../../`
- copy to your **project/bin** folder:
  - contents of `libs/astra/lib/osx/` folder (not the `osx` folder itself). That is...
    - `libAstra.dylib`
    - `libAstraAPI.dylib`
    - `libAstraUL.dylib`
    - `Plugins` folder
    - `astra.toml`

## Support

This has been tested with the following setup:

- Xcode 6
- OS X 10.10, 10.11
- openFrameworks 0.9.0
- Astra SDK 0.4.0 (which is included, no separate download/installation is required)
- Orbbec Astra camera

Windows support hopefully coming soon. The libs from the Win32 and x64 SDKs are included, but I haven't had a chance to test this.

## SDK Note

As of the Astra 0.4.0 SDK release, one of the libraries in the SDK (`liborbbec.dylib`) is hard-coded to look for libusb at `/usr/local/lib/libusb-1.0.0.dylib`. I've bundled libusb with this addon (buried deep in the Plugins folder) and modified liborbbec.dylib so that no external depdencies are needed.