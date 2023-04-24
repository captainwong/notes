# setup HomeAssistant on Ubuntu 20.04

0. ladder

    v2rayN append custom PAC

    ```
    ||home-assistant.io,
    ||cartocdn.com
    ```

    cartocnd.com is the map's cdn site.

1. uninstall python3.8.10
   
    ```
    apt purge python3 python3-dev
    ```

2. build python from source

    visit https://www.python.org/downloads/source/ and copy the lastest download link.

    ```
    wget https://www.python.org/ftp/python/3.10.11/Python-3.10.11.tgz
    tar zxvf Python-3.10.11.tgz
    cd Python-3.10.11
    ./configure --enable-optimizations
    make -j $(nproc)
    sudo make install
    rm -f /usr/bin/python3 /usr/local/bin/python3
    ln -s /usr/local/python3.10.11 /usr/bin/python3
    ln -s /usr/local/python3.10.11 /usr/local/bin/python3
    ```

3. install pip and use tsinghua mirror

    https://mirrors.tuna.tsinghua.edu.cn/help/pypi/

    ```
    sudo apt install python3-pip
    rm -f /usr/bin/pip3
    ln -s /usr/local/bin/pip3 /usr/bin/pip3
    python3 -m pip install -i https://pypi.tuna.tsinghua.edu.cn/simple --upgrade pip
    pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
    ```

4. install HomeAssistant

    according to https://www.home-assistant.io/installation/linux, step by step.

    before run `hass`, enable proxy and set proxy

    1. enable proxy

       according to https://community.home-assistant.io/t/support-http-proxy/204661 and https://docs.aiohttp.org/en/stable/client_reference.html, had to change source file to enable http proxy.

       edit `./lib/python3.10/site-packages/homeassistant/helpers/aiohttp_client.py`

       find `aiohttp.ClientSession(`, append a param `trust_env=True` after `**args`

    2. set proxy

        ```
        export http_proxy=http://localhost:10809
        export https_proxy=http://localhost:10809
        git config --global http.proxy http://localhost:10809
        git config --global https.proxy http://localhost:10809
        ```

    then run

    ```
    hass -v
    ```

    should be very fluent.

5. after first install, it seems ok to disable proxy, just use tsinghua's pip mirror.
