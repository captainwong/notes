nginx notes
===========

## tcp tls 转发

**目的**：监听 `tcp 8883`，使用 `let's encrypt` 自动管理证书，加密，并转发给后端 `emqx` 的 `tcp 1883`

参考 [emqx文档](https://docs.emqx.com/zh/emqx/latest/deploy/cluster/lb-nginx.html)，编辑 `/etc/nginx/nginx.conf`:

```conf
stream {
    upstream mqtt_servers {
        server localhost:1883;
    }

	server {
		listen 8883 ssl;
		#server_name mqtts.dev.hbwechatserver.com;
		ssl_session_cache shared:SSL:10m;
		ssl_session_timeout 10m;
		ssl_verify_depth 2;
		proxy_pass mqtt_servers;
		proxy_connect_timeout 10s;
		# 默认心跳时间为 10 分钟
		proxy_timeout 1800s;
		proxy_buffer_size 3M;
		tcp_nodelay on;

		# 配置 SSL 证书
		ssl_certificate /etc/letsencrypt/live/mqtts.dev.hbwechatserver.com/fullchain.pem;
		ssl_certificate_key /etc/letsencrypt/live/mqtts.dev.hbwechatserver.com/privkey.pem;

		ssl_protocols TLSv1.2 TLSv1.3;
		ssl_ciphers HIGH:!aNULL:!MD5;
	}
}
```

其中 `letsencrypt` 证书是先创建了一个虚拟主机获取的，在虚拟主机的基础上无法实现纯 `tcp` 流量的转发.

而 `nginx` 的 `stream` 模块中，`server_name`指令是不支持的，这导致了`certbot` 无法再自动管理证书续期，解决办法是保留虚拟主机，但不做任何事，就用来让 `certbot` 认识：

1. 先创建目录
   
    ```bash
    sudo mkdir -p /var/www/certbot
    sudo chown -R www-data:www-data /var/www/certbot
    ```

2. 配置 `/etc/nginx/sites-available/certbot`

    ```conf
    server {
        listen 80;
        server_name mqtts.dev.hbwechatserver.com;

        location /.well-known/acme-challenge/ {
            root /var/www/certbot;
        }
    }
    ```

3. 启用并重启 nginx

    ```bash
    sudo ln -s /etc/nginx/sites-available/certbot /etc/nginx/sites-enabled/
    sudo nginx -s reload
    ```

4. 验证 certbot 能自动管理该域名证书的续期

    ```bash
    certbot renew --dry-run --cert-name mqtts.dev.hbwechatserver.com
    ```

5. 最终验证

    使用 `emqx` 连接 `mqtts://mqtts.dev.hbwechatserver.com`，可以正常连接、通信.