#!/usr/bin/env bash
# 生成要部署的静态站点到 dist/：页面、样式、examples、exercise，以及每个阶段的 zip。
# solution/ 不进网站，只留在仓库里。
set -euo pipefail
cd "$(dirname "$0")/.."

rm -rf dist
mkdir -p dist/downloads
cp index.html 404.html dist/
cp -r assets dist/

for stage in [0-9][0-9]-*/; do
    stage=${stage%/}
    mkdir -p "dist/$stage"
    cp "$stage/index.html" "dist/$stage/"
    for sub in examples exercise; do
        [ -d "$stage/$sub" ] && cp -r "$stage/$sub" "dist/$stage/"
    done
    if [ -d "dist/$stage/examples" ] || [ -d "dist/$stage/exercise" ]; then
        (cd dist && zip -qr "downloads/$stage.zip" "$stage" -x "$stage/index.html")
    fi
done

# 构建产物不该出现在站点里
find dist \( -name '*.o' -o -name test -o -name race -o -name demo -o -name bits \) -type f -delete
echo "dist/ 已生成：$(find dist -type f | wc -l) 个文件"
