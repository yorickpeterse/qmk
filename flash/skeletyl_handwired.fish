#!/usr/bin/env fish

./util/docker_build.sh yorickpeterse/skeletyl/v2/splinky_3:default
qmk flash -kb yorickpeterse/skeletyl/v2/splinky_3 -km default yorickpeterse_skeletyl_v2_splinky_3_default.uf2
