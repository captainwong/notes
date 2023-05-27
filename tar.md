# tar notes

[Linux tar.gz、tar、bz2、zip 等解压缩、压缩命令详解](https://www.runoob.com/w3cnote/linux-tar-gz.html)

## `tar`

### compress

`tar -cf out.tar *.txt`

### append

`tar -rf out.tar *.jpg`

### update

`tar -uf out.tar index.html`

### list

`tar -tf out.tar`

### umcompress

`tar -xf out.tar`


## `tar.gz` or `tgz`

### compress using `gzip`

`tar -czf out.tar.gz *.jpg`

`tar -czf out.tgz *.jpg`

### uncompress using `gunzip`

`tar -xzf out.tar.gz`

`tar -xzf out.tgz`





