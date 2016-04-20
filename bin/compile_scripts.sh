#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo "compile_scripts---DIR = $DIR"
php "$DIR/lib/compile_scripts.php" $*
