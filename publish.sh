#!/bin/bash
#发布带时间戳的版本
git config --global user.email "2205599679@qq.com"
git config --global user.name "sweet-haha123"
version=v1.0-$(date +%Y%m%d)
git add .
git commit -m "完成xxx功能，发布$version"
git push origin main
git tag $version
git push origin $version
