# ECNU 操作系统实验配套讲义

华东师范大学 2026 秋季操作系统实验的非官方配套讲义。每个阶段对应课程的一个 lab：先讲清楚背景，再给能在自己电脑上跑的示例和练习，帮零基础的同学读懂 lab 指导书在要求什么。

这不是课程官方材料，也不是 lab 的答案。练习是在本机用普通 `gcc` 完成的热身，真正的 lab 仍然要在课程仓库里自己做。

在线阅读：部署后补上地址

## 目录结构

```
src/content/docs/     讲义正文（MDX），站点用 Astro + Starlight 生成
  index.mdx           目录页
  prereq/*.mdx        预备知识：每个主题一页，主线的“预备”框链接到这里
  NN-labN-xxx/index.mdx
src/styles/custom.css 样式调整
public/_redirects     旧 .html 地址到新地址的跳转
prereq/examples/      预备知识的配套示例
NN-labN-xxx/
  examples/           示例：跑一下看输出，不用改
  exercise/           练习：补完 TODO，make 看到全部 PASS 就过关
  solution/           参考答案（只在仓库里，网站上不放）
scripts/
  check.sh            检查所有练习能编译且未通过、所有答案全部通过
  build-site.sh       astro build 之后把示例和练习拷进 dist/，并打包每个阶段的 zip
```

## 做练习

需要 Linux 或 macOS（Windows 用 WSL）和 `gcc`：

```sh
cd 01-lab1-boot/exercise/printf
make
```

RISC-V 交叉工具链和 QEMU 只在看反汇编、跑真正的 lab 时需要，安装方法见 Lab0 讲义第 6 节。

## 维护

```sh
npm install       # 第一次先装依赖
npm run dev       # 本地写作，改动实时刷新
npm run check     # 检查练习和答案
npm run build     # 生成 dist/，同时检查站内链接
npm run preview   # 生成 dist/ 并用 wrangler 在本地预览
npm run deploy    # 生成 dist/ 并部署到 Cloudflare Workers
```

标题后写 `{#id}` 可以固定锚点，比如 `## 寄存器 {#reg}`。其他页面链接到这里时就不受标题文字改动的影响。

站点是纯静态文件，用 Workers 的静态资源功能托管，没有服务端代码。第一次部署前运行 `npx wrangler login`。

## 参与

发现错误或讲得不清楚的地方，欢迎提 issue 或 PR。改练习时同时改对应的 `solution/`，并确认 `npm run check` 通过。

## 许可

- 讲义文字（`src/`）：[CC BY-SA 4.0](LICENSE-CONTENT)
- 示例、练习、答案和脚本代码：[MIT](LICENSE)

课程框架代码和指导书的版权属于课程团队，本仓库不包含它们。
