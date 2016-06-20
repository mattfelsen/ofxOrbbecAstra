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

If you're creating a new project, the easiest approach is to copy the example project, which is already set up with the correct header & linker paths.

If you're using the projectGenerator, either to create a new project or update an existing one, most things will be taken care of for you, but you will still need to set some things manually. Likewise, the Xcode OF plugin will probably do some, but not all, of the necessary things. Check that the following settings, which are also outlined  `addon_config.mk`, are set up correctly, or do so manually if needed:

- add to **Header Search Paths**:
  - `../../../addons/ofxOrbbecAstra/libs/astra/include/`
- add to **Other Linker Flags**:
  - `../../../addons/ofxOrbbecAstra/libs/astra/lib/osx/libastra_core_api.dylib`
  - `../../../addons/ofxOrbbecAstra/libs/astra/lib/osx/libastra_core.dylib`
  - `../../../addons/ofxOrbbecAstra/libs/astra/lib/osx/libastra.dylib`
- add to **Runpath Search Paths**:
  - `@executable_path/../../../../../../../addons/ofxOrbbecAstra/libs/astra/lib/osx/`

Note: this assumes your project folder is at the standard "three levels down" from your openFrameworks folder, e.g. `openFrameworks/apps/myApps/projectFolder/`. If not, you may need to adjust the runpath setting.

## Support

This has been tested with the following setup:

- Xcode 6
- OS X 10.11
- openFrameworks 0.9.0
- Astra SDK 0.5.0 (which is included, no separate download/installation is required)
- Orbbec Astra/Astra Pro camera

Windows support hopefully coming soon. The libs from the Win32 and x64 SDKs are included, but I haven't had a chance to test this.

## Hardware Note – Astra Pro & color data

There is a known issue with the SDK and Astra Pro cameras which does not make the color data available. Trying to start the color stream (i.e. calling `astra.initColorStream()`) will also cause other streams to fail, so you must comment-out this line in the example and/or your projects.

The color data is separately available as a standard webcam. Rather than using `initColorStream()`, you can use `initVideoGrabber()` which uses an `ofVideoGrabber` under the hood for you.

You can keep an eye on the [Orbbec forums](https://3dclub.orbbec3d.com/) to see the latest.