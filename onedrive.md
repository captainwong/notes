onedrive
========

## How to fix always loading?

https://support.microsoft.com/zh-cn/office/%E9%87%8D%E7%BD%AE-onedrive-34701e00-bf7b-42db-b960-84905399050c

1. run `wsreset.exe`, not working
2. run `%localappdata%\Microsoft\OneDrive\onedrive.exe /reset`, then open `onedrive app` in `start menu`, worked.

## How to delete "Move to OneDrive" from explorer context menu?

1. download this powershell script

    [file-remove-move-to-onedrive-ps1](https://gist.github.com/logchan/3f9762291c2c93193e0d94d2d5cbcae6#file-remove-move-to-onedrive-ps1)

    ```powershell
    #Requires -RunAsAdministrator

    New-PSDrive -Name HKCR_RMTO -PSProvider Registry -Root 'HKEY_CLASSES_ROOT'
    pushd HKCR_RMTO:

    $keys = '*\shellex\ContextMenuHandlers\ FileSyncEx', 'Directory\Background\shellex\ContextMenuHandlers\ FileSyncEx', 'Directory\shellex\ContextMenuHandlers\ FileSyncEx', 'IE.AssocFile.URL\shellex\ContextMenuHandlers\ FileSyncEx', 'lnkfile\shellex\ContextMenuHandlers\ FileSyncEx'
    $rights = 'ChangePermissions', 'CreateSubKey', 'Delete', 'FullControl', 'SetValue', 'TakeOwnership', 'WriteKey'

    foreach ($key in $keys) {
        REG DELETE "HKEY_CLASSES_ROOT\$key" /ve /f
        
        $reg = "\$key"
        $acl = Get-Acl -LiteralPath $reg
        foreach ($right in $rights) {
            $rule = New-Object System.Security.AccessControl.RegistryAccessRule("everyone",$right,"Deny")
            $acl.AddAccessRule($rule)
        }

        $acl | Format-List
        Set-Acl -LiteralPath $reg -AclObject $acl
    }

    popd
    Remove-PSDrive -Name HKCR_RMTO
    ```

2. execution

   Refers to [ps-enabling-exec-scripts](https://github.com/whonion/ps-enabling-exec-scripts), run `powershell.exe -noprofile -executionpolicy bypass -file .\file-remove-move-to-onedrive-ps1`


