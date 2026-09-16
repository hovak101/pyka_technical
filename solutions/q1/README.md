# Q1

## Setup (for `explore_data.ipynb`)

The notebook's dependencies are pinned in `environment.yml`. Create and activate the conda environment with:

```
conda env create -f environment.yml
conda activate pyka_technical
```

Then select the `pyka_technical` kernel when running `explore_data.ipynb`.

## Data

Add your log files to a `data/` folder in this directory before running `main.cpp` or the notebook. Each file must:

- Be named `log<N>.csv` (e.g. `log1.csv`, `log2.csv`), where `<N>` is any integer.
- Have a header row followed by columns, in order: `timestamp, gps_altitude, altimeter_1_altitude, altimeter_2_altitude`.

```
timestamp,gps_altitude,altimeter_1_altitude,altimeter_2_altitude
0,45.668459583757794,0.0,0.0
1,45.66841421471328,0.0,0.0
...
```

`main.cpp` scans `data/` for files matching `log<N>.csv` and writes a corresponding `output/corrected<N>.csv` for each.

## Build & Run

Build with CMake from this directory:

```
mkdir build
cd build
cmake ..
cmake --build .
```

Then run the resulting `main` executable (e.g. `./main` on Linux/macOS, or `main.exe` / `Debug\main.exe` on Windows depending on your generator). It reads from `data/` and writes to `output/`, both resolved relative to the source directory, so it can be run from anywhere inside `build/`.
