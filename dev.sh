#!/bin/bash
set -eou pipefail
CMD="${@:-make}"
LF=$(pwd)/.log.txt
cmd="reap nodemon --delay .1 -i b -i bin -w src -w include -w tests -w meson.build -w dev.sh -w build.sh --signal SIGKILL -e build,c,h,sh -V -x sh -- -c \"$CMD||true\""

ansi --yellow --bg-black --italic "$cmd"
eval "$cmd"
