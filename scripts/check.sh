#!/usr/bin/env bash
# 检查练习和答案：exercise 必须能编译、跑出失败用例；solution 必须全部通过。
set -uo pipefail
cd "$(dirname "$0")/.."
fail=0

run() {  # 输出 make 的结果，返回 0=全部通过 1=有失败用例 2=编译出错
    local out
    out=$(timeout 60 make -s -C "$1" 2>&1)
    make -s -C "$1" clean >/dev/null 2>&1
    if grep -q 'error:' <<<"$out"; then return 2; fi
    if grep -qE 'FAIL|panic|失败' <<<"$out"; then return 1; fi
    return 0
}

for dir in [0-9][0-9]-*/exercise/*/; do
    dir=${dir%/}
    sol=${dir/exercise/solution}
    run "$dir"
    case $? in
        1) echo "✓ $dir（未完成，有失败用例）" ;;
        0) echo "✗ $dir：未完成的练习不应该通过"; fail=1 ;;
        *) echo "✗ $dir：编译出错"; fail=1 ;;
    esac
    if [ ! -d "$sol" ]; then
        echo "✗ $sol：缺少答案"; fail=1
    elif run "$sol"; then
        echo "✓ $sol"
    else
        echo "✗ $sol：答案没有全部通过"; fail=1
    fi
done

if timeout 60 make -s -C 01-lab1-boot/examples race >/dev/null 2>&1; then
    echo "✓ 01-lab1-boot/examples race"
else
    echo "✗ 01-lab1-boot/examples race"; fail=1
fi
make -s -C 01-lab1-boot/examples clean >/dev/null 2>&1
if make -s -C 00-lab0-env/examples/make-demo run >/dev/null 2>&1; then
    echo "✓ 00-lab0-env/examples/make-demo"
else
    echo "✗ 00-lab0-env/examples/make-demo"; fail=1
fi
make -s -C 00-lab0-env/examples/make-demo clean >/dev/null 2>&1
exit $fail
