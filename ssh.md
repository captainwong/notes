# ssh notes

## Increase SSH connection timeout

`vi /etc/ssh/sshd_config`

find `ClientAliveInterVal` and `ClientAliveCountMax`

- `ClientAliveInterval` specifies the time in seconds that the server will wait before sending a null packet to the client system to kep the connection alive.
- `ClientAliveCountMax` defines the number of client alive messages which are sent without getting any messages from the client. If this limit is reached while the messages are being sent, the `sshd` daemon will drop the connection, effectively terminating the ssh session.

The timeout value is given by the product of the above parameters i.e.:

`Timeout value = ClientAliveInterval * ClientAliveCountMax`

For example, if set

```config
ClientAliveInterval 1200
ClientAliveCountMax 3
```

The `timeout` value will be `3600` seconds. After changed the config file, `systemctl reload sshd` to take effect.

[How to Increase SSH Connection Timeout in Linux](https://www.tecmint.com/increase-ssh-connection-timeout/)

## generate local public key

- `ssh-keygen -t ed25519 -C "your_email@example.com"`
- `ssh-keygen -t rsa -b 4096 -C "your_email@example.com"`

[Generating a new SSH key and adding it to the ssh-agent](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)

## add ssh public key to server

`ssh-copy-id -i ~/.ssh/id_ed25519.pub USER@SERVER`

or

`ssh-copy-id -i ~/.ssh/id_rsa.pub USER@SERVER`

[How to Add SSH Public Key to Server](https://linuxhandbook.com/add-ssh-public-key-to-server/)