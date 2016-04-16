#!/bin/bash
DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
TOLUA="/data/quick_hero/master/bin/mac/tolua++"

cd "$DIR/"
echo "QUICK_COCOS2DX_ROOT = \"$QUICK_COCOS2DX_ROOT\""
echo "$TOLUA"
echo "$DIR/"
${TOLUA} -L "$DIR/basic.lua" -o "/data/quick_hero/master/lib/cocos2d-x/scripting/lua/cocos2dx_support/LuaCocos2d.cpp" Cocos2d.tolua
