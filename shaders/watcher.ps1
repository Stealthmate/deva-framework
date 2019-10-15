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
    $date = get-date -format hh:mm:ss
    write-host "$date Compiling $file..." -Foreground "green"
    $output = glslangValidator.exe -V $file -o ($file -replace("\.(frag|vert)",".spv")) 2>&1

    $formattedOutput = @()
    $output | foreach {
        if($_.trim().length -gt 0) {
            $formattedOutput += $_.trim()
        }
    }

    $formattedOutput | foreach {
        if($_.startswith("Warning")) {
            write-host $_ -Foreground "yellow"
        }
        elseif($_.startswith("ERROR")) {
            write-host $_ -Foreground "red"
        }
        else {
            write-host $_
        }
    }
}

function global:copyShader {
    param(
        [string]$shader
    )
    $date = get-date -format hh:mm:ss
    write-host "$date Copying $shader..."
    $output = remove-item ..\bin\shaders\$shader
    write-host $output
    $output = robocopy.exe . ..\bin\shaders $shader /NFL /NDL /NJH /NJS /nc /ns /np
    $output = $output.trim()
    if($output)
    {
        $output = $output -join("`n")
        write-host $output
    }
    write-host "Done" -Foreground "green"
}

$changed = Register-ObjectEvent $watcher "Changed" -Action {
    if($global:shaderNameMask.Match($eventArgs.Name).Success)
    {
        compileShader $eventArgs.Name
        $shader = $eventArgs.Name -replace("\.(vert|frag)",".spv")
        copyShader $shader
    }
}
$created = Register-ObjectEvent $watcher "Created" -Action {
    if($global:shaderNameMask.Match($eventArgs.Name).Success)
    {
        compileShader $eventArgs.Name
        $shader = $eventArgs.Name -replace("\.(vert|frag)",".spv")
        copyShader $shader
    }
}

function cleanup {
    remove-variable shaderNameMask -scope "Global"
    remove-item function:\compileShader
    remove-item function:\copyShader
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
