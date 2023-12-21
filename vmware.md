# vmware notes

## growpart

- in vmware, expand disk space
- in ubuntu, `growpart /dev/sda 5`, ok
- `resize2fs /dev/sda5` failed, nothing to do
- found [this link](https://unix.stackexchange.com/a/687489)
- I have a `extended` partition `/dev/sda2`
- grow it too: `growpart /dev/sda 2 && growpart /dev/sda 5`
- then `resize2fs /dev/sda5` will work.

