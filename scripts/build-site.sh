#!/usr/bin/env bash
# astro build 之后执行：把 examples、exercise 拷进 dist/，并给每个阶段打 zip。
# solution/ 不进网站，只留在仓库里。
set -euo pipefail
cd "$(dirname "$0")/.."

rm -rf dist/downloads
mkdir -p dist/downloads
for stage in [0-9][0-9]-*/ prereq/; do
    stage=${stage%/}
    subs=()
    for sub in examples exercise; do
        [ -d "$stage/$sub" ] && subs+=("$stage/$sub")
    done
    [ ${#subs[@]} -eq 0 ] && continue
    mkdir -p "dist/$stage"
    cp -r "${subs[@]}" "dist/$stage/"
    (cd dist && zip -qr "downloads/$stage.zip" "${subs[@]}")
done

# 构建产物不该出现在站点里
find dist \( -name '*.o' -o -name test -o -name race -o -name demo -o -name bits \
    -o -name memory -o -name pointer \) -type f -delete
echo "dist/ 已生成：$(find dist -type f | wc -l) 个文件"
