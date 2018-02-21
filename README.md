# UniStyle

`UniStyle` is an utility to parse and compile `uss` (*universal style sheet*) files into `CSS3` or `LaTeX` class.
The `uss` is just a `YAML` file that contain a sub-set of the `CSS3` styling option. The need of `uss` files is needed to fill the gab between web publication and paper publication.
As well `uss` is a simpler language for machine and user interpretation.

## Build and Use

The only dependancy of this project is `libyaml` available in most of GNU/Linux distribution.

Open a terminal and move on the project directory then:

```bash
mkdir build
cd build
meson ..
# to compile
ninja
# to install
sudo ninja install
```

To try out the converter simply:

```
cd build
./convert --css input.uss
# or for tex classes
./convert --cls input.uss
# or for AST
./convert --ast input.uss
```
