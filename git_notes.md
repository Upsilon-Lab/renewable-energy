### cloning repo
    git clone url folderDestination


### switching branches
    git checkout branchname                 ; ie git checkout main,
                                            ; git checkout branch1

### git push workflow
    git status                              ; shows all modified files
    
    git add file.txt or git add --all       ; add files you want to commit            
    
    git commit -m "commit name subject"

    git pull upstream    ; checks for differences before pushing
                         ; if there are differences use the merge section to update

    git reset HEAD          ; if you dont want to push commits, reset clears it
    
    git push or git push origin
### checking and changing origin and upstream
    git remote -v

    git remote remove origin            ; remove if want to change
    
    git remote remove upstream          ; remove if want to change
    
    git remote add origin https://github.com/Upsilon-Renewable-Energy/renewable-energy
    
    git remote add upstream https://github.com/Upsilon-Lab/renewable-energy
    
    git fetch upstream                  ; fetch data
    
    git merge upstream/main             ; merge update merge into your fork

## pycharm exempt .idea folder
    Remove the file from the repository
        git rm --cached .idea/
    
    now update your gitignore file to ignore this folder
        echo '.idea' >> .gitignore
    
    add the .gitignore file
        git add .gitignore
    
    git commit -m "Removed .idea files"
    git push origin <branch>

### github CLI pull requests
#### Windows users install CLI with tool, ie. scoop
    # Installs scoop
    iwr -useb get.scoop.sh | iex

    # Installs CLI with scoop
    scoop bucket add github-gh https://github.com/cli/scoop-gh.git
    scoop install gh        ;installs it
#
    gh pr create        # create pull request
    # when choosing base and head
    # base is repo that will be updated ie. upsilon
    # head is your fork

### To assign a pull request to an individual, use the --assignee or -a flags. You can use @me to self-assign the pull request.
    gh pr create --assignee "@octocat"

### To specify the branch into which you want the pull request merged, use the --base or -B flags. To specify the branch that contains commits for your pull request, use the --head or -H flags.
    gh pr create --base my-base-branch --head my-changed-branch

### To include a title and body for the new pull request, use the --title and --body flags.
    gh pr create --title "The bug is fixed" --body "Everything works again"

### To mark a pull request as a draft, use the --draft flag.
    gh pr create --draft

### To add a labels or milestones to the new pull request, use the --label and --milestone flags.
    gh pr create --label "bug,help wanted" --milestone octocat-milestone

### To add the new pull request to a specific project, use the --project flag.
    gh pr create --project octocat-project

### To assign an individual or team as reviewers, use the --reviewer flag.
    gh pr create --reviewer monalisa,hubot  --reviewer myorg/team-name

### To create the pull request in your default web browser, use the --web flag.
    gh pr create --web
