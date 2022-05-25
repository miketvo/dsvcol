#
# Syntax: build.ps1 -d [ROOT_DIRECTORY] -m [ debug | release ] [-c] [-h]
# Options:
#   -d Specify the project's root directory. Use './' if you're already in the project's root.
#   -m Specify build mode. Accepted values are 'debug' and 'release'
#   -c (Optional) Clean built files.  Use in conjunction with '-m'
#   -h (Optional) Display help and exit.
#

param(
    [Parameter(Mandatory = $true)][string]$d,
    [Parameter(Mandatory = $true)][string]$m,
    [switch]$c,
    [switch]$h
)

if ($h.IsPresent) {
    Write-Output "Syntax: build.sh -d [ROOT_DIRECTORY] -m [ debug | release ]"
    Write-Output "Options:"
    Write-Output "  -d Specify the project's root directory. Use './' if you're already in the project's root."
    Write-Output "  -m Specify build mode. Accepted values are 'debug' and 'release'"
    Write-Output "  -c (Optional) Clean built files. Use in conjunction with '-m'"
    Write-Output "  -h (Optional) Display this help and exit."
    exit 0
}

if (Test-Path -Path $d) {
    switch ($m)
    {
        "debug" {
            if ($c.IsPresent) {
                Write-Output "[ Clean | Debug ]"
                Write-Output "cmake --build ./cmake-build-debug --target clean -j 9"
                cmake --build ./cmake-build-debug --target dsvcol -j 9
                Write-Output "[ Clean finished ]"
            } else {
                Write-Output "[ Build | Debug ]"
                Write-Output "cmake --build ./cmake-build-debug --target dsvcol -j 9"
                cmake --build ./cmake-build-debug --target dsvcol -j 9
                Write-Output "[ Build finished ]"
            }
        }
        "release" {
            if ($c.IsPresent) {
                Write-Output "[ Clean | Release ]"
                Write-Output "cmake --build ./cmake-build-release --target clean -j 9"
                cmake --build ./cmake-build-release --target dsvcol -j 9
                Write-Output "[ Clean finished ]"
            } else {
                Write-Output "[ Build | Release ]"
                Write-Output "cmake --build ./cmake-build-release --target dsvcol -j 9"
                cmake --build ./cmake-build-release --target dsvcol -j 9
                Write-Output "[ Build finished ]"
            }
        }
        Default {
            Write-Error "Invalid build mode '$m'"
            exit 1
        }
    }
} else {
    Write-Error "Error: '$d' is not a valid directory."
    exit 1
}
