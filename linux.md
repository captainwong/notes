linux
=====

## create user and add to sudoers

```bash
# create user with home directory
sudo useradd -m jack
# add user to sudoers
sudo adduser jack sudo
# optional: jack can run `sudo` without password
echo "jack ALL=(ALL:ALL) NOPASSWD: ALL" | sudo tee /etc/sudoers.d/jack
# and don't forget to set a password for him, run `sudo passwd jack`
```

if jack's default shell is sh, run `chsh` to change it.
