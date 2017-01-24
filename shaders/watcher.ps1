$watcher = New-Object System.IO.FileSystemWatcher
$watcher.Path = $PSScriptRoot
$watcher.IncludeSubdirectories = $true
$watcher.EnableRaisingEvents = $true

$global:shaderNameMask = [regex]"[^.]+\.(vert|frag)"

write-host "Watching $PSScriptRoot"

function global:compileShader {
    [cmdletbinding()]
    param(
        [string]$file
    )
    $output = glslangValidator.exe -V $file 2>&1
    $output = $output -join("`n")
    $output = "`n$output"
    write-host $output
}

function global:copyShaders {
    write-host "copying "
    $output = robocopy.exe .\ ..\bin\shaders *.spv 2>&1 /NFL /NDL /NJH /NJS /nc /ns /np
    if($output.trim())
    {
        $output = $output -join("`n")
        write-host $output
    }
}

$changed = Register-ObjectEvent $watcher "Changed" -Action {
    if($global:shaderNameMask.Match($eventArgs.Name).Success)
    {
        compileShader $eventArgs.Name
        copyShaders
    }
}
$created = Register-ObjectEvent $watcher "Created" -Action {
    if($global:shaderNameMask.Match($eventArgs.Name).Success)
    {
        compileShader $eventArgs.Name
        copyShaders
    }
}

function cleanup {
    remove-variable shaderNameMask -scope "Global"
    remove-item function:\compileShader
    remove-item function:\copyShaders
}

[console]::TreatControlCAsInput = $true
while($True)
{
    if($Host.UI.RawUI.KeyAvailable -and (3 -eq
    [int]$Host.UI.RawUI.ReadKey("AllowCtrlC,IncludeKeyUp,NoEcho").Character))
    {
        Unregister-Event $changed.Id
        Unregister-Event $created.Id
        cleanup
        write-host "Stopping..."
        exit
    }
}
