# recon

## Build
Dependencies: `opencv4`
```sh
git clone https://github.com/LukasDrsman/recon.git
cd recon
cmake .
make
```
## Run
```sh
./build/recon [left_camera].cam [right_camera].cam [left_sample] [right_sample]
```

## Camera configs
File extension: `.cam`  
Structure:
```
camera_x camera_y camera_z
image_width image_height sensor_width sensor_height focal_length 
```
Values must be expressed in the form `number.number` (e.g `1.0`, `0.04`, `0.0`).  
Camera configs are parsed using `c::paramload(args...)` defined in `src/conf/paramload.hpp`.

## Features
- [x] projection from a given R^3 vector in world coordinates - `re::Camera.project(args...)`
- [x] triangulation using two R^2 vectors on camera image - `re::Stereo.triangulate(args...)`
- [ ] epipolar line based point matching (not tested) - `re::Stereo.match(args...)`
- [ ] interest point search
