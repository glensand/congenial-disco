# congenial-disco
[![Actions Status](https://github.com/glensand/congenial-disco/workflows/BuildAndTest/badge.svg)](https://github.com/glensand/congenial-disco/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
![GitHub last commit](https://img.shields.io/github/last-commit/glensand/congenial-disco?color=red&style=plastic)
![GitHub stars](https://img.shields.io/github/stars/glensand/congenial-disco?style=social)
![GitHub watchers](https://img.shields.io/github/watchers/glensand/congenial-disco?style=social)
![GitHub followers](https://img.shields.io/github/followers/glensand?style=social)

Small library. Helps invoke function by name. Work in progress.
# Build
- Clone repository: ``git clone https://github.com/glensand/congenial-disco``
- Generate platform dependent project: ``cmake -S [root_clone/lib] -B [root_clone\install]``
- Go to ``root_clone\install`` and run ``cmake --build . --target install --config [Config]``. The ``Config`` parameter might be Release or Debug
