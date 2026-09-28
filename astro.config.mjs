// @ts-check
import { defineConfig } from 'astro/config';
import starlight from '@astrojs/starlight';
import starlightLinksValidator from 'starlight-links-validator';
import { satteri } from '@astrojs/markdown-satteri';

export default defineConfig({
  site: 'https://oslab.ychome.net',
  trailingSlash: 'always',
  // {#id} 保留旧讲义的英文锚点，站内链接和外部书签不失效
  markdown: { processor: satteri({ features: { headingAttributes: true } }) },
  integrations: [
    starlight({
      title: 'OS 实验讲义',
      description: 'ECNU 操作系统实验非官方配套讲义',
      defaultLocale: 'root',
      locales: { root: { label: '简体中文', lang: 'zh-CN' } },
      social: [{ icon: 'github', label: 'GitHub', href: 'https://github.com/sudoyc/ecnu-oslab-guide' }],
      customCss: ['./src/styles/custom.css'],
      lastUpdated: false,
      sidebar: [
        { label: '目录', link: '/' },
        {
          label: '预备知识',
          items: [
            { label: '总览', link: '/prereq/' },
            'prereq/memory', 'prereq/pointer', 'prereq/bits', 'prereq/asm', 'prereq/trap', 'prereq/git',
          ],
        },
        {
          label: '阶段',
          items: [
            { label: '00 · Lab0 环境与工具', link: '/00-lab0-env/' },
            { label: '01 · Lab1 机器启动', link: '/01-lab1-boot/' },
            { label: '02 · Lab2 内存管理', link: '/02-lab2-memory/', badge: { text: '提纲', variant: 'note' } },
          ],
        },
      ],
      plugins: [starlightLinksValidator({ exclude: ['/downloads/**'] })],
    }),
  ],
});
