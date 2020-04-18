# ENGR-152-Makers-Competition
All commands should be run in powershell

# Commands to run 
Run powershell with admin

    Set-ExecutionPolicy AllSigned"

    Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
    
    choco install git
    
Close Powershell window

Open new powershell window

    git clone https://github.com/KylerHoward/ENGR-152-Makers-Competition.git


# To do work
Open up powershell and direct it to the repository that you are working on. If you have spaces in the file names, you need "" around the address. If there are no spaces, "" are not needed

    cd "file address" 
    (ex: cd .\OneDrive\Documents\Arduino)

To pull in latest code

    git pull 

To see what files are in the current branch

    ls

To make a new branch to work in

    git checkout -b "name of branch (yourName/branchName)"
    
Edit the files like you normaly would

To see what changes have been made

    git status
    
To add your files so they will be updated

    git add "file name"
    
To save your changes

    git commit -m "description of edits"
    
To send changes to git hub server. This might pull up a line of command that you need to copy and paste

    git push

Go to main git hub repository website to make pull request

make a pull request, approve it, squash and merge to master, and delete the branch

To go back to master to start again

    git checkout master

Start from top again
