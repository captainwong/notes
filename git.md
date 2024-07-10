# Git Notes

## compare two files

`git diff --no-index file1 file2`

## github

`2023-3-24 18:08:44`

repositories using scheme `git@gihub.com:` show errors below when pushing.

```
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
The fingerprint for the RSA key sent by the remote host is
SHA256:uNiVztksCsDhcc0u9e8BujQXVUpKZIDTMczCvj3tD2s.
Please contact your system administrator.
Add correct host key in /c/Users/Jack/.ssh/known_hosts to get rid of this message.
Offending RSA key in /c/Users/Jack/.ssh/known_hosts:1
Host key for github.com has changed and you have requested strict checking.
Host key verification failed.
fatal: Could not read from remote repository.

Please make sure you have the correct access rights
and the repository exists.
```

after googling, oh, github changed their RAS key.

[We updated our RSA SSH host key](https://github.blog/2023-03-23-we-updated-our-rsa-ssh-host-key/)

as the page said, just remove github's known-hosts will work:

```
ssh-keygen -R github.com
```

## change file case

```bash
git mv -f File1 file1
git mv -f file2 File2
git add .
git commit -m msg
```

## git-bash for windows 中文乱码

如果遇到诡异的乱码问题：能正常输出中文，但编译输出有中文时乱码，执行 `make clean && make all > build.log 2>&1 && cat build.log` 又能正常输出中文时，当你尝试了网上各种设置方法没用后：

尝试编辑 `~/.bashrc`, 追加 `chcp.com 65001` ...