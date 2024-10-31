# Step 1: Enable WSL with Virtual Machine Platform features
Write-Output "Enabling WSL and Virtual Machine Platform..."
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

# Step 2: Install USBIPD-WIN for USB device sharing between Windows and WSL
Write-Output "Installing USBIPD-WIN..."
winget install --id usbipd usbipd-win -e --accept-package-agreements --accept-source-agreements

# Step 3: Install Debian from the Microsoft Store using the WSL command
Write-Output "Installing Debian WSL Distro..."
wsl --install -d Debian

# Prompt for restart to apply changes if necessary
$restartPrompt = Read-Host "Would you like to restart now to apply changes? (Y/N)"
if ($restartPrompt -eq "Y" -or $restartPrompt -eq "y") {
    Write-Output "Restarting computer..."
    Restart-Computer -Force
    exit
} else {
    Write-Output "Please remember to restart the computer to apply changes, and to enable BIOS/UEFI CPU Virtualization features."
}

# Confirm installation success
Write-Output "Installation completed. WSL Debian is installed, and USBIPD-WIN should now be set up."
