# ofxOrbbecAstra

openFrameworks addon for using the [Orbbec Astra SDK](https://orbbec3d.com/develop/). Mostly barebones support at the moment – PRs are welcome to help build this out!

## Setup

Clone this addon into your `openFrameworks/addons` folder.

```
cd path/to/openFrameworks/addons/
git clone https://github.com/mattfelsen/ofxOrbbecAstra.git
```

The Astra SDK is bundled in the `libs` folder and does not require a separate download or installation.

## Creating a new project

The easiest approach is to copy the example project, which is already set up with the correct header & linker paths, and has the dynamic libraries in the `bin` folder of the application.

If you are using openFrameworks from github, newer versions of the projectGenerator should automatically set up the project correctly based on the `addon_config.mk` file.

For manual setup, adding to an existing project, or if things are wonky, take a look at `addon_config.mk` for setup. Use the projectGenerator to create or update a project, including ofxOrbbecAstra. Then follow these steps:

- add to **Header Search Paths**:
  - `../../../addons/ofxOrbbecAstra/libs/astra/include/`
- add to **Other Linker Flags**:
  - `../../../addons/ofxOrbbecAstra/libs/astra/lib/osx/libAstra.dylib`
  - `../../../addons/ofxOrbbecAstra/libs/astra/lib/osx/libAstraAPI.dylib`
  - `../../../addons/ofxOrbbecAstra/libs/astra/lib/osx/libAstraUL.dylib`
- copy to your **project/bin** folder:
  - contents of `libs/astra/lib/osx/` folder

## Support

This has been tested with the following setup:

- Xcode 6
- OS X 10.10
- openFrameworks 0.9.0
- Astra SDK 0.4.0 (which is included, no separate download/installation is required)
- Orbbec Astra camera

Windows support hopefully coming soon.