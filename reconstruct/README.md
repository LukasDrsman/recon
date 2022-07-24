# reconstruct@recon

## Build
```sh
cd reconstruct
make
cd ..
```
## Run
```sh
./build/recon [left camera config].cam [right camera config].cam
```

## Camera configs
File extension: `.cam`  
Structure:
```
camera_x camera_y camera_z
image_width image_height sensor_width sensor_height focal_length 
```
Values must be expressed in the form `number.number` (e.g `1.0`, `0.04`, `0.0`).  
Camera configs are parsed using `paramload(args...)` defined in `src/conf/paramload.h`.
