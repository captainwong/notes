# setup HomeAssistant on Ubuntu 20.04

1. uninstall python3.8.10
   
    ```
    apt purge python3 python3-dev
    ``

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

3. install pip and use tsinghua image

    ```
    sudo apt install python3-pip
    rm -f /usr/bin/pip3
    ln -s /usr/local/bin/pip3 /usr/bin/pip3
    python3 -m pip install -i https://pypi.tuna.tsinghua.edu.cn/simple --upgrade pip
    pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
    ```

4. install HomeAssistant

    according to https://www.home-assistant.io/installation/linux, step by step.

    before run `hass`, set proxy

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
