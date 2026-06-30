wsl
===

## install

```powershell
wsl --install
```

## error 

maybe the registry was messed up by `ContextMenuManager.NET.4.0.exe`, due to:

https://github.com/microsoft/WSL/issues/11697 and https://stackoverflow.com/questions/78029799/wsl-cannot-upgrade-to-wsl2-as-class-not-registered-error-arises

rename or delete some registries, download `wsl-installer.msi` from `https://github.com/microsoft/WSL/releases`, manully install will fix.
