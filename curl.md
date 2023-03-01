# curl command line cheatsheet

## 0. Windows Build

outputs are in `path/to/curl/builds`

### x64

open `x64 Native Tools Command Prompt for VS 2019`

`cd` to `path/to/curl/winbuild`

`Debug dll`

`nmake -f Makefile.vc VC=14 mode=dll DEBUG=yes MACHINE=x64`

`Release dll`

`nmake -f Makefile.vc VC=14 mode=dll DEBUG=no MACHINE=x64`

### Win32

open `x86 Native Tools Command Prompt for VS 2019`

`cd` to `path/to/curl/winbuild`

`Debug dll`

`nmake -f Makefile.vc VC=14 mode=dll DEBUG=yes MACHINE=x86`

`Release dll`

`nmake -f Makefile.vc VC=14 mode=dll DEBUG=no MACHINE=x86`


## 1. common download file

`curl -o /path/to/file -x http://proxy.server:port -L https://download.link`

- `-o` 下载后的存储文件路径
- `-x` 可选的代理服务器
- `-L` 自动跟随重定向，防止下载来一个 `302 reidrection`，后面是下载链接


## 2. libcurl send multiple http requests with one socket

After `curl_easy_init`, add `Connection: keep-alive` to `http headers` by calling 

`curl_slist_append(headers, "Connection: keep-alive");`

Then call `curl_easy_perform` as much as needed before calling `curl_easy_cleanup`.
