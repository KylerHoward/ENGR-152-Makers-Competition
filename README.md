# ENGR-152-Makers-Competition
All commands in "" should be run in powershell

# Commands to run 
run powershell with admin
"Set-ExecutionPolicy AllSigned"
"Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"
"choco install git"
Close Powershell window


open new powershell window
"git clone https://github.com/KylerHoward/ENGR-152-Makers-Competition.git"


# To do work
"git pull" to pull in latest code
"ls" to see what is in the current branch/master
"git checkout -b "name of branch (yourName/branchName)""
edit the files like normal
"git status" to see what changes have been made
"git add "file name""
"git commit -m "description of edits" if you're good with the edits
"git push" when done and want others to see

Go to git hub repository website to make pull request
make a pull request, approve it, merge/squash to master, and delete the branch

"git checkout master" to move to master
"git pull" to start again and pull in latest code