#!/bin/bash
#发布带时间戳的版本
# git config --global user.email "2205599679@qq.com"
# git config --global user.name "sweet-haha123"
# version=v1.0-$(date +%Y%m%d)
# git add .
# git commit -m "完成xxx功能，发布$version"
# git push origin main
# git tag $version
# git push origin $version


#!/bin/bash
# 发布带时间戳的版本

# 可选：如果你已经全局配置过用户名邮箱，就不用每次写了
# git config --global user.email "2205599679@qq.com"
# git config --global user.name "sweet-haha123"

# 出错时自动退出
set -e

version=v1.0-$(date +%Y%m%d)

echo "📦 正在提交代码，版本号：$version"

git add .
git commit -m "完成xxx功能，发布$version"
git push origin main

echo "🏷️ 打标签 $version"
git tag $version
git push origin $version

echo "✅ 发布完成"
