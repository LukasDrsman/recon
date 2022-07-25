# reconstruct

## Clone
```sh
git clone https://github.com/LukasDrsman/recon.git
cd recon
```

## Export BUILD variable
A `BUILD` variable should be exported before building any components.
```sh
export BUILD="/the/path/to/a/desired/build/directory"
```
To build targets into `recon/build`, use
```sh
export BUILD="$(pwd)/build"
```
while in `recon`.


By default, `../build` is used when making reconstruct. When building search, no such default exists, thus `BUILD` var is required.

## Features
- [x] projection from a given R^3 vector in world coordinates - `cameraProject @ reconstruct, camera.h`
- [x] triangulation using two R^2 vectors on camera image - `stereoTriangulate @ reconstruct, stereo.h`
- [ ] reconstruction from misaligned cameras
- [ ] interest point...
  - [ ] search
  - [ ] matching
