# curl command line cheatsheet

## 1. common download file

`curl -o /path/to/file -x http://proxy.server:port -L https://download.link`

- `-o` 下载后的存储文件路径
- `-x` 可选的代理服务器
- `-L` 自动跟随重定向，防止下载来一个 `302 reidrection`，后面是下载链接

